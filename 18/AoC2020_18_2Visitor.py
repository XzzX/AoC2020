# Generated from AoC2020_18_2.g4 by ANTLR 4.9
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .AoC2020_18_2Parser import AoC2020_18_2Parser
else:
    from AoC2020_18_2Parser import AoC2020_18_2Parser

# This class defines a complete generic visitor for a parse tree produced by AoC2020_18_2Parser.

class AoC2020_18_2Visitor(ParseTreeVisitor):

    # Visit a parse tree produced by AoC2020_18_2Parser#prog.
    def visitProg(self, ctx:AoC2020_18_2Parser.ProgContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by AoC2020_18_2Parser#add.
    def visitAdd(self, ctx:AoC2020_18_2Parser.AddContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by AoC2020_18_2Parser#parentheses.
    def visitParentheses(self, ctx:AoC2020_18_2Parser.ParenthesesContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by AoC2020_18_2Parser#mul.
    def visitMul(self, ctx:AoC2020_18_2Parser.MulContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by AoC2020_18_2Parser#int.
    def visitInt(self, ctx:AoC2020_18_2Parser.IntContext):
        return self.visitChildren(ctx)



del AoC2020_18_2Parser