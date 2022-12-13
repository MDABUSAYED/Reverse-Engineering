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
	int numBytes = 5;
	char cheat_Instr[5]   = {'\x90', '\x90', '\x90', '\x90', '\x90'};
	char original_Instr[5] = {'\x66', '\x89','\x44', '\x53', '\x0E'};
	DWORD cheat_InstrAddress = 0x00405452;

    virtual bool OnInit()
    {   
        wxString cheatString("");
        CheatSubmissionDlg dlg(cheatString);

        // Automatically turn on invulnerability ability once the dll injected
        dontloseHealth();

        while ( dlg.ShowModal() == wxID_OK )
        {           
            processInput(cheatString);
        }
        return false;                
    }

	private: 
    void dontloseHealth() {
        // Parameters to inject instruction that freeze health
        numBytes = 15;
        char hl_cheat_instr1[15] = {'\xC7', '\x84', '\x5E', '\x4E', '\x02', '\x00', '\x00', '\x30', '\x00', '\x00', '\x00','\x90', '\x90', '\x90', '\x90'};
        DWORD hl_cheat_InstrAddress1 = 0x0040539E;
        //DWORD hl_cheat_InstrAddress2 = 0x004054A6;


        // Modify instructions
        overwriteMemory(hl_cheat_InstrAddress1, hl_cheat_instr1, numBytes);
    }

    void processInput(wxString input) {
        //do something with the input
        if(input == "cheat on")
        {
            overwriteMemory(cheat_InstrAddress, cheat_Instr, numBytes);
        }
        else if(input == "cheat off")
        {
            overwriteMemory(cheat_InstrAddress, original_Instr, numBytes);
        }
    }
    
	void overwriteMemory(DWORD addressToWrite, char* valueToWrite, int numBytesToWrite) {
        // Initialize a pointer which will point to old access protection value later
        unsigned long savedProtection;
        
        // Change permission on a page at specified address:addressToWrite to read & write
        // and let the pointer savedProtection points to the old access protection value
        VirtualProtect((LPVOID)(addressToWrite), numBytesToWrite, PAGE_EXECUTE_READWRITE, &savedProtection);
        
        //TODO: Insert code to copy values to memory
        memcpy((LPVOID)(addressToWrite), valueToWrite, numBytesToWrite);

        // Restore permission to previous version
        VirtualProtect((LPVOID)(addressToWrite), numBytesToWrite, savedProtection, NULL);
    }
}; wxIMPLEMENT_APP(MyApp);