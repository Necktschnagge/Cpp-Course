#include <iostream>
#include <string>
#define Umlaute
// Benutzung bedingter Compilierung zum Debugging

#ifdef Umlaute
#include <locale>
#endif //Umlaute

int main(int argc, char* argv[]){
	
	//std::locale::global(std::locale("German"));
	
	int zahl = 0;
	std::string str {"Das ä geht nicht."};
	std::cout << "Wie alt bist du?\n"; // eine simple Ausgabe
	std::cout << str << '\n';
	std::cin >> zahl; // eine simple Eingabe
	
	std::cout << "\nIn 7 Jahren bist du " << 7 + zahl << " Jahre alt." << '\n';
	
	std::cin.get(); // warted auf Enter zum fortfahren.
#ifdef Umlaute
	
#endif //Umlaute
	std::cout << "Was ist mit Ä ä Ö ö Ü ü ß ???" << std::endl;
	
	/*
	Das ist
	ein mehrzeiliger
	Kommentar
	*/
	
	// Das ist ein einzeiliger Kommentar.
	
	return 0;
}
