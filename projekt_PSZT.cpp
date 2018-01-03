//============================================================================
// Name        : projekt_PSZT.cpp
// Author      : Dominik Orli�ski
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Paleta.h"

using namespace std;
/*
	Konstruktor paleta(D,n) tworzy zestaw desek do wyprodukowania w naszej farbryce.
	D - standardowa d�ugo�� deski
	n - liczba desek do wyprodukowania (losowowa d�ugo�� desek z przedzia�u [0,D]).
*/
int main() {
	float D = 5;
	int n = 10;
	int liczbaProb = 100;
	Paleta paleta(D,n);
	paleta.wypiszPalete();
	int a = 0;
	int k = 0;
	// sprawdzam 100 razy czy da si� zmiescic na jednej desce, potem 100 razy czy da si� zmie�ci� na dw�ch i tak dalej. Zatrzymuje si� na pierwszym, kt�re znajd�.
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
