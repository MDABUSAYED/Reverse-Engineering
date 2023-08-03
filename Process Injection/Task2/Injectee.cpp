#include <stdlib.h>
#include "wx/wx.h"
#include <wx/valtext.h>
#include <process.h> 
#include <stdio.h>
#include <windows.h>

// The only public function, declared also in library's header.
void RunApp()
{
    wxApp::SetInitializerFunction(wxCreateApp);
    wxEntry(0,NULL);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        RunApp();
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}

class CheatSubmissionDlg : public wxDialog
{
    public:
    CheatSubmissionDlg(wxString& cheatStr) 
        : wxDialog(NULL, wxID_ANY, _("Acosta's Cheat Entry System"))
    {   
        wxFlexGridSizer* loginInfoSizer = new wxFlexGridSizer(2);
        
        loginInfoSizer->Add(new wxStaticText(this, wxID_ANY, _("&CheatEntry:")), 0, wxALL | wxALIGN_RIGHT, 5);
        wxTextCtrl* ctlCheatTxt = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(500,25), 0, wxDefaultValidator,_("Entry"));
        ctlCheatTxt->SetValidator(wxTextValidator(wxFILTER_EMPTY, &cheatStr));
        loginInfoSizer->Add(ctlCheatTxt, 0, wxALL, 5);

        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        mainSizer->Add(loginInfoSizer, 0, wxALL, 5);                
        mainSizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALL, 5);   
        
        SetSizerAndFit(mainSizer);         
        Centre();
    }
};

class MyApp : public wxApp
{
public:
	/*
	 *TODO: the following initial values do not work! Change these and include comments!
	 */
	int numBytes = 1;
	char cheat_Instr[2]   = {'\x90', '\x00'};
	char original_Instr[6] = {'\x66', '\x89','\x44', '\x53', '\x0E', '\x00'};
	DWORD cheat_InstrAddress = 0x00405452;

    virtual bool OnInit()
    {     
        wxString cheatString("");
        CheatSubmissionDlg dlg(cheatString);

        while ( dlg.ShowModal() == wxID_OK )
        {           
            processInput(cheatString);
            
        }
        return false;                
    }

	private: 
    void processInput(wxString input) {
        //do something with the input
        if(input == "cheat on")
        {
            numBytes = 2;
            overwriteMemory(cheat_InstrAddress, cheat_Instr, numBytes);
        }
        else if(input == "cheat off")
        {
            numBytes = 6;
            overwriteMemory(cheat_InstrAddress, original_Instr, numBytes);
        }
    }

	void overwriteMemory(DWORD addressToWrite, char* valueToWrite, int numBytesToWrite) {
        //TODO: comment each line in this function
        unsigned long savedProtection;
        
        VirtualProtect((LPVOID)(addressToWrite), numBytesToWrite, PAGE_EXECUTE_READWRITE, &savedProtection);
        
        //TODO: Insert code to copy values to memory
        memcpy(&addressToWrite, valueToWrite, numBytesToWrite);

        
        VirtualProtect((LPVOID)(addressToWrite), numBytesToWrite, savedProtection, NULL);
    }
    
}; wxIMPLEMENT_APP(MyApp);