from AoC2020_18_2Visitor import AoC2020_18_2Visitor


class AoC2020_18_2Eval(AoC2020_18_2Visitor):

    # Visit a parse tree produced by AoC2020_18Parser#prog.
    def visitProg(self, ctx):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by AoC2020_18Parser#parentheses.
    def visitParentheses(self, ctx):
        return self.visit(ctx.expr())


    # Visit a parse tree produced by AoC2020_18Parser#add.
    def visitAdd(self, ctx):
        lhs = self.visit(ctx.children[0])
        rhs = self.visit(ctx.children[2])
        return lhs + rhs

    # Visit a parse tree produced by AoC2020_18Parser#mul.
    def visitMul(self, ctx):
        lhs = self.visit(ctx.children[0])
        rhs = self.visit(ctx.children[2])
        return lhs * rhs

    # Visit a parse tree produced by AoC2020_18Parser#int.
    def visitInt(self, ctx):
        return int(ctx.getText())

