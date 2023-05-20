/*
 * Parken.cpp
 *
 *  Created on: 14 Jan 2023
 *      Author: Rebal Atteya
 */

#include "Parken.h"

#include "Fahrzeug.h"
#include "Losfahren.h"

#include <iostream>

Parken::Parken(Weg& weg, double startZeit):
		Verhalten(weg),
		dStartZeit(startZeit)
{}

Parken::~Parken() {
	// TODO Auto-generated destructor stub
}

double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall){
	extern double dGlobaleZeit;

	//Berechnet, ob der Start Zeit des Fahrzeugs erreicht wurde, dann meldet es eine ensprechende Meldung
	if(dGlobaleZeit >= dStartZeit){
		std::cout << aFzg.getName() <<  " kann jetzt fahren!" << std::endl;
		throw Losfahren(p_rWeg, aFzg);	//Ausgeben der Meldung mittels throw
	}

	return 0.0;
}

