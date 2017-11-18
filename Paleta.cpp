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
	for(int i=0;i<n;++i){
		doWyprodukowania[i].dlugosc =  D * rand()/RAND_MAX;
	}

}

void Paleta::wypiszPalete(){
	std::cout<<"Deski do wyprodukowania : \n";
	for(int i=0;i<n;++i){
		std::cout<<i+1<<"|"<<doWyprodukowania[i].dlugosc<<"\n";
	}
	std::cout<<"\n";
}

void Paleta::znajdzRozwiazanie(){
	float lacznaDlugosc = 0;
	float lacznaDlugoscScinek = 0;
	for(int i=0;i<n;++i){
		lacznaDlugosc += doWyprodukowania[i].dlugosc;
	}
	for(int i=0;i<n;++i){
		doWyprodukowania[i].koszt = 0;
		doWyprodukowania[i].kolejnoscWykonania = 0;
		doWyprodukowania[i].heurystyka = 0;
	}
	Deska* zbiorKoncowek = new Deska[n];
	Deska* zbiorOcenionych = new Deska[n];
	float* scinki = new float[n];
	float najdluzszaScinka = 0;
	lacznaDlugoscScinek = 0;
	for (int i = 0; i < n; ++i) {
		zbiorKoncowek[i] = doWyprodukowania[i];
		zbiorOcenionych[i] = 0;
	}
	int minimalnaF= -1;
	float lacznaDlugoscScinekTMP = 0;
	int kolejnoscWykonania = 1;
	float lacznaDlugoscWykonanych = 0;
	int indeksMinimum = 0;
	int indeks = 0;
	int indeksScinek = 0;
	int liczbaZuzytychDesek = 0;
	int liczbaWykonanychDesek = 0;
	while(liczbaWykonanychDesek != n){
		for(int i=0;i<n;i++){
			lacznaDlugoscScinekTMP = lacznaDlugoscScinek;
			if(zbiorKoncowek[i].dlugosc != 0){
				if(zbiorKoncowek[i].dlugosc > najdluzszaScinka){
					zbiorKoncowek[i].koszt = liczbaZuzytychDesek + 1;
					lacznaDlugoscScinekTMP += D - zbiorKoncowek[i].dlugosc;
				}else{
					zbiorKoncowek[i].koszt = liczbaZuzytychDesek;
					lacznaDlugoscScinekTMP -= zbiorKoncowek[i].dlugosc;
				}
				if(modf((lacznaDlugosc - lacznaDlugoscWykonanych - zbiorKoncowek[i].dlugosc /*- lacznaDlugoscScinekTMP*/)/D,&zbiorKoncowek[i].heurystyka) > 0){
					zbiorKoncowek[i].heurystyka += 1;
				}
				if(zbiorKoncowek[i].heurystyka <= 0) zbiorKoncowek[i].heurystyka=0;
			}
		}
		minimalnaF= -1;
		for(int i=0;i<n;i++){
			if(zbiorKoncowek[i].dlugosc != 0){
				if(minimalnaF == -1 || minimalnaF > zbiorKoncowek[i].heurystyka + zbiorKoncowek[i].koszt){
					minimalnaF = zbiorKoncowek[i].heurystyka + zbiorKoncowek[i].koszt;
					indeksMinimum = i;
				}
			}
		}
		if(zbiorKoncowek[indeksMinimum].dlugosc > najdluzszaScinka){
			scinki[indeksScinek] = D - zbiorKoncowek[indeksMinimum].dlugosc;
			zbiorKoncowek[indeksMinimum].numerDeskiMacierzystej = indeksScinek;
			liczbaZuzytychDesek++;
			indeksScinek++;
		}else{
			minimalnaF= -1;
			for(int i=0;i<n;i++){
				if(scinki[i] >= zbiorKoncowek[indeksMinimum].dlugosc){
					if(minimalnaF == -1 || minimalnaF > scinki[i]){
						minimalnaF = scinki[i];
						indeks = i;
					}
				}
			}
			zbiorKoncowek[indeksMinimum].numerDeskiMacierzystej = indeks;
			scinki[indeks] -= zbiorKoncowek[indeksMinimum].dlugosc;
		}
		najdluzszaScinka = 0;
		lacznaDlugoscScinek = 0;
		for(int i=0;i<n;i++){
				if(scinki[i] > najdluzszaScinka){
					najdluzszaScinka = scinki[i];
				}
				lacznaDlugoscScinek += scinki[i];
			}
		zbiorKoncowek[indeksMinimum].kolejnoscWykonania = kolejnoscWykonania;
		lacznaDlugoscWykonanych += zbiorKoncowek[indeksMinimum].dlugosc;
		kolejnoscWykonania++;
		liczbaWykonanychDesek++;
		zbiorOcenionych[indeksMinimum] = zbiorKoncowek[indeksMinimum];
		zbiorKoncowek[indeksMinimum] = 0;
	}
	std::cout << "\nOptymalna liczba zuzytych desek: "<< liczbaZuzytychDesek << "\n";
	std::cout<<"Procentowy odpad: "<<100*(liczbaZuzytychDesek*D - lacznaDlugosc)/(liczbaZuzytychDesek*D)<< " %\n\n";
	for(int i=0;i<liczbaZuzytychDesek;i++){
		std::cout<<i+1<<" => ";
		for(int z=0;z<n;++z){
			if(zbiorOcenionych[z].numerDeskiMacierzystej == i){
				std::cout<<zbiorOcenionych[z].dlugosc<<" ; ";
			}
		}
		std::cout << "\nOdpad : "<<scinki[i];
		std::cout<<"\n\n";
	}
}

Paleta::~Paleta() {
	// TODO Auto-generated destructor stub
}

