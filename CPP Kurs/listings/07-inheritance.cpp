
#include <string>
#include <iostream>
#include <vector>
#include <array>

using std::vector;
using std::cout;
using std::cin;
using std::array;

class vehicle {

private:

	const unsigned int max_personen;
	const std::string farbe;
	
protected:

	array<double, 2> position;
	array<double, 2> velocity;
	// array<double, 2> acceleration;	

public:

	/* Konstruktordelegation */

	/* erstelle einen Konstruktor der Koordinaten x,y entgegen nimmt.
		Erstelle dann einen Standardkonstruktor, der x=0, y=0 setzt und dabei an den ersten Konstruktor delegiert. */

		/* setzt die Position auf gegebene Koordinaten. Setzt Geschwindigkeit und Beschleunigung auf 0. */
	void set_position(double x, double y);

	void set_velocity(/*...*/); // virtuell machen

	// auto get_position ... const 

	auto operator () (double time) -> const decltype(position)& {
		/* beweg dich! */
		return position;
	}


	// noise - Funktion (rein virtuell) gibt string zurück.

};


/* Auto, Fahrrad und Pferd */

/*
	auto:
		Motor-Leistung
		Batteriespannung
		Hersteller

	fahrrad:
		Raddurchmesser
		elektrisch (ja, nein)

	Pferd:
		Alter
		Mutter
		Rasse

*/

int main() {
	
}

/*
Inhalt der Stunde:

Wiederholung

Sichtbarkeiten

Vererbung

Vererbungsmodi

Vererbte Daten und Methoden

override

Zuweisung / Konstruktor zwischen "verwandten" Klassen

Basisklassenzeiger

Verhalten von Methoden bei Basisklassenzeiger

virtuelle Methoden

Sichtbarkeiten und virtual

*/