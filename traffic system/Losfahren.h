/*
 * Losfahren.h
 *
 *  Created on: 14 Jan 2023
 *      Author: Rebal Atteya
 */

#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_

#include <iostream>

#include "Fahrausnahme.h"

class Losfahren: public Fahrausnahme {
public:
	Losfahren(Weg& weg, Fahrzeug& fahrzeug);
	virtual ~Losfahren();

	virtual void vBearbeiten() override;	//Bearbeitung der Ausnahme Objekt
};

#endif /* LOSFAHREN_H_ */
