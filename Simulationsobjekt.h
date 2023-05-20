/*
 * Simulationsobjekt.h
 *
 *  Created on: 18 Dec 2022
 *      Author: rebal
 */

#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_


#include <iostream>
#include <string>
#include <limits>

class Simulationsobjekt {
private:
	static inline int p_iMaxID = 0;		//Statische Zähler über alle Instanzen

protected:
	std::string p_sName = "";			//Default ist leer über Standardkonstrukter
	const int p_iID = p_iMaxID++;		//ID wird zugewiesen, dann p_iMaxID um 1 inkrementieren

	double p_dGesamtZeit;				//Gesamte Fahrzeit
	double p_dZeit;						//Zeit letzter Simulation

public:
	Simulationsobjekt();									//Standardkonstruktur
	Simulationsobjekt(std::string name);					//Param.-konstruktur
	Simulationsobjekt(const Simulationsobjekt&) = delete;	//Verbietung der Copy-Konstruktur, da er bei Übergebung (nicht als Referenz) von Variabeln an Funktionen/Methoden aufgerufen wird, kann unangenehem Folgen haben (führt zu duplizieren von Zeigern bzw. wilder Zeiger) + Copiert alles byte-wise (auch ID)
	virtual ~Simulationsobjekt() = 0;						//Destruktor, rein-virtuell bzw kennzeichent die Klasse als abstrakt

	int getID() const {return p_iID;};						//Getter für ID
	std::string getName() const {return p_sName;};			//Getter für Name

	virtual void vAusgeben(std::ostream& o = std::cout) const;	//Methode zum Ausgeben der Daten einer Simulationsobjekt
	virtual void vSimulieren();									//Methode zur Simulieren von Objekte
	//virtual void vSimulieren() = 0;							//Methode zur Simulieren von Objekte, könnte als rein-virtuell gekennzeichnet, aber bin nicht sicher.

	virtual Simulationsobjekt& operator= (const Simulationsobjekt& s);	//Überladung der Zuweisungsoperator '=' für Simulationsobjekte
};

std::ostream& operator<<(std::ostream& o, const Simulationsobjekt& s);		//Überladung der Ausgabeoperator '<<' für Simulationsobjekte
bool operator==(const Simulationsobjekt& S1, const Simulationsobjekt& S2);	//Überladung der Vergleichsoperator '<' für Fahrzeuge

#endif /* SIMULATIONSOBJEKT_H_ */
