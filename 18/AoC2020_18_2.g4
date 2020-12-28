grammar AoC2020_18_2;

prog: expr
    ;

expr: '(' expr ')'  #parentheses
    | expr '+' expr #add
    | expr '*' expr #mul
    | INT           #int
    ;

INT    : [0-9]+ ;             // match integers
WS     : [ \t\r\n]+ -> skip ; // toss out whitespaces and tabs
