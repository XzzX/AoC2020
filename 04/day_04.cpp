#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../strutil/strutil.h"

using Passport = std::unordered_map<std::string, std::string>;

auto read_input()
{
  Passport passport;
  std::vector<Passport> passports;
  std::string input;
  std::ifstream fin("input");
  std::getline(fin, input);
  while (!fin.eof())
  {
    strutil::trim(input);
    if (input=="")
    {
      passports.push_back(passport);
      passport.clear();
    } else
    {
      auto fields = strutil::split(input, " ");
      for (auto field : fields)
      {
        strutil::trim(field);
        if (field=="") continue;
        auto pair = strutil::split(field, ":");
        assert(pair.size() == 2);
        passport.emplace(pair[0], pair[1]);
      }
    }
    std::getline(fin, input);
  }
  passports.push_back(passport);
  fin.close();
  return passports;
}

bool is_valid1(const Passport& passport)
{
  const std::vector<std::string> required_fields = 
    {"ecl", "pid", "eyr", "hcl", "byr", "iyr", "hgt"};

  return std::all_of(required_fields.begin(),
                     required_fields.end(),
                     [&](const auto& field)
                     { return passport.find(field) != passport.cend(); } );
}

bool check_byr(const std::string& val)
{
  std::regex re("[0-9]{4}");
  if (!std::regex_match(val, re)) return false;
  auto year = std::stoi(val);
  return (1920 <= year) && (year <= 2002 );
}

bool check_iyr(const std::string& val)
{
  std::regex re("[0-9]{4}");
  if (!std::regex_match(val, re)) return false;
  auto year = std::stoi(val);
  return (2010 <= year) && (year <= 2020 );
}

bool check_eyr(const std::string& val)
{
  std::regex re("[0-9]{4}");
  if (!std::regex_match(val, re)) return false;
  auto year = std::stoi(val);
  return (2020 <= year) && (year <= 2030 );
}

bool check_hgt(const std::string& val)
{
  std::regex re("([0-9]{3})cm");
  std::smatch match;
  if (std::regex_match(val, match, re))
  {
    auto size = std::stoi(match[1].str());
    return (150 <= size) && (size <= 193 );
  }
  re = std::regex("([0-9]{2})in");
  if (std::regex_match(val, match, re))
  {
    auto size = std::stoi(match[1].str());
    return (59 <= size) && (size <= 76 );
  }
  return false;
}

bool check_hcl(const std::string& val)
{
  std::regex re("#[0-9a-f]{6}");
  return std::regex_match(val, re);
}

bool check_ecl(const std::string& val)
{
  const std::vector<std::string> possible_vals = 
    {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

  return std::any_of(possible_vals.begin(),
                     possible_vals.end(),
                     [&](const auto& v)
                     { return val == v; } );
}

bool check_pid(const std::string& val)
{
  std::regex re("[0-9]{9}");
  return std::regex_match(val, re);
}

bool is_valid2(Passport& passport)
{
  if (!is_valid1(passport)) return false;
  if (!check_byr(passport["byr"])) return false;
  if (!check_iyr(passport["iyr"])) return false;
  if (!check_eyr(passport["eyr"])) return false;
  if (!check_hgt(passport["hgt"])) return false;
  if (!check_hcl(passport["hcl"])) return false;
  if (!check_ecl(passport["ecl"])) return false;
  if (!check_pid(passport["pid"])) return false;
  return true;
}

int main()
{
   auto passports = read_input();
   auto num_valid_passports = std::count_if(passports.begin(),
                                            passports.end(),
                                            is_valid1);
   std::cout << "valid passports: " << num_valid_passports << std::endl;
   num_valid_passports = std::count_if(passports.begin(),
                                       passports.end(),
                                       is_valid2);
   std::cout << "valid passports: " << num_valid_passports << std::endl;
}
