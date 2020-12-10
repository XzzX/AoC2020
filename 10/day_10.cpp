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
  std::vector<int64_t> jolts{0};
  std::string input;
  std::ifstream fin("input");
  std::getline(fin, input);
  while (!fin.eof())
  {
    jolts.push_back(std::stoll(input));
    std::getline(fin, input);
  }
  fin.close();
  return jolts;
}

auto solve1(const std::vector<int64_t>& adaptors)
{
  std::vector<int64_t> jolts;
  std::adjacent_difference(
      adaptors.begin(),
      adaptors.end(),
      back_inserter(jolts));
  auto res = std::count(jolts.begin(), jolts.end(), 1) * 
            (std::count(jolts.begin(), jolts.end(), 3) + 1);
  return res;
}

auto cached_dfs(const std::vector<int64_t>& adaptors, 
                const int64_t idx,
                std::unordered_map<int64_t,int64_t>& cache)
{
  if (idx == adaptors.size() - 1) return 1l;
  int64_t sum = 0;
  for (int64_t delta = 1; delta < 4; ++delta)
  {
    if (idx+delta >= adaptors.size()) break;
    if (adaptors[idx+delta] - adaptors[idx] < 4)
    {
      auto lookup = cache.find(idx+delta);
      if (lookup != cache.end())
      {
        sum += lookup->second;
      } else
      {
        auto branches = cached_dfs(adaptors, idx+delta, cache);
        cache.emplace(idx+delta, branches);
        sum += branches;
      }
    } else break;
  }
  return sum;
}

auto solve2(const std::vector<int64_t>& adaptors)
{
  std::unordered_map<int64_t, int64_t> cache;
  return cached_dfs(adaptors, 0, cache);
}

int main()
{
  auto adaptors = read_input();
  std::sort(adaptors.begin(), adaptors.end());
  auto res1 = solve1(adaptors);
  std::cout << res1 << std::endl;
  auto res2 = solve2(adaptors);
  std::cout << res2 << std::endl;
}
