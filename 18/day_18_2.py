from functools import reduce

from antlr4 import *
from antlr4.InputStream import InputStream
from AoC2020_18_2Lexer import AoC2020_18_2Lexer
from AoC2020_18_2Parser import AoC2020_18_2Parser
from AoC2020_18_2Eval import AoC2020_18_2Eval

def eval(cmd):
    lexer = AoC2020_18_2Lexer(InputStream(cmd))
    token_stream = CommonTokenStream(lexer)
    parser = AoC2020_18_2Parser(token_stream)
    tree = parser.prog()

    visitor = AoC2020_18_2Eval()
    res = visitor.visit(tree)
    return res

print(eval('1 + 2 * 3 + 4 * 5 + 6'))
print(eval('1 + (2 * 3) + (4 * (5 + 6))'))
print(eval('2 * 3 + (4 * 5)'))
print(eval('5 + (8 * 3 + 9 + 3 * 4 * 3)'))

with open('input', 'r') as fin:
    print(reduce(lambda x,y: x+y, map(lambda x: eval(x), fin.readlines())))

