# Generated from AoC2020_18.g4 by ANTLR 4.9
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .AoC2020_18Parser import AoC2020_18Parser
else:
    from AoC2020_18Parser import AoC2020_18Parser

# This class defines a complete generic visitor for a parse tree produced by AoC2020_18Parser.

class AoC2020_18Visitor(ParseTreeVisitor):

    # Visit a parse tree produced by AoC2020_18Parser#prog.
    def visitProg(self, ctx:AoC2020_18Parser.ProgContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by AoC2020_18Parser#parentheses.
    def visitParentheses(self, ctx:AoC2020_18Parser.ParenthesesContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by AoC2020_18Parser#op.
    def visitOp(self, ctx:AoC2020_18Parser.OpContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by AoC2020_18Parser#int.
    def visitInt(self, ctx:AoC2020_18Parser.IntContext):
        return self.visitChildren(ctx)



del AoC2020_18Parser