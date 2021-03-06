// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "primes.h"
#include "participants.h"
#include "prime_checker.h"

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <functional>
#include <map>
#include <algorithm>
#include <set>
#include <filesystem>

auto measure_duration(const std::function<void()>& f, const std::string& label, const std::string& indent){
	std::cout << indent << "Start measure   \"" << label << "\"\n";
	std::chrono::steady_clock::time_point before_f{ std::chrono::steady_clock::now() };
	f();
	std::chrono::steady_clock::time_point after_f{ std::chrono::steady_clock::now() };
	std::cout << indent << "End measure.\n";
	auto result{ after_f - before_f };
	std::cout << indent << "Took " << std::chrono::duration_cast<std::chrono::milliseconds>(result).count() << "ms\n\n";
	return result;
}

struct ratings {
	std::map<unsigned long long, std::vector<std::chrono::duration<long long, std::nano>>> measures;
	std::map<unsigned long long, long double> averages;
	std::set<unsigned long long> failures;
};


int main(int count, char** args)
{
	std::cout << "Hello.\n";

	// configs:
	constexpr int number_of_redundand_measures{ 3 };
	constexpr unsigned long long global_bound{ 10'000'000'001 };
	constexpr long double time_bound{ 300'000'000'000 }; // 300 seconds;
	constexpr bool enable_checker{ false };
	const std::string file_name{ "D:\\ram volatile dynamic\\primes.txt" };
	//const std::string file_location{ "C:\\Users\\F-NET-ADMIN\\Desktop\\test\\" };
	//const std::string file_name{ "primes.txt" };
	//unsigned long long file_counter{ 0 };
	
	// participants' solutions:
	std::map<std::string, void(*)(unsigned long long, std::ostream&)> solutions;

	solutions["Tutor0  "] = primes<Tutor0>;
	solutions["Tim_fast"] = primes<fast_Tim>;
	solutions["Tutor1  "] = primes<Tutor1>;

	
	// results:
	std::map<std::string, ratings> participants_mapped_to_ratings;
	std::vector<unsigned long long> bounds;

	// checker:
	prime_checker checker;

	
	// measure:
	for (unsigned long long current_bound = 2; current_bound < global_bound;
		current_bound = current_bound * 3 / 2 < global_bound ?
		current_bound * 3 / 2 : std::max(current_bound + 1, global_bound - 1)) {
		std::cout << "Start measures for upper bound  " << current_bound << " :" << std::endl;
		bounds.push_back(current_bound);

		for (const auto& solution : solutions) {
			auto& name{ solution.first };
			auto& function_ptr{ solution.second };

			std::cout << "\tStart measures for participant " << name << " :" << std::endl;
			// check skipping! ##

			if (!participants_mapped_to_ratings[name].averages.empty())
				if (std::max_element(participants_mapped_to_ratings[name].averages.cbegin(), participants_mapped_to_ratings[name].averages.cend())->second > time_bound)
					continue;

			for (int i = 0; i < number_of_redundand_measures; ++i) {
				// calculate prime numbers:
				const std::string this_file_name = file_name; // file_location + std::to_string(++file_counter) + file_name;
				std::ofstream s;
				s.open(this_file_name);
				auto calc = [&] { function_ptr(current_bound, s); };
				auto label = std::string("for ") + name;
				participants_mapped_to_ratings[name].measures[current_bound].push_back(measure_duration(calc, label, "\t\t"));
				s.close();
			
				// verify:	
				if constexpr (enable_checker) {
					std::ifstream t(this_file_name);
					measure_duration([&] {
						if (!checker.check(t, current_bound)) participants_mapped_to_ratings[name].failures.insert(current_bound);
					}, "for checker", "\t");
					t.close();
				}

				// delete file:
				auto path = std::experimental::filesystem::path(this_file_name);
				if (!std::experimental::filesystem::remove(path)) std::cerr << "error delete file\n";
				
			}
			long double sum{ 0 };
			for (const auto& measure : participants_mapped_to_ratings[name].measures[current_bound]) {
				sum += static_cast<long double>(measure.count());
			}
			participants_mapped_to_ratings[name].averages[current_bound] = sum / number_of_redundand_measures;
		}
	}
	std::cout << "\n\n\n\n------------------\n TABLE OF RESULTS\n------------------\n\n";
	std::cout << "\n\nParticipants with failures: \n\n";
	for (const auto& pair : participants_mapped_to_ratings) {
		const auto& name = pair.first;
		const auto& rating = pair.second;

		if (!rating.failures.empty()) {
			std::cout << "\t" << name << ":\n";
			for (const auto& b : rating.failures) std::cout << b << ' ';
			std::cout << std::endl;
		}
	}

	std::cout << "\n\nAverages: \n\n";
	for (const auto& bound : bounds) {
		std::cout << "Measures for upperbound  " << bound << ":\n";
		for (const auto& pair : participants_mapped_to_ratings) {
			const auto& name = pair.first;
			const auto& rating = pair.second;

			std::cout << "\t" << name << "  :  ";
			if (rating.averages.find(bound) != rating.averages.end()) {
				std::cout << rating.averages.at(bound) / 1'000'000 << "ms";
			}
			else {
				std::cout << "not measured";
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;

	std::cout << "Bye.\n";
    return 0;
}

