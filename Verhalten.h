/*
 * Verhalten.h
 *
 *  Created on: 9 Jan 2023
 *      Author: Rebal Atteya
 */

#ifndef VERHALTEN_H_
#define VERHALTEN_H_

#include "Fahrausnahme.h"

class Weg;
class Fahrzeug;

class Verhalten {
protected:
	Weg& p_rWeg;

public:
	Verhalten(Weg& weg);
	virtual ~Verhalten();	//Destruktur, [sollte] rein-virtuelle Methode bekennzeichnet die Klasse als abstrakt

	virtual Weg& getWeg() const {return p_rWeg;};						//Getter für p_rWeg

	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;	//Berechnet den zurückgelegten Strecke die ein Fahrzeug auf einem Weg führt
};

#endif /* VERHALTEN_H_ */
