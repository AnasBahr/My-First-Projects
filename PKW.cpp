/*
 * PKW.cpp
 *
 *  Created on: 19 Nov 2022
 *      Author: Rebal Atteya
 */

#include "PKW.h"

#include "Weg.h"
#include "Verhalten.h"
#include "SimuClient.h"

#include <iomanip>

PKW::PKW() {
	// TODO Auto-generated constructor stub

}

PKW::~PKW() {
	// TODO Auto-generated destructor stub
}

PKW::PKW(std::string name, double maxGeschwindigkeit, double verbrauch, double tankvolumen)
	:Fahrzeug(name, maxGeschwindigkeit),
	 p_dVerbrauch(verbrauch),
	 p_dTankvolumen(tankvolumen)
{}

void PKW::vAusgeben(std::ostream& o) const{
	Fahrzeug::vAusgeben(o);							//Methode für Ausgeben von Variablen in Base (Fahrzeug)

	o << std::setw(2) << " ";						//Formatierung: Leerzeichen zwishcen Elemente

	o << std::setw(15);
	o << ((p_dVerbrauch / 100) * p_dGesamtStrecke);

	o << std::setw(2) << " ";						//Formatierung: Leerzeichen zwishcen Elemente

	o << std::setw(10);
	o << p_dTankinhalt;
}

void PKW::vSimulieren(){
	extern double dGlobaleZeit;

	//Vergleich von Zeit, um extra Aufrufe bzw. Simulationsschritte im selben Zeit zu vermeiden
	//oder ob es genug Gas gibt, ob Schritt zu führen
	if(dGlobaleZeit <= p_dZeit || p_dTankinhalt <= 0){
		return;
	}

	double dVergangeneZeit = dGlobaleZeit - p_dZeit;					//Rechnung von Vergangene Zeit seit letzte Simulationsschritt
	//double dfahrbahrStrecke = p_dMaxGeschwindigkeit * dVergangeneZeit;//Ermittlung der, in die vergangene Zeitraum aufgrund der Geschwindigkeit, fahrbahr Strecke

	//p_dGesamtStrecke += p_dMaxGeschwindigkeit * dVergangeneZeit;

	p_dAktGeschwindigkeit = this->dGeschwindigkeit();					//Setzt den aktuelle Geschwindigkeit in Bezug auf der Tempolimit des Weges

	double dAbgelegteStrecke = p_pVerhalten->dStrecke(*this, dVergangeneZeit);

	p_dAbschnittStrecke += dAbgelegteStrecke;
	p_dGesamtStrecke += dAbgelegteStrecke;

	double dVerbraucht = (p_dVerbrauch / 100.0) * dAbgelegteStrecke;		//Rechnung für verbrauchtes Gas in gefahrten Strecke

	p_dTankinhalt = ((p_dTankinhalt - dVerbraucht) < 0) ? 0:(p_dTankinhalt - dVerbraucht); 	//Weist neue Tankinhalt zu und macht sicher, dass es nicht negativ wird

	//Aktualisiern des Zeit Variabelen
	p_dZeit = dGlobaleZeit;
	p_dGesamtZeit = dGlobaleZeit;
}

void PKW::vZeichnen(const Weg& weg) const{
	bZeichnePKW(p_sName, weg.getName(), (p_dAbschnittStrecke/weg.getLaenge()), p_dAktGeschwindigkeit, p_dTankinhalt);	//Zeichnet den PKW auf den gegebenen Weg in der Grafikfenester
}

double PKW::dGeschwindigkeit(){
	//Wenn der Max Geschwindigkeit der Tempolimit überschreitet, übergibt es der Tempolimit, wenn nicht, dann gibt er die Maxgeschwindigkeit zurück
	return (p_dMaxGeschwindigkeit > p_pVerhalten->getWeg().getTempolimit()) ? p_pVerhalten->getWeg().getTempolimit() : p_dMaxGeschwindigkeit;
}

double PKW::dTanken(double dMenge){
	double dGetankteMenge = ((p_dTankinhalt + dMenge) > p_dTankvolumen) ? (p_dTankvolumen - p_dTankinhalt):dMenge;	//Ermittlung getankte Menge (Kann nicht Tankvolumen überschreiten)
	p_dTankinhalt += dGetankteMenge;	//Befüllung des Tanks

	return dGetankteMenge;
}
