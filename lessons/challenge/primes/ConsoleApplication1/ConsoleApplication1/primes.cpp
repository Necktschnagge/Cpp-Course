#include "stdafx.h"
#include "primes.h"
#include "participants.h"

#include <vector>
#include <exception>
#include <mutex>
#include <numeric>
#include <limits>
#include <list>
#include <iostream>
#include <algorithm>
#include <execution>

namespace {

	/* parameters: */

	constexpr unsigned short count_threads{ 24 }; //24

	constexpr bool check_agent_start_is_prime_once{ true };

	constexpr bool extract_primes_before_writing_to_stream{ false }; // true is buggy?
}

/* One cell of Sieve of Eratosthenes */
class cell {
	bool crossed;
public:
	inline cell() : crossed(false) {}
	inline void cross() { crossed = true; }
	inline bool is_prime() { return !crossed; }
	inline bool is_no_prime() { return crossed; }
};

template <>
void primes<Tutor0>(unsigned long long upperbound, std::ostream & os)
{
	using int_type = decltype(upperbound);

	const auto size = upperbound + 1;
	const unsigned long long sqrt_size = std::sqrt(size) + 1;
	if (sqrt_size * sqrt_size < size) std::cerr << "numeric error";

	/* Sieve of Eratosthenes */
	std::vector<cell> eratosthenes(size);

	/* Agent who crosses all multiples of start_value, beginning at start_value² */
	auto crosser = [&](const int_type& start_value) {
		int_type position = start_value*start_value;
		if constexpr (check_agent_start_is_prime_once) if (eratosthenes[start_value].is_no_prime()) return;
		while (position < size) {
			if constexpr (!check_agent_start_is_prime_once) if (eratosthenes[start_value].is_no_prime()) return;
			eratosthenes[position].cross();
			position += start_value;
		}
	};

	auto worker = [&](int_type start_value, unsigned short number_of_threads) {
		while (start_value < sqrt_size) {
			crosser(start_value);
			start_value += number_of_threads;
		}
	};

	std::vector<std::thread> threads;
	threads.reserve(count_threads);
	for (unsigned short i = 0; i < count_threads; ++i) {
		threads.emplace_back(std::thread(worker, i + 2, count_threads));
	}

	for (auto& t : threads) t.join();

	if constexpr (extract_primes_before_writing_to_stream) {
		std::vector<std::list<int_type>> results = std::vector<std::list<int_type>>(count_threads);
		auto extractor = [&](unsigned short thread_id) {
			// 2... upperbound
			// 0... upperbound -2
			auto start = thread_id * ((upperbound - 2) / count_threads) + 2;
			auto end = (thread_id + 1) * ((upperbound - 2) / count_threads) + 2;
			if (thread_id == count_threads - 1) end = upperbound; // fix rounding errors;
			for (int_type i = start; i < end; ++i) {
				if (eratosthenes[i].is_prime()) results[thread_id].emplace_back(i);
			}
		};
		threads.clear();
		threads.reserve(count_threads);
		for (unsigned short i = 0; i < count_threads; ++i) {
			threads.emplace_back(std::thread(extractor, i));
		}
		for (auto& t : threads) t.join();

		for (const std::list<int_type>& list : results) for (auto it = list.cbegin(); it != list.cend(); ++it) os << *it << '\n';
	}
	else {
		for (std::size_t i = 2; i < size; ++i) if (eratosthenes[i].is_prime()) os << i << '\n';
	}
}


template <>
void primes<Tutor1>(unsigned long long upperbound, std::ostream & os)
{
	using int_type = decltype(upperbound);

	const auto size = upperbound + 1;
	const unsigned long long sqrt_size = std::sqrt(size) + 1;
	if (sqrt_size * sqrt_size < size) std::cerr << "numeric error";

	/* Sieve of Eratosthenes */
	std::vector<cell> eratosthenes(size);

	unsigned long long next = 1;
	std::mutex m_next;
	auto get_next = [&]() {
		std::lock_guard<std::mutex> lock(m_next);
		++next;
		while (next < size && eratosthenes[next].is_no_prime()) ++next;
		return next;
	};

	/* Agent who crosses all multiples of start_value, beginning at start_value² */
	auto crosser = [&](const int_type& start_value) {
		int_type position = start_value*start_value;
		if constexpr (check_agent_start_is_prime_once) if (eratosthenes[start_value].is_no_prime()) return;
		while (position < size) {
			if constexpr (!check_agent_start_is_prime_once) if (eratosthenes[start_value].is_no_prime()) return;
			eratosthenes[position].cross();
			position += start_value;
		}
	};

	auto worker = [&](int_type start_value, unsigned short number_of_threads) {
		while (start_value < sqrt_size) {
			crosser(start_value);
			start_value = get_next();
		}
	};

	std::vector<std::thread> threads;
	threads.reserve(count_threads);
	for (unsigned short i = 0; i < count_threads; ++i) {
		threads.emplace_back(std::thread(worker, get_next(), count_threads));
	}

	for (auto& t : threads) t.join();

	if constexpr (extract_primes_before_writing_to_stream) {
		std::vector<std::list<int_type>> results = std::vector<std::list<int_type>>(count_threads);
		auto extractor = [&](unsigned short thread_id) {
			// 2... upperbound
			// 0... upperbound -2
			auto start = thread_id * ((upperbound - 2) / count_threads) + 2;
			auto end = (thread_id + 1) * ((upperbound - 2) / count_threads) + 2;
			if (thread_id == count_threads - 1) end = upperbound; // fix rounding errors;
			for (int_type i = start; i < end; ++i) {
				if (eratosthenes[i].is_prime()) results[thread_id].emplace_back(i);
			}
		};
		threads.clear();
		threads.reserve(count_threads);
		for (unsigned short i = 0; i < count_threads; ++i) {
			threads.emplace_back(std::thread(extractor, i));
		}
		for (auto& t : threads) t.join();

		for (const std::list<int_type>& list : results) for (auto it = list.cbegin(); it != list.cend(); ++it) os << *it << '\n';
	}
	else {
		for (std::size_t i = 2; i < size; ++i) if (eratosthenes[i].is_prime()) os << i << '\n';
	}
}


template <>
void primes<Tutor2>(unsigned long long upperbound, std::ostream & os)
{
	std::vector<unsigned long long> v(upperbound + 1);
	v[0] = v[1] = 0;
	std::vector<std::thread> threads;
	threads.reserve(count_threads);

	for (auto i = 0ull; i < v.size(); ++i) {
		v[i] = i;
	}
	for (auto i = 2; i < v.size(); ++i) {
		while (!(v[i]) && i < v.size()) ++i;
		os << i << '\n';
		const auto& prime = i;
		auto i_square = i*i;
		if (i_square < v.size()) {
			std::transform(std::execution::par_unseq, v.begin() + i_square, v.end(), v.begin() + i_square, [&](const unsigned long long& x) { return x * static_cast<bool>(x / prime); });
		}
	}


}