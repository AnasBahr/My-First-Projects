/*
 * Parken.h
 *
 *  Created on: 14 Jan 2023
 *      Author: Rebal Atteya
 */

#ifndef PARKEN_H_
#define PARKEN_H_

#include "Verhalten.h"
#include "Fahrausnahme.h"

class Parken: public Verhalten {
private:
	double dStartZeit = 0;	//Den Zeit andem das Fahrzeug fahren soll

public:
	Parken(Weg& weg, double startZeit);
	virtual ~Parken();

	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;	//Berechne für die Strecke, aber liefert 0, da das Fahrzeug parkend ist
};

#endif /* PARKEN_H_ */
