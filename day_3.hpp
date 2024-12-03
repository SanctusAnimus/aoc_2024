#ifndef AOC_DAY_3
#define AOC_DAY_3


#include "solution.hpp"

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
		std::string& source = solution_input[0];
		size_t size = source.size();
		const char* ptr = source.data();

		long int p1 = 0;
		long int p2 = 0;

		bool p2_enabled = true;

		size_t cursor = 0;

		do {
			size_t mul_pos = source.find("mul(", cursor);
			size_t do_pos = source.find("do()", cursor);
			size_t dont_pos = source.find("don't()", cursor);

			if (mul_pos == std::string::npos) break;

			size_t closest_pos = std::numeric_limits<size_t>::max();
			std::string closest_token;

			if (mul_pos < closest_pos) {
				closest_pos = mul_pos;
				closest_token = "mul(";
			}
			if (do_pos != std::string::npos && do_pos < closest_pos) {
				closest_pos = do_pos;
				closest_token = "do()";
			}
			if (dont_pos != std::string::npos && dont_pos < closest_pos) {
				closest_pos = dont_pos;
				closest_token = "don't()";
			}

			cursor = closest_pos + 1;

			if (closest_pos != std::numeric_limits<size_t>::max()) {
				if (closest_token == "do()") p2_enabled = true;
				else if (closest_token == "don't()") p2_enabled = false;
				else {
					// validate mul
					closest_pos += 4; // step over "mul(" to first num
					int num1 = 0, num2 = 0;
					size_t comma_pos = source.find(',', closest_pos);

					if ((comma_pos - closest_pos) > 4) continue;

					size_t close_pos = source.find(')', comma_pos);

					if ((close_pos - comma_pos) > 4) continue;

					std::from_chars(ptr + closest_pos, ptr + comma_pos, num1);
					std::from_chars(ptr + comma_pos + 1, ptr + close_pos, num2);

					long int result = num1 * num2;
					p1 += result;
					if (p2_enabled) p2 += result;
				}
			}
		} while(cursor < size);

		return { p1, p2 };
	}
};

#endif