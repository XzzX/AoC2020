# Generated from AoC2020_18_1.g4 by ANTLR 4.9
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .AoC2020_18_1Parser import AoC2020_18_1Parser
else:
    from AoC2020_18_1Parser import AoC2020_18_1Parser

# This class defines a complete generic visitor for a parse tree produced by AoC2020_18_1Parser.

class AoC2020_18_1Visitor(ParseTreeVisitor):

    # Visit a parse tree produced by AoC2020_18_1Parser#prog.
    def visitProg(self, ctx:AoC2020_18_1Parser.ProgContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by AoC2020_18_1Parser#parentheses.
    def visitParentheses(self, ctx:AoC2020_18_1Parser.ParenthesesContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by AoC2020_18_1Parser#op.
    def visitOp(self, ctx:AoC2020_18_1Parser.OpContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by AoC2020_18_1Parser#int.
    def visitInt(self, ctx:AoC2020_18_1Parser.IntContext):
        return self.visitChildren(ctx)



del AoC2020_18_1Parser