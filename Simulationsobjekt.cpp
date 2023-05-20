/*
 * Simulationsobjekt.cpp
 *
 *  Created on: 18 Dec 2022
 *      Author: rebal
 */

#include "Simulationsobjekt.h"

#include <iomanip>

Simulationsobjekt::Simulationsobjekt() {
	// TODO Auto-generated constructor stub

}

Simulationsobjekt::Simulationsobjekt(std::string name)
	: p_sName(name)
{}

Simulationsobjekt::~Simulationsobjekt() {
	// TODO Auto-generated destructor stub
	std::cout << "Aufruf des Destruktor: " << p_iID << std::endl;
}

void Simulationsobjekt::vAusgeben(std::ostream& o) const{
	o << std::setw(4);
	o << p_iID;

	o << std::setw(2) << " ";								//Formatierung: Leerzeichen zwishcen Elemente

	o << std::setiosflags(std::ios::left) << std::setw(10);
	o << p_sName;
	o << std::resetiosflags(std::ios::left);
}

void Simulationsobjekt::vSimulieren(){
//	extern double dGlobaleZeit;
//
//	//Vergleich von Zeit, um extra Aufrufe bzw. Simulationsschritte im selben Zeit zu vermeiden
//	if(dGlobaleZeit <= p_dZeit){
//		return;
//	}
//
//	double dVergangeneZeit = dGlobaleZeit - p_dZeit;				//Rechnung von Vergangene Zeit seit letzte Simulationsschritt
//
//	p_dGesamtStrecke += p_dAktGeschwindigkeit * dVergangeneZeit;	//Ermittlung der, in die vergangene Zeitraum aufgrund der akt Geschwindigkeit, fahrbahr Strecke
//
//	//Aktualisiern des Zeit Variabelen
//	p_dZeit = dGlobaleZeit;
//	p_dGesamtZeit = dGlobaleZeit;
}

//Ausgabeoperatorüberladung für alle Fahrzeuge (Base- und Unterklassen), führt zu Ausgeben alle Daten
//Durch den Einsetzen von Fahrzeug Objekt Name in den Stream (in std::cout)
std::ostream& operator<<(std::ostream& o, const Simulationsobjekt& S){
	S.vAusgeben(o);
	return o;
}

//Zuweisung von Stammdaten zu angegebene Objekt
//Ohne dieser Definition versucht der Zuweisungsoperator alle Daten zu kopieren, was zu einer Fehlermeldung führt, da es konstante Variabeln gibt (bsp. p_iID)
Simulationsobjekt& Simulationsobjekt::operator= (const Simulationsobjekt& s){
	if(this == &s){			//Ausnahmebehandlung zur Selbstzuweisung
		return *this;
	}

	p_sName = s.p_sName;
	//p_iID = s.iID;		//Könnte unangenehme Folgen haben, dass es dann zwei Objekte mit den selben ID gibt

	return *this;
}

//Vergleichsoperatorüberldung
//Lifert true, falls die IDs übereinstimmen
bool operator==(const Simulationsobjekt& S1, const Simulationsobjekt& S2){
	return S1.Simulationsobjekt::getID() == S2.Simulationsobjekt::getID();
}
