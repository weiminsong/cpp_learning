#include "HistogramFit.h"
#include <iostream>
#include "TMath.h"
#include <unistd.h>
#include "lmcurve_tyd.h"
#include "Statistics.h"

double scurveFct2(double x, const double *par){
	double xx, y;

	if(par[2] == 0){
		xx = 0;
	}else{
		xx = ( (par[1]-x) / par[2]) / 1.414213562;
	}

	y  = (par[0]/2) * ( 1 + TMath::Erf(xx) );

	return y;
}

HistogramFit::HistogramFit(unsigned arg_hitDiscCfg) : DataProcessor(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

HistogramFit::~HistogramFit() {

}

void HistogramFit::init() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	scanDone = false;
}

void HistogramFit::run() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	const unsigned int numThreads = std::thread::hardware_concurrency();
	for (unsigned i=0; i<numThreads; i++) {
		thread_ptrs.emplace_back( new std::thread(&HistogramFit::process, this) );
		std::cout << "  -> Processor thread #" << i << " started!" << std::endl;
	}
}

void HistogramFit::join() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	for( auto& thread : thread_ptrs ) {
		if( thread->joinable() ) thread->join();
	}
}


void HistogramFit::process() {
	while(true) {
		std::unique_lock<std::mutex> lk(mtx);
		input->cv.wait( lk, [&] {return scanDone || !input->empty(); } );
		process_core();
		output->cv.notify_all(); // notification to the downstream
		if( scanDone ) {
			process_core();
			output->cv.notify_all(); // notification to the downstream
			break;
		}

	}
	process_core();
	output->cv.notify_all(); // notification to the downstream
}

void HistogramFit::process_core(){

	while(!input->empty()){
		//std::vector<std::vector<double>> *inData = input->popData();
		datain *inData = input->popData();
		//std::vector<std::array<double, ST_MAX_SCANPOINTS>> *inData = input->popData();
		//std::vector<double> x_fit =inData->at(0);
		//std::vector<double> xe_fit=inData->at(1);
		//std::vector<double> y_fit =inData->at(2);
		//std::vector<double> x_fit =inData->at(0);
		//auto xe_fit=inData->at(1);
		//auto y_fit =inData->at(2);
		//auto ye_fit=inData->at(3);
		//auto ye_fit=inData->at(3);
		//std::vector<double> x_fit =(*inData)[0];
		//std::vector<double> xe_fit=(*inData)[1];
		//std::vector<double> y_fit =(*inData)[2];
		//std::vector<double> ye_fit=(*inData)[3];
		std::vector<double> x_fit =(*inData).X;
		std::vector<double> xe_fit=(*inData).XE;
		std::vector<double> y_fit =(*inData).Y;
		std::vector<double> ye_fit=(*inData).YE;
		std::vector<double> par_fit=(*inData).PAR;
		for (std::vector<double>::const_iterator i = x_fit.begin(); i != x_fit.end(); ++i)
			std::cout <<"X	"<<*i << ' ';
		for (std::vector<double>::const_iterator i = y_fit.begin(); i != y_fit.end(); ++i)
			std::cout <<"Y	" <<*i << ' ';
		lm_status_struct status;
		lm_control_struct control = lm_control_double;
		//	control.msgfile = NULL;
		//auto *fit_stuff=new Statistics;
		Statistics anything (0.0, NULL);
		double par[3] = {par_fit[0],par_fit[1],par_fit[2]};
		//lmcurve_tyd(3, par, (ST_MAX_SCANPOINTS+1), x, y, ye, scurveFct2, &control, &status);
		int number_points=x_fit.size();
		//lmcurve_tyd(3, par, ST_MAX_SCANPOINTS, &x_fit[0], &y_fit[0], &ye_fit[0], scurveFct2, &control, &status);
		lmcurve_tyd(3, par, number_points, &x_fit[0], &y_fit[0], &ye_fit[0], scurveFct2, &control, &status);
		//fit_stuff->fit_function(2.0, par);
		//lmcurve_tyd(3, par, number_points, &x_fit[0], &y_fit[0], &ye_fit[0], fit_stuff->fit_function, &control, &status);

		printf( "status after %d function evaluations:\n  %s\n", status.nfev, lm_infmsg[status.outcome] );
		printf("obtained norm:\n  %12g\n", status.fnorm );

		std::cout<<"par[0]	"<<par[0]<<std::endl;
		std::cout<<"par[1]	"<<par[1]<<std::endl;
		std::cout<<"par[2]	"<<par[2]<<std::endl;
		//auto *fit_result=new std::vector<double>;
		//fit_result->push_back(par[0]);
		//fit_result->push_back(par[1]);
		//fit_result->push_back(par[2]);
		auto *fit_result=new dataout;
		(*fit_result).fitresult.push_back(par[0]);
		(*fit_result).fitresult.push_back(par[1]);
		(*fit_result).fitresult.push_back(par[2]);
		(*fit_result).stream=(*inData).stream;
		(*fit_result).index=(*inData).index;
		output->pushData(fit_result);
	}

}
