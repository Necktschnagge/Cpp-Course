#include <iostream>
#include <cstdint>

int main(){
	static_assert(sizeof(int)==1,"int ist nicht 1 Byte gross");
	uint8_t a = 5;

	int b {4};
	int* pb {&b};

	int& c {b};
	c = 7;

	std::cout << b << '\n';

	std::cout << "Ausgabe der Zahl a:\n" << static_cast<int>(a) << std::endl;
	return 0;
}
