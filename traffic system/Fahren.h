/*
 * Fahren.h
 *
 *  Created on: 14 Jan 2023
 *      Author: Rebal Atteya
 */

#ifndef FAHREN_H_
#define FAHREN_H_

#include "Verhalten.h"

class Fahren: public Verhalten{
public:
	Fahren(Weg& weg);
	virtual ~Fahren();

	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override; //Berechnet den zurückgelegten Strecke die ein Fahrzeug auf einem Weg führt
};

#endif /* FAHREN_H_ */
