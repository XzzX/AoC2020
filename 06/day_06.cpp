#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

auto read_input()
{
  std::vector<std::vector<uint32_t>> customs; //groups, persons
  std::vector<uint32_t> persons;
  std::string input;
  std::ifstream fin("input");
  std::getline(fin, input);
  while (!fin.eof())
  {
    uint32_t bitset = 0;
    for (auto c : input) bitset |= 1 << (c - 'a'); 
    if (bitset == 0)
    {
      customs.push_back(persons);
      persons.clear();
    } else
    {
      persons.push_back(bitset);
    }
    std::getline(fin, input);
  }
  fin.close();
  customs.push_back(persons);
  return customs;
}

uint32_t count_ones(uint32_t v)
{
  uint32_t count = 0;
  for (auto i = 0; i < 32; ++i)
  {
    if (v & 1) ++count;
    v >>= 1;
  }
  return count;
}

int main()
{
  auto customs = read_input();
  std::vector<uint32_t> groups(customs.size());
  auto or_persons = [](const auto& group)  
    { return std::accumulate(
        group.begin(),
        group.end(),
        0,
        std::bit_or<uint32_t>()); };
  std::transform(
    customs.begin(),
    customs.end(),
    groups.begin(),
    or_persons);
  auto count = std::accumulate(
    groups.begin(),
    groups.end(),
    0,
    [](uint32_t lhs, const auto& rhs)
    { return lhs + count_ones(rhs); });
  std::cout << "count: " << count << std::endl;

  auto and_persons = [](const auto& group)
    { return std::accumulate(
        group.begin(),
        group.end(),
        0xFFFFFFFF,
        std::bit_and<uint32_t>()); };
  std::transform(
    customs.begin(),
    customs.end(),
    groups.begin(),
    and_persons);
  count = std::accumulate(
    groups.begin(),
    groups.end(),
    0,
    [](uint32_t lhs, const auto& rhs)
    { return lhs + count_ones(rhs); });
  std::cout << "count: " << count << std::endl;
}
