#include "stdafx.h"

#include <string>
#include <iostream>
#include <vector>


#if false
Wozu Klassen ?
Funktionen direkt an die Daten binden(Methoden)

Sichtbarkeiten : public, protected, private
	neue, komplexere Datentypen erstellen.
	Kapselung, Vererbung, Polymorphie.
	abgesicherte Zustände
#endif

	// Klassendeklaration := mindestens der Name der Klasse wird bekannt gemacht.
struct A; // auch Nur-Deklaration oder Vorausdeklaration oder Forward-Deklaration genannt
class Datum;
union U;

	// Klassendefinition := Angabe aller Datenmember und Deklaration aller Methoden.
	// Ist eine spezielle Deklaration
struct A {
	/* per default public:*/
	int x;
	int y;

private:
	/* explizit private */
	int z;
public:
	/* explizit public */
	int get_z();
};


class Datum { // nur zur Demonstration. Unser virtuelles Jahr besteht aus genau 12 Monaten mit jeweils genau 30 Tagen.
	/* per default private */
	int jahr;
	short monat;
	short tag;
public:
	/* explizit public */
	Datum(short jahr, short monat, short tag) : jahr(jahr), monat(monat), tag(tag) {
		if ((tag > 30) || (tag <= 0))
			tag = 1;
		if ((monat > 12) || (monat <= 0))
			monat = 1;
	}; // Konstruktordeklaration und -definition

	std::string get_date() const {
		return std::to_string(tag) + std::string(". ") + std::to_string(monat) + std::string(". ") + std::to_string(jahr);
	}; // eine Objektmethode

	void set_date(int jahr, short monat, short tag) {
		// to be done...
	}

	void next_day() {
		++tag;
		if (tag > 30) {
			tag = 1;
			++monat;
			if (monat > 12) {
				monat = 1;
				++jahr;
			}
		}
	};
};

// Objektattribute und Klassenattribute..
// Klassenattribute/ -methoden : existieren einmal für die Klasse, sind an keine Instanz gebunden
// werden mit Schlüsselwort static deklariert.

class CountedClass {
	// Wir wollen eine Klasse zu irgendeinem jetzt noch irrelevanten Zweck schreiben und wollen zu jeder Zeit wissen, wie viele Objekte von unserer Klasse existieren.

	static unsigned int count; // der Zähler, der angibt, wie viele Objekte existieren.
			// static macht count zu einem Klassenattribut. Es existiert nur einmal für die ganze Klasse und nicht für jedes Objekt einzeln.

	// weitere Attribute nur als Dummy: 
	const char* x{nullptr};

	int y;

public:
	
	// Was ist ein Standardkonstruktor?
	// -> Konstruktor der keine Parameter entgegennimmt.

	// Nutzung vom Elementinitialisierer:
	CountedClass() : x(nullptr), y(100) {
		++count;
	}


	static void init_count() {
		count = 0;
	}

	static unsigned int get_count() {
		return count;
	}

	~CountedClass() { // Destruktor
		--count;
	}
};

unsigned int CountedClass::count{ 0 };


// Jetzt schreiben wir einen Container, der über einen Pointer sich einen String im Hintergrund hält.
// Dazu implementieren wir die Move-Semantik und Copy-Operationen
class Container {

	std::string* ptr; // private Pointer auf den String

public:

	std::string& getRef() const { //Getter für eine Referenz (LValue) auf den String im Container.
		return *ptr; 
	}

	Container() { // Standardkonstruktor, erstellt im Hintergrund einen neuen leeren String
		ptr = new std::string(); 
	}

	// Destruktor. Wird automatisch aufgerufen, wenn das Objekt seinen Gültigkeitsbereich verlässt bzw. sein Speicher freigegeben wird.
	~Container() { // Vom Heap reservierte Speicherbereiche müssen wieder freigegeben werden, wenn das Objekt zerstört wird (Destructor)
		delete ptr;
	}

	// Copy-Constructor: Wir erstellen eine Kopie des Objektes
	Container(const Container& c) {
		ptr = new std::string(c.getRef());
	}

	// Move-Constructor: Wir erstellen ein neues Objekt und reichen sämtliche Pointer weiter.
	// alles, was im Hintergrund befindlich ist, wird nicht kopiert,
	// sondern das neue Objekt bekommt die bereits an einer anderen Stelle reservierten Speicherbereiche zugewiesen.
	Container(Container&& c) {
		ptr = c.ptr;
		c.ptr = new std::string("weggemoved"); // zur Demonstration
	}

	// Konvertierungskonstruktor: Das sind Konstruktoren, welche genau einen Parameter nehmen.
	// Hier im Beispiel wird quasi ein String zu einem Container "konvertiert".
	explicit Container(const std::string& str) {
		ptr = new std::string(str);
	}

	// Move-Konvertierungskonstruktor
	Container(std::string&& str) {
		ptr = new std::string(std::move(str));
		// Wir erstellen einen neuen String mit dessen Movekonstruktor aus dem alten String.
		// Aus dem alten String wird dabei ein leerer String, weil der Movekonstruktor von std::string so implementiert ist.
	}

	// Wenn man eine von C++ automatisch bereitgestellte Methode verbieten will, nutzt man (seit C++11):
	//const Container& operator = (const Container&) = delete;

	// Copy-Zuweisungsoperator
	const Container& operator = (const Container& c) {
		delete ptr;
		ptr = new std::string(c.getRef());
		return *this;
	}

	// Move-Zuweisungsoperator:
	const Container& operator = (Container&& c) {
		delete ptr;
		ptr = c.ptr;
		c.ptr = new std::string("weggemoved");
		return *this;
	}

};




int main()
{
    //Instanz (also ein Obkjekt) der Klasse CountedClass erstellen:
	Datum datum(2017,5,18);
	datum.next_day();
	std::cout << datum.get_date() << std::endl;
	

	CountedClass::init_count();

	CountedClass * ptr = new CountedClass();

	{
		using namespace std;
		cout << CountedClass::get_count();
		CountedClass b, c, d;
		cout << CountedClass::get_count();
		std::vector<CountedClass*> vec(0);
		while (CountedClass::get_count() < 10) {
			vec.push_back(new CountedClass());
			cout << "\n neues Objekt angelegt! \n" << CountedClass::get_count() << "\n";
		}
	}
	
	Container cont;
	cont.getRef() = "blabla";
	Container cont2(cont);
	std::cout << cont2.getRef() << std::endl;
	Container cont3 = cont2;
	cont3.getRef() = "nicht blabla";
	cont2 = std::move(cont3);
	std::cout << cont2.getRef() << '\n' << cont3.getRef() << '\n' ;
	std::string str("Heute ist nur Hannes gekommen.");
	Container cont4 = static_cast<Container>(str);
	std::cout << cont4.getRef() << "###" << str << "###";

	std::cin.get();

	return 0;

}

/*
************** Stichworte zu den Kommentaren der Stunde *********************

// new und delete

// The Big Three:
	Kopierkonstruktor
	Zuweisungsoperator
	Destruktor
	// Von diesen dreien stellt C++ eine Standardversion zur Verfügung.

// oder besser: die großen Fünf:
	Move-Konstruktor
	Move-Zuweisungsoperator

	"Brauchst du einen, brauchst du alle"
	~ Wenn man einen selbst implementieren musste / hat, muss man dies auch mit den anderen tun.
	
	
	
// Konvertierungskonstruktor und explicit
	Konstruktoren, die genau einen Parameter entgegen nehmen
	implizite Konvertierung verhindern mit dem Schlüsselwort explicit
	


// const Methoden
// inline, implizit / explicit
// this - Zeiger

// friend Funktionen

// operator Überladung

	*/
