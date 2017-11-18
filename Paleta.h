/*
 * Paleta.h
 *
 *  Created on: 4 lis 2017
 *      Author: Dominik
 */

#ifndef PALETA_H_
#define PALETA_H_

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
using namespace std;

class Deska{
public:
	int koszt;
	int numerDeskiMacierzystej;
	float heurystyka;
	float dlugosc;
	int kolejnoscWykonania;

	Deska& operator= (int a)
		{
			numerDeskiMacierzystej = 0;
			kolejnoscWykonania = 0;
			koszt = 0;
			heurystyka = 0;
			dlugosc = 0;
			return *this;
		}
	Deska& operator= (Deska const& ex)
		{
			numerDeskiMacierzystej = ex.numerDeskiMacierzystej;
			koszt = ex.koszt;
			heurystyka = ex.heurystyka;
			dlugosc = ex.dlugosc;
			kolejnoscWykonania = ex.kolejnoscWykonania;
			return *this;
		}
};

class Paleta {
public:
	Paleta(float D, int n);
	void znajdzRozwiazanie();
	void wypiszPalete();
	virtual ~Paleta();
private:
	Deska* doWyprodukowania;
	int n;
	float D;
};

#endif /* PALETA_H_ */
