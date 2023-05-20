/*
 * Weg.cpp
 *
 *  Created on: 18 Dec 2022
 *      Author: Rebal Atteya
 */

#include "Weg.h"

#include "Fahrzeug.h"

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <iterator>

Weg::Weg() {
	// TODO Auto-generated constructor stub

}

Weg::Weg(std::string name, double laenge, Tempolimit limit)
	:Simulationsobjekt(name),
	 p_dLaenge(laenge),
	 p_eTempolimit(limit)
{}

Weg::Weg(std::string name, double laenge, std::weak_ptr<Kreuzung> zielKreuzung, Tempolimit limit)
	:Simulationsobjekt(name),
	 p_dLaenge(laenge),
	 p_pZielKreuzung(zielKreuzung),
	 p_eTempolimit(limit)
{}

Weg::~Weg() {
	// TODO Auto-generated destructor stub
}

//Annahme von fahrendes Fahrzeug
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> f){
	f->vNeueStrecke(*this);				//Signalisierung des Fahrzeuges, dass es sich auf einem neuen Weg befindet
	p_pFahrzeuge.push_back(move(f));	//Annehmung von Fahrzeug auf dem Weg hinten an der Liste
}

//Annahme von parkendes Fahrzeug
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> f, double startZeit){
	f->vNeueStrecke(*this, startZeit);	//Signalisierung des Fahrzeuges, dass es sich auf einem neuen Weg befindet
	p_pFahrzeuge.push_front(move(f));	//Annehmung von Fahrzeug auf dem Weg vorne an der Liste
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fahrzeug){
	std::unique_ptr<Fahrzeug> tmp;

	//Iteriert durch alle Fahrzeuge
	for(std::list<std::unique_ptr<Fahrzeug>>::iterator it = p_pFahrzeuge.begin(); it!=p_pFahrzeuge.end(); it++){
		//Checkt ob die gesuchte Fahrzeuge gefunden wurde
		if(fahrzeug == **it){
			tmp = move(*it);
			p_pFahrzeuge.erase(it);	//Löscht das Fahrzeug aus die Liste

			return tmp;
		}
	}

	return 0;	//Nicht gefunden
}

void Weg::vKopf() const{
	std::cout << std::setiosflags(std::ios_base::left);	//links-bündig für alle Textfeldern

	std::cout << std::setw(4);
	std::cout << "ID";

	std::cout << std::setw(12);
	std::cout << "| Name";

	std::cout << std::setw(20);
	std::cout << "| Laenge";

	std::cout << std::setw(22);
	std::cout << "| Fahrzeuge" << std::endl;

	std::cout << std::setfill('-') << std::setw(100) << "-" << std::setfill(' ');	//Gestrichelte Linie
	std::cout << std::resetiosflags(std::ios_base::left) << std::endl;				//Zurücksetzung von Formatierung
}

void Weg::vAusgeben(std::ostream& o) const{
	Simulationsobjekt::vAusgeben(o);						//Methode für Ausgeben von Variablen in Base (Simulationsobjekt)

	o << std::setw(1) << ':';								//Formatierung

	o << std::setw(19);
	o << p_dLaenge;

	o << std::setw(1) << " ";								//Formatierung: Leerzeichen zwishcen Elemente

	//Ausgabe alle Fahrzeuge auf dem Weg
	o << "( ";
	for(auto& f: p_pFahrzeuge){
		o << f->getName();
		o << " ";
	}
	o << ")";

	o << std::setw(2) << " ";								//Formatierung: Leerzeichen zwishcen Elemente
}

void Weg::vSimulieren(){
	//Durch ein try-catch Block werden Ausnahmen von Losfahren und Streckenende aufgefangen und bearbeitet
	p_pFahrzeuge.vAktualisieren();
	try
	{
		//Iteriert durch alle Fahrzeuge und simuliert sie
		for(auto& f: p_pFahrzeuge){
			f->vSimulieren();
			f->vZeichnen(*this);	//Zeichnet alle Fahrzeuge auf die Grafikfenster
		}
	}catch(Fahrausnahme& ausnahme){
		ausnahme.vBearbeiten();
	}
	p_pFahrzeuge.vAktualisieren();
}

