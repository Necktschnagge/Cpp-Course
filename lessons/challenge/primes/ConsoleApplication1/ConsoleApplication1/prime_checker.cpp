#include "stdafx.h"
#include "prime_checker.h"
#include <string>
#include <future>
#include <numeric>


prime_checker::prime_checker()
{
	known_primes.push_back(2);
	checked_bound = 2;
}

bool prime_checker::check(std::istream & source, unsigned long long upperbound)
{
	try {
		decltype(known_primes)::iterator next_known_prime{ known_primes.begin() };

		while (!source.eof()) {
			std::string line;
			std::getline(source, line);
			if (line == "") break;
			const unsigned long long next_prime_candidate{ std::stoull(line) };

			if (next_known_prime != known_primes.end()) {
				// simply check whether prime candidate is the next known prime
				if (next_prime_candidate != *next_known_prime++) return false;
			}
			else {
				// explicitly check whether the candidate is the next prime number
				auto last_prime = known_primes.back();
				std::list<std::future<bool>> check_results;

				// checks that no prime number has been skipped
				for (unsigned long long no_prime_candidate = std::max(last_prime + 1, checked_bound + 1); no_prime_candidate < next_prime_candidate; ++no_prime_candidate) {
					auto check = [no_prime_candidate, this]{ 
						for (const auto& prime : this->known_primes)
							if (!(no_prime_candidate % prime)) return true; // found divider
						return false;
					};
					check_results.emplace_back(std::async(std::launch::async,check));
				}

				// checks that prime candidate is really prime
				auto check = [this, next_prime_candidate] { 
					for (const auto& prime : this->known_primes)
						if (!(next_prime_candidate % prime)) return false; // found divider
					return true;
				};
				check_results.emplace_back(std::async(check));

				bool is_correct = std::accumulate(check_results.begin(), check_results.end(), true, [](bool l, std::future<bool>& r) { return l && r.get(); });

				if (is_correct){
					known_primes.push_back(next_prime_candidate);
					checked_bound = std::max(checked_bound, next_prime_candidate);
				}
				else return false;
			}
		}
		// check that no prime number is missing at the end.
		std::list<std::future<bool>> check_results;
		for (unsigned long long no_prime_candidate = checked_bound + 1; no_prime_candidate <= upperbound; ++no_prime_candidate) {
			auto check = [no_prime_candidate, this] {
				for (const auto& prime : this->known_primes)
					if (!(no_prime_candidate % prime)) return true; // found divider
				return false;
			};
			check_results.emplace_back(std::async(check));
		}
		bool is_correct = std::accumulate(check_results.begin(),
			check_results.end(),
			true,
			[](bool l, std::future<bool>& r) { return l && r.get(); });
		
		if (!is_correct) return false;
		checked_bound = std::max(checked_bound, upperbound);
	} catch (...) {
		return false;
	}

	return true;
}


prime_checker::~prime_checker()
{
}
