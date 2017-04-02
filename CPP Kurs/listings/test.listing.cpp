#include <iostream>

int main(int argc, char* argv[])
// main-Funktion: Einstiegspunkt der Anwendung
// count: Anzahl der uebergebenen Parameter
// arg: Pointer auf ein Array von Pointern auf C-Style-Strings (die Parameter)
// Parameter der main-Funktion duerfen in der Signatur auch weggelassen werden.

// Parameter der main-Funktion
{   // Beginn vom Anweisungsblock der main-Funktion

	std::cout << "Hello World" << std::endl;
	/*
	* implizite Klammerung:
	* ((std::cout) << "Hello World") << (std::endl);
	* std              ... ein Namensraum
	* ::               ... scope-Operator (Bereichsoperator)
	* cout:            ... gepufferter Standardausgabestream
	* <<               ... Ausgabeoperator (auch bitshift-Operator)
	* "Hello World"    ... C-Style-String Literal
	* endl             ... Objekt aus dem std Namensraum, das einen Zeilenumbruch ('\n') erzeugt.
	* ;                ... Abschluss einer einzelnen Anweisung
	*/

	for(int i = 0; i < argc; ++i ){
		std::cout << i << ". Parameter:  " << argv[i] << '\n';
	} // Beipiel fuer die Ausgabe der Komandozeilenargumente
	// argv[0] ist der Name der executable Datei

	return 0; // Rueckgabewert 0 "erfolgreich (ohne Fehler) beendet"
}
