//---------------------------------------------------------------------------

#ifndef pomocnaH
#define pomocnaH
#include <vector>


using namespace std;




struct Tacka {
	int x;
	int y;
	Tacka():x(0),y(0) {}
	Tacka(int X, int Y):x(X),y(Y) {}
    void Crtaj(TImage*) const;
};

struct Duz {
	Tacka pocetna, krajnja;
	Duz(Tacka A,Tacka B) : pocetna(A),krajnja(B) {}
	void Crtaj(TImage*) const;
};


Tacka rotirajTacku(const Tacka& rotTacka, const Tacka& okoTacke, float ugao) {
    Tacka rezultat;

    float xDelta = rotTacka.x - okoTacke.x;
    float yDelta = rotTacka.y - okoTacke.y;

    rezultat.x = okoTacke.x + cos(ugao) * xDelta - sin(ugao) * yDelta;
    rezultat.y = okoTacke.y + sin(ugao) * xDelta + cos(ugao) * yDelta;

    return rezultat;
}

double stepeniURadijane(int stepeni) {
    double pi = 3.14159;
	return 2 * pi * stepeni / 360;
}

int PresjekDuzi(const Duz&, const Duz&);
Tacka TackaPresjekaPravih(const Duz&, const Duz&);

double Udaljenost(const Tacka&, const Tacka&);


struct Kamera {

	Tacka k, rotTacka, lijeva, desna;
	float ugao;

	Kamera(Tacka _k, Tacka _rotTacka, Tacka _lijeva, Tacka _desna) : k(_k), rotTacka(_rotTacka),
	lijeva(_lijeva), desna(_desna), ugao(0.0) {}
	void Crtaj(TImage*) const;

	void rotacijaZaUgao(float _ugao) {
        ugao += _ugao;
		rotTacka = rotirajTacku(Tacka(k.x - 1000, k.y), k, ugao);
		lijeva = rotirajTacku(rotTacka, k, stepeniURadijane(-30));
		desna = rotirajTacku(rotTacka, k, stepeniURadijane(30));
	}

    // generira duz izmedju lijevog i desnog kraka interpoliranu po uglu
	Duz generirajDuz(float t) const {
		Tacka kraj = rotirajTacku(lijeva, k, stepeniURadijane(60) * t);
		return Duz(k, kraj);
	}

	vector<Tacka> vidljivoPodrucje(const vector<Duz>& mnogougao) const {

		vector<Tacka> rezultat;

		float t = 0.f;
		while (t<=1.f) {
			Duz tempDuz = generirajDuz(t);
			float najmanjaUdaljenost = 10000.f;
			Tacka najblizaTacka;
			for (int i=0; i<mnogougao.size(); i++) {
				if (PresjekDuzi(tempDuz, mnogougao[i])==1) {
					Tacka presjek = TackaPresjekaPravih(tempDuz, mnogougao[i]);
					float udaljenostPresjeka = Udaljenost(presjek, k);
					if (udaljenostPresjeka<najmanjaUdaljenost) {
						najmanjaUdaljenost = udaljenostPresjeka;
						najblizaTacka = presjek;
					}
				}
			}
			if (najmanjaUdaljenost<10000.f)
				rezultat.push_back(najblizaTacka);

			t += 0.001f;	// 1000 duzi
		}

		return rezultat;
	}

};


int Orijentacija(Tacka,Tacka,Tacka);
void iscrtajPoligon(vector<Tacka> &poligon, vector<Duz> &duzi, TImage *image);


bool operator==(Tacka,Tacka);
bool operator<(Tacka,Tacka);
Tacka rotirajTacku(const Tacka&, const Tacka&, float);



//---------------------------------------------------------------------------
#endif


