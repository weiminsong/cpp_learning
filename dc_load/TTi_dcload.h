#ifndef TTi_dcload_h
#define TTi_dcload_h

//
//  TTi_dcload.h
//

#include "TSystem.h"
#include "TObject.h"
#include "../stlib/st_error.h"

#if !defined __CINT__
#include "visa.h"
#endif



#include "../dcsdll/TDCSDevice.h"


class TTi_dcload : public TObject, public TDCSDevice {
 public:
  
  TTi_dcload(char* resName);
  ~TTi_dcload();

  void initSupply(char* resName); //Initialization the device

  bool setMode(char* mode); // Set the mode, C, P, R, G, or V for constant current, constant power, constant resistance, 
                            // constant conductance, and constant voltage separately
  char* checkMode(); // Check the mode     

  bool setRange(char* range);// Set the level range, 0=High Range, 1=Low Range (finer resolution);
  bool checkRange();// Check the range
  //unsigned char* checkRange();// Check the range

  bool setLevelState(char* level);// Select the level, and A, B, T or E conresponding to Level A, Level B, Transient, Ext Voltage, 
                                  // Ext TTL
  bool checkLevelState();// Check which level is used
 
  bool setLevelValue(char* level, char* m_level);// Set the level, and units are implied by the mode, for example CC, the unit is A 
  //unsigned char* checkLevelValue(char* level);// Check the setted value of current level
  bool checkLevelValue(char* level);// Check the setted value of current level

  bool setDropout(char* m_dropout);// Set the dropout voltage in the unit of V
  //unsigned char* checkDropout();// Check the dropout voltage
  bool checkDropout();// Check the dropout voltage

  bool setVoltLimit(char* voltlimit);//Set the voltage limit
  bool turnoffVoltLimit();//Disable the voltage limit by taking NONE as parameter
  //unsigned char* checkVoltLimit();// Check the voltage
  bool checkVoltLimit();// Check the voltage

  bool setCurrentLimit(char* currentlimit);//Same as voltage
  bool turnoffCurrentLimit();
  //unsigned char* checkCurrentLimit();
  bool checkCurrentLimit();
 
  //unsigned char* checkInputState();//Check whether the input is enabled or not
  bool checkInputState();//Check whether the input is enabled or not
  bool setInputState(char* inputstate);//Set the input on or off: 0=off, 1=on

  //unsigned char* outputVolt();// Return the measured source input voltage
  bool outputVolt();// Return the measured source input voltage
  //unsigned char* outputCurrent();// Return the measured load current
  bool outputCurrent();// Return the measured load current

  bool checkSlewRate();//Check the slew rate
  bool setSlewRate(char* slewrate);//Set the slew rate

  bool checkDuty();//Check the percentage of A level in the transient mode
  bool setDuty(char* duty);//Set the duty

  bool checkFrequency();//Check the frequency in Hz
  bool setFrequency(char* frequency);//Set the frequency

  bool checkSlowStart();//Check whether the slow start is actived
  bool setSlowStart(char* slowstart);//Set the slow start

  void Log(FILE* outfile);  
  bool Mon();
  bool Mon(unsigned char* status, float* V, float* I);
  bool Off();
  bool On();
  bool PrintStatus();
  bool ReadLabel(char* label);
  bool ReadLimits(float* V, float* I);
  bool ReadSettings();
  bool ReadSettings(float* V, float* I);
  bool Set(float v, float i);
  
 private:
  bool CheckError(char* source, ViStatus status);
  std::string readResponse(std::string sendString);

  unsigned char data[1024];
  char stringinput[128];
  char m_resource[256];
  int deviceType;
  bool debug;


 #if !defined __CINT__

  // NI-VISA Specific Types must be hidden from CINT
  ViJobId job;
  ViStatus status;
  ViSession instPSU;
  ViUInt32 BytesToWrite;
  ViSession defaultRM;
  ViUInt32 rcount;
  
#endif

  ClassDef(TTi_dcload,1)

};

#endif
