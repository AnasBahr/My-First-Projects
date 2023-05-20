/*
 * main.cpp
 *
 *  Created on: 18 Nov 2022
 *      Author: Rebal Atteya
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <random>

#include "Simulationsobjekt.h"
#include "Kreuzung.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "vertagt_liste.h"

#include "SimuClient.h"


double dGlobaleZeit = 0.0;	//Globale Variable für Zeit in Stunden

void vAufgabe_1(){

	//Instanzierung von statische Elemente
	Fahrzeug a("Auto 1");
	Fahrzeug b = Fahrzeug("Auto 2");

	//Instanzierung von dynamische Elemente
	Fahrzeug* pC = new Fahrzeug("Auto 3");
	Fahrzeug* pD = new Fahrzeug("Auto 4");

	//Löschung von dynamische Elemente
	delete pC;	//Aufruf Destruktur für pC [ID: 2]
	delete pD;	//Aufruf Destruktur für pD [ID: 3]

	/* Instanzierung von Eelemnte durch Smart Pointers */

	//Durch unique pointer
	std::unique_ptr<Fahrzeug> pE = std::make_unique<Fahrzeug>("Auto 5");
	std::unique_ptr<Fahrzeug> pF = std::make_unique<Fahrzeug>("Auto 6");

	//Durch shared pointer
	std::shared_ptr<Fahrzeug> pG = std::make_shared<Fahrzeug>("Auto 7");
	std::shared_ptr<Fahrzeug> pH = std::make_shared<Fahrzeug>("Auto 8");

	//Speichern von shared pointer in ein shared pointer
	std::cout << "Anzahl von Referenzen auf pH: " << pH.use_count() << std::endl; 	//Anzahl von Referenzen auf pH

	std::shared_ptr<Fahrzeug> pI = pH;
	std::cout << "Shared pointer pH wurde in shared pointer pI geschpeichert." << std::endl;

	std::cout << "Anzahl von Referenzen auf pH: " << pH.use_count() << std::endl;	//Anzahl von Referenzen auf pH

	//Speichern von unique pointer in ein unique pointer
	//std::unique_ptr<Fahrzeug> pJ = pF; 	//Erzeugt Fehlermeldung: unique pointers nur über 'move()' tragbar, nicht copierbar


	//Speichern aller Fahrzeuge in einem Vektor
	std::vector<std::unique_ptr<Fahrzeug>> vUniFahrzeuge;

	//vUniFahrzeuge.push_back(a);	//Statisch deklariert: kein unique ptr
	//vUniFahrzeuge.push_back(b);	//Statisch deklariert: kein unique ptr
	//vUniFahrzeuge.push_back(pC);	//raw pointer: kein unique ptr
	//vUniFahrzeuge.push_back(pD);	//raw pointer: kein unique ptr
	//vUniFahrzeuge.push_back(pE);	//Nur über move()-Befehl möglich
	//vUniFahrzeuge.push_back(pF);	//Nur über move()-Befehl möglich
	vUniFahrzeuge.push_back(move(pE));	//Übertragung ins Vektor
	vUniFahrzeuge.push_back(move(pF));	//Übertragung ins Vektor
	//vUniFahrzeuge.push_back(pG);	//shared pointer: kein unique ptr
	//vUniFahrzeuge.push_back(pH);	//shared pointer: kein unique ptr
	//vUniFahrzeuge.push_back(pI);	//shared pointer: kein unique ptr

	std::cout << "Anzahl von Elemente im Vektor vUniFahrzeuge: " << vUniFahrzeuge.size() << std::endl;

	vUniFahrzeuge.clear();	//Aufruf Destrukturen für Objekte [ID: 4, 5] in vUniFahrzeuge (früher pE, pF)

	std::cout << "Anzahl von Elemente im Vektor vUniFahrzeuge: " << vUniFahrzeuge.size() << std::endl;


	std::cout << "Anzahl von Referenzen auf pG: " << pG.use_count() << " und pH: " << pH.use_count() << std::endl;	//Anzahl von Referenzen auf pG und pH

	std::vector<std::shared_ptr<Fahrzeug>>  vShrFahrzeuge;

	vShrFahrzeuge.push_back(pG);
	vShrFahrzeuge.push_back(move(pH));

	std::cout << "Anzahl von Referenzen auf pG: " << pG.use_count() << " und pH: " << pH.use_count() << std::endl;	//Anzahl von Referenzen auf pG und pH
	std::cout << "Anzahl von Elemente im Vektor vShrFahrzeuge: " << vShrFahrzeuge.size() << std::endl;

	//Aufruf des Destrukturs für Objekte [ID: 0, 1, 6, 7] a, b, pG und in vShrFahrzeuge (pG und frühere pH) bei ende des Programs
}

void vAufgabe_1a(){
	double dZeitSpanne = 1;	//Dauer des Simulation
	double dZeittakt = 0.1;	//Zeit zwischen Sim-schritte

	std::vector<std::unique_ptr<Fahrzeug>> vFahrzeuge;	//Dekleration von Vektor

	//Einlesen von 3 Fahrzeuge
	for(int i = 0; i < 3; i++){
		std::string sName;
		double dMaxGeschwindigkeit;

		std::cout << "Name: ";
		std::cin >> sName;						//Einlesen von Name

		std::cout << "Max Geschwindigkeit: ";
		std::cin >> dMaxGeschwindigkeit;		//Einlesen von max Geschwindigkeit

		std::cout << std::endl;

		std::unique_ptr<Fahrzeug> f = std::make_unique<Fahrzeug>(sName, dMaxGeschwindigkeit);	//Erzeugen des Fahrzeug Objectks mit eingelesenen Daten
		vFahrzeuge.push_back(move(f));															//Speichern von Fahrzeuge in Vektor
	}

	//Das erweitern von der globale Zeit auf die gegebne Zeittakt
	for(double i = 0; i < dZeitSpanne; i += dZeittakt){
		dGlobaleZeit += dZeittakt;

		vFahrzeuge[0]->vKopf();

		//Das aktualisieren der Simulationsschritt für alle Fahrzeuge
		for(auto& j : vFahrzeuge){
			j->vSimulieren();

			j->vAusgeben();
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

void vAufgabe_2(){
	double dZeitSpanne = 5;	//Dauer der Simulation
	double dZeittakt = 0.2;	//Zeit zwischen Sim-schritte

	//Einlesen der Anzahl von PKWs und Fahrräder
	int iAnzPKW;
	int iAnzFahrrad;

	std::cout << "Anzahl von PKWs: ";
	std::cin >> iAnzPKW;
	std::cout << "Anzahl von Fahrräder: ";
	std::cin >> iAnzFahrrad;
	std::cout << std::endl;

	//Erzeugen eines Vektor, für das Speichern aller Fahrzeuge
	//Kann PKWs und Fahrräder im selben Vektor speichern, wegen gemeinsame Obere-(Base)Klasse
	//Man soll kein Fahrzeug-Objekte erzeugen, dass sie entweder PKW oder Fahrrad sein sollen (sollte abstrakte Klasse sein)
	std::vector<std::unique_ptr<Fahrzeug>> vGesFahrzeuge;

	for(int i = 0; i < iAnzPKW; i++){
		std::string sName;
		double dMaxGeschwindigkeit;
		double dVerbrauch;
		double dTankvolumen;

		std::cout << "Name: ";
		std::cin >> sName;						//Einlesen von Name

		std::cout << "Max Geschwindigkeit: ";
		std::cin >> dMaxGeschwindigkeit;		//Einlesen von max Geschwindigkeit

		std::cout << "Verbrauch: ";
		std::cin >> dVerbrauch;					//Einlesen von max Geschwindigkeit

		std::cout << "Tankvolumen: ";
		std::cin >> dTankvolumen;				//Einlesen von max Geschwindigkeit

		std::cout << std::endl;

		std::unique_ptr<PKW> p = std::make_unique<PKW>(sName, dMaxGeschwindigkeit, dVerbrauch, dTankvolumen);	//Erzeugen des PKW Objekts mit eingelesenen Daten
		vGesFahrzeuge.push_back(move(p));																		//Speichern des PKWs ins gesamt Vektor
	}

	for(int i = 0; i < iAnzFahrrad; i++){
		std::string sName;
		double dMaxGeschwindigkeit;

		std::cout << "Name: ";
		std::cin >> sName;						//Einlesen von Name

		std::cout << "Max Geschwindigkeit: ";
		std::cin >> dMaxGeschwindigkeit;		//Einlesen von max Geschwindigkeit

		std::cout << std::endl;

		std::unique_ptr<Fahrrad> f = std::make_unique<Fahrrad>(sName, dMaxGeschwindigkeit);	//Erzeugen des Fahrrads Objekts mit eingelesenen Daten
		vGesFahrzeuge.push_back(move(f));													//Speichern des Fahrrads ins gesamt Vektor
	}

	bool getankt = false;						//Um die Tanken nur einmal zu füllen (Prüfungsschritt)

	//Das erweitern von der globale Zeit auf die gegebne Zeitspanne
	for(dGlobaleZeit = 0; dGlobaleZeit < dZeitSpanne; dGlobaleZeit += dZeittakt){
		vGesFahrzeuge[0]->vKopf();

		//Simulationschritte für alle Fahrzeuge durchführen
		for(auto& i : vGesFahrzeuge){
			i->vSimulieren();
			i->vAusgeben();

			//Überprüft ob 3 Stunden vergangen sind, um die PKWs voll zu tanken
			if(dGlobaleZeit >= 3 && getankt == false){i->dTanken();}

			std::cout << std::endl;		//Formatierung
		}

		//Macht sicher, dass ist nicht unendlich nach die 3. Stunde wieder getankt wird, aber wartet bis alle PKWs voll getankt sind
		if(dGlobaleZeit >= 3 ){getankt = true;}

		std::cout << std::endl;			//Formatierung
	}
}

void vAufgabe_3(){
	//Erzeugen von Fahrzeug Objekte mit Smart Pointers
	std::unique_ptr<Fahrzeug> a = std::make_unique<Fahrzeug>("PKW 1", 60);
	std::unique_ptr<Fahrzeug> b = std::make_unique<Fahrzeug>("PKW 2", 120);


	a->vKopf();
	std::cout << *a << std::endl << *b << std::endl;	//Ausgeben von Fahrzeug Objekte durch überladene Ausgabeoperator

	//Vergleich von Fahrzeuge durch den überladene Vergleichsoperator
	if(a < b){
		std::cout << std::endl << "Gesamstrecke der PKW 1 ist weniger als der von PKW 2" << std::endl << std::endl;
	}

	*a = *b;											//Das Kopieren der Stammdaten von Fahrzeug 2 in Fahrzeug 1 durch überladene Zuweisungsoperator

	a->vKopf();
	std::cout << *a << std::endl << *b << std::endl;	//Ausgeben von Fahrzeug Objekte durch überladene Ausgabeoperator

}

void vAufgabe_4(){
	//Erzeugen eines Weges
	std::unique_ptr<Weg> w = std::make_unique<Weg>("Weg", 20);

	//Ausgeben der Weges
	w->vKopf();
	std::cout << *w << std::endl;
}

void vAufgabe_5(){
	//Erzeugen eines Weges
	std::unique_ptr<Weg> w = std::make_unique<Weg>("Weg_1", 40);

	//Erzeugen drei Fahrzeuge
	std::unique_ptr<Fahrzeug> f1 = std::make_unique<Fahrzeug>("Benz", 180);
	std::unique_ptr<Fahrzeug> f2 = std::make_unique<Fahrzeug>("Audi", 120);
	std::unique_ptr<Fahrzeug> f3 = std::make_unique<Fahrzeug>("BMW", 10);

	//Annahme von Fahrzeuge auf dem Weg
	w->vAnnahme(move(f1));
	w->vAnnahme(move(f2));
	w->vAnnahme(move(f3));

	//Weg simulieren und ausgeben

	w->vKopf();
	std::cout << *w << std::endl;

	//Das mehrfach Simulieren von Fahrzeug
	for(int i = 0; i < 6; i++){
		dGlobaleZeit += 0.25;	//Fortschritt der Zeit

		w->vSimulieren();

		std::cout << *w << std::endl;
	}
}

void vAufgabe_6(){
	//Initialisieren eines Grafikfenster
	bInitialisiereGrafik(800, 500);

	//Erzeugen zwei Wege, einer mit einem Tempolimit
	std::unique_ptr<Weg> w1 = std::make_unique<Weg>("Weg_1", 500, Tempolimit::Autobahn);
	std::unique_ptr<Weg> w2 = std::make_unique<Weg>("Weg_2", 500, Tempolimit::Autobahn);

	int iAnzKord = 2, Koordinaten[2*iAnzKord] = {700, 250, 100, 250};				//Koordinaten(-anzahl) der Strasse für den grafischen Ausgabe
	bZeichneStrasse(w1->getName(), w2->getName(), w1->getLaenge(), 2, Koordinaten);	//Zeichnen einer Strasse durch die oben erzeugte Wege

	//Erzeugen alle Fahrzeuge
	std::unique_ptr<PKW> f1 = std::make_unique<PKW>("Benz", 180, 12, 60);
	std::unique_ptr<PKW> f2 = std::make_unique<PKW>("Audi", 120, 8, 55);

	std::unique_ptr<PKW> f3 = std::make_unique<PKW>("BMW", 20, 19, 20);
	std::unique_ptr<PKW> f4 = std::make_unique<PKW>("VW", 110, 16, 40);
	std::unique_ptr<PKW> f5 = std::make_unique<PKW>("Porsche", 260, 17, 45);

	//Annahme von Fahrzuege auf die Wege
	w1->vAnnahme(move(f1));			//Fahrende Fahrzeug
	w1->vAnnahme(move(f2), 1);		//Parkende Fahrzeug mit Startzeit nach 1 Stunden

	w2->vAnnahme(move(f3), 10);		//Parkende Fahrzeug mit Startzeit nach 10 Stunden (Hoffentlich unendlich geparkt)
	w2->vAnnahme(move(f4), 1.5);	//Parkende Fahrzeug mit Startzeit nach 1.5 Stunden
	w2->vAnnahme(move(f5));			//Fahrende Fahrzeug

	//Simulieren und Ausgeben von Wege/Fahrzeuge
	w1->vKopf();
	std::cout << *w1 << std::endl << *w2 << std::endl << std::endl;

	//Das mehrfach Simulieren von Fahrzeuge
	for(int i = 0; i < 6*4; i++){
		dGlobaleZeit += 0.25;		//Fortschritt der Zeit
		vSetzeZeit(dGlobaleZeit);	//Grafische Ausgabe vn dGlobaleZeit im Fenster

		w1->vSimulieren();
		w2->vSimulieren();

		vSleep(100);				//Verzögert der Zeit jeder Simulationsschritt, für die Lesbarkeit

		std::cout << *w1 << std::endl << *w2 << std::endl << std::endl;
	}
}

void vAufgabe_6a(){
	//Erzeugen einer Liste und Iterator
	vertagt::VListe<int> liste;
	vertagt::VListe<int>::iterator LisIt;

	//Setup für Zufahlszahl
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(1, 10);

	//Liste mit random ints auffüllen
	for(int i = 1; i <= 10; i++){
		int j = dist(device);
		//std::cout << j << " ";
		liste.push_back(j);
	}

	liste.vAktualisieren();	//Aktualisieren der Liste, damit die Werten gespeichert werden kann

	//Ausgeben der Liste
	for(auto i: liste){
		std::cout << i << std::endl;
	}
	std::cout << std::endl;	//Formating

	//Innerhalb einer Schleife alle Elemente >5 mit erase (Löschen)
	for(vertagt::VListe<int>::iterator it = liste.begin(); it != liste.end(); it++){
		if((*it) > 5){
			liste.erase(it);
		}
	}

	//Ausgeben der Liste
	//Die Werte werden noch ausgegeben, obwohl die erase-funktion aufgeruft wurde, weil vAktualisiren noch nicht aufgeruft wurde
	for(auto i: liste){
		std::cout << i << std::endl;
	}
	std::cout << std::endl;	//Formating

	liste.vAktualisieren();	//Aktualisieren der Liste, damit die erase-funktion durchgeführt werden kann

	//Ausgeben der Liste
	//Nach vAktualisiren hat sich die Liste tatsächlich verändert
	for(int i: liste){
		std::cout << i << std::endl;
	}
	std::cout << std::endl;	//Formating

	//Beliebige Zahlen in die Liste hinzufügen
	liste.push_back(3);
	liste.push_front(19);

	liste.vAktualisieren();	//Aktualisieren der Liste, damit die Zahlen hinzugefügt werden können

	//Ausgeben der Liste
	for(auto i: liste){
		std::cout << i << std::endl;
	}

}

void vAufgabe_7(){
	//Iitialisieren einer Grafikfenester
	bInitialisiereGrafik(1000, 700);

	//Ezeugen von Kreuzungen
	std::shared_ptr<Kreuzung> Kr1 = std::make_shared<Kreuzung>("Kr1", 1000);
	std::shared_ptr<Kreuzung> Kr2 = std::make_shared<Kreuzung>("Kr2", 1000);
	std::shared_ptr<Kreuzung> Kr3 = std::make_shared<Kreuzung>("Kr3", 0);
	std::shared_ptr<Kreuzung> Kr4 = std::make_shared<Kreuzung>("Kr4", 0);

	//Zeichnen von Kreuzungen
	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	//Das Verbinden der Krezungen mittels Strassen (Hin- / Rückweg)
	Kr1->vVerbinde("W12", "W21", 40, Kr1, Kr2, Tempolimit::Innerorts);
	Kr2->vVerbinde("W23a", "W32a", 115, Kr2, Kr3, Tempolimit::Autobahn);
	Kr2->vVerbinde("W23b", "W32b", 40, Kr2, Kr3, Tempolimit::Innerorts);
	Kr2->vVerbinde("W24", "W42", 55, Kr2, Kr4, Tempolimit::Innerorts);
	Kr3->vVerbinde("W34", "W43", 85, Kr3, Kr4, Tempolimit::Autobahn);
	Kr4->vVerbinde("W44a", "W44b", 130, Kr4, Kr4, Tempolimit::Landstrasse);

	//Zeichen von Strassen
	int strasse1[] = {680, 40, 680, 300};
	int strasse2[] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570};
	int strasse3[] = {680, 300, 680, 570};
	int strasse4[] = {680, 300, 320, 300};
	int strasse5[] = {680, 570, 500, 570, 350, 510, 320, 420, 320, 300};
	int strasse6[] = {320, 300, 170, 300, 70, 250, 80, 90, 200, 60, 320, 150, 320, 300};

	bZeichneStrasse("W12", "W21", 40, 2, strasse1);
	bZeichneStrasse("W23a", "W32a", 115, 6, strasse2);
	bZeichneStrasse("W23b", "W32b", 40, 2, strasse3);
	bZeichneStrasse("W24", "W42", 55, 2, strasse4);
	bZeichneStrasse("W34", "W43", 85, 5, strasse5);
	bZeichneStrasse("W44a", "W44b", 130, 7, strasse6);


	//Erzeugen von Fahrzeuge
	std::unique_ptr<PKW> f1 = std::make_unique<PKW>("Benz", 180, 12, 60);
	std::unique_ptr<PKW> f2 = std::make_unique<PKW>("Audi", 120, 8, 55);
	std::unique_ptr<PKW> f3 = std::make_unique<PKW>("BMW", 20, 19, 20);
	std::unique_ptr<PKW> f4 = std::make_unique<PKW>("VW", 110, 16, 40);
	std::unique_ptr<PKW> f5 = std::make_unique<PKW>("Porsche", 260, 17, 45);

	//Das Annehmung von die erzeugtem Fahrzeuge an der Krezung Kr1 als parkend
	Kr1->vAnnahme(move(f1), 3);
	Kr1->vAnnahme(move(f2), 0.5);
	Kr1->vAnnahme(move(f3), 10);
	Kr1->vAnnahme(move(f4), 1);
	Kr1->vAnnahme(move(f5), 1.5);

	Kr2->vAusgeben();

	//Das Simulieren von alle Kreuzungen, bzw. Wege, bzw. Fahrzeuge
	for(dGlobaleZeit = 0; dGlobaleZeit < 20; dGlobaleZeit += 0.1){
			vSetzeZeit(dGlobaleZeit);	//Grafische Ausgabe vn dGlobaleZeit im Fenster

			Kr1->vSimulieren();
			Kr2->vSimulieren();
			Kr3->vSimulieren();
			Kr4->vSimulieren();

			vSleep(100);				//Verzögert der Zeit jeder Simulationsschritt, für die Lesbarkeit
		}
}


















int main(void){

	//vAufgabe_1(); //Aufruf Funktion für Befehle der Aufgabe 1

	//vAufgabe_1a();//Aufruf Funktion für Befehle der Aufgabe 1a

	//vAufgabe_2();	//Aufruf Funktion für Befehle der Aufgabe 2

	//vAufgabe_3();	//Aufruf Funktion für Befehle der Aufgabe 3

	//vAufgabe_4();	//Aufruf Funktion für Befehle der Aufgabe 4

	//vAufgabe_5();	//Aufruf Funktion für Befehle der Aufgabe 5

	//vAufgabe_6();	//Aufruf Funktion für Befehle der Aufgabe 6

	//vAufgabe_6a();//Aufruf Funktion für Befehle der Aufgabe 6a

	vAufgabe_7();//Aufruf Funktion für Befehle der Aufgabe 7










	return 0;

}


