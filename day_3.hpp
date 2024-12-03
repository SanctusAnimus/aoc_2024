#ifndef AOC_DAY_3
#define AOC_DAY_3


#include "solution.hpp"
#include <re2/re2.h>

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

		bool p2_enabled = true;

		std::string token, num1, num2;
		re2::StringPiece input_sp(source);

		RE2 re("(do\\(\\)|don't\\(\\)|mul\\((\\d{1,3}),(\\d{1,3})\\))");

		if (!re.ok()) {
			std::cerr << "Invalid regex: " << re.error() << std::endl;
		}

		while (!input_sp.empty()) {
			size_t match_start = source.size() - input_sp.size(); // Get match start position

			if (RE2::FindAndConsume(&input_sp, re, &token, &num1, &num2)) {
				if (token == "do()") {
					p2_enabled = true;
				}
				else if (token == "don't()") {
					p2_enabled = false;
				}
				else {
					int parsed_left, parsed_right;
					std::from_chars(num1.data(), num1.data() + num1.size(), parsed_left);
					std::from_chars(num2.data(), num2.data() + num2.size(), parsed_right);
					long int result = parsed_left * parsed_right;
					p1 += result;

					if (p2_enabled) p2 += result;
				}
			}
			else {
				break;
			}
		}

		return { p1, p2 };
	}
};

#endif