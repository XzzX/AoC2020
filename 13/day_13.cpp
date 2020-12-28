#include <fstream>
#include <iostream>
#include <unordered_set>

#include "../strutil/strutil.h"
using namespace strutil;

auto read_input()
{
   std::ifstream fin("input");
   std::string str;
   std::getline(fin, str);
   auto possible_departure = std::stoll(str);
   std::getline(fin, str);
   trim(str);
   auto busses = split(str, ',');
   fin.close();
   return std::make_pair(possible_departure, busses);
}

int64_t solve1(int64_t possible_departure, std::vector<std::string> busses)
{
  busses.erase(std::remove(busses.begin(), busses.end(), "x"), busses.end());
  std::vector<int64_t> delay;
  std::transform(
    busses.begin(),
    busses.end(),
    std::back_inserter(delay),
    [possible_departure](const auto bus)
    { return (possible_departure / std::stoll(bus) + 1) * std::stoll(bus) - possible_departure; });
  auto idx = std::distance(delay.begin(), std::min_element(delay.begin(), delay.end()));
  return std::stoll(busses[idx]) * delay[idx];
}

int main()
{
   auto input = read_input();
   std::cout << solve1(input.first, input.second) << std::endl;
}
