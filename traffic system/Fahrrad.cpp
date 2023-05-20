/*
 * Fahrrad.cpp
 *
 *  Created on: 19 Nov 2022
 *      Author: Rebal Atteya
 */

#include "Fahrrad.h"

#include "Weg.h"
#include "SimuClient.h"

#include <cmath>
#include <iomanip>


Fahrrad::Fahrrad() {
	// TODO Auto-generated constructor stub

}

Fahrrad::~Fahrrad() {
	// TODO Auto-generated destructor stub
}

Fahrrad::Fahrrad(std::string name, double maxGeschwindigkeit) : Fahrzeug(name, maxGeschwindigkeit)
{}

void Fahrrad::vAusgeben(std::ostream& o) const{
	Fahrzeug::vAusgeben(o);
}

void Fahrrad::vSimulieren(){
	Fahrzeug::vSimulieren();

	dGeschwindigkeit();
}

void Fahrrad::vZeichnen(const Weg& weg) const{
	bZeichneFahrrad(p_sName, weg.getName(), (p_dAbschnittStrecke/weg.getLaenge()), p_dAktGeschwindigkeit);	//Zeichnet den Fahrrad auf den gegebenen Weg in der Grafikfenester
}

double Fahrrad::dGeschwindigkeit(){
	int iAbnahme = p_dGesamtStrecke / 20;		//Ermitlung der Exponent für die Geschwindigkeitabnahme (int damit es nur je 20km abnimmt)

	//Berechnung der aktueller Geschwindigkeit
	//Berücksichtgung, dass die akt. Geschwindigkeit nicht unter 12km/h sein kann
	p_dAktGeschwindigkeit = ((p_dMaxGeschwindigkeit * pow(0.9, iAbnahme)) < 12)? 12:(p_dMaxGeschwindigkeit * pow(0.9, iAbnahme));

	return p_dAktGeschwindigkeit;
}

