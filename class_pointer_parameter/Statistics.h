#ifndef STATISTICS_H
#define STATISTICS_H


// #################################
// # Author: Weimin Song
// # Email: wesong at cern.ch
// # Project: Yarr
// # Description: statistics for histogram fitting 
// ################################

class Statistics{
	public:
	Statistics();
	Statistics(double x, double *par);
	~Statistics();
	//double fit_function(double , const double *);
	private:
};


#endif
