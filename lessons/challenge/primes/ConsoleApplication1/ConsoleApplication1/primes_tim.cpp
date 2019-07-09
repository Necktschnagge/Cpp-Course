#include "stdafx.h"

#include "primes.h"
#include "participants.h"
#include <vector>

template <>
void primes<fast_Tim>(unsigned long long upper_bound, std::ostream& os) {

	std::vector<bool> prime_numbers(upper_bound + 1);
	prime_numbers.assign(prime_numbers.size(), true);

	os << 2 << "\n";

	for (decltype(upper_bound) i = 3; i <= upper_bound; i += 2) {

		if (prime_numbers[i] == true) {
			os << i << "\n";

			if (i <= sqrt(upper_bound)) {
				for (int j = pow(i, 2); j <= upper_bound; j = j + i) {

					prime_numbers[j] = false;
				}
			}
		}

	}

}
