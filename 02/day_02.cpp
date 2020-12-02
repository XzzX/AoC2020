#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Password
{
   int min;
   int max;
   char letter;
   std::string password;
};

auto read_input()
{
   std::vector<Password> password_list;
   std::ifstream fin("input");
   while (!fin.eof())
   {
      Password pwd;
      std::string str;
      std::getline(fin, str, '-');
      if (fin.eof()) return password_list;
      pwd.min = std::stoi(str);
      std::getline(fin, str, ' ');
      pwd.max = std::stoi(str);
      std::getline(fin, str, ':');
      pwd.letter = str[0];
      std::getline(fin, str);
      pwd.password = str;
      password_list.push_back(pwd);
   }
   fin.close();
   return password_list;
}

bool check_password1(const Password& pwd)
{
   auto count_char = std::count(pwd.password.begin(),
                                pwd.password.end(),
                                pwd.letter);
   return (pwd.min <= count_char) && (count_char <= pwd.max);
}

bool check_password2(const Password& pwd)
{
   //Passwords are not trimmed and the first letter is a space.
   //This corrects for 1-based index.
   bool first_pos  = pwd.password[static_cast<size_t>(pwd.min)] == pwd.letter;
   bool second_pos = pwd.password[static_cast<size_t>(pwd.max)] == pwd.letter;
   return first_pos != second_pos;
}

int main()
{
   auto pwds = read_input();
   auto correct_pwds1 = std::count_if(pwds.begin(),
                                      pwds.end(),
                                      check_password1);
   std::cout << correct_pwds1 << std::endl;
   auto correct_pwds2 = std::count_if(pwds.begin(),
                                      pwds.end(),
                                      check_password2);
   std::cout << correct_pwds2 << std::endl;
}
