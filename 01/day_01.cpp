#include <fstream>
#include <iostream>
#include <unordered_set>

auto read_input()
{
   std::unordered_set<int> nums;
   std::ifstream fin("input");
   while (!fin.eof())
   {
      int val;
      fin >> val;
      nums.insert(val);
   }
   fin.close();
   return nums;
}

std::pair<int,int> find_pair(const std::unordered_set<int>& nums)
{
   for (auto& v : nums)
   {
      if (nums.find(2020-v) != nums.end())
         return std::make_pair(v, 2020-v);
   }
   return std::make_pair(0,0);
}

std::pair<int,int> find_triplet(const std::unordered_set<int>& nums)
{
   for (auto& x : nums)
   {
      for (auto& y : nums)
      {
         if (nums.find(2020-x-y) != nums.end())
            return std::make_pair(x, y);
      }
   }
   return std::make_pair(0,0);
}

int main()
{
   auto nums = read_input();
   auto pair = find_pair(nums);
   std::cout << pair.first << " " << pair.second << " " << pair.first * pair.second << std::endl;
   pair = find_triplet(nums);
   std::cout << pair.first << " " << pair.second << " " << pair.first * pair.second * (2020-pair.first-pair.second) << std::endl;
}
