/*
 * Paleta.cpp
 *
 *  Created on: 4 lis 2017
 *      Author: Dominik
 */

#include "Paleta.h"

#include <cmath>
#include <cstdio>
#include <limits>

Paleta::Paleta(float D, int n) {
	srand(time(NULL));
	this->n = n;
	this->D = D;
	doWyprodukowania = new Deska[n];
	//for(int i=0;i<n;++i){
		//doWyprodukowania[i].dlugosc =  D * rand()/RAND_MAX;
	//}
	doWyprodukowania[0].dlugosc = 1.46031;
	doWyprodukowania[1].dlugosc = 0.748619;
	doWyprodukowania[2].dlugosc = 2.0011;
	doWyprodukowania[3].dlugosc = 0.68804;
	doWyprodukowania[4].dlugosc = 0.932493;
	doWyprodukowania[5].dlugosc = 1.09897;
	doWyprodukowania[6].dlugosc = 1.95715;
	doWyprodukowania[7].dlugosc = 0.499283;
	doWyprodukowania[8].dlugosc = 3.70861;
	doWyprodukowania[9].dlugosc = 1.66509;
}
void Paleta::potasuj() {
	int* tab = new int[n];
	int a = 0;
	bool f = false;
	for (int i = 0; i < n; i++) {
		tab[i] = -1;
	}
	for (int i = 0; i < n; i++) {
		a = rand() % n;
		for (int j = 0; j < n; j++) {
			if (tab[j] != -1) {
				if (tab[j] == a) {
					f = true;
					break;
				}
			}
		}
		if (f == true) {
			f = false;
			i--;
		}
		else {
			tab[i] = a;
		}
	}
	Deska* doWyprodukowaniaTMP = new Deska[n];
	for (int i = 0; i < n; i++) {
		doWyprodukowaniaTMP[i] = doWyprodukowania[i];
	}
	for (int i = 0; i < n; i++) {
		doWyprodukowania[i] = doWyprodukowaniaTMP[tab[i]];
	}
}
void Paleta::wypiszPalete(){
	std::cout<<"Deski do wyprodukowania : \n";
	for(int i=0;i<n;++i){
		std::cout<<i+1<<"|"<<doWyprodukowania[i].dlugosc<<"\n";
	}
	std::cout<<"\n";
}

int Paleta::znajdzRozwiazanie(){
	// scinki, �eby�my wiedzieli czy zosta�y jakie� kawa�ki, z k�rych mo�emy ci�� zamiast bra� now� desk�
	float* scinki = new float[n];
	// b�dziemy pami�ta� najd�u�sz� �cink�, �eby szybciej sprawdza� czy trzeba uci�� now� desk�
	float najdluzszaScinka = 0;
	// ��czna d�ugo�� wszystkich desek jak� musimy wyprodukowa� i d�ugo�� ju� wyprodukowanych 
	float lacznaDlugoscWykonanych = 0;
	float lacznaDlugosc = 0;
	for(int i=0;i<n;++i)
		lacznaDlugosc += doWyprodukowania[i].dlugosc;
	// deski, kt�re mo�emy uci�� w nast�pnym kroku - w obecnej wersji algorytmu, ju� w drugim kroku ta tablica jest pe�na
	Deska* deskiRozwazane = new Deska[n];
	// deski ju� wyprodukowane, b�dziemy je sobie tylko zapisywa�, a potem wypiszemy
	Deska* deskiWyprodukowane = new Deska[n];
	for (int i = 0; i < n; ++i) {
		deskiRozwazane[i] = doWyprodukowania[i];
		deskiWyprodukowane[i] = Deska();
	}
	// minimum ze wszystkich desek dla sumy (koszt + heurystyka), zawsze pocz�tkowo ustawiana na warto�� -1 odpowiwadaj�cej niesko�czono�ci
	int minF= -1;
	int indeksWybranej = 0;
	int indeksPomocniczy = 0;
	int indeksScinek = 0;
	// liczba zu�ytych desek to poszukiwana przez nas warto��, zale�y nam �eby by�a jak najmniejsza
	int liczbaZuzytychDesek = 0;
	// liczba wykonanych desek �eby�my wiedzieli czy ju� wyprodukowali�my wszystkie
	int liczbaWykonanychDesek = 0;
	// p�tla chodz�ca dop�ki nie wyprodukujemy wszystkich desek
	while(liczbaWykonanychDesek != n){
		// wsr�d wszystkich desek rozwa�anych szukamy takiej o najmniejszej funckji F - czyli sumie kosztu i heurystyki
		// na pocz�tku obliczymy sobie hipotetyczne koszty i heurystyki dla ka�dej deski w rozwazanych
		for(int i = 0; i < n; i++){
			// je�li d�ugo�� takiej deski jest r�wna 0 tzn, �e albo jeszcze nie mo�na jej rozwa�a�, albo ju� j� rozwa�ono
			if(deskiRozwazane[i].dlugosc != 0){
				// je�li d�ugo�� jest wi�ksza od najd�u�szej �cinki to koszt wzro�nie o 1 w por�wnaniu do obecnego kosztu
				// w przeciwnym wypadku koszt pozostaje taki sam
				if(deskiRozwazane[i].dlugosc > najdluzszaScinka){
					deskiRozwazane[i].koszt = liczbaZuzytychDesek + 1;
				}else{
					deskiRozwazane[i].koszt = liczbaZuzytychDesek;
				}
				// obliczamy heurystyk� tzn. ��czn� d�ugo�� desek, kt�re pozosta�y do wykonania dzielimy przez d�ugo�� nominalnej deski i bierzemy cz�� sufit
				if(modf((lacznaDlugosc - lacznaDlugoscWykonanych - deskiRozwazane[i].dlugosc)/D,&deskiRozwazane[i].heurystyka) > 0){
					deskiRozwazane[i].heurystyka += 1;
				}
				// je�li jest to ostatnia rozwa�ana deska to funkcja modf mo�e zwr�ci� -1, co trzeba zinterpretowa� jako 0 i poprawi�
				if (deskiRozwazane[i].heurystyka <= 0) {
					deskiRozwazane[i].heurystyka = 0;
				}
			}
		}
		// zawsze zoaczynamy od -1, kt�ra reprezentuje niesko�czono��, je�li znajdziemy mniejsz� warto�� to wpiszemy j� na minF
		minF= -1;
		// szukamy najmniejszej warto�ci funckji F
		for(int i = 0; i < n; i++){
			if(deskiRozwazane[i].dlugosc != 0){
				if(minF == -1 || minF > deskiRozwazane[i].heurystyka + deskiRozwazane[i].koszt){
					minF = deskiRozwazane[i].heurystyka + deskiRozwazane[i].koszt;
					// zapisujemy indeks wybranej deski kt�ra ma potencja� do bycia t� o najmniejszej F
					indeksWybranej = i;
				}
			}
		}
		// ju� wybrali�my desk�
		// tutaj decydujemy czy zwi�kszy si� liczba zuzytych desek po naszym wyborze (miejmy nadzieje, �e optymalnym)
		// je�li si� zwi�ksza to musimy dopisa� �cink�, je�li nie to musimy uci�� z ju� dost�pnych �cinek 
		if(deskiRozwazane[indeksWybranej].dlugosc > najdluzszaScinka){
			scinki[indeksScinek] = D - deskiRozwazane[indeksWybranej].dlugosc;
			deskiRozwazane[indeksWybranej].numerDeskiMacierzystej = indeksScinek;
			liczbaZuzytychDesek++;
			// od razu inkrementujemy indeksScinek, bo tam wpiszemy nastepna scinke
			indeksScinek++;
		}else{
			// tutaj minF u�yta tylko pomocniczo, szukamy najkr�tszej �cinki, w kt�rej zmie�ci si� nasza wbrana deska
			minF= -1;
			for(int i=0;i<n;i++){
				if(scinki[i] >= deskiRozwazane[indeksWybranej].dlugosc){
					if(minF == -1 || minF > scinki[i]){
						minF = scinki[i];
						indeksPomocniczy = i;
					}
				}
			}
			// ucinamy z pasuj�cej �cinki nasz� desk� i zapisujemy macierzyst� desk�
			deskiRozwazane[indeksWybranej].numerDeskiMacierzystej = indeksPomocniczy;
			scinki[indeksPomocniczy] -= deskiRozwazane[indeksWybranej].dlugosc;
		}
		// aktualizujemy najdlu�sz� �cink�
		najdluzszaScinka = 0;
		for(int i=0;i<n;i++){
			if(scinki[i] > najdluzszaScinka){
				najdluzszaScinka = scinki[i];
			}
		}
		// aktualizujemy reszt�
		lacznaDlugoscWykonanych += deskiRozwazane[indeksWybranej].dlugosc;
		liczbaWykonanychDesek++;
		deskiWyprodukowane[indeksWybranej] = deskiRozwazane[indeksWybranej];
		// usuwamy z rozwazanych nasza Desk� - ju� nie mo�na jej przegl�da� - ona jest ju� tak jakby NULL
		deskiRozwazane[indeksWybranej] = Deska();
	} 
	// po ucieciu ostatniej deski wypisujemy sobie jakie deski ucieli�my i to dok�adnie z kt�rych macierzystych desek
	std::cout << "\nOptymalna liczba zuzytych desek: "<< liczbaZuzytychDesek << "\n";
	std::cout<<"Procentowy odpad: "<<100*(liczbaZuzytychDesek*D - lacznaDlugosc)/(liczbaZuzytychDesek*D)<< " %\n\n";
	for(int i=0;i<liczbaZuzytychDesek;i++){
		std::cout<<i+1<<" => ";
		for(int z = 0; z < n; ++z){
			if(deskiWyprodukowane[z].numerDeskiMacierzystej == i){
				std::cout<<deskiWyprodukowane[z].dlugosc<<" ; ";
			}
		}
		std::cout << "\nOdpad : "<<scinki[i];
		std::cout<<"\n\n";
	}
	// zwalniamy pamiec �eby nie za�mieca�
	delete deskiWyprodukowane;
	delete deskiRozwazane;
	delete scinki;
	return liczbaZuzytychDesek;
}

Paleta::~Paleta() {
	// TODO Auto-generated destructor stub
}

