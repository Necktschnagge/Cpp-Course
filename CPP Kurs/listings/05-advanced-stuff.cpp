// füge folgende Funktionen in das Programm ein und rufe sie auf.
// Ergänze fehlende Implementationen.

// Default-Werte
// Für Funktionsargumenten dürfen Standardparameter angegeben werden. Beispiel:

int Summe(int a, int b, int c = 0, int d = 0){
	return a + b + c + d;
}


// Funktionen können überladen werden:
int Summe(double a, double b){
	return a + b;
}

int Summe(const double* pa, const double* pb){
	// schreib das selbst
}


//inline
// Dem Compiler wird vorgeschlagen, die Funktion an Ort und Stelle des Aufrufs auszurollen anstatt aufzurufen
inline void printdbl(const double& d){
	std::cout << d;
}


//static:
// Als static deklarierte Funktions-lokale Variablen bleiben beim Verlassen der Funktion
// diese Objekte werden nicht auf dem Stack, sondern global gespeichert.
// die Initialisierung wird nur beim ersten Aufruf ausgeführt
std::string& sammeln(const std::string& additional){
	static std::string s {};
	s = s + additional;
	return s;
}

// das hier ist nicht erlaubt!!!
int& differenz(int m, int s){
	int d = m - s;
	return d;
} // d, worauf eine Referenz zurückgegeben wurde wird beim Verlassen der Funktion ungültig.


// auto und decltype: statische Typinferenz
auto kgV(unsigned int x, unsigned int y) -> decltype(x*y){
		// implementiert das selbst
}
