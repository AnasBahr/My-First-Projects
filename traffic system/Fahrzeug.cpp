/*
 * Fahrzeug.cpp
 *
 *  Created on: 18 Nov 2022
 *      Author: Rebal Atteya
 */

#include "Fahrzeug.h"

#include "Fahren.h"
#include "Parken.h"

#include <iomanip>

Fahrzeug::Fahrzeug() {
	// TODO Auto-generated constructor stub

	std::cout << "Aufruf des Standardkonstruktors" << std::endl;
}


Fahrzeug::Fahrzeug(std::string name) : Simulationsobjekt(name){
	std::cout << "Aufruf des Nicht-Standardkonstruktors" << std::endl;
	std::cout << "Name: " << p_sName << std::endl;
	std::cout << "ID: " << p_iID << std::endl;
}

Fahrzeug::Fahrzeug(std::string name, double maxGeschwindigkeit)
	: Simulationsobjekt(name),
	  p_dMaxGeschwindigkeit((maxGeschwindigkeit >= 0) ? maxGeschwindigkeit:0) //Läst nur positive Zahlen übermitteln
{}

Fahrzeug::~Fahrzeug() {
	// TODO Auto-generated destructor stub
}

void Fahrzeug::vKopf() const{
	std::cout << std::setiosflags(std::ios_base::left);	//links-bündig für alle Textfeldern

	std::cout << std::setw(4);
	std::cout << "ID";

	std::cout << std::setw(12);
	std::cout << "Name";

	std::cout << std::setw(20);
	std::cout << "MaxGeschwindigkeit";

	std::cout << std::setw(22);
	std::cout << "akt. Geschwindigkeit";

	std::cout << std::setw(15);
	std::cout << "Gesamtstrecke";

	std::cout << std::setw(17);
	std::cout << "Gesamtverbrauch";

	std::cout << std::setw(10);
	std::cout << "Tankinhalt" << std::endl;

	std::cout << std::setfill('-') << std::setw(100) << "-" << std::setfill(' ');	//Gestrichelte Linie
	std::cout << std::resetiosflags(std::ios_base::left) << std::endl;				//Zurücksetzung von Formatierung
}

void Fahrzeug::vAusgeben(std::ostream& o) const{
	Simulationsobjekt::vAusgeben(o);						//Methode für Ausgeben von Variablen in Base (Simulationsobjekt)

	o << std::setw(18);
	o << p_dMaxGeschwindigkeit;

	o << std::setw(2) << " ";								//Formatierung: Leerzeichen zwishcen Elemente

	o << std::setw(20);
	o << p_dAktGeschwindigkeit;

	o << std::setw(2) << " ";								//Formatierung: Leerzeichen zwishcen Elemente

	o << std::setw(13);
	o << p_dGesamtStrecke;
}

void Fahrzeug::vSimulieren(){
	extern double dGlobaleZeit;

	//Vergleich von Zeit, um extra Aufrufe bzw. Simulationsschritte im selben Zeit zu vermeiden
	if(dGlobaleZeit <= p_dZeit){
		return;
	}

	double dVergangeneZeit = dGlobaleZeit - p_dZeit;				//Rechnung von Vergangene Zeit seit letzte Simulationsschritt

//	p_dGesamtStrecke += p_dAktGeschwindigkeit * dVergangeneZeit;	//Ermittlung der, in die vergangene Zeitraum aufgrund der akt Geschwindigkeit, fahrbahr Strecke

	double dAbgelegteStrecke = p_pVerhalten->dStrecke(*this, dVergangeneZeit);

	p_dAbschnittStrecke += dAbgelegteStrecke;
	p_dGesamtStrecke += dAbgelegteStrecke;

	//Aktualisiern des Zeit Variabelen
	p_dZeit = dGlobaleZeit;
	p_dGesamtZeit = dGlobaleZeit;
}

void Fahrzeug::vZeichnen(const Weg& w) const{

}

//NeueStrecke für fahrendes Fahrzeug
void Fahrzeug::vNeueStrecke(Weg& weg){
	p_dAbschnittStrecke = 0;						//Setzt den Abschnitt Strecken Zähler wieder zurück
	p_pVerhalten = std::make_unique<Fahren>(weg);	//Instanziert ein neues Fahren Objekt
}

//NeueStrecke für parkendes Fahrzeug
void Fahrzeug::vNeueStrecke(Weg& weg, double startZeit){
	p_dAbschnittStrecke = 0;						//Setzt den Abschnitt Strecken Zähler wieder zurück
	p_pVerhalten = std::make_unique<Parken>(weg, startZeit);	//Instanziert ein neues Parken Objekt
}

////Ausgabeoperatorüberladung für alle Fahrzeuge (Base- und Unterklassen), führt zu Ausgeben alle Daten
////Durch den Einsetzen von Fahrzeug Objekt Name in den Stream (in std::cout)
//std::ostream& operator<<(std::ostream& o, const Fahrzeug& f){
//	f.vAusgeben(o);
//	return o;
//}

//Vergleichsoperatorüberldung
//Lifert true, falls der Gesamtstrecke der aktuellem Objekt kleiner als der von der Vergleichsobjekt ist
bool operator<(const Fahrzeug& f1, const Fahrzeug& f2){
	return f1.Fahrzeug::getGesamtsStrecke() < f2.Fahrzeug::getGesamtsStrecke();
}


//Zuweisung von Stammdaten zu angegebene Objekt
//Ohne dieser Definition versucht der Zuweisungsoperator alle Daten zu kopieren, was zu einer Fehlermeldung führt, da es konstante Variabeln gibt (bsp. p_iID)
Fahrzeug& Fahrzeug::operator= (const Fahrzeug& f){
	if(this == &f){			//Ausnahmebehandlung zur Selbstzuweisung
		return *this;
	}

	//p_sName = f.p_sName;	//Kann funktionieren, aber p_sName sollte dann änderbar sein (nicht const)
	//p_iID = f.iID;		//Könnte unangenehme Folgen haben, dass es dann zwei Objekte mit den selben ID gibt
	p_dMaxGeschwindigkeit = f.p_dMaxGeschwindigkeit;
	p_dAktGeschwindigkeit = f.p_dAktGeschwindigkeit;

	return *this;
}

