#include "TTi_dcload.h"
#include "../stlib/st_error.cpp"

#include <string>
#include <iostream>
#include <typeinfo>
#include <Riostream.h>


ClassImp(TTi_dcload)

TTi_dcload::TTi_dcload(char* resName)
{
  initSupply(resName);
}

void TTi_dcload::initSupply(char* resName)
{
  strcpy(m_resource, resName);
  deviceType = -1;
  debug = false;
  isValid = false;

  // Open session to VISA resource manager
  status = viOpenDefaultRM (&defaultRM);
  if (status < VI_SUCCESS){
    std::cout << "TTi_dcload::TTi_dcload Could not open a session to the VISA Resource Manager :-(" << std::endl;
    return; // exit (EXIT_FAILURE);
  }

  // Open specified resource
  // For a serial link, parameter accessMode can have two values
  // - 0 means use VISA defaults (9600 baud etc)
  // - 4 means load saved config (defined within MAX)
  // As older TTI supplied with integrated FTDI USB/serial converters only run at 19200 baud, 
  // we must use option 4 when a serial link is specified.

  if(strncmp(m_resource,"ASRL",4)==0){
    status = viOpen (defaultRM, m_resource, 4, VI_NULL, &instPSU);
  }else{
    status = viOpen (defaultRM, m_resource, VI_NULL, VI_NULL, &instPSU);
  }
  if (true == CheckError("TTi_dcload::TTi_dcload (viOpen)", status)){
    // Ignore failure so we can try a different one
    return;
    // exit (EXIT_FAILURE);
  }

  // Query device identity
  sprintf(stringinput,"*IDN?;\x0A");
  BytesToWrite = strlen(stringinput);
  status = viWrite (instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  if (true == CheckError("TTi_dcload::TTi_dcload (*IDN? viWrite)", status)) {
    exit(EXIT_FAILURE);
  }
  status = viRead(instPSU, data, 1024, &rcount);
  data[rcount]=0;
  if (1) std::cout<<"The device identity is:	"<<data<<std::endl;
  if (true == CheckError("TTi_dcload::TTi_dcload (*IDN? viRead)", status)) {
    exit(EXIT_FAILURE);
  }

  //std::cout<<checkMode()<<std::endl;
  //setMode("C");
  //setRange("1");
  //checkRange();
  //checkLevelState();
  //setLevelState("B");
  //setLevelValue("A", "0.01");
  //checkLevelValue("A");
  //setDropout("0.01");
  //checkDropout();
  //setVoltLimit("0.01");
  //checkVoltLimit();
  //turnoffVoltLimit();
  //checkVoltLimit();
  //setInputState("1");
  //checkInputState();
  //setCurrentLimit("0.01");
  //checkCurrentLimit();
  //turnoffCurrentLimit();
  //checkCurrentLimit();
  //outputCurrent();
  //outputVolt();

  isValid = true;

  return;
}

void TTi_dcload::Log(FILE* outfile){

  if(outfile==NULL){
    std::cout << "TTi_dcload::Log called with null file" << std::endl;
    return;
  }else{
    fprintf(outfile, "#CURRENT\tVOLTAGE\n%s\t%s\n", outputCurrent(), outputVolt());
  }

  return;
}

std::string TTi_dcload::readResponse(std::string sendData) {
  ViUInt32 read_count;
  int write_count = sendData.size();
  int status = viWrite(instPSU, (ViBuf)sendData.c_str(), write_count, &read_count);
  if (CheckError("TTi_dcload::readResponse (sending)", status)) {
//   if(status != VI_SUCCESS) {
    cout << "Error Writing " << sendData << "\n";
    exit(1);
  }

  const int DATA_SIZE=1024;
  char data[DATA_SIZE];  
  status = viRead(instPSU, (ViBuf)data, DATA_SIZE, &read_count);
  if (CheckError("TTi_dcload::readResponse (receiving)", status)) {
//   if(status != VI_SUCCESS) {
    cout << "Error reading response from " << sendData << "\n";
    exit(1);
  }

  data[read_count]=0;

  std::cout << "Response to '" << sendData << "' is '" << data << std::endl;

  return data;
}

char* TTi_dcload::checkMode(){
  sprintf(stringinput, "MODE?;\x0A"); 
  BytesToWrite = strlen(stringinput);
  std::string response = readResponse(stringinput);
//   status = viRead(instPSU, data, 1024, &rcount);
//  data[rcount]=0;
  strncpy((char*)data, response.c_str(), 1024);
  char* token = strtok((char*)data," ");
  token = strtok(NULL," ");
  std::cout << "MODE:	" << token << std::endl;
  return  token;
}


bool TTi_dcload::setMode(char* mode){
  sprintf(stringinput, "MODE "); 
  sprintf(stringinput+strlen(stringinput), mode); 
  sprintf(stringinput+strlen(stringinput), ";\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  std::cout<<"Setting to constant "<<mode<<" mode!"<<std::endl;
  return true;
}


bool TTi_dcload::checkRange(){
//unsigned char* TTi_dcload::checkRange(){
  sprintf(stringinput, "RANGE?;\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  status = viRead(instPSU, data, 1024, &rcount);
  data[rcount]=0;
  char* token;
  token = strtok((char*)data," ");
  token = strtok(NULL," ");
  std::cout << "RANGE:	" << token << std::endl;
  return  true;
  //return  data;
}
 

bool TTi_dcload::setRange(char* range){
  sprintf(stringinput, "RANGE "); 
  sprintf(stringinput+strlen(stringinput), range); 
  sprintf(stringinput+strlen(stringinput), ";\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  return  true;
}

bool TTi_dcload::checkLevelState(){
  sprintf(stringinput, "LVLSEL?;\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  status = viRead(instPSU, data, 1024, &rcount);
  data[rcount]=0;
  char* token;
  token = strtok((char*)data," ");
  token = strtok(NULL," ");
  std::cout << "LVLSEL:	" << token << std::endl;
  return  true;
}

bool TTi_dcload::setLevelState(char* level){
  sprintf(stringinput, "LVLSEL "); 
  sprintf(stringinput+strlen(stringinput), level); 
  sprintf(stringinput+strlen(stringinput), ";\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  return  true;
}

//unsigned  char* TTi_dcload::checkLevelValue(char* level){
bool TTi_dcload::checkLevelValue(char* level){
  sprintf(stringinput+strlen(stringinput), level); 
  sprintf(stringinput+strlen(stringinput), "?\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  status = viRead(instPSU, data, 1024, &rcount);
  data[rcount]=0;
  std::cout << "The value of level " << data << std::endl;
  //return  data;
  return  true;
}

bool TTi_dcload::setLevelValue(char* level, char* m_level){
  sprintf(stringinput+strlen(stringinput), level); 
  sprintf(stringinput+strlen(stringinput), " "); 
  sprintf(stringinput+strlen(stringinput), m_level); 
  sprintf(stringinput+strlen(stringinput), ";\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  return  true;
}

//unsigned char* TTi_dcload::checkDropout(){
bool TTi_dcload::checkDropout(){
  sprintf(stringinput, "DROP?;\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  status = viRead(instPSU, data, 1024, &rcount);
  data[rcount]=0;
  std::cout <<"The dropout voltage is "<< data << std::endl;
  //return  data;
  return true;
}

bool TTi_dcload::setDropout(char* m_dropout){
  sprintf(stringinput, "DROP "); 
  sprintf(stringinput+strlen(stringinput), m_dropout); 
  sprintf(stringinput+strlen(stringinput), ";\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  return  true;
}

//unsigned char* TTi_dcload::checkVoltLimit(){
bool TTi_dcload::checkVoltLimit(){
  sprintf(stringinput, "VLIM?;\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  status = viRead(instPSU, data, 1024, &rcount);
  data[rcount]=0;
  std::cout << data << std::endl;
  //return  data;
  return  true;
}

bool TTi_dcload::setVoltLimit(char* voltlimit){
  sprintf(stringinput, "VLIM "); 
  sprintf(stringinput+strlen(stringinput), voltlimit); 
  sprintf(stringinput+strlen(stringinput), ";\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  return  true;
}

bool TTi_dcload::turnoffVoltLimit(){
  sprintf(stringinput, "VLIM "); 
  sprintf(stringinput+strlen(stringinput), "NONE"); 
  sprintf(stringinput+strlen(stringinput), ";\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  return  true;
}

//unsigned char* TTi_dcload::checkCurrentLimit(){
bool TTi_dcload::checkCurrentLimit(){
  sprintf(stringinput, "ILIM?;\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  status = viRead(instPSU, data, 1024, &rcount);
  data[rcount]=0;
  std::cout << data << std::endl;
  //return  data;
  return  true;
}

bool TTi_dcload::setCurrentLimit(char* currentlimit){
  sprintf(stringinput, "ILIM "); 
  sprintf(stringinput+strlen(stringinput), currentlimit); 
  sprintf(stringinput+strlen(stringinput), ";\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  return  true;
}

bool TTi_dcload::turnoffCurrentLimit(){
  sprintf(stringinput, "ILIM "); 
  sprintf(stringinput+strlen(stringinput), "NONE"); 
  sprintf(stringinput+strlen(stringinput), ";\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  return  true;
}

//unsigned char* TTi_dcload::checkInputState(){
bool TTi_dcload::checkInputState(){
  sprintf(stringinput, "INP?;\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  status = viRead(instPSU, data, 1024, &rcount);
  data[rcount]=0;
  std::cout << data << std::endl;
  //return  data;
  return  true;
}

bool TTi_dcload::setInputState(char* inputstate){
  sprintf(stringinput, "INP "); 
  sprintf(stringinput+strlen(stringinput), inputstate); 
  sprintf(stringinput+strlen(stringinput), ";\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  return  true;
}

//unsigned char* TTi_dcload::outputVolt(){
bool TTi_dcload::outputVolt(){
  sprintf(stringinput, "V?;\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  status = viRead(instPSU, data, 1024, &rcount);
  data[rcount]=0;
  std::cout <<"The measured source input voltage is "<< data << std::endl;
  //return  data;
  return  data;
}

//unsigned char* TTi_dcload::outputCurrent(){
bool TTi_dcload::outputCurrent(){
  sprintf(stringinput, "I?;\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  status = viRead(instPSU, data, 1024, &rcount);
  data[rcount]=0;
  std::cout <<"The measured load current is "<< data << std::endl;
  //return  data;
  return  true;
}

bool TTi_dcload::checkSlewRate(){
  sprintf(stringinput, "SLEW?;\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  status = viRead(instPSU, data, 1024, &rcount);
  data[rcount]=0;
  std::cout << data << std::endl;
  return true;
}

bool TTi_dcload::setSlewRate(char* slewrate){
  sprintf(stringinput, "SLEW "); 
  sprintf(stringinput+strlen(stringinput), slewrate); 
  sprintf(stringinput+strlen(stringinput), ";\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  return  true;
}


bool TTi_dcload::checkDuty(){
  sprintf(stringinput, "DUTY?;\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  status = viRead(instPSU, data, 1024, &rcount);
  data[rcount]=0;
  std::cout << data << std::endl;
  return true;
}

bool TTi_dcload::setDuty(char* duty){
  sprintf(stringinput, "DUTY "); 
  sprintf(stringinput+strlen(stringinput), duty); 
  sprintf(stringinput+strlen(stringinput), ";\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  return  true;
}

bool TTi_dcload::checkSlowStart(){
  sprintf(stringinput, "SLOW?;\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  status = viRead(instPSU, data, 1024, &rcount);
  data[rcount]=0;
  std::cout << data << std::endl;
  return true;
}

bool TTi_dcload::setSlowStart(char* slowstart){
  sprintf(stringinput, "SLOW "); 
  sprintf(stringinput+strlen(stringinput), slowstart); 
  sprintf(stringinput+strlen(stringinput), ";\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  return  true;
}

bool TTi_dcload::checkFrequency(){
  sprintf(stringinput, "FREQ?;\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  status = viRead(instPSU, data, 1024, &rcount);
  data[rcount]=0;
  std::cout << data << std::endl;
  return true;
}

bool TTi_dcload::setFrequency(char* frequency){
  sprintf(stringinput, "FREQ "); 
  sprintf(stringinput+strlen(stringinput), frequency); 
  sprintf(stringinput+strlen(stringinput), ";\x0A"); 
  BytesToWrite = strlen(stringinput);
  status = viWrite(instPSU, (ViBuf)stringinput,BytesToWrite, &rcount);
  return  true;
}

bool TTi_dcload::Mon(){
  return true;
}

bool TTi_dcload::Mon(unsigned char* Ustatus, float* V, float* I){
  return true;
}

bool TTi_dcload::Off(){
  return true;
}

bool TTi_dcload::On(){
  return true;
}

bool TTi_dcload::PrintStatus(){
  return true;
}

bool TTi_dcload::ReadLabel(char* label){
  return true;
}

bool TTi_dcload::ReadLimits(float* V, float* I){
  return true;
}

bool TTi_dcload::ReadSettings(){
  return true;
}

bool TTi_dcload::ReadSettings(float* V, float* I){
  return true;
}

bool TTi_dcload::Set(float v, float i){
  return true;
}

TTi_dcload::~TTi_dcload(){
  // Destructor
  viClose(instPSU);
  viClose(defaultRM);
}

Bool_t TTi_dcload::CheckError(char* source, ViStatus status) {
  // Present VISA error codes in human readable, HIGHLIGHTED form ;-)
  // - return TRUE if error detected, else FALSE
  if (status < VI_SUCCESS) {
    char mesg[1024];
    char desc[512];  //The size of the desc parameter should be at _least_ 256 bytes.
    viStatusDesc(instPSU, status, desc);

    sprintf(mesg, "%s for at resource %s failed with code 0x%x (%s)\n", source, m_resource, status, desc);
    st_error(mesg);
    return true;
  }
  return false;
}
