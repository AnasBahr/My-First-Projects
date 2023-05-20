/*
 * Kreuzung.cpp
 *
 *  Created on: 28 Jan 2023
 *      Author: Rebal Atteya
 */

#include "Kreuzung.h"

#include <random>
#include <iterator>

#include "Fahrzeug.h"
#include "Weg.h"

Kreuzung::Kreuzung() {
	// TODO Auto-generated constructor stub

}

Kreuzung::Kreuzung(std::string name, double tankvolumen)
	: Simulationsobjekt(name),
	  p_dTankstelle(tankvolumen)
{}

Kreuzung::~Kreuzung() {
	// TODO Auto-generated destructor stub
}

void Kreuzung::vVerbinde(std::string hinName, std::string rueckName, double laenge, std::weak_ptr<Kreuzung> start, const std::weak_ptr<Kreuzung> ziel, Tempolimit limit){
	std::shared_ptr<Weg> hinWeg = std::make_shared<Weg>(hinName, laenge, ziel, limit);// Hinweg wird als shared pointer erstellt
	std::shared_ptr<Weg> rueckWeg = std::make_shared<Weg>(rueckName, laenge, start, limit); // Rückweg wird erstellt

	ziel.lock()->p_pWege.push_back(rueckWeg);// Rückweg wird zur Wegliste der Zielkreuzung hinzugefügt
	start.lock()->p_pWege.push_back(hinWeg); // Hinweg wird zur Wegliste der Startkreuzung hinzugefügt
}

void Kreuzung::vTanken(Fahrzeug& fahrzeug){
	if(p_dTankstelle <= 0) return; //Ausnahmebehandlung wenn der Tankstelle leer ist

	double getankteMenge = fahrzeug.dTanken(p_dTankstelle); // dTanken Funkton in PKW gibt getankte Menge zurrrück

	//fals nicht genug Tankinhalt in der Tankstelle befindet-> nur verfügbares Tankinhalt abziehen.

	p_dTankstelle -= (p_dTankstelle - getankteMenge <= 0) ? p_dTankstelle : getankteMenge;
}

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startZeit){
	vTanken(*fahrzeug); //tankt das Fahrzeug und aktualisiert Tankinhalt der Kreuzung
	p_pWege.front()->vAnnahme(move(fahrzeug), startZeit); //stellt ein Fahrzeug auf dem ersten Weg in der Liste von Wegen, die mit der Kreuzung verbunden sind.
}//Fahrzeuge werden dabei als parkend betrachet bis Starrtzeit erreicht wird.

void Kreuzung::vSimulieren(){
	for(auto w: p_pWege){
		w->vSimulieren();
	}//simuliert jeden Weg verbunden mit Kreuzung der Liste p_pWege.
}

std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& weg){
	//Ausnahme für "Sackgasse"
	if(p_pWege.size() == 1){
		return *(p_pWege.begin());
	}//fals nur ein Weg vorhanden -> einfach den ersten und einzelnen Weg zurückgeben

	//Setup für Zufahlszahl
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(1, p_pWege.size());//Zufallszahl zwischen 1 und Größe der Liste

	//Suchen einer Weg durch Zufall
	int zufall = dist(device);

	std::list<std::shared_ptr<Weg>>::iterator it = p_pWege.begin();

	for(int i = 1; i <= zufall-1; i++){
		it++;// iterator erhöht bis Zufahlzahl erreicht wurde => Position des zufälligen Weges auf der Liste
	}

	//TODO Fehler bei testen von Rückweg

	//Macht sicher, dass dies nicht der Weg, der das Fahrzeug zur Kreuzung aufgefahren ist
	//Wenn der zufällig der Rückweg ist, nimmt den Weg danach;
//	if(**it == weg){
//		return pZufaelligerWeg(weg);
//	}else{
//		return *it;
//	}

	return *it; // zufälliger Weg wird zurückgegeben

	return 0; //Fehlermeldung
}
