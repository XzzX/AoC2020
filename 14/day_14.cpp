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

std::string replace_all(const std::string& input, const std::string & target, const std::string & replecament)
{
  std::string str(input);
  size_t start_pos = 0;

  while ((start_pos = str.find(target, start_pos)) != std::string::npos)
  {
    str.replace(start_pos, target.length(), replecament);
    start_pos += replecament.length();
  }

  return str;
}

enum class OpCode : uint64_t {MASK, MEM};

struct Instruction
{
  Instruction(OpCode op_, uint64_t arg0_, uint64_t arg1_) : op(op_), arg0(arg0_), arg1(arg1_) {}
  OpCode op;
  uint64_t arg0;
  uint64_t arg1;
};

auto read_input()
{
  std::regex mask_regex("mask = ([X01]*)");
  std::regex mem_regex("mem\\[(\\d*)\\] = (\\d*)");
  std::smatch match;

  std::vector<Instruction> code;
  std::string input;
  std::ifstream fin("input");
  std::getline(fin, input);
  while (!fin.eof())
  {
    if (std::regex_match(input, match, mask_regex))
    {
      std::string and_mask = replace_all(match[1].str(), "X", "1");
      std::string or_mask = replace_all(match[1].str(), "X", "0");
      std::cout << "MASK " << and_mask << " " << or_mask << std::endl;
      code.emplace_back(OpCode::MASK, std::stoll(and_mask, nullptr, 2), std::stoll(or_mask, nullptr, 2));
    } else if (std::regex_match(input, match, mem_regex))
    {
      std::cout << "MEM " << std::stoll(match[1].str()) << " " << std::stoll(match[2].str()) << std::endl;
      code.emplace_back(OpCode::MEM, std::stoll(match[1].str()), std::stoll(match[2].str()));
    } else
    {
      std::cout << "unknown cmd: " << input << std::endl;
    }
    std::getline(fin, input);
  }
  fin.close();
  return code;
}

struct State
{
  std::pair<uint64_t, uint64_t> mask = {0xFFFFFFFFFFFFFFFF, 0};
  std::map<uint64_t, uint64_t> mem;
};

void execute_instruction(const Instruction& inst, State& state)
{
  switch (inst.op)
  {
    case OpCode::MASK:
      state.mask = std::make_pair(inst.arg0, inst.arg1);
      break;
    case OpCode::MEM:
      state.mem[inst.arg0] = (inst.arg1 & state.mask.first) | state.mask.second;
      break;
  }
}

int main()
{
  auto code = read_input();
  State state;
  std::for_each(
    code.begin(),
    code.end(),
    [&](const auto& inst)
    { execute_instruction(inst, state); });
  auto sum = std::accumulate(
    state.mem.begin(),
    state.mem.end(),
    0ull,
    [](uint64_t lhs, const auto& rhs)
    { return lhs + rhs.second; });

  std::cout << sum << std::endl;
}
