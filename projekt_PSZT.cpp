//============================================================================
// Name        : projekt_PSZT.cpp
// Author      : Dominik Orliñski
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Paleta.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
using namespace std;


int main() {
	Paleta paleta(5,10);
	paleta.wypiszPalete();
	paleta.znajdzRozwiazanie();
	return 0;
}
