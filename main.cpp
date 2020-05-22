//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForma *Forma;
//---------------------------------------------------------------------------
__fastcall TForma::TForma(TComponent* Owner)
	: TForm(Owner)
{
	Slika->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));
    crtajTacke = false;
	crtajProstiMnogougao = false;
}
//---------------------------------------------------------------------------
void TForma::dodajTacku(Tacka nova) {
	tacke.push_back(nova);
    crtajTacke = true;
	//nova.Crtaj(Slika);
}
//---------------------------------------------------------------------------

void TForma::dodajKameru(Kamera novaKamera) {
	kamere.push_back(novaKamera);
	novaKamera.Crtaj(Slika);
}

//---------------------------------------------------------------------------


void __fastcall TForma::GenerisanjeTacakaClick(TObject *Sender)
{
  int broj_tacaka = EditBrojTacaka->Text.ToInt();
  for(int i=0;i<broj_tacaka;i++) {
	  Tacka nova(rand()%(Slika->Width),rand()%(Slika->Height));
	  dodajTacku(nova);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForma::SlikaMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	EditKoordinate->Text = "( " + IntToStr(X) + " , " + IntToStr(Y) + " )";
}
//---------------------------------------------------------------------------

void __fastcall TForma::DugmeProstiMnogougaoClick(TObject *Sender)
{
   for(int i=1;i<tacke.size();i++)
	 if(tacke[i] < tacke[0])
	   swap(tacke[i],tacke[0]);

   Tacka prva = tacke[0];
   sort(tacke.begin()+1,tacke.end(),[prva](Tacka A, Tacka B) {
										return Orijentacija(prva,A,B) < 0;
									});

   crtajProstiMnogougao = true;

}
//---------------------------------------------------------------------------


void __fastcall TForma::SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(DodavanjeKamere->Checked) {
		int brojac = 0;
		bool unutar;
			Duz poluprava(Tacka(X,Y),Tacka(Slika->Width,Slika->Height));
			for(int i=0;i<tacke.size();i++) {
				Duz trenutna(tacke[i],tacke[(i+1)%tacke.size()]);
				if(PresjekDuzi(poluprava,trenutna) == 1)
				  brojac++;
			}
			if(brojac%2 == 1)
			  unutar = true;
			else unutar = false;

		if (unutar) {
            Tacka cam = Tacka(X,Y);
			Tacka rot = Tacka(-1000, Y);
			double radijan30 = stepeniURadijane(30);
			Tacka lijeva = rotirajTacku(rot, cam, -radijan30);
			Tacka desna = rotirajTacku(rot, cam, radijan30);
			Kamera novaKamera(cam, rot, lijeva, desna);
			dodajKameru(novaKamera);
		}
	}
}

//---------------------------------------------------------------------------


void __fastcall TForma::ZavrsiMnogougaoClick(TObject *Sender)
{
   Slika->Canvas->LineTo(tacke[0].x,tacke[0].y);
   crtajProstiMnogougao = true;
}
//---------------------------------------------------------------------------

void __fastcall TForma::ClearClick(TObject *Sender)
{
  Slika->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));
  tacke.clear();
  duziMnogougla.clear();
  kamere.clear();
}



void __fastcall TForma::Timer1Timer(TObject *Sender)
{
	Timer1->Interval = 1;


    Slika->Canvas->Brush->Color = clWhite;
	Slika->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));

	if (crtajProstiMnogougao) {
		iscrtajPoligon(tacke,duziMnogougla,Slika);

	}
	if (crtajTacke) {
		for (int i = 0; i < tacke.size(); i++) {
			 tacke[i].Crtaj(Slika);
		}
	}
    for (int i = 0; i < kamere.size(); i++) {
		 if (kamere.size() > 0) {
			kamere[i].rotacijaZaUgao(0.017);
			//bool nasaoPresjekLijeve = false, nasaoPresjekDesne = false;
			//Tacka presjekLijeve = kamere[i].lijeva, presjekDesne = kamere[i].desna;
			//Duz lijevaDuz(kamere[i].k, kamere[i].lijeva);
			//Duz desnaDuz(kamere[i].k, kamere[i].desna);
			kamere[i].k.Crtaj(Slika);
			//presjekLijeve.Crtaj(Slika);
			//presjekDesne.Crtaj(Slika);

			vector<Tacka> vidljivoPodrucje = kamere[i].vidljivoPodrucje(duziMnogougla);

			vector<TPoint> points;

			points.resize(vidljivoPodrucje.size() + 1);
			points[0] = TPoint(kamere[i].k.x, kamere[i].k.y);
            Slika->Canvas->Brush->Color = clGreen;


			for (int i = 0; i < vidljivoPodrucje.size(); i++) {
                points[i+1] = TPoint(vidljivoPodrucje[i].x, vidljivoPodrucje[i].y);
			}

            Slika->Canvas->Polygon(points.data(), points.size() - 1);
		}
	}

}

