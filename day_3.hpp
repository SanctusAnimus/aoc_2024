#ifndef AOC_DAY_3
#define AOC_DAY_3


#include "solution.hpp"
#include <regex>

class Day3 : public Solution<Day3> {
public:
	Day3() {
		day_num = 3;

		p1_expected = 157621318;
		p2_expected = 79845780;

		resolve_benchmark_tries = 100;
	};

	using Result_T = std::pair<long int, long int>;


	Result_T _get_solutions(SolutionInput_T solution_input) {
		size_t cursor = 0;

		std::string& source = solution_input[0];
		size_t size = source.size();
		const char* ptr = source.data();

		long int p1 = 0;
		long int p2 = 0;

		auto regex_start = chrono::high_resolution_clock::now();

		std::regex tokenRegex(R"(do\(\)|don't\(\)|mul\(\d{1,3},\d{1,3}\))");
		auto begin = std::sregex_iterator(source.begin(), source.end(), tokenRegex);
		auto end = std::sregex_iterator();

		auto regex_end = chrono::high_resolution_clock::now();
		Duration_T time_resolving = regex_end - regex_start;
		std::cout << "regex took " << time_resolving.count() << "ms" << std::endl;

		bool p2_enabled = true;

		auto loop_start = chrono::high_resolution_clock::now();

		for (auto& it = begin; it != end; ++it) {
			std::string token = it->str();
			// std::cout << "Processing " << token << " at position " << it->position() << std::endl;

			if (token == "do()") p2_enabled = true;
			else if (token == "don't()") p2_enabled = false;
			else {
				int parsed_left, parsed_right;
				size_t position = it->position() + 4;

				auto [left_ptr, ec] = std::from_chars(ptr + position, ptr + position + 4, parsed_left);
				std::from_chars(left_ptr + 1, left_ptr + 4, parsed_right);
				long int result = parsed_left * parsed_right;
				// std::cout << "mul( " << parsed_left << " * " << parsed_right << " " << source[position] << std::endl;
				p1 += result;

				if (p2_enabled) p2 += result;
			}
		}

		auto loop_end = chrono::high_resolution_clock::now();
		Duration_T time_looping = loop_end - loop_start;
		// std::cout << "loop took " << time_looping.count() << "ms" << std::endl;

		return { p1, p2 };
	}
};


#endif