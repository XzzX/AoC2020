#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

auto read_input()
{
  std::vector<std::string> boarding_passes;
  std::string input;
  std::ifstream fin("input");
  std::getline(fin, input);
  while (!fin.eof())
  {
    assert(input.length() == 10);
    boarding_passes.push_back(input);
    std::getline(fin, input);
  }
  fin.close();
  return boarding_passes;
}

struct Seat
{
  int row = 0;
  int col = 0;
  int id  = 0;
};

Seat calc_seat(const std::string& boarding_pass)
{
  Seat seat;
  for (size_t i = 0; i < 7; ++i)
  {
    seat.row <<= 1;
    if (boarding_pass[i] == 'B') seat.row |= 1;
  }
  for (size_t i = 7; i < 10; ++i)
  {
    seat.col <<= 1;
    if (boarding_pass[i] == 'R') seat.col |= 1;
  }
  seat.id = seat.row * 8 + seat.col;
  return seat;
}

int main()
{
   auto boarding_passes = read_input();
   std::vector<Seat> seats;
   std::back_insert_iterator<std::vector<Seat>> inserter(seats);
   std::transform(
       boarding_passes.begin(),
       boarding_passes.end(),
       inserter,
       calc_seat);
   auto minmax_id = std::minmax_element(
       seats.begin(), 
       seats.end(),
       [](const auto& lhs, const auto& rhs)
       { return lhs.id < rhs.id; });

   std::cout << "max seat id: " << minmax_id.second->id << std::endl;

   auto id_sum = std::accumulate(
       seats.begin(),
       seats.end(),
       0,
       [](const int a, const auto& seat)
       { return a + seat.id; } );

   auto max_sum = (minmax_id.second->id * (minmax_id.second->id + 1)) / 2;
   auto min_sum = (minmax_id.first->id * (minmax_id.first->id - 1)) / 2;

   std::cout << "your seat: " << max_sum - min_sum - id_sum << std::endl;
}
