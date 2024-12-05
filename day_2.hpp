#ifndef AOC_DAY_2
#define AOC_DAY_2

#include "solution.hpp"

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

class Day2 : public Solution<Day2> {
public:
	Day2() {
		day_num = 2;

		p1_expected = 663;
		p2_expected = 692;

		resolve_benchmark_tries = 1000;
	};

	using Result_T = std::pair<int, int>;

	bool process_p2_bruteforce(std::vector<int>& source_nums) {
		size_t source_size = source_nums.size();

		// yay o(n2) - but this way we don't allocate vector copies
		for (int ignored = 0; ignored < source_size; ignored++) {
			int prev_number = -1;
			int prev_sign = -2;

			bool report_correct = true;
			for (int i = 0; i < source_size; i++) {
				if (i == ignored) {
					continue; // skip ignored from processing
				}
				int num = source_nums[i];

				if (prev_number == -1) prev_number = num;
				else {
					int difference = num - prev_number;
					int sign = sgn(difference);

					if (prev_sign == -2) prev_sign = sign;
					else {
						if (prev_sign != sign) {
							report_correct = false;
							break;
						}
					}

					if (difference == 0 || abs(difference) > 3) {
						report_correct = false;
						break;
					}

					prev_sign = sign;
					prev_number = num;
				}
			}

			// this permutation is correct with 1 num skipped
			if (report_correct) return true;
		}

		return false;
	}

	Result_T _get_solutions(SolutionInput_T solution_input) {
		int p1_total = 0;
		int p2_total = 0;

		for (const auto& line : solution_input) {
			int p1_prev_number = -1;
			int p1_prev_sign = -2;

			const char* parse_ptr = line.data();
			const char* line_end = parse_ptr + line.size();

			bool p1_report_correct = true;
			bool p2_report_correct = true;

			std::vector<int> nums = {};

			do {
				int parsed;
				auto [ptr, ec] = std::from_chars(parse_ptr, line_end, parsed);
				parse_ptr = ptr + 1;
				nums.push_back(parsed);

				if (p1_prev_number == -1) p1_prev_number = parsed;
				else {
					int difference = parsed - p1_prev_number;
					int sign = sgn(difference);

					if (p1_prev_sign == -2) p1_prev_sign = sign;
					else {
						if (p1_prev_sign != sign) {
							p1_report_correct = false;
						}
					}

					if (difference == 0 || abs(difference) > 3) {
						p1_report_correct = false;
					}

					p1_prev_sign = sign;
					p1_prev_number = parsed;
				}
			} while (parse_ptr < line_end);

			// if p1 is correct, p2 is automatically correct too
			if (!p1_report_correct)
				p2_report_correct = process_p2_bruteforce(nums);

			if (p1_report_correct) p1_total++;
			if (p2_report_correct) p2_total++;
		}

		return { p1_total, p2_total };
	}
};

#endif