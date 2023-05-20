/*
 * Streckenende.cpp
 *
 *  Created on: 14 Jan 2023
 *      Author: Rebal Atteya
 */

#include "Streckenende.h"

#include "Simulationsobjekt.h"
#include "Weg.h"
#include "Kreuzung.h"
#include "Fahrzeug.h"

Streckenende::Streckenende(Weg& weg, Fahrzeug& fahrzeug):
	Fahrausnahme(weg, fahrzeug, "Streckenende wurde erreicht!")
{}

Streckenende::~Streckenende() {
	// TODO Auto-generated destructor stub
}

void Streckenende::vBearbeiten(){
	extern double dGlobaleZeit;

	std::cout << what << std::endl;	//Ausgeben der Ausnahme
    //löscht Fahrzeug aus der Liste und speichert es in f
	std::unique_ptr<Fahrzeug> f = std::move(p_rWeg.pAbgabe(p_rFahrzeug));

	/*	Kann das nicht simultan mit der Ausgabe einsetzen :(
	p_rWeg.getZielKreizung()->vTanken(*f);									//Tankt das Fahrzeug von der Tankstelle
	p_rWeg.getZielKreizung()->pZufaelligerWeg(p_rWeg)->vAnnahme(move(f));	//Auf Zufälligem Weg fahrend einsetzen
	*/

	std::shared_ptr<Kreuzung> k = p_rWeg.getZielKreizung();// Zielkreuzung von aktuellen Weg wird in "k" gespeichert
	std::shared_ptr<Weg> w = k->pZufaelligerWeg(p_rWeg);// ein zufälliger Weg verbunden mit der Zielkreuzung wird in "w" gespeicher.

	//Tanken und fortsetzung des Fahrzeuges auf ein neuem Weg
	k->vTanken(*f);// das gelöschte Fahrzeug wird gelöscht
	w->vAnnahme(move(f));// Fahrzeug wird wieder auf dem zufällige Weg als fahrend wieder aufgenommen

	//Ausgeben das Umsetzen
	std::cout << "Zeit		: " << dGlobaleZeit << std::endl;
	std::cout << "Kreuzung	: " << k->getName() << ", " << k->getTankstelle() << std::endl; //gibt Tankvolumen und Namae der Kreuzung aus
	std::cout << "Wechsel	: " << p_rWeg.getName() << "->" << w->getName() << std::endl;// gibt neuer und alter Wegname aus
	//std::cout << "Fahrzeug	: " << f->getName() << std::endl;
}
