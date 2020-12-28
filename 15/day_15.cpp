#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <regex>
#include <set>
#include <string>
#include <stack>
#include <unordered_set>
#include <vector>

#include "../strutil/strutil.h"
using namespace strutil;

auto read_input()
{
  std::string input;
  std::ifstream fin("input");
  std::getline(fin, input);
  fin.close();

  return split(input, ',');
}

int64_t solve1(std::vector<std::string> starting_sequence, int64_t turns)
{
  int64_t last_number = 0;
  int64_t last_occurance = 0;
  std::unordered_map<int64_t, int64_t> lookup; //number, last position

  for (auto i = 0; i < starting_sequence.size(); ++i)
  {
    last_number = std::stoll(starting_sequence[i]);
    auto pos = lookup.find(last_number);
    last_occurance = pos != lookup.end() ? pos->second : -1;
    lookup[last_number] = i;
  }

  for (int64_t i = starting_sequence.size(); i < turns; ++i)
  {
    last_number = last_occurance == -1 ? 0 : i - last_occurance - 1;
    auto pos = lookup.find(last_number);
    last_occurance = pos != lookup.end() ? pos->second : -1;
    if (pos != lookup.end())
      pos->second = i; else
      lookup[last_number] = i;
  }
  return last_number;
}

int main()
{
  auto starting_sequence = read_input();
  std::cout << solve1(starting_sequence, 2020) << std::endl;
  std::cout << solve1(starting_sequence, 30000000) << std::endl;
}
