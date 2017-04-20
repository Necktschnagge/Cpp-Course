#include <iostream>
#include <cstdint>

int main(){
	static_assert(sizeof(int)==2,"fehler");
	std::uint16_t a = 5;
	std::cout << "Ausgabe der Zahl a:\n" << a << std::endl;
	return 0;
}
