#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <stack>
#include <unordered_set>
#include <vector>

auto read_input()
{
  std::vector<int64_t> numbers;
  std::string input;
  std::ifstream fin("input");
  std::getline(fin, input);
  while (!fin.eof())
  {
    numbers.push_back(std::stoll(input));
    std::getline(fin, input);
  }
  fin.close();
  return numbers;
}

auto solve1(const std::vector<int64_t>& numbers, const int64_t ring_buffer_size)
{
  std::unordered_set<int64_t> ring_buffer;
  for (auto i = 0; i < ring_buffer_size; ++i)
    ring_buffer.insert(numbers[i]);

  for (auto i = ring_buffer_size; i < numbers.size(); ++i)
  {
    //check
    auto check = std::any_of(
        ring_buffer.begin(),
        ring_buffer.end(),
        [&](const int64_t& first) mutable
        {
          auto second = numbers[i] - first;
          if (first == second) return false;
          return ring_buffer.find(second) != ring_buffer.end();
        });

    if (!check) return std::make_pair(i, numbers[i]);
    
    //update
    ring_buffer.erase(numbers[i - ring_buffer_size]);
    ring_buffer.insert(numbers[i]);
  }

  exit(EXIT_FAILURE);
}

auto solve2(const std::vector<int64_t>& numbers, const int64_t idx)
{
  const auto target_number = numbers[idx];
  int64_t sum = numbers[0];
  int64_t left = 0;
  int64_t right = 0;

  while (sum != target_number)
  {
    //extend
    while (sum < target_number)
    {
      assert(right < numbers.size());
      ++right;
      sum += numbers[right];
    }

    //shrink
    while (sum > target_number)
    {
      assert(left < numbers.size());
      sum -= numbers[left];
      ++left;
    }
  }
  return std::make_pair(left, right);
}

int main()
{
  auto numbers = read_input();
  auto first_failure = solve1(numbers, 25);
  std::cout << first_failure.second << std::endl;
  auto range = solve2(numbers, first_failure.first);
  auto minmax = std::minmax_element(numbers.begin() + range.first, numbers.begin() + range.second);
  std::cout << *minmax.first << "  " << *minmax.second << std::endl;
  std::cout << *minmax.first + *minmax.second << std::endl;
}
