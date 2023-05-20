/*
 * PKW.h
 *
 *  Created on: 19 Nov 2022
 *      Author: Rebal Atteya
 */

#ifndef PKW_H_
#define PKW_H_

#include <limits>

#include "Fahrzeug.h"

class PKW: public Fahrzeug {
private:
	double p_dVerbrauch;						//Verbrauch des PKWs (Liter/100km)
	double p_dTankvolumen = 55;					//Tankvolumen des PKWs (Liter)
	double p_dTankinhalt = p_dTankvolumen / 2.0;//Tankinhalt des PKWs (Liter)

public:
	PKW();										//Standardkonstruktur
	PKW(std::string name, double maxGeschwindigkeit, double verbrauch, double tankvolumen = 55);		//Param. Konstruktur (Default für Tankvolumen: 55 l)
	PKW(const PKW&) = delete;					//Verbietung von Copy-Konstruktur
	virtual ~PKW();

	virtual void vAusgeben(std::ostream& o  = std::cout) const override;	//Method zum Ausgeben der Daten
	virtual void vSimulieren() override;									//Methode zur Simulieren des Fahrzeugs
	virtual void vZeichnen(const Weg&) const override;						//Zeichnet ein PKW auf dem Grafikfenster

	virtual double dGeschwindigkeit() override;								//Gibt
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;	//Tanken des PKW (Default: unendlich)
};

#endif /* PKW_H_ */
