// To run it do either:
// .x listBox.C
// .x listBox.C++

#include <TApplication.h>
#include <TGClient.h>
#include <TGButton.h>
#include <TGListBox.h>
#include <TList.h>
#include "STGUICommon.h"

class MyMainFrame : public TGMainFrame {

private:
   TGListBox           *fListBox;
   TList               *fSelected;   

public:
   MyMainFrame(const TGWindow *p, UInt_t w, UInt_t h);
   virtual ~MyMainFrame();
   void DoSelect();
   void PrintSelected();

   ClassDef(MyMainFrame, 0)
};

void MyMainFrame::DoSelect()
{
   e->ConfigureVariable(ST_HCC_XOFFR1_ENABLE, 1); 
   e->ExecuteConfigs();
   e->ConfigureVariable(ST_HCC_XOFFR2_ENABLE, 1); 
   e->ExecuteConfigs();
   e->ConfigureVariable(ST_HCC_XOFFL1_ENABLE, 1); 
   e->ExecuteConfigs();
   e->ConfigureVariable(ST_HCC_XOFFL2_ENABLE, 1); 
   e->ExecuteConfigs();
   e->ConfigureVariable(ST_ABC130_PACKET_ENABLES, 15); 
   e->ExecuteConfigs();

   e->ConfigureVariable(ST_HCC_DATAINL1_ENABLE, 1); 
   e->ExecuteConfigs();
   e->ConfigureVariable(ST_HCC_DATAINL2_ENABLE, 1); 
   e->ExecuteConfigs();
   e->ConfigureVariable(ST_HCC_DATAINR1_ENABLE, 1); 
   e->ExecuteConfigs();
   e->ConfigureVariable(ST_HCC_DATAINR2_ENABLE, 1); 
   e->ExecuteConfigs();

   int mode=fListBox->GetSelected();
   switch (mode){
   case (1):
     e->ConfigureChipVariableByAddress(0, 20, ST_ABC130_DIRECTION, 1); 
     e->ExecuteConfigs(); 
     e->ConfigureChipVariableByAddress(0, 19, ST_ABC130_DIRECTION, 1); 
     e->ExecuteConfigs(); 
     e->ConfigureChipVariableByAddress(0, 18, ST_ABC130_DIRECTION, 1); 
     e->ExecuteConfigs(); 
     e->ConfigureChipVariableByAddress(0, 17, ST_ABC130_DIRECTION, 1); 
     e->ExecuteConfigs(); 
     e->ConfigureChipVariableByAddress(0, 16, ST_ABC130_DIRECTION, 1); 
     e->ExecuteConfigs(); 
     e->ConfigureVariable(ST_HCC_DATAINL2_ENABLE, 0); 
     e->ExecuteConfigs();
     break;
   }

}

MyMainFrame::MyMainFrame(const TGWindow *p, UInt_t w, UInt_t h) :
   TGMainFrame(p, w, h)
{
   // Create main frame
   
   fListBox = new TGListBox(this, 89);
   fSelected = new TList;
   fListBox->AddEntry("<-20<-19<-18<-17<-16", 1);
   fListBox->AddEntry("<-20<-19<-18<-17 16->", 2);
   fListBox->AddEntry("<-20<-19<-18 17->16->", 3);
   fListBox->AddEntry("<-20<-19 18->17->16->", 4);
   fListBox->AddEntry("<-20 19->18->17->16->", 5);
   fListBox->AddEntry("20->19->18->17->16->", 6);
//      e->ConfigureVariable(ST_ABC130_PACKET_ENABLES, 15); 
//      e->ExecuteConfigs();
//   }
   fListBox->Resize(300,450);
   AddFrame(fListBox, new TGLayoutHints(kLHintsTop | kLHintsLeft |
                                        kLHintsExpandX | kLHintsExpandY, 
                                        5, 5, 5, 5));
                                                         
   TGHorizontalFrame *hframe = new TGHorizontalFrame(this, 150, 20, kFixedWidth);
   TGTextButton *show = new TGTextButton(hframe, "&Show");
   show->SetToolTipText("Click here to print the selection you made");
   show->Connect("Pressed()", "MyMainFrame", this, "PrintSelected()");
   hframe->AddFrame(show, new TGLayoutHints(kLHintsExpandX, 5, 5, 3, 4));
   AddFrame(hframe, new TGLayoutHints(kLHintsExpandX, 2, 2, 5, 1));

   // Set a name to the main frame   
   SetWindowName("Readout method");
   MapSubwindows();

   // Initialize the layout algorithm via Resize()
   Resize(GetDefaultSize());

   // Map main frame
   MapWindow();
   fListBox->Select(1);
}

MyMainFrame::~MyMainFrame()
{
   // Clean up main frame...
   Cleanup();
   if (fSelected) {
      fSelected->Delete();
      delete fSelected;
   }
}

void MyMainFrame::PrintSelected()
{
   // Writes selected entries in TList if multiselection.

   fSelected->Clear();

   Printf("Selected entries is: %d\n", fListBox->GetSelected());
}

void listBox()
{
   // Popup the GUI...
   new MyMainFrame(gClient->GetRoot(), 200, 200);
}
