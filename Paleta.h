/*
 * Paleta.h
 *
 *  Created on: 4 lis 2017
 *      Author: Dominik Orli�ski
 */

#ifndef PALETA_H_
#define PALETA_H_

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
using namespace std;
/*
	koszt - liczba desek, kt�r� zu�yjemy aby wyprodukowa� dan� desk� (czyli t� kt�rej dotyczy koszt) i wszystkie wcze�niejsze deski
	heurystyka - przewidywana, minimalna liczba desek, kt�r� zu�yjemy do wypdorukowania pozosta�ych desek
	koszt i heurystyka s� zawsze liczbami ca�kowitymi
	d�ugosc - dlugo�� deski z przedzia�u [0,D]
	numerDeskiMacierzystej - dodatkowa zmienna, �eby�my wiedzieli, �e dane deski by�y uci�te z tej samej standardowej deski nazwanej macierzyst�					
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
	doWyprodukowania - paleta z deskami jakie mamy wyprodukowa�
	n - liczba tych desek
	D - standardowa (nominalna) d�ugo�� deski 
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
