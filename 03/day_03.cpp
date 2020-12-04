#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Map
{
  std::vector<std::string> data;
  int width;
  int height;
};

auto read_input()
{
  Map map;
  std::ifstream fin("input");
  std::string str;
  fin >> str;
  while (!fin.eof())
  {
    map.data.push_back(str);
    fin >> str;
  }
  fin.close();
  map.height = static_cast<int> (map.data.size());
  map.width  = static_cast<int> (map.data[0].length());
  return map;
}

int count_trees_during_traversal(const Map& map, const int delta_x, const int delta_y)
{
  int x = 0;
  int y = 0;
  int trees = 0;

  do
  {
    if (map.data[y][x] == '#') ++trees;
    x = (x+delta_x) % map.width;
    y = y + delta_y;
  } while (y < map.height);

  return trees;
}

int main()
{
   auto map = read_input();
   uint64_t a = static_cast<uint64_t>(  count_trees_during_traversal(map, 1, 1) );
   uint64_t b = static_cast<uint64_t>(  count_trees_during_traversal(map, 3, 1) );
   uint64_t c = static_cast<uint64_t>(  count_trees_during_traversal(map, 5, 1) );
   uint64_t d = static_cast<uint64_t>(  count_trees_during_traversal(map, 7, 1) );
   uint64_t e = static_cast<uint64_t>(  count_trees_during_traversal(map, 1, 2) );
   std::cout << "right 1, down 1, " << a << std::endl;
   std::cout << "right 3, down 1, " << b << std::endl;
   std::cout << "right 5, down 1, " << c << std::endl;
   std::cout << "right 7, down 1, " << d << std::endl;
   std::cout << "right 1, down 2, " << e << std::endl;
   std::cout << "product: " << a*b*c*d*e << std::endl;
}
