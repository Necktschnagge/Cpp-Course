#if false

***************************************************************
WHY FUNCTIONS?
	- Zerlegung von Aufgaben in Teilaufgaben
	- Wiederverwendung von Programmcode: Funktionen können beliebig oft aufgerufen werden
	- Schaffung von Schnittstellen, (...neben Klassen)

HOW DO THEY WORK?
	- Parameterargumente werden bei Auruf aus den angegebenen Ausdrücken (Expressions) berechnet.
	- Neuer Platz wird auf dem Stack (Activation Record) "allokiert" und initialisiert mit übergebenen Werten
	- übergebene Werte werden immer kopiert
	- Funktion wird ausgeführt
	- Funktion schreibt Ergebnis (es sei denn void Funktion) auf den Stack zurück.
	- Funktion kehrt mit return [value]; an Stelle des Aufrufes zurück.
***************************************************************
Zusatzwissen:

	Randfälle:
	- Man kann keine Funktionen lokal in Funktionen definieren.
			-> // Aber dafür gibt es sog. Funktoren: Man erstelle eine Klasse mit einer entsprechenden Methode, meist dem operator ()
			- Es gibt auch lambda Funktionen in C++

	Was ist Rekursion?
	Was ist dynamische Programmierung?
	rohe Arrays an Funktionen übergeben?
	Objekte an Funktionen übergeben?
***************************************************************
#endif



#include <iostream>
#include <string>
#include <iostream>

//#define aufgabe

//Funktion deklarieren:
// [Spezifizierer] Rückgabetyp Funktionsname(Parameterliste);
char einZeichen(const char* string, unsigned int position); // Nur-Deklaration

// Funktion definieren
char einZeichen(const char* string, unsigned int position){
	std::string s {string};
	if ((position > s.size()) || (position < 1) ){
		return ' ';
	}
	return string[position-1];
	// return Anweisung für beenden der Funktion und (hier) Rückgabe eines Wertes.
}





// Der Rückgabetyp void ist der leere Datentyp und wird verwendet, wenn keine Rückgabe erfolgt.
// Referenz auf ein konstantes Objekt
#ifdef aufgabe
	/* gibt my_string auf std::cout aus */
void gibStringAus(const std::string& my_string){


}
#endif
// diese Funktion sollt ihr einmal selbst implementieren




int getVersion(); // in C++ ist es (im Gegensatz zu C) gleichwertig () oder (void) zu schreiben.
// implementation kommt weiter unten...



// neue Funktionssyntax von C++11:
auto ggT(unsigned int a, unsigned int b) -> int {
	if (getVersion() < 500 ) exit (1); // getVersion darf verwendet werden, denn ist schon deklariert
	if (b == 0) {
		if (a==0) exit(2); // ggT von (0,0) nicht definiert oder unendlich.
		return a;
	}
	return ggT(b, a % b);
}

#ifdef aufgabe
// Anwendung von Referenzen:
	// x wird halbiert und true wird zurück gegeben, falls x gerade ist.
	// Falls x ungerade, wird false zurückgegeben und x nicht geändert.
bool halbiere(int& x){

}
	// Diese Funktion soll auch selbst implementiert werden.
#endif

int getVersion(){
	return 1000;
}



int main(){
	const char* beispiel_cstr = "Wir verwenden jetzt professionell Funktionen.";
	char bsp2[] = "Wir testen das jetzt aus.";

	std::cout << einZeichen(beispiel_cstr, 1) << einZeichen(bsp2, 5) << '\n';
	std::cout << ggT(18,21) << "   " << ggT(250,175) << "\n\n\n\n";

	std::string cppstr {bsp2};
#ifdef aufgabe

	// Rufe deine Funktionen mal auf
	// Teile 6:2, 7:3, 8:4, 9:5


#endif

}
