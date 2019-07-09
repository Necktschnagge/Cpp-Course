#pragma once

#include <istream>
#include <list>

class prime_checker
{
	std::list<unsigned long long> known_primes;

	unsigned long long checked_bound;

public:
	prime_checker();

	bool check(std::istream& source, unsigned long long upperbound);

	~prime_checker();
};

