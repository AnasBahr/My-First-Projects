/*
 * Fahren.cpp
 *
 *  Created on: 14 Jan 2023
 *      Author: Rebal Atteya
 */

#include "Fahren.h"

#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

Fahren::Fahren(Weg& weg): Verhalten(weg)
{}

Fahren::~Fahren() {
	// TODO Auto-generated destructor stub
}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall){

	//Testet, ob das Fahrzeug die Wegende erreicht hat, wenn ja dann meldet es das
	if(aFzg.getAbschnittStrecke() >= p_rWeg.getLaenge()){
		std::cout << aFzg.getName() << " ist am Ende des Weges angegkommen (hat Wegende erreicht)!" << std::endl;
		throw Streckenende(p_rWeg, aFzg);		//Ausgeben einer Meldung für Streckende mittels throw
		return 0;
	}

	double FahrbarStrecke = aFzg.getAktGeschwindigkeit() * dZeitIntervall;	//Ermittlung der, in die vergangene Zeitraum aufgrund der akt Geschwindigkeit, fahrbar Strecke

	//Wenn die fahrbar Strecke die Länge des Weges überschreitet, wird der differenz berenchet, damit die Auto ans Wegende ankommt...
	//wenn nicht dann liefert es die fahrbare Strecke
	return (aFzg.getAbschnittStrecke() + FahrbarStrecke > p_rWeg.getLaenge()) ? (p_rWeg.getLaenge()-aFzg.getAbschnittStrecke()):FahrbarStrecke;
}

