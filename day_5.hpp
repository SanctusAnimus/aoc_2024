#ifndef AOC_DAY_5
#define AOC_DAY_5
#include "solution.hpp"
#include <unordered_map>


class Day5 : public Solution<Day5> {
public:
    Day5() {
        day_num = 5;

        p1_expected = 7307;
        p2_expected = 4713;

        resolve_benchmark_tries = 100;
    };

    using Result_T = std::pair<long int, long int>;


    Result_T _get_solutions(SolutionInput_T solution_input) {
        int p1 = 0, p2 = 0;
        std::unordered_map<int, std::vector<int>> rules = {};

        bool parsing_rules = true;

        for (const auto& line : solution_input) {
            if (line == "") {
                parsing_rules = false;

                continue;
            }
            const char* ptr = line.data();
            const char* line_end = ptr + line.size();

            if (parsing_rules) {
                int rule_left;
                int rule_right;

                std::from_chars(ptr, ptr + 3, rule_left);
                std::from_chars(ptr + 3, ptr + line.size(), rule_right);

                if (rules.contains(rule_left)) {
                    rules[rule_left].push_back(rule_right);
                }
                else {
                    rules[rule_left] = { rule_right };
                }
            }
            // parsing pages
            else {
                std::vector<int> pages = {};
                const char* page_ptr = ptr;
                do {
                    int parsed_page;
                    auto [nptr, ec] = std::from_chars(page_ptr, page_ptr + 3, parsed_page);
                    page_ptr = nptr + 1;

                    pages.push_back(parsed_page);
                } while (page_ptr < line_end);

                bool valid;
                bool initiallyValid = true;

                do {
                    valid = true;

                    for (int i = 0; i < pages.size(); i++) {
                        //std::cout << "processing page entry " << pages[i] << "\n";
                        if (auto search = rules.find(pages[i]); search != rules.end())
                        {
                            std::vector<int>& deps = search->second;

                            for (const int dep : deps) {
                                auto end = pages.begin() + i;
                                auto it = std::find(pages.begin(), end, dep);

                                if (it != end) {
                                    int pos = std::distance(pages.begin(), it);

                                    int temp = pages[i];
                                    pages[i] = pages[pos];
                                    pages[pos] = temp;

                                    valid = false;
                                }
                            }
                        }
                        else {
                            continue;
                        }
                    }

                    if (valid && initiallyValid) {
                        break;
                    }

                    initiallyValid = false;
                } while (!valid);

                int mid = pages[pages.size() / 2];

                if (initiallyValid) {
                    p1 += mid;
                }
                else {
                    p2 += mid;
                }
            }

        }

        return { p1, p2 };
    }
};

#endif