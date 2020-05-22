//---------------------------------------------------------------------------

#pragma hdrstop

#include "pomocna.h"


void Tacka::Crtaj(TImage *image) const {
	image->Canvas->Ellipse(x-3,y-3,x+3,y+3);
}

bool operator<(Tacka A, Tacka B) {
	if(A.x < B.x)
	  return true;
	if(A.x == B.x)
	  return A.y < B.y;
	return false;
}

bool operator==(Tacka A, Tacka B) {
  return A.x == B.x && A.y == B.y;
}

void iscrtajPoligon(vector<Tacka> &poligon, vector<Duz> &duzi, TImage *image) {
  image->Canvas->MoveTo(poligon[poligon.size()-1].x,poligon[poligon.size()-1].y);
  for(int i=0; i<poligon.size(); i++) {
	image->Canvas->LineTo(poligon[i].x,poligon[i].y);
  }

  if (duzi.size() <= 0) {
     for(int i=0; i<poligon.size(); i++) {
	if (i == poligon.size() - 1) {
		duzi.push_back(Duz(Tacka(poligon[poligon.size()-1].x,poligon[poligon.size()-1].y), Tacka(poligon[0].x,poligon[0].y)));
	}
	else {
		duzi.push_back(Duz(Tacka(poligon[i].x,poligon[i].y), Tacka(poligon[i+1].x,poligon[i+1].y)));
	}
  }
  }


}



int Orijentacija(Tacka A, Tacka B, Tacka C) {

	int P = A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y);
	if(P > 0)
	  return -1;
	if(P < 0)
	  return 1;
	return 0;

}

void Duz::Crtaj(TImage *slika) const {
	pocetna.Crtaj(slika);
	krajnja.Crtaj(slika);
	slika->Canvas->MoveTo(pocetna.x,pocetna.y);
	slika->Canvas->LineTo(krajnja.x,krajnja.y);
}

void Kamera::Crtaj(TImage *slika) const {
	k.Crtaj(slika);       //Tacka::Crtaj
	lijeva.Crtaj(slika);       //Duz::Crtaj
	desna.Crtaj(slika);        //Duz::Crtaj
}



//1 za presjek
//0 ako nema presjeka
int PresjekDuzi(const Duz &p, const Duz &q) {
   int or1 = Orijentacija(p.pocetna,p.krajnja,q.pocetna);
   int or2 = Orijentacija(p.pocetna,p.krajnja,q.krajnja);
   int or3 = Orijentacija(q.pocetna,q.krajnja,p.pocetna);
   int or4 = Orijentacija(q.pocetna,q.krajnja,p.krajnja);

   if( or1 * or2 < 0 && or3 * or4 < 0)
	 return 1;
   return 0;
}


Tacka TackaPresjekaPravih(const Duz &p, const Duz &q) {
    double a1 = p.krajnja.y - p.pocetna.y;
    double b1 = p.pocetna.x - p.krajnja.x;
    double c1 = a1*(p.pocetna.x) + b1*(p.pocetna.y);



    double a2 = q.krajnja.y - q.pocetna.y;
    double b2 = q.pocetna.x - q.krajnja.x;
    double c2 = a2*(q.pocetna.x) + b2*(q.pocetna.y);



	double determinant = a1*b2 - a2*b1;



    if (determinant == 0)
    {
        return Tacka(INT_MAX, INT_MAX);
    }
    else
    {
		double x = (b2*c1 - b1*c2)/determinant;
		double y = (a1*c2 - a2*c1)/determinant;
		return Tacka(round(x), round(y));
	}
}


double Udaljenost(const Tacka &A, const Tacka &B) {
  return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
}




//---------------------------------------------------------------------------
#pragma package(smart_init)


