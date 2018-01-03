//============================================================================
// Name        : projekt_PSZT.cpp
// Author      : Dominik Orliñski
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Paleta.h"

using namespace std;
/*
	Konstruktor paleta(D,n) tworzy zestaw desek do wyprodukowania w naszej farbryce.
	D - standardowa d³ugoœæ deski
	n - liczba desek do wyprodukowania (losowowa d³ugoœæ desek z przedzia³u [0,D]).
*/
int main() {
	float D = 5;
	int n = 10;
	int liczbaProb = 100;
	Paleta paleta(D,n);
	paleta.wypiszPalete();
	int a = 0;
	int k = 0;
	// sprawdzam 100 razy czy da siê zmiescic na jednej desce, potem 100 razy czy da siê zmieœciæ na dwóch i tak dalej. Zatrzymuje siê na pierwszym, które znajdê.
	for (int z = 1; z != n+1; z++) {
		k = 0;
		a = n+1;
		while (a != z || (a > z)) {
			paleta.potasuj();
			a = paleta.znajdzRozwiazanie();
			k++;
			if (k == liczbaProb) {
				break;
			}
		}
		if (a == z) {
			break;
		}
	}
	system("pause");
	return 0;
}
