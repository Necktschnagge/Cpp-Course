#include <iostream>


#define debug // Benutzung bedingter Compilierung zum Debugging

int main(int argc, char* argv[]){
	
	int zahl = 0;
	std::cout << "Wie alt bist du?\n"; // eine simple Ausgabe
	std::cin >> zahl; // eine simple Eingabe
	std::cout << "Okay!\n\n";
	
#ifndef debug 
	//folgende Zeile compiliert nicht:
	std::cout << << "In 7 Jahren bist du " << 7 + zahl << " Jahre alt." << '\n';
#endif //debug
	
	std::cout << "Tsch" << static_cast<char>(0x81) << "ss\n";
	//https://de.wikipedia.org/wiki/Codepage_850
	
	std::cin.sync();
	std::cin.get(); // warted auf Enter zum fortfahren.
	
	/*
	Das ist
	ein mehrzeiliger
	Kommentar
	*/
	
	// Das ist ein einzeiliger Kommentar.
}
