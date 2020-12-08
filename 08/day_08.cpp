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

#include "../strutil/strutil.h"
using namespace strutil;

struct State
{
  int32_t ip = 0; //instruction pointer
  int32_t acc = 0; //global accumulator
};

struct Instruction
{
  Instruction(const std::string& str, const int32_t i) : opcode(str), arg(i) {}
  std::string opcode;
  int32_t arg;
};

auto read_input()
{
  std::vector<Instruction> code;
  std::string input;
  std::ifstream fin("input");
  std::getline(fin, input);
  while (!fin.eof())
  {
    auto inst = split(input, " ");
    code.emplace_back(inst[0], std::stoi(inst[1]));
    std::getline(fin, input);
  }
  fin.close();
  return code;
}

void execute_instruction(const std::vector<Instruction>& code, State& state)
{
  if (code[state.ip].opcode == "nop")
  {
    ++state.ip;
  } else
  if (code[state.ip].opcode == "acc")
  {
    state.acc += code[state.ip].arg;
    ++state.ip;
  } else
  if (code[state.ip].opcode == "jmp")
  {
    state.ip += code[state.ip].arg;
  }
}

int32_t solve1(const std::vector<Instruction>& code)
{
  State state;
  std::set<int32_t> executed_instructions;
  while (executed_instructions.insert(state.ip).second) execute_instruction(code, state);
  return state.acc;
}

int32_t solve2(std::vector<Instruction> code)
{
  for (auto& inst : code)
  {
    if (inst.opcode == "jmp") inst.opcode = "nop"; else
    if (inst.opcode == "nop") inst.opcode = "jmp";

    State state;
    std::set<int32_t> executed_instructions;
    while ((executed_instructions.insert(state.ip).second) && (state.ip != code.size()))
      execute_instruction(code, state);
    if (state.ip == code.size()) return state.acc;

    if (inst.opcode == "jmp") inst.opcode = "nop"; else
    if (inst.opcode == "nop") inst.opcode = "jmp";
  }
  assert(false);
  return 0;
}

int main()
{
  auto code = read_input();
  std::cout << solve1(code) << std::endl;
  std::cout << solve2(code) << std::endl;
}
