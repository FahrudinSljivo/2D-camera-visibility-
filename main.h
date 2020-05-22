//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "pomocna.h"
#include <vector>
#include <list>
#include <utility>
#include <queue>
#include <set>

using namespace std;
//---------------------------------------------------------------------------
class TForma : public TForm
{
__published:	// IDE-managed Components
	TImage *Slika;
	TLabel *LabelBrojTacaka;
	TEdit *EditBrojTacaka;
	TButton *GenerisanjeTacaka;
	TLabel *LabelKoordinate;
	TEdit *EditKoordinate;
	TButton *DugmeProstiMnogougao;
	TLabel *TrenutnaAkcija;
	TButton *Clear;
	TButton *ZavrsiMnogougao;
	TRadioButton *DodavanjeKamere;
	TTimer *Timer1;
	void __fastcall GenerisanjeTacakaClick(TObject *Sender);
	void __fastcall SlikaMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall DugmeProstiMnogougaoClick(TObject *Sender);
	void __fastcall SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall ZavrsiMnogougaoClick(TObject *Sender);
	void __fastcall ClearClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);


private:
	vector<Tacka> tacke;
	vector<Kamera> kamere;
	vector<Duz> duziMnogougla;
    bool crtajTacke;
    bool crtajProstiMnogougao;
	void dodajTacku(Tacka);
	void dodajKameru(Kamera);

public:
	__fastcall TForma(TComponent* Owner);
};


//---------------------------------------------------------------------------
extern PACKAGE TForma *Forma;
//---------------------------------------------------------------------------
#endif

