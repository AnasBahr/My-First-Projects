/*
 * Losfahren.cpp
 *
 *  Created on: 14 Jan 2023
 *      Author: Rebal Atteya
 */

#include "Losfahren.h"

#include "Weg.h"
#include "Fahrzeug.h"

Losfahren::Losfahren(Weg& weg, Fahrzeug& fahrzeug):
Fahrausnahme(weg, fahrzeug, "Startzeit wurde erreicht!")
{}

Losfahren::~Losfahren() {
	// TODO Auto-generated destructor stub
}

void Losfahren::vBearbeiten(){
	std::cout << what << std::endl;

	p_rWeg.vAnnahme(p_rWeg.pAbgabe(p_rFahrzeug));	//Löscht das parkende Fahrzeug aus der Liste und fügt es wieder ein als eine fahrendes Fahrzeug
}
