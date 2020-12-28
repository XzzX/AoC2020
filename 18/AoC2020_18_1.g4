grammar AoC2020_18_1;

prog: expr
    ;

expr: '(' expr ')'  #parentheses
    | expr OP expr  #op
    | INT           #int
    ;

OP     : '+' | '*' ;
INT    : [0-9]+ ;             // match integers
WS     : [ \t\r\n]+ -> skip ; // toss out whitespaces and tabs
