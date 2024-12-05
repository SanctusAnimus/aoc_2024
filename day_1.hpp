#ifndef AOC_DAY_1
#define AOC_DAY_1

#include "solution.hpp"
#include <unordered_map>


class Day1 : public Solution<Day1> {
public:
	Day1() {
		day_num = 1;

		p1_expected = 2904518;
		p2_expected = 18650129;

		resolve_benchmark_tries = 200;
	};

	using Result_T = std::pair<int, int>;

	inline int parse_location_ids(const std::string& line, std::vector<int>& l_side, std::vector<int>& r_side) {
		size_t from = 0;
		size_t to = line.find(' ');

		int num_left;
		int num_right;
		auto line_ptr = line.data();
		auto line_end = line_ptr + line.size();
		auto [ptr, ec] = std::from_chars(line_ptr + from, line_ptr + to, num_left);
		auto [ptr2, ec2] = std::from_chars(line_ptr + to + 3, line_end, num_right);

		l_side.emplace_back(num_left);
		r_side.emplace_back(num_right);

		return num_right;
	}

	Result_T _get_solutions(SolutionInput_T solution_input) {
		const size_t input_length = solution_input.size();

		std::vector<int> left_side = {};
		left_side.reserve(input_length);
		std::vector<int> right_side = {};
		right_side.reserve(input_length);

		std::unordered_map<int, int> right_side_times = {};
		right_side_times.reserve(input_length);

		for (const auto& line : solution_input) {
			int right_num = parse_location_ids(line, left_side, right_side);

			if (right_side_times.contains(right_num)) right_side_times[right_num]++;
			else {
				right_side_times[right_num] = 1;
			}
		}

		std::sort(left_side.begin(), left_side.end(), std::less<int>());
		std::sort(right_side.begin(), right_side.end(), std::less<int>());

		int total_distance = 0;
		int total_similarity_score = 0;

		for (int i = 0; i < input_length; i++) {
			int left_entry = left_side[i];
			total_distance += abs(right_side[i] - left_entry);

			total_similarity_score += left_entry * right_side_times[left_entry];
		}

		return { total_distance, total_similarity_score };
	}
};

#endif