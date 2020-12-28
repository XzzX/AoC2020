from AoC2020_18_1Visitor import AoC2020_18_1Visitor


class AoC2020_18_1Eval(AoC2020_18_1Visitor):

    # Visit a parse tree produced by AoC2020_18Parser#prog.
    def visitProg(self, ctx):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by AoC2020_18Parser#parentheses.
    def visitParentheses(self, ctx):
        return self.visit(ctx.expr())


    # Visit a parse tree produced by AoC2020_18Parser#op.
    def visitOp(self, ctx):
        lhs = self.visit(ctx.children[0])
        rhs = self.visit(ctx.children[2])
        op  = ctx.children[1].getText()
        if op == '+':
            return lhs + rhs
        elif op == '*':
            return lhs * rhs

    # Visit a parse tree produced by AoC2020_18Parser#int.
    def visitInt(self, ctx):
        return int(ctx.getText())

