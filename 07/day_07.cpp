#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <string>
#include <stack>
#include <unordered_set>
#include <vector>

#include "../strutil/strutil.h"
using namespace strutil;

struct Content
{
  Content(const int amnt, const std::string& clr) : amount(amnt), color(clr) {};
  int amount;
  std::string color;
};

struct Node
{
  bool visited = false;
  std::vector<Content> contains;
  std::vector<Content> fits_into;
};

using RuleNodes = std::map<std::string, Node>;

auto read_input()
{
  std::regex color_regex("(\\w* \\w*) bag");
  std::regex count_regex("(\\d+)");
  RuleNodes rules;
  std::string input;
  std::ifstream fin("input");
  std::getline(fin, input);
  while (!fin.eof())
  {
    std::sregex_iterator it_color(input.begin(), input.end(), color_regex);
    std::sregex_iterator it_count(input.begin(), input.end(), count_regex);
    std::string bag_color = it_color->operator[](1);
    for (++it_color; it_count != std::sregex_iterator(); ++it_count, ++it_color)
    {
      assert(it_count != std::sregex_iterator());
      auto count = std::stoi(it_count->str());

      assert(it_color != std::sregex_iterator());
      auto color = it_color->operator[](1);

      rules[bag_color].contains.emplace_back(count, color);
      rules[color].fits_into.emplace_back(count, bag_color);
    }
    std::getline(fin, input);
  }
  fin.close();
  return rules;
}

int count_containers(RuleNodes& rules)
{
  //start with shiny gold
  //do depth-first search and count all nodes
  for ( auto& node : rules ) {node.second.visited = false;}
  
  int counter = 0;

  std::stack<std::string> search_nodes;
  search_nodes.push("shiny gold");
  while (!search_nodes.empty())
  {
    auto& node = rules[search_nodes.top()];
    search_nodes.pop();
    if (node.visited) continue;
    node.visited = true;
    ++counter;
    for (auto& edge : node.fits_into)
    {
      search_nodes.push(edge.color);
    }
  }

  return counter - 1;
}

int dfs(RuleNodes& rules, const std::string& node_string)
{
  int counter = 0;
  auto& node = rules[node_string];
  if (node.contains.empty()) return 1;
  for (auto& edge : node.contains)
  {
    counter += edge.amount * dfs(rules, edge.color);
  }
  return counter + 1;
}

int count_containees(RuleNodes& rules)
{
  //start with shiny gold
  //do depth-first search and count all containees
  return dfs(rules, "shiny gold") - 1;
}

int main()
{
  auto rules = read_input();
  std::cout << count_containers(rules) << std::endl;
  std::cout << count_containees(rules) << std::endl;
}
