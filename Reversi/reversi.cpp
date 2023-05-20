/**
 * Praktikum Informatik 1 MMXXIII
 *
 * @file main.cpp
 *
 * Die Funktionen fuer das Spiel Reversi
 */

/**
* @mainpage Reversi
*
* Dokumentation des Spiels Reversi im Rahmen des Praktikums Informatik 1.
*
*/

#include <iostream>
#include <string>
#include "config.h"
#include "test.h"
#include "reversiKI.h"


/**
 * @brief Funktion zur ersten Initialisierung eines neuen Spielfelds
 *
 * Diese Funktion fuellt ein existierendes Spielfeld mit Nullen und erzeugt die Startaufstellung.
 *
 * @param spielfeld Spielfeld, das initialisiert wird
 */
void initialisiereSpielfeld(int spielfeld[GROESSE_Y][GROESSE_X])
{
    for (int j = 0; j < GROESSE_Y; j++)
        {
            for(int i = 0; i < GROESSE_X; i++)
            {
                spielfeld[j][i] = 0;
            }
        }
        spielfeld[GROESSE_Y / 2 - 1][GROESSE_X / 2 - 1] = 1;
        spielfeld[GROESSE_Y / 2][GROESSE_X / 2 - 1] = 2;
        spielfeld[GROESSE_Y / 2 - 1][GROESSE_X / 2] = 2;
        spielfeld[GROESSE_Y / 2][GROESSE_X / 2] = 1;
}



/**
* @brief Ausgabe des Spielfelds auf der Konsole
*
* Ausgabe des aktuellen Spielfelds, 0 bedeutet leeres Feld, 1 ist Spieler 1 und 2 ist Spieler2
* Kreuze symbolisieren Spieler 1, waehrend Kreise Spieler 2 symbolisieren
*
*  @param spielfeld  Spielfeld, das ausgeben wird
*/
void zeigeSpielfeld(const int spielfeld[GROESSE_Y][GROESSE_X])
{
    std::cout << "   | ";

    //Start bei ASCII 65 = A
    for (int i = 65; i < 65 + GROESSE_X; ++i)
        std::cout << ((char) i) << " | " ;

    std::cout << std::endl;

    for (int j = 0; j < GROESSE_Y; ++j)
    {
        for(int i = 0; i < GROESSE_X; ++i)
        {
            std::cout << "---+";
        }
        std::cout << "---+" << std::endl;

        std::cout << " " << j + 1 << " |";
        for (int i = 0; i < GROESSE_X; ++i)
        {
            switch (spielfeld[j][i])
            {
                case 0:
                    std::cout << "   " ;
                    break;
                case 1:
                    std::cout << " X ";
                    break;
                case 2:
                    std::cout << " O ";
                    break;
                default:
                    std::cout << "Unzulaessige Daten im Spielfeld!" << std::endl;
                    std::cout << "Abbruch .... " << std::endl;
                    exit(0);
                    break;
            }
            std::cout << "|";
        };  //for i
        std::cout <<  std::endl;
    }  //for j
}

/**
 * @brief Prueft, wer Gewinner ist
 *
 * Zaehlt alle Steine auf dem Feld
 *
 * @param spielfeld Aktuelles Spielfeld, fuer das der Gewinner ermittelt wird
 * @return winner
 */
int gewinner(const int spielfeld[GROESSE_Y][GROESSE_X])
{
    int zaehlerSpieler1 = 0;
    int zaehlerSpieler2 = 0;

    for (int j = 0; j < GROESSE_Y; ++j)
    {
        for (int i = 0; i < GROESSE_X; ++i)
        {
            if (spielfeld[j][i] == 1)
            {
                ++zaehlerSpieler1;
            }
            if (spielfeld[j][i] == 2)
            {
                ++zaehlerSpieler2;
            }

        }
    }

    if (zaehlerSpieler1 == zaehlerSpieler2)
    {
        return 0;
    }
    if (zaehlerSpieler1 < zaehlerSpieler2)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

/**
* @brief Ueberprueft fuer zwei Indizes, ob sie auf dem Spielfeld sind
*
* @param posX Index fuer die Spalte
* @param posY Index fuer die Zeile
* @return true, wenn Spalte und Zeile innerhalb des Spielfelds sind, sonst false
*/
bool aufSpielfeld(const int posX, const int posY)
{
    // Die Funktion testet, ob die posX und posY (nur) kleiner als der bestimmten Feldgrösse, weil der Feld von 0-(GROESSE-1) geht (und auch nicht negativ ist)
    if(posX >= 0 && posX < GROESSE_X && posY >= 0 && posY < GROESSE_Y)
        return true;
    return false;
}


/**
 * @brief Ueberprueft fuer zwei Indizes, ob der Zug gueltig ist
 *
 *  Ueberprueft, ob auf einem benachbarten Feld ein gegnerischer Stein liegt.
 *  Wenn ja, wird diese Richtung solange untersucht, bis ein eigener Stein
 *  gefunden wird. Wird vorher der Spielfeldrand erreicht oder ein leeres Feld
 *  gefunden, wird false zurueckgegeben, sonst true
 *
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler Der aktuelle Spieler
 * @param posX Zu ueberpruefende Spalte
 * @param posY Zu ueberpruefende Zeile
 * @return ture, wenn der Zug gueltg ist
 */
bool zugGueltig(const int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler, const int posX, const int posY)
{
    int gegner = 3 - aktuellerSpieler; // dasselbe wie: if aktuellerSpieler == 1 -> gegner = 2
                                       //               if aktuellerSpieler == 2 -> gegner = 1

    if (spielfeld[posY][posX] != 0) // ist das Feld leer?
    {
        return false;
    }

    // Alle Richtungen ueberpruefen bis erster gueltiger Zug gefunden
    for (int j = -1; j <= 1; j++)
    {
    	
    	
    	
        for (int i = -1; i <= 1; i++)
        {
        	
        	
        	
            // Prüft ob an der Position ein Stein des Gegners steht (also gültigem Zug)
            if(spielfeld[posY + j][posX + i] == gegner)
            {
            	
                int m = 2;  // Multiplier, um durch den Zug zu gehen

                // While Schleife, die in Richtung des Zuges durchzieht
                while (aufSpielfeld(posY + j * m,posX + i * m) == 1)
                {
                	
                    // Bricht ab, wenn der Feld leer ist (bzw. Zug unterbruchen wird)
                    if(spielfeld[posY + j * m][posX + i * m] == 0)
                    {
                    
                    	
                    	
                    	break;
                    }

                    
                    // Liefert true, wenn ein Stein der Spieler erreicht wurde
                    if(spielfeld[posY + j * m][posX + i * m] == aktuellerSpieler)
                    {
                    
                    	return true;
                    }

                    m++;
                }
            }
        }
    }
    return false;
}


/**
 * @brief Funktion, die einen Zug ausfuehrt
 *
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler Der aktuelle Spieler
 * @param posX Die aktuelle Spalte
 * @param posY Die aktuelle Zeile
 */
void zugAusfuehren(int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler, const int posX, const int posY)
{
    int gegner = 3 - aktuellerSpieler;

    // Stellt den ersten Stein (Stein zu platzieren)
    spielfeld[posY][posX] = aktuellerSpieler;

    //Alle Richtungen bearbeiten
    for (int j = -1; j <= 1; j++)
    {
        for (int i = -1; i <= 1; i++)
        {
            // aehnlich wie die Funktion zugGueltig(), aber stellen Sie sicher, das alle gegnerischen Steine in
            // allen Richtungen in Ihre eigenen Steine umgewandelt werden

            // Prüft ob an der Position ein Stein des Gegners steht (also gültigem Zug)
            if(spielfeld[posY + j][posX + i] == gegner)
            {
                int m = 2;  // Multiplier, um durch den Zug zu gehen

                // While Schleife, die in Richtung des Zuges durchzieht
                while (aufSpielfeld(posY + j * m,posX + i * m) == 1)
                {
                    // Bricht ab, wenn der Feld leer ist (bzw. Zug unterbruchen wird)
                    if(spielfeld[posY + j * m][posX + i * m] == 0)
                    {
                        break;
                    }

                    // Wird angerufen, wenn ein anderen Stein des Spieleres gefunden wurde
                    if(spielfeld[posY + j * m][posX + i * m] == aktuellerSpieler)
                    {
                        // Führt den Pfad zurück, indem es alle Steine des Gegners umwandelt zur Spielers
                        for(int k = m-1; k > 0; k--)
                        {
                            spielfeld[posY + j * k][posX + i * k] = aktuellerSpieler;
                        }

                        break;  // Damit der Stein des Spielers nicht überspringt wird (Steine des Gegners in Richtung danach nicht zu ändern bzw. illegales Spiel)
                    }

                    m++;
                }
            }
        }
    }
}

/**
 * @brief Funktion, die die mögliche Züge ausrechnet
 *
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler Der aktuelle Spieler
 */
int moeglicheZuege(const int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler)
{
    int anzahl = 0;

    // For-loops, um gültige Züge für jedes Position in dem Spielfeld testen
    for (int i = 0; i < GROESSE_Y; i++)
    {
        for (int j = 0; j < GROESSE_X; j++)
        {
            // Prüft, ob einen gültigem Zug gefunden wurde
            if(zugGueltig(spielfeld, aktuellerSpieler, j, i) == true)
                anzahl++;
        }
    }

    return anzahl;
}


bool menschlicherZug(int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler)
{
    if (moeglicheZuege(spielfeld, aktuellerSpieler) == 0)
    {
        return false;
    }

    int posX;
    int posY;
    std::string symbolSpieler;
    if (aktuellerSpieler == 1)
    {
        symbolSpieler = "X";
    }
    else
    {
        symbolSpieler = "O";
    }

    while (true)
    {
        std::string eingabe;
        std::cout << std::endl << "Du bist " << symbolSpieler << ". Dein Zug (z.B. A1, a1): " ;
        std::cin >> eingabe;
        posX = (int) eingabe[0] % 32 -1;
        posY = (int) eingabe[1] - 49;

        if (zugGueltig(spielfeld, aktuellerSpieler, posX, posY))
        {
            //accept turn;
            break;
        }
        else
        {
            std::cout << std::endl << "Ungueltige Eingabe !" << std::endl;
        }
    }

    zugAusfuehren(spielfeld, aktuellerSpieler, posX, posY);
    std::cout << std::endl << "Spieler " << aktuellerSpieler << " setzt auf " << (char) (posX + 65) << (posY + 1) << std::endl;

    return true;
}

/**
 * @brief Funktion, die das Spiel organisiert
 *
 * @param spielerTyp Feld, der das Typ von beide Gegnern bestimmt
 */
void spielen(const int spielerTyp[2])
{
    int spielfeld[GROESSE_Y][GROESSE_X];

    //Erzeuge Startaufstellung
    initialisiereSpielfeld(spielfeld);

    int aktuellerSpieler = 1;
    zeigeSpielfeld(spielfeld);

    // solange noch Zuege bei einem der beiden Spieler moeglich sind ("Or", da die While Loop sich nur, wenn BEIDE Spieler keine mögliche Züge haben, abstürzt)
    while(moeglicheZuege(spielfeld, 1) > 0 || moeglicheZuege(spielfeld, 2) > 0)
    {

        // Fühere Menschliche Zug (und speichere, ob das erfolgreich war)
        //bool erfolgreichesZug = menschlicherZug(spielfeld, aktuellerSpieler);

        bool erfolgreichesZug;

        // Prüfe, ob der Spieler, menschlich oder künstlich ist
        if(spielerTyp[aktuellerSpieler - 1] == COMPUTER)
        {
            // Künstliche Zug
            erfolgreichesZug = computerZug(spielfeld, aktuellerSpieler);
        }
        else
        {
            // Menschlicher Zug
            erfolgreichesZug = menschlicherZug(spielfeld, aktuellerSpieler);
        }

        // Prüfe, ob der Spieler spielen kann
        if(erfolgreichesZug == true)
        {
            // Zeigt den Feld
            zeigeSpielfeld(spielfeld);
        }
        else
        {
            // Informiert, dass der Spieler kein Zug durchführen
            std::cout << "Spieler kann kein Zug führen." << std::endl;
        }

        // Spieler umtauschen / abwechseln (zwischen 1 und 2)
        aktuellerSpieler = 3 - aktuellerSpieler;
    }

    switch (gewinner(spielfeld))
    {
        case 0:
            std::cout << "Unentschieden!" << std::endl << std::endl;
            break;
        case 1:
            std::cout << "Spieler 1 gewinnt!" << std::endl << std::endl;
            break;
        case 2:
            std::cout << "Spieler 2 gewinnt!" << std::endl << std::endl;
            break;
    }

    // Spiel-Zyklus erstellen (Nochmal spielen?)

}

int main()
{
    //if (TEST == 1)
   // {
      //  bool gesamtErgebnis = ganzenTestAusfuehren();
       // if (gesamtErgebnis == true)
      //  {
          //  std::cout << "ALLE TESTS BESTANDEN!" << std::endl;
       // }
        //else
        //{
            //std::cout << "MINDESTENS EIN TEST IST FEHLGESCHLAGEN!" << std::endl;
          //  exit(1);
        //}
        //std::cout << std::endl << std::endl;
    //}

    // Die folgenden drei Zeilen werden auskommentiert oder geloescht, nachdem Sie die Funktion spielen()
    // implementiert haben (waeren sonst doppelt)

    /*
    int spielfeld[GROESSE_Y][GROESSE_X];

    initialisiereSpielfeld(spielfeld);

    zeigeSpielfeld(spielfeld);
     */

    // SpielerTyp Dekleration
    int spielerTyp[2] = { COMPUTER, COMPUTER };
    spielen(spielerTyp);// Feld, das Informationen ueber den Typ des Spielers enthaelt. MENSCH(=1) oder COPMUTER(=2)


    return 0;
}
