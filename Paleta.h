/*
 * Paleta.h
 *
 *  Created on: 4 lis 2017
 *      Author: Dominik Orliñski
 */

#ifndef PALETA_H_
#define PALETA_H_

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
using namespace std;
/*
	koszt - liczba desek, któr¹ zu¿yjemy aby wyprodukowaæ dan¹ deskê (czyli tê której dotyczy koszt) i wszystkie wczeœniejsze deski
	heurystyka - przewidywana, minimalna liczba desek, któr¹ zu¿yjemy do wypdorukowania pozosta³ych desek
	koszt i heurystyka s¹ zawsze liczbami ca³kowitymi
	d³ugosc - dlugoœæ deski z przedzia³u [0,D]
	numerDeskiMacierzystej - dodatkowa zmienna, ¿ebyœmy wiedzieli, ¿e dane deski by³y uciête z tej samej standardowej deski nazwanej macierzyst¹					
*/
class Deska{
public:
	int koszt;
	int numerDeskiMacierzystej;
	float heurystyka;
	float dlugosc;

	Deska() {
		koszt = 0;
		heurystyka = 0;
		numerDeskiMacierzystej = 0;
		dlugosc = 0;
	}
	Deska& operator= (Deska const& ex)
		{
			numerDeskiMacierzystej = ex.numerDeskiMacierzystej;
			koszt = ex.koszt;
			heurystyka = ex.heurystyka;
			dlugosc = ex.dlugosc;
			return *this;
		}
};
/*
	doWyprodukowania - paleta z deskami jakie mamy wyprodukowaæ
	n - liczba tych desek
	D - standardowa (nominalna) d³ugoœæ deski 
*/
class Paleta {
public:
	Paleta(float D, int n);
	int znajdzRozwiazanie();
	void wypiszPalete();
	void potasuj();
	virtual ~Paleta();
private:
	Deska* doWyprodukowania;
	int n;
	float D;
};

#endif /* PALETA_H_ */
