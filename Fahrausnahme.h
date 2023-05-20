/*
 * Fahrausnahme.h
 *
 *  Created on: 14 Jan 2023
 *      Author: Rebal Atteya
 */

#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_

#include <exception>
#include <string>

class Weg;
class Fahrzeug;

class Fahrausnahme: public std::exception {
protected:
	Weg& p_rWeg;
	Fahrzeug& p_rFahrzeug;
	std::string what;

public:
	Fahrausnahme(Weg& weg, Fahrzeug& fahrzeug, std::string ausnahmeString);
	virtual ~Fahrausnahme();

	virtual void vBearbeiten() = 0;	//Rein-virtuelle Funktion, die die Klasse als abstrakt bekennzeichnet
};

#endif /* FAHRAUSNAHME_H_ */
