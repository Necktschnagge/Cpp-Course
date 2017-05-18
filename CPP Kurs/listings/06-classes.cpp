// Learning - By - Doing File


#include <string>
#include <iostream>
#include <vector>


#if false
Wozu Klassen ?
Funktionen direkt an die Daten binden(Methoden)
Sichtbarkeiten : public, protected, private
	neue, komplexere Datentypen erstellen.
	Kapselung, Vererbung, Polymorphie.
	abgesicherte Zustände,
#endif

	// Klassendeklaration := mindestens der Name der Klasse wird bekannt gemacht.
struct A;
class Datum;

	// Klassendefinition := Angabe aller Datenmember und Deklaration aller Methoden.
struct A {
	/* per default public:*/
	int x;
	int y;
private:
	int z;
public:
	int get_z();
};


class Datum {
	/* per default private */
	int jahr;
	short monat;
	short tag;
public:
	Datum(short jahr, short monat, short tag); // Konstruktordeklaration

	// Diese drei Funktionen sind selbst zu implementieren:
	std::string get_date(); // Objektmethode
	void set_date(int jahr, short monat, short tag);
	void next_day();
};

// Objektattribute und Klassenattribute..
// Klassenattribute/ -methoden : existieren einmal für die Klasse, sind an keine Instanz gebunden

class B {
	static unsigned int count;
	// weitere Attribute:
	const char* x;
	int y;
public:
	// Was ist ein Standardkonstruktor?

	static void init_count() {
		count = 0;
	}

	static unsigned int get_count() {
		return count;
	}

	// Elementinitialisierer:
	B() : x(nullptr), y(100) {
		++count;
	}

	~B() { // Destruktor
		--count;
	}
};



int main()
{
    //Instanz (also ein Obkjekt) der Klasse B erstellen:
	Datum datum(2017,5,18);

	{
		using namespace std;
		B::init_count();
		cout << B::get_count();
		B b, c, d;
		cout << B::get_count();
		std::vector<B> vec(0);
		while (B::get_count() < 10) {
			vec.emplace_back();
		}
	}

	return 0;

}
/*
// new und delete

// The Big Three:
	Kopierkonstruktor
	Zuweisungsoperator
	Destruktor
// oder besser: die großen Fünf:
	Move-Konstruktor
	Move-Zuweisungsoperator

	
// Konvertierungskonstruktor und explicit
	Konstruktoren, die genau einen Parameter entgegen nehmen
	implizite Konvertierung verhindern mit 
	


// const Methoden
// inline, implizit / explicit
// this - Zeiger

// friend Funktionen

// operator Überladung

	*/


