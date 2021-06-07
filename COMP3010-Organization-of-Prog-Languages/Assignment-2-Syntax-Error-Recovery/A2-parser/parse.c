/* Complete recursive descent parser for the calculator language.
    Builds on figure 2.16.  Prints a trace of productions predicted and
    tokens matched.  Does no error recovery: prints "syntax error" and
    dies on invalid input.
    Michael L. Scott, 2008-2017.
*/

#include "stdio.h"
#include "stdlib.h"

#include "scan.h"

const char* names[] = {"read", "write", "id", "literal", "gets",
                       "add", "sub", "mul", "div", "lparen", "rparen", "eof"};

static token input_token;

void error () {
    printf ("syntax error\n");
    exit (1);
}

void match (token expected) {
    if (input_token == expected) {
        printf ("matched %s", names[input_token]);
        if (input_token == t_id || input_token == t_literal)
            printf (": %s", token_image);
        printf ("\n");
        input_token = scan ();
    }
    else error ();
}

void program ();
void stmt_list ();
void stmt ();
void expr ();
void term_tail ();
void term ();
void factor_tail ();
void factor ();
void add_op ();
void mul_op ();

void program () {
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            printf ("predict program --> stmt_list eof\n");
            stmt_list ();
            match (t_eof);
            break;
        default: error ();
    }
}

void stmt_list () {
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
            printf ("predict stmt_list --> stmt stmt_list\n");
            stmt ();
            stmt_list ();
            break;
        case t_eof:
            printf ("predict stmt_list --> epsilon\n");
            break;          /*  epsilon production */
        default: error ();
    }
}

void stmt () {
    switch (input_token) {
        case t_id:
            printf ("predict stmt --> id gets expr\n");
            match (t_id);
            match (t_gets);
            expr ();
            break;
        case t_read:
            printf ("predict stmt --> read id\n");
            match (t_read);
            match (t_id);
            break;
        case t_write:
            printf ("predict stmt --> write expr\n");
            match (t_write);
            expr ();
            break;
        default: error ();
    }
}

void expr () {
    switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
            printf ("predict expr --> term term_tail\n");
            term ();
            term_tail ();
            break;
        default: error ();
    }
}

void term_tail () {
    switch (input_token) {
        case t_add:
        case t_sub:
            printf ("predict term_tail --> add_op term term_tail\n");
            add_op ();
            term ();
            term_tail ();
            break;
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            printf ("predict term_tail --> epsilon\n");
            break;          /*  epsilon production */
        default: error ();
    }
}

void term () {
    switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
            printf ("predict term --> factor factor_tail\n");
            factor ();
            factor_tail ();
            break;
        default: error ();
    }
}

void factor_tail () {
    switch (input_token) {
        case t_mul:
        case t_div:
            printf ("predict factor_tail --> mul_op factor factor_tail\n");
            mul_op ();
            factor ();
            factor_tail ();
            break;
        case t_add:
        case t_sub:
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            printf ("predict factor_tail --> epsilon\n");
            break;          /*  epsilon production */
        default: error ();
    }
}

void factor () {
    switch (input_token) {
        case t_id :
            printf ("predict factor --> id\n");
            match (t_id);
            break;
        case t_literal:
            printf ("predict factor --> literal\n");
            match (t_literal);
            break;
        case t_lparen:
            printf ("predict factor --> lparen expr rparen\n");
            match (t_lparen);
            expr ();
            match (t_rparen);
            break;
        default: error ();
    }
}

void add_op () {
    switch (input_token) {
        case t_add:
            printf ("predict add_op --> add\n");
            match (t_add);
            break;
        case t_sub:
            printf ("predict add_op --> sub\n");
            match (t_sub);
            break;
        default: error ();
    }
}

void mul_op () {
    switch (input_token) {
        case t_mul:
            printf ("predict mul_op --> mul\n");
            match (t_mul);
            break;
        case t_div:
            printf ("predict mul_op --> div\n");
            match (t_div);
            break;
        default: error ();
    }
}

int main () {
    input_token = scan ();
    program ();
    return 0;
}
