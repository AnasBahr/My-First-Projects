/*
 * Fahrzeug.h
 *
 *  Created on: 18 Nov 2022
 *      Author: Rebal Atteya
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include <iostream>
#include <string>
#include <limits>
#include <memory>

#include "Simulationsobjekt.h"

class Weg;
class Verhalten;

class Fahrzeug: public Simulationsobjekt {
protected:
	double p_dMaxGeschwindigkeit = 0;						//Maximale Geschwindigkeit
	double p_dAktGeschwindigkeit = p_dMaxGeschwindigkeit;	//Aktueller Geschwindigkeit (nur für Fahrräder)
	double p_dGesamtStrecke = 0;							//Gesamte Strecke die das Fahrzeug zurückgelegt hat
	double p_dAbschnittStrecke = 0;							//Strecke die das Fahrzeug auf dem aktuellen Weg zurückgelegt hat

	std::unique_ptr<Verhalten> p_pVerhalten;				//Steuern des Verhalten von Fahrzeug

public:
	Fahrzeug();							//Standardkunstruktur
	Fahrzeug(std::string name);			//Parameteräsierte Nicht-Standardkonstruktur
	Fahrzeug(std::string name, double maxGeschwindigkeit);	//Konstruktur für Name und Geschwindigkeit
	Fahrzeug(const Fahrzeug&) = delete;	//Verbietung der Copy-Konstruktur, da er bei Übergebung (nicht als Referenz) von Variabeln an Funktionen/Methoden aufgerufen wird, kann unangenehem Folgen haben (führt zu duplizieren von Zeigern bzw. wilder Zeiger) + Copiert alles byte-wise (auch ID)
	virtual ~Fahrzeug();				//Destruktor
	//virtual ~Fahrzeug() = 0;			//Destruktor, rein-virtuell bzw kennzeichent die Klasse als abstrakt (Hier auskommentiert, um keine Fehlermeldungen zu erzeugen)

	double getAktGeschwindigkeit() const {return p_dAktGeschwindigkeit;}; 	//Getter für die aktuelle Geschwindigkeit
	double getAbschnittStrecke() const {return p_dAbschnittStrecke;};		//Getter für die auf dem Weg abgelegten Strecke
	double getGesamtsStrecke() const {return p_dGesamtStrecke;};			//Getter für gesamt Strecke

	virtual void vKopf() const;											//Überschrift für die Ausgabetabelle für Fahrzeuge
	virtual void vAusgeben(std::ostream& o = std::cout) const override;	//Method zum Ausgeben der Daten
	virtual void vSimulieren() override;								//Methode zur Simulieren des Fahrzeugs
	virtual void vZeichnen(const Weg&) const;							//Zeichnet den korrekten Fahrzeug im Grafikfenster

	void vNeueStrecke(Weg& weg);										//Methode zur Konfiguration von fahrende Fahrzeug bei einem neuen Weg
	void vNeueStrecke(Weg& weg, double startZeit);						//Methode zur Konfiguration von parkende Fahrzeug bei einem neuen Weg

	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity()){	//Ausnahme - nur für PKW
		return 0.0;
	}

	virtual double dGeschwindigkeit(){							//Ausnahme -  nur für Fahrräder
		return 0.0;
	}

	virtual Fahrzeug& operator= (const Fahrzeug& f);			//Überladung der Zuweisungsoperator '=' für Fahrzeuge
};

//std::ostream& operator<<(std::ostream& o, const Fahrzeug& f);	//Überladung der Ausgabeoperator '<<' für Fahrzeuge
bool operator<(const Fahrzeug& f1, const Fahrzeug& f2);			//Überladung der Vergleichsoperator '<' für Fahrzeuge

#endif /* FAHRZEUG_H_ */
