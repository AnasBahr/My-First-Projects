/*
 * Weg.h
 *
 *  Created on: 18 Dec 2022
 *      Author: Rebal Atteya
 */

#ifndef WEG_H_
#define WEG_H_


#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include <list>

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "Fahrausnahme.h"
#include "vertagt_liste.h"

class Fahrzeug;
class Kreuzung;

class Weg: public Simulationsobjekt {
private:
	double p_dLaenge;										//Länge des Weges in km
	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;//Liste von Fahrzeuge auf dem Weg
	Tempolimit p_eTempolimit;								//Maximaler zulässige Geschwindigkeit - 50 | 100 | unbegrenzt in km/h
	//Wege und Kreuzungen zyklisch wieder auf sich selbst verweisen
	const std::weak_ptr<Kreuzung> p_pZielKreuzung;			//Zielkreuzung eines Weges ->weak pointer
	std::weak_ptr<Weg> p_pRueckWeg;						//Rückweg des aktuellen Weges



public:
	Weg();																							//Standardkonstruktur
	Weg(std::string name, double laenge, Tempolimit limit = std::numeric_limits<Tempolimit>::max());//Param.-konstruktur für Weg (Tempolimit default ist unbegrenzt)
	//Zielkreuzung wird zusätzlich übergeben
	Weg(std::string name, double laenge, std::weak_ptr<Kreuzung> zielKreuzung, Tempolimit limit = std::numeric_limits<Tempolimit>::max());	//Param.-konstruktur für Weg mit Setup für Kreuzung (Tempolimit default ist unbegrenzt)
	virtual ~Weg();																					//Destruktur

	double getLaenge() const {return p_dLaenge;};						//Gibt die Länge des Weges zurück
	double getTempolimit() const {return (double)p_eTempolimit;};		//Gibt den maximaler Geschwindigkeit aus enum zurück

	std::shared_ptr<Kreuzung> getZielKreizung() const {return p_pZielKreuzung.lock();};	//lock wandel weak pointer zu shared pointer
	std::shared_ptr<Weg> getRueckWeg() const {return p_pRueckWeg.lock();};				//Gibt den Weak_ptr locked als shared_ptr zurück, als Weg Objekt

	void vAnnahme(std::unique_ptr<Fahrzeug> f);							//Nimmt das gegebene fahrende Fahrzeug, und stellt ihn 'auf dem Weg'
	void vAnnahme(std::unique_ptr<Fahrzeug> f, double startZeit);		//Nimmt das gegebene parkende Fahrzeug, und stellt ihn 'auf dem Weg'

	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fahrzeug);		//Löscht ein Fahrzeug aus der Fahrzeug-Liste

	virtual void vKopf() const;											//Überschrift für die Ausgabetabelle für Wege
	virtual void vAusgeben(std::ostream& o = std::cout) const override;	//Gibt aus info über Weg und Fahrzeuge auf dem Weg
	virtual void vSimulieren() override;								//Simuliert alle Fahrzeuge auf dem Weg
};

#endif /* WEG_H_ */
