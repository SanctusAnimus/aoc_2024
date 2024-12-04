#ifndef AOC_DAY_4
#define AOC_DAY_4


#include "solution.hpp"

class Day4 : public Solution<Day4> {
public:
	Day4() {
		day_num = 4;

		p1_expected = 2336;
		p2_expected = 1831;

		resolve_benchmark_tries = 1000;
	};

	using Result_T = std::pair<long int, long int>;

	bool verify_char_at(int target_line, int target_char, const char expected_char, SolutionInput_T input) {
		size_t input_size = input.size();
		size_t line_size = input[0].size();

		if (target_line < 0) return false;
		if (target_line >= input_size) return false;
		if (target_char < 0) return false;
		if (target_char >= line_size) return false;

		return input[target_line][target_char] == expected_char;
	}


	bool trace_from(int char_index, int line_index, int offset_x, int offset_y, SolutionInput_T input) {
		if (!verify_char_at(line_index + offset_y, char_index + offset_x, 'S', input)) return false;
		if (!verify_char_at(line_index - offset_y, char_index - offset_x, 'M', input)) return false;
		if (!verify_char_at(line_index - offset_y * 2, char_index - offset_x * 2, 'X', input)) return false;

		return true;
	}

	bool trace_x(int char_index, int line_index, SolutionInput_T input) {
		int valid_diagonals = 0;

		if (verify_char_at(line_index - 1, char_index - 1, 'M', input) && verify_char_at(line_index + 1, char_index + 1, 'S', input)) valid_diagonals++;
		if (verify_char_at(line_index - 1, char_index - 1, 'S', input) && verify_char_at(line_index + 1, char_index + 1, 'M', input)) valid_diagonals++;
		if (verify_char_at(line_index - 1, char_index + 1, 'S', input) && verify_char_at(line_index + 1, char_index - 1, 'M', input)) valid_diagonals++;
		if (verify_char_at(line_index - 1, char_index + 1, 'M', input) && verify_char_at(line_index + 1, char_index - 1, 'S', input)) valid_diagonals++;

		return valid_diagonals == 2;
	}

	Result_T _get_solutions(SolutionInput_T solution_input) {
		int p1 = 0, p2 = 0;

		size_t input_size = solution_input.size();
		size_t line_size = solution_input[0].size();

		for (int i = 0; i < input_size; i++) {
			const std::string& line = solution_input[i];

			for (int j = 0; j < line_size; j++) {
				const char c = line[j];

				if (c == 'A') {
					p1 += trace_from(j, i, 0, 1, solution_input);
					p1 += trace_from(j, i, 1, 0, solution_input);
					p1 += trace_from(j, i, 1, 1, solution_input);
					p1 += trace_from(j, i, 0, -1, solution_input);
					p1 += trace_from(j, i, -1, 0, solution_input);
					p1 += trace_from(j, i, -1, -1, solution_input);
					p1 += trace_from(j, i, -1, 1, solution_input);
					p1 += trace_from(j, i, 1, -1, solution_input);

					p2 += trace_x(j, i, solution_input);
				}
			}
		}

		return { p1, p2 };
	}
};

#endif