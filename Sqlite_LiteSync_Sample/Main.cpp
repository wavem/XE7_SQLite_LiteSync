//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvMemo"
#pragma link "AdvGlassButton"
#pragma link "AdvSmoothButton"
#pragma link "AdvEdit"
#pragma resource "*.dfm"
#pragma link "litesync-0.1.lib"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
	InitProgram();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	ExitProgram();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::InitProgram() {

	// Common
    UnicodeString tempStr = L"";

	// Init Member Variables
    m_db = NULL;



    // Get SQLite Version
    tempStr = L"SQLite Version : ";
    tempStr += sqlite3_libversion();
    PrintMsg(tempStr);

    // Init Complete Message
	PrintMsg(L"Init Success");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ExitProgram() {

	// Close DB Routine
	if(m_db) sqlite3_close(m_db);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PrintMsg(UnicodeString _str) {
	int t_RowIdx = memo->Lines->Add(_str);
    memo->SetCursor(0, t_RowIdx);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btn_DB_OpenClick(TObject *Sender)
{
	// Common
	UnicodeString tempStr = L"";
	AnsiString t_AnsiStr = "";

    // Making Command
    t_AnsiStr.sprintf("file:%s?node=secondary&connect=tcp://%s:%s",
		((AnsiString)ed_DB_Name->Text).c_str(),
    	((AnsiString)ed_IP->Text).c_str(),
    	((AnsiString)ed_Port->Text).c_str()  );

	// Print Command
    tempStr = L"CMD : ";
    tempStr += t_AnsiStr;
    PrintMsg(tempStr);

    // Open DB Routine
    if(sqlite3_open(t_AnsiStr.c_str(), &m_db) == SQLITE_OK) {
		PrintMsg(L"DB Open Success");
    } else {
        tempStr = L"DB Open Fail : ";
        tempStr += sqlite3_errmsg(m_db);
        PrintMsg(tempStr);
        sqlite3_close(m_db);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btn_TestClick(TObject *Sender)
{
	// Common
	UnicodeString tempStr = L"";
    AnsiString t_AnsiStr = "";
    int rc = 0;
    char *temp = NULL;

	// Making Query
	rc = sqlite3_prepare_v2(m_db, "SELECT * from t1", -1, &m_res, 0);

    if(rc == SQLITE_OK) {
        PrintMsg(L"Query Success");
    } else {
    	tempStr.sprintf(L"Query Fail (Err Code : %d) : ", rc);
        tempStr += sqlite3_errmsg(m_db);
        PrintMsg(tempStr);
        return;
    }


    while(sqlite3_step(m_res) != SQLITE_DONE) {

    	temp = sqlite3_column_text(m_res, 0);

    	tempStr = temp;

        PrintMsg(tempStr);

        temp = sqlite3_column_text(m_res, 1);

    	tempStr = temp;

        PrintMsg(tempStr);
    }

    sqlite3_finalize(m_res);
}
//---------------------------------------------------------------------------

