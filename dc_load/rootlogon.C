{
  // c:\sctdaq\rootlogon.c
  // version 0.1 GFM Nov98
  // version 0.2 PWP 16.08.2000
  // version 0.3 PWP 20.12.2001
  // version 0.4 BJG/PWP 29.05.2002 
  // With recent versions of ROOT, this file MUST
  // be executed at startup, so ROOT MUST be started
  // in the sctdaq directory

  printf("\nFor ROOT demos, type \".x demos.C\"\n"); 
  printf("\nFor ROOT demo help,  \".x demoshelp.C\"\n");
  printf("\n");
  printf("  **********************************\n");
  printf("  *                                *\n");
  printf("  *      SCTDAQ Root Session       *\n");
  printf("  *                                *\n");
  printf("  **********************************\n");
  printf("\n");
  printf("If SCTDAQ does not start automatically, type\n");
  printf("\".X ST.cpp\" to start the application.\n");
  printf("\".X Stavelet.cpp\" to start the application using the new GUI.\n\n");
  printf("The VXI Resource Manager will be run automatically.\n");
  printf("\n");

  printf("Attempting to load header file parameters.h\n");
  #include "macros/parameters.h"
  printf("...done\n");

  int loadResult = -1;
  // GetName == "Unix" for Apple too, so this comes first!
  if(strncmp(gSystem->GetBuildArch(),"macosx64",8)==0){
    printf("Running under MacOS\n");
    printf("Attempting to load stdll..");
    loadResult = gSystem->Load("libstdll.dylib");
  } else if(strncmp(gSystem->GetName(),"Unix",4)==0){
    printf("Running under Linux\n");
    printf("Attempting to load stdll.so..");
    loadResult = gSystem->Load("libstdll.so");
  }else{
    printf("Running under Windows\n");
    printf("Attempting to load stdll.dll..");
    loadResult = gSystem->Load("stdll.dll");
  }
  
  if(loadResult == -1) {
    printf("\n  Failed (is it installed in the bin dir, or maybe SCTDAQ_ROOT needs setting?)\n");
    gSystem->Exit(1);
  }
  printf(".done\n");

  TST* e =0;


  // DC loads
  Int_t dctype = 1;
  //   Int_t nLVSupplies = 0;

  switch(dctype) {
  case 1: // 
    printf("Attempting to load tti_dcload.dll");
    gSystem->Load("libtti_dcload_dll.so");
    printf("...done\n");

    TTi_dcload* DCSupplies[1];
    DCSupplies[0] = new TTi_dcload("ASRL6");
    if(DCSupplies[0]->isValid)
      printf("DC load is found with ASRL6!\n");   // Sometimes, the name of ASRL is 5 and sometimes it is 6. 
    else {
      DCSupplies[0] = new TTi_dcload("ASRL5");    // Try to solve this by a better way later.
      if(DCSupplies[0]->isValid)
        printf("DC load is found with ASRL5!\n"); // For now, do it by if...else....
      else
        DCSupplies[0] = 0;
    }
    break;
  }

  // Edit the following section to match your  LV power setup
  Int_t lvtype = 0;
  Int_t nLVSupplies = 0;

  switch(lvtype) {
  case 1: // FTDI driver for Custom Current Source
    printf("Attempting to load csdll.dll");
    gSystem->Load("csdll.dll");
    printf("...done\n");

    TCS* LVSupplies[1];
    LVSupplies[0] = new TCS();
    if(LVSupplies[nLVSupplies]->isValid) nLVSupplies++;
    else LVSupplies[nLVSupplies] = 0;
    break;

  case 2: // NI-VISA driver for TTi TSX3510P or TSX1820P
    if(strncmp(gSystem->GetName(),"Unix",4)==0){
      printf("Attempting to load libttidll.so");
      gSystem->Load("libttidll.so");    // Linux
    }
    else {
      printf("Attempting to load ttidll.dll");
      gSystem->Load("ttidll.dll");   // Windows
    }
    printf("...done\n");

    TTi* LVSupplies[8];
    
    LVSupplies[nLVSupplies] = new TTi("ASRL6::INSTR",1, "Modules 0-3");
    if(LVSupplies[nLVSupplies]->isValid) nLVSupplies++;
    else LVSupplies[nLVSupplies] = 0;
    LVSupplies[1] = new TTi("ASRL8::INSTR",2, "Modules 4-7");
    if(LVSupplies[nLVSupplies]->isValid) nLVSupplies++;
    else LVSupplies[nLVSupplies] = 0;
    LVSupplies[2] = new TTi("ASRL9::INSTR",1, "Modules 8-11");
    if(LVSupplies[nLVSupplies]->isValid) nLVSupplies++;
    else LVSupplies[nLVSupplies] = 0;
    LVSupplies[3] = new TTi("ASRL9::INSTR",2, "Modules 12-15");
    if(LVSupplies[nLVSupplies]->isValid) nLVSupplies++;
    else LVSupplies[nLVSupplies] = 0;
    LVSupplies[4] = new TTi("GPIB0::10::INSTR",1, "HSIO");
    if(LVSupplies[nLVSupplies]->isValid) nLVSupplies++;
    else LVSupplies[nLVSupplies] = 0;
    break;

  case 3:
    if(strncmp(gSystem->GetName(),"Unix",4)==0){
      printf("Attempting to load libttidll.so");
      gSystem->Load("libttidll.so");    // Linux
    }
    else {
      printf("Attempting to load ttidll.dll");  
      gSystem->Load("ttidll.dll");   // Windows
    }
    printf("...done\n");
	
	TTi* LVSupplies[8];
	
	LVSupplies[nLVSupplies] = new TTi("ASRL13::INSTR",1, "Analogue");
    if(LVSupplies[nLVSupplies]->isValid) nLVSupplies++;
    else LVSupplies[nLVSupplies] = 0;
	
	LVSupplies[nLVSupplies] = new TTi("ASRL13::INSTR",2, "Digital");
    if(LVSupplies[nLVSupplies]->isValid) nLVSupplies++;
    else LVSupplies[nLVSupplies] = 0;
	
	LVSupplies[nLVSupplies] = new TTi("ASRL13::INSTR",3, "Driver Board");
    if(LVSupplies[nLVSupplies]->isValid) nLVSupplies++;
    else LVSupplies[nLVSupplies] = 0;
	
	break;

  case 4:    // NI-VISA under Linux, one PSU for now...
    if(strncmp(gSystem->GetName(),"Unix",4)==0){
      printf("Attempting to load libttidll.so");
      gSystem->Load("libttidll.so");    // Linux
    }
    else {
      printf("Attempting to load ttidll.dll");  
      gSystem->Load("ttidll.dll");   // Windows
    }
    printf("...done\n");
    
    TTi* LVSupplies[2];
    LVSupplies[nLVSupplies] = new TTi("ASRL1::INSTR", 1, "Module 0"); // Direct USB connection
    if(LVSupplies[nLVSupplies]->isValid) nLVSupplies++;
//     LVSupplies[nLVSupplies] = new TTi("ASRL1::INSTR", 2, "Atlys");  // Direct USB connection
//     if(LVSupplies[nLVSupplies]->isValid) nLVSupplies++;
    
    break;
    
        
	
  default:
    void* LVSupplies[8];
    LVSupplies[0]=0;
    break;
  } 

  
  // Edit the following section to match your  HV power setup
  
  
  Int_t hvtype = 0;
  Int_t nHVSupplies = 0;
  
  switch(hvtype){
  case 1: // NI-VISA driver for Keithley 237, 487 or 2410
    if(strncmp(gSystem->GetName(),"Unix",4)==0){
      printf("Attempting to load libkhvdll.so");
      gSystem->Load("libkhvdll.so");
    } else {
      printf("Attempting to load khvdll.dll");
      gSystem->Load("khvdll.dll");
    }
    printf("...done\n");

    TkHV* HVSupplies[8];
    
    HVSupplies[nHVSupplies] = new TkHV("GPIB0::22::INSTR","Module 0");
    if(HVSupplies[nHVSupplies]->isValid) nHVSupplies++;
    else HVSupplies[nHVSupplies] = 0;
    HVSupplies[1] = new TkHV("GPIB0::24::INSTR","Module 1");
    if(HVSupplies[nHVSupplies]->isValid) nHVSupplies++;
    else HVSupplies[nHVSupplies] = 0;
    break;

  case 2:	// NI-VISA driver for Keithley 2410 via USB-RS232
    printf("Attempting to load ");
    if (strncmp(gSystem->GetName(), "Unix", 4) == 0) {
      printf("libkhvdll.so");
      gSystem->Load("libkhvdll.so");	// Linux
    }
    else {
      printf("khvdll.dll");
      gSystem->Load("khvdll.dll");
    }
    printf("... done\n");
    TkHV* HVSupplies[8];
    HVSupplies[nHVSupplies] = new TkHV("ASRL6::INSTR", "Module 0");
    if (HVSupplies[nHVSupplies]->isValid) {
      nHVSupplies++;
    }
    else {
      HVSupplies[nHVSupplies] = 0;
    }
    
    break;

  case 3:   // NI-VISA driver for iseg SHQ224M
    printf("Attempting to load ");
    if (strncmp(gSystem->GetName(), "Unix", 4) == 0) {
      printf("libiseghvdll.so");
      gSystem->Load("libiseghvdll.so");	// Linux
    }
    else {
      printf("iseghvdll.dll");
      gSystem->Load("iseghvdll.dll");
    }
    printf("... done\n");
    TisegHV* HVSupplies[8];
    HVSupplies[nHVSupplies] = new TisegHV("ASRL7::INSTR", "Module 0", 1);
    if (HVSupplies[nHVSupplies]->isValid) {
      nHVSupplies++;
    }
    else {
      HVSupplies[nHVSupplies] = 0;
    }
    
    break;
    
   default:
    void* HVSupplies[8];
    HVSupplies[0]=0;
    break;
  } 

    
}
