/*
 * Streckenende.h
 *
 *  Created on: 14 Jan 2023
 *      Author: Rebal Atteya
 */

#ifndef STRECKENENDE_H_
#define STRECKENENDE_H_

#include <iostream>

#include "Fahrausnahme.h"

class Streckenende: public Fahrausnahme {
public:
	Streckenende(Weg& weg, Fahrzeug& fahrzeug);
	virtual ~Streckenende();

	virtual void vBearbeiten() override;	//Bearbeitung der Ausnahme Objekt
};

#endif /* STRECKENENDE_H_ */
