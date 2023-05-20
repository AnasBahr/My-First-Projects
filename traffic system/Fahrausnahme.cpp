/*
 * Fahrausnahme.cpp
 *
 *  Created on: 14 Jan 2023
 *      Author: Rebal Atteya
 */

#include "Fahrausnahme.h"

Fahrausnahme::Fahrausnahme(Weg& weg, Fahrzeug& fahrzeug, std::string ausnahmeString):
		p_rWeg(weg),
		p_rFahrzeug(fahrzeug),
		what(ausnahmeString)
{}

Fahrausnahme::~Fahrausnahme() {
	// TODO Auto-generated destructor stub
}
