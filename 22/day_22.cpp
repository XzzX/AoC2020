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
  std::queue<int64_t> player1;
  std::queue<int64_t> player2;

  std::string input;
  std::ifstream fin("input");
  std::getline(fin, input);
  std::getline(fin, input);
  while (input != "")
  {
    player1.push(std::stoll(input));
    std::getline(fin, input);
  }
  std::getline(fin, input);
  std::getline(fin, input);
  while (input != "")
  {
    player2.push(std::stoll(input));
    std::getline(fin, input);
  }
  fin.close();

  return std::make_pair(player1, player2);
}

int64_t calc_score(std::queue<int64_t>& player)
{
  int64_t sum = 0;
  for (int64_t idx = player.size(); idx > 0; --idx)
  {
    sum += idx * player.front();
    player.pop();
  }
  return sum;
}

int64_t solve1(std::queue<int64_t>& player1, std::queue<int64_t>& player2)
{
  while (!player1.empty() && !player2.empty())
  {
    if (player1.front() > player2.front())
    {
      player1.push(player1.front());
      player1.push(player2.front());
    } else
    {
      player2.push(player2.front());
      player2.push(player1.front());
    }
    player1.pop();
    player2.pop();
  }

  return player1.empty() ? calc_score(player2) : calc_score(player1);
}

int main()
{
  auto cards = read_input();
  std::cout << solve1(cards.first, cards.second) << std::endl;
}
