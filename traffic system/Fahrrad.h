/*
 * Fahrrad.h
 *
 *  Created on: 19 Nov 2022
 *      Author: Rebal Atteya
 */

#ifndef DEBUG_FAHRRAD_H_
#define DEBUG_FAHRRAD_H_

#include "Fahrzeug.h"

class Fahrrad: public Fahrzeug {
public:
	Fahrrad();												//Standardkonstruktur
	Fahrrad(std::string name, double maxGeschwindigkeit);	//Param. Konstruktur
	Fahrrad(const Fahrrad&) = delete;						//Verbiertung von Copy-Konstruktu
	virtual ~Fahrrad();										//Destruktur

	virtual void vAusgeben(std::ostream& o = std::cout) const override;	//Method zum Ausgeben der Daten
	virtual void vSimulieren() override;								//Methode zur Simulieren des Fahrzeugs
	virtual void vZeichnen(const Weg& weg) const override;				//Zeichnet ein Fahrrad auf dem Grafikfenster

	virtual double dGeschwindigkeit() override;	//Methode für die Berechnung der aktueller Geschwindikeit (Abnahme von Max)
};

#endif /* DEBUG_FAHRRAD_H_ */
