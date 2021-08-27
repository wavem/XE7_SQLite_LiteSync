//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include "sqlite3.h"
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "AdvMemo.hpp"
#include "AdvGlassButton.hpp"
#include "AdvSmoothButton.hpp"
#include "AdvEdit.hpp"
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *___pnBase;
	TAdvMemo *memo;
	TAdvGlassButton *btn_DB_Open;
	TAdvEdit *ed_DB_Name;
	TLabel *lb_DB_Name;
	TLabel *lb_IP;
	TLabel *lb_Port;
	TAdvEdit *ed_IP;
	TAdvEdit *ed_Port;
	TAdvGlassButton *btn_Test;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btn_DB_OpenClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);

public: // BASIC MEMBER VARIABLES

public: // BASIC MEMBER FUNCTIONS
	void __fastcall InitProgram();
    void __fastcall ExitProgram();
    void __fastcall PrintMsg(UnicodeString _str);

public: // SQLITE (with Lite Sync)
	sqlite3 *m_db;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
