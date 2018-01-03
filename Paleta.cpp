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
	// scinki, ¿ebyœmy wiedzieli czy zosta³y jakieœ kawa³ki, z kórych mo¿emy ci¹æ zamiast braæ now¹ deskê
	float* scinki = new float[n];
	// bêdziemy pamiêtaæ najd³u¿sz¹ œcinkê, ¿eby szybciej sprawdzaæ czy trzeba uci¹æ now¹ deskê
	float najdluzszaScinka = 0;
	// ³¹czna d³ugoœæ wszystkich desek jak¹ musimy wyprodukowaæ i d³ugoœæ ju¿ wyprodukowanych 
	float lacznaDlugoscWykonanych = 0;
	float lacznaDlugosc = 0;
	for(int i=0;i<n;++i)
		lacznaDlugosc += doWyprodukowania[i].dlugosc;
	// deski, które mo¿emy uci¹æ w nastêpnym kroku - w obecnej wersji algorytmu, ju¿ w drugim kroku ta tablica jest pe³na
	Deska* deskiRozwazane = new Deska[n];
	// deski ju¿ wyprodukowane, bêdziemy je sobie tylko zapisywaæ, a potem wypiszemy
	Deska* deskiWyprodukowane = new Deska[n];
	for (int i = 0; i < n; ++i) {
		deskiRozwazane[i] = doWyprodukowania[i];
		deskiWyprodukowane[i] = Deska();
	}
	// minimum ze wszystkich desek dla sumy (koszt + heurystyka), zawsze pocz¹tkowo ustawiana na wartoœæ -1 odpowiwadaj¹cej nieskoñczonoœci
	int minF= -1;
	int indeksWybranej = 0;
	int indeksPomocniczy = 0;
	int indeksScinek = 0;
	// liczba zu¿ytych desek to poszukiwana przez nas wartoœæ, zale¿y nam ¿eby by³a jak najmniejsza
	int liczbaZuzytychDesek = 0;
	// liczba wykonanych desek ¿ebyœmy wiedzieli czy ju¿ wyprodukowaliœmy wszystkie
	int liczbaWykonanychDesek = 0;
	// pêtla chodz¹ca dopóki nie wyprodukujemy wszystkich desek
	while(liczbaWykonanychDesek != n){
		// wsród wszystkich desek rozwa¿anych szukamy takiej o najmniejszej funckji F - czyli sumie kosztu i heurystyki
		// na pocz¹tku obliczymy sobie hipotetyczne koszty i heurystyki dla ka¿dej deski w rozwazanych
		for(int i = 0; i < n; i++){
			// jeœli d³ugoœæ takiej deski jest równa 0 tzn, ¿e albo jeszcze nie mo¿na jej rozwa¿aæ, albo ju¿ j¹ rozwa¿ono
			if(deskiRozwazane[i].dlugosc != 0){
				// jeœli d³ugoœæ jest wiêksza od najd³u¿szej œcinki to koszt wzroœnie o 1 w porównaniu do obecnego kosztu
				// w przeciwnym wypadku koszt pozostaje taki sam
				if(deskiRozwazane[i].dlugosc > najdluzszaScinka){
					deskiRozwazane[i].koszt = liczbaZuzytychDesek + 1;
				}else{
					deskiRozwazane[i].koszt = liczbaZuzytychDesek;
				}
				// obliczamy heurystykê tzn. ³¹czn¹ d³ugoœæ desek, które pozosta³y do wykonania dzielimy przez d³ugoœæ nominalnej deski i bierzemy czêœæ sufit
				if(modf((lacznaDlugosc - lacznaDlugoscWykonanych - deskiRozwazane[i].dlugosc)/D,&deskiRozwazane[i].heurystyka) > 0){
					deskiRozwazane[i].heurystyka += 1;
				}
				// jeœli jest to ostatnia rozwa¿ana deska to funkcja modf mo¿e zwróciæ -1, co trzeba zinterpretowaæ jako 0 i poprawiæ
				if (deskiRozwazane[i].heurystyka <= 0) {
					deskiRozwazane[i].heurystyka = 0;
				}
			}
		}
		// zawsze zoaczynamy od -1, która reprezentuje nieskoñczonoœæ, jeœli znajdziemy mniejsz¹ wartoœæ to wpiszemy j¹ na minF
		minF= -1;
		// szukamy najmniejszej wartoœci funckji F
		for(int i = 0; i < n; i++){
			if(deskiRozwazane[i].dlugosc != 0){
				if(minF == -1 || minF > deskiRozwazane[i].heurystyka + deskiRozwazane[i].koszt){
					minF = deskiRozwazane[i].heurystyka + deskiRozwazane[i].koszt;
					// zapisujemy indeks wybranej deski która ma potencja³ do bycia t¹ o najmniejszej F
					indeksWybranej = i;
				}
			}
		}
		// ju¿ wybraliœmy deskê
		// tutaj decydujemy czy zwiêkszy siê liczba zuzytych desek po naszym wyborze (miejmy nadzieje, ¿e optymalnym)
		// jeœli siê zwiêksza to musimy dopisaæ œcinkê, jeœli nie to musimy uci¹æ z ju¿ dostêpnych œcinek 
		if(deskiRozwazane[indeksWybranej].dlugosc > najdluzszaScinka){
			scinki[indeksScinek] = D - deskiRozwazane[indeksWybranej].dlugosc;
			deskiRozwazane[indeksWybranej].numerDeskiMacierzystej = indeksScinek;
			liczbaZuzytychDesek++;
			// od razu inkrementujemy indeksScinek, bo tam wpiszemy nastepna scinke
			indeksScinek++;
		}else{
			// tutaj minF u¿yta tylko pomocniczo, szukamy najkrótszej œcinki, w której zmieœci siê nasza wbrana deska
			minF= -1;
			for(int i=0;i<n;i++){
				if(scinki[i] >= deskiRozwazane[indeksWybranej].dlugosc){
					if(minF == -1 || minF > scinki[i]){
						minF = scinki[i];
						indeksPomocniczy = i;
					}
				}
			}
			// ucinamy z pasuj¹cej œcinki nasz¹ deskê i zapisujemy macierzyst¹ deskê
			deskiRozwazane[indeksWybranej].numerDeskiMacierzystej = indeksPomocniczy;
			scinki[indeksPomocniczy] -= deskiRozwazane[indeksWybranej].dlugosc;
		}
		// aktualizujemy najdlu¿sz¹ œcinkê
		najdluzszaScinka = 0;
		for(int i=0;i<n;i++){
			if(scinki[i] > najdluzszaScinka){
				najdluzszaScinka = scinki[i];
			}
		}
		// aktualizujemy resztê
		lacznaDlugoscWykonanych += deskiRozwazane[indeksWybranej].dlugosc;
		liczbaWykonanychDesek++;
		deskiWyprodukowane[indeksWybranej] = deskiRozwazane[indeksWybranej];
		// usuwamy z rozwazanych nasza Deskê - ju¿ nie mo¿na jej przegl¹daæ - ona jest ju¿ tak jakby NULL
		deskiRozwazane[indeksWybranej] = Deska();
	} 
	// po ucieciu ostatniej deski wypisujemy sobie jakie deski ucieliœmy i to dok³adnie z których macierzystych desek
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
	// zwalniamy pamiec ¿eby nie zaœmiecaæ
	delete deskiWyprodukowane;
	delete deskiRozwazane;
	delete scinki;
	return liczbaZuzytychDesek;
}

Paleta::~Paleta() {
	// TODO Auto-generated destructor stub
}

