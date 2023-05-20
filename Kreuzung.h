/*
 * Kreuzung.h
 *
 *  Created on: 28 Jan 2023
 *      Author: Rebal Atteya
 */

#ifndef KREUZUNG_H_
#define KREUZUNG_H_

#include "Simulationsobjekt.h"

#include <memory>
#include <string>
#include <list>

#include "Tempolimit.h"

#include "Weg.h"

class Weg;//Klasse Weg als Memebervariable
class Fahrzeug;

class Kreuzung: public Simulationsobjekt {//vererbt von Simulationsobjekt
protected:
	//shared pointer da, mehrerer Kreuzungen mit dem selben Weg verknüpftg werden können
	std::list<std::shared_ptr<Weg>> p_pWege;	//Liste von Wegen von Typ shared pointers
	double p_dTankstelle;//speichert



public:
	Kreuzung();
	Kreuzung(std::string name, double tankvolumen);
	virtual ~Kreuzung();

	double getTankstelle() {return p_dTankstelle;};

	void vAusgeben() {
		for(auto w: p_pWege){
			w->vAusgeben();
		}
		std::cout << std::endl;
	};
//verbindet Kreuzungen durch Wegen mit einander
	static void vVerbinde(std::string hinName, std::string rueckName, double laenge, std::weak_ptr<Kreuzung> start, const std::weak_ptr<Kreuzung> ziel, Tempolimit limit);

	virtual void vSimulieren() override;	//Simuliert alle verknüpfte Wege

	void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startZeit);	//Erzeugt ein parkendes Fahrzeug auf den Weg und tank ihn
	void vTanken(Fahrzeug& fahrzeug);	//Tankt jeder PKW, der bei der Kreuzung vorbeifährt, voll und zieht das vom gesamt Volumen ab

	std::shared_ptr<Weg> pZufaelligerWeg(Weg& weg);	//Sucht ein Weg, der ein fahrendes Fahrzeug nehmen soll
};

#endif /* KREUZUNG_H_ */
