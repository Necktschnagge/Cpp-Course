#include <iostream>
#include <cstdint>

int main(){
	static_assert(sizeof(int)==4,"fehler");
	uint16_t a = 5;
	std::cout << "Hello World und eine Zahl:\n" << a << std::endl;
	return 0;
}