/* Complete recursive descent parser for the calculator language.
    Builds on figure 2.16.  Prints a trace of productions predicted and
    tokens matched.  Does no error recovery: prints "syntax error" and
    dies on invalid input.
    Michael L. Scott, 2008-2017.
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "scan.h"
using namespace std;

const char* names[] = {"read", "write", "id", "literal", "gets",
                       "add", "sub", "mul", "div", "lparen", "rparen", "eof", "if", "fi", "do", "od", "check", "<", "<=", "<>", "==", ">", ">="};

static token input_token;
class SyntaxError
{
public:
    SyntaxError() {}
    ~SyntaxError() {}

private:

};
void error () {
    cout <<  "syntax error\n" <<endl;
    return;
}

void match (token expected){
    if (input_token == expected) {
        //cout << "matched " << names[input_token];
        //if (input_token == t_id || input_token == t_literal)
        //    cout << ": " << token_image;
        //cout << endl;
        input_token = scan ();
    }
    else {
        error();
        input_token = scan();
        throw SyntaxError();
    };
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
void bool_op();
void relation();
void relation_tail();

void program () {
    cout << "(program " << endl;
    cout << "[";
    try {
        switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
        case t_if:
        case t_do:
        case t_check:
            //cout << "predict program --> stmt_list eof" << endl;
            stmt_list();
            match(t_eof);
            break;
        default: error(); throw SyntaxError();
        }
    }
    catch (SyntaxError) {
        while (true)
        {
            switch (input_token)
            {
            case t_id:
            case t_read:
            case t_write:
            case t_eof:
            case t_if:
            case t_do:
            case t_check:
                program();
                return;
            default:
                input_token = scan();
            }
        }
    }
    cout << "]" << endl;
    cout << ")" << endl;
}

void stmt_list () {
    try {
        switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_if:
        case t_do:
        case t_check:
            //cout << "predict stmt_list --> stmt stmt_list" << endl;

            stmt();
            stmt_list();

            break;
        case t_eof:
        case t_fi:
        case t_od:
            //cout << "predict stmt_list --> epsilon" << endl;
            break;          /*  epsilon production */
        default: error(); throw SyntaxError();
        }
    }
    catch (SyntaxError) {
        while (true)
        {
            switch (input_token)
            {
            case t_id:
            case t_read:
            case t_write:
            case t_if:
            case t_do:
            case t_check:
                stmt_list();
                return;
            case t_eof:
                return;
            default:
                break;
            }
        }
    }
    
    
}

void stmt () {
    try {
        cout << "(";
        switch (input_token) {
        case t_id:
            //cout << "predict stmt --> id gets expr" << endl;
            cout << token_image << " := " << " ";
            match(t_id);
            match(t_gets);
            expr();
            break;
        case t_read:
            //cout << "predict stmt --> read id" << endl;
            cout << "read ";
            match(t_read);
            cout << "\"" << token_image << "\"";
            match(t_id);
            break;
        case t_if:
            //cout << "predict stmt --> if expr stmt fi" << endl;
            cout << "if" << endl;
            match(t_if);
            expr();
            cout << endl;
            cout << "[";
            stmt_list();
            cout << "]" << endl;
            match(t_fi);
            break;
        case t_do:
            //cout << "predict stmt --> do stmt od" << endl;
            cout << "do" << endl;
            match(t_do);
            cout << "[";
            stmt_list();
            cout << "]" << endl;
            match(t_od);
            break;
        case t_check:
            //cout << "predict stmt --> check expr" << endl;
            cout << "check ";
            match(t_check);
            expr();
            break;
        case t_write:
            //cout << "predict stmt --> write expr" << endl;
            cout << "write ";
            match(t_write);
            expr();
            break;
        default: error(); throw SyntaxError();
        }
    }
    catch (SyntaxError) {
        while (true)
        {
            switch (input_token)
            {
            case t_id:
            case t_read:
            case t_if:
            case t_do:
            case t_check:
            case t_write:
                stmt();
                return;
               
            default:
                input_token = scan();
            }
        }
    }
    cout << ")" << endl;
}

void expr () {
    try {
        switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
            //cout << "predict expr --> relation relation_tail" << endl;
            relation();
            relation_tail();
            break;
        default: error(); throw SyntaxError();
        }
    }
    catch (SyntaxError) {
        while (true)
        {
            switch (input_token)
            {
            case t_id:
            case t_literal:
            case t_lparen:
                expr();
                return;
            case t_rparen:
            case t_read:
            case t_write:
            case t_if:
            case t_do:
            case t_check:
            case t_fi:
            case t_od:
            case t_eof:
                return;
            default:
                input_token = scan();
            }
        }
    }
}

void relation() {
    try {
        switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
            //cout << "predict term --> term term_tail" << endl;
            term();
            term_tail();
            break;
        default: error(); throw SyntaxError();
        }
    }
    catch (SyntaxError) {
        while (true)
        {
            switch (input_token)
            {
            case t_id:
            case t_literal:
            case t_lparen:
                relation();
                return;
            case t_less:
            case t_lesse:
            case t_ne:
            case t_e:
            case t_large:
            case t_largee:
            case t_rparen:
            case t_read:
            case t_write:
            case t_if:
            case t_do:
            case t_check:
            case t_fi:
            case t_od:
            case t_eof:
                return;
            default:
                input_token = scan();
            }
        }
    }
}

void relation_tail() {
    try {
        switch (input_token) {
        case t_less:
        case t_lesse:
        case t_ne:
        case t_e:
        case t_large:
        case t_largee:
            //cout << "predict relation_tail --> relation_op relation" << endl;
            bool_op();
            relation();
            break;
        case t_id:
        case t_read:
        case t_write:
        case t_if:
        case t_do:
        case t_check:
        case t_fi:
        case t_od:
        case t_eof:
            //cout << "predict relation_tail --> epsilon" << endl;
            break;          /*  epsilon production */
        default: error(); throw SyntaxError();
        }
    }
    catch (SyntaxError) {
        while (true)
        {
            switch (input_token)
            {
            case t_less:
            case t_lesse:
            case t_ne:
            case t_e:
            case t_large:
            case t_largee:
                relation_tail();
                return;
            case t_rparen:
            case t_id:
            case t_read:
            case t_write:
            case t_if:
            case t_do:
            case t_check:
            case t_fi:
            case t_od:
            case t_eof:
                return;
            default:
                input_token = scan();
            }
        }
    }
}

void term_tail () {
    try {
        switch (input_token) {
        case t_add:
        case t_sub:
            //cout << "predict term_tail --> add_op term term_tail" << endl;
            add_op();
            term();
            term_tail();
            break;
        case t_less:
        case t_lesse:
        case t_ne:
        case t_e:
        case t_large:
        case t_largee:
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_if:
        case t_do:
        case t_check:
        case t_fi:
        case t_od:
        case t_eof:
            //cout << "predict term_tail --> epsilon" << endl;
            break;          /*  epsilon production */
        default: error(); throw SyntaxError();
        }
    }
    catch (SyntaxError) {
        while (true)
        {
            switch (input_token)
            {
            case t_add:
            case t_sub:
                term_tail();
                return;
            case t_less:
            case t_lesse:
            case t_ne:
            case t_e:
            case t_large:
            case t_largee:
            case t_rparen:
            case t_id:
            case t_read:
            case t_write:
            case t_if:
            case t_do:
            case t_check:
            case t_fi:
            case t_od:
            case t_eof:
                return;
            default:
                input_token = scan();
            }
        }
    }
    
}

void term () {
    try {
        switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
            //cout << "predict term --> factor factor_tail" << endl;
            factor();
            factor_tail();
            break;
        default: error(); throw SyntaxError();
        }
    }
    catch (SyntaxError) {
        while (true)
        {
            switch (input_token)
            {
            case t_id:
            case t_literal:
            case t_lparen:
                term();
                return;
            case t_add:
            case t_sub:
            case t_less:
            case t_lesse:
            case t_ne:
            case t_e:
            case t_large:
            case t_largee:
            case t_rparen:
            case t_read:
            case t_write:
            case t_if:
            case t_do:
            case t_check:
            case t_fi:
            case t_od:
            case t_eof:
                return;
            default:
                input_token = scan();
            }
        }
    }
}

void factor_tail () {
    try {
        switch (input_token) {
        case t_mul:
        case t_div:
            //cout << "predict factor_tail --> mul_op factor factor_tail" << endl;
            mul_op();
            factor();
            factor_tail();
            break;
        case t_less:
        case t_lesse:
        case t_ne:
        case t_e:
        case t_large:
        case t_largee:
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_if:
        case t_do:
        case t_check:
        case t_fi:
        case t_od:
        case t_add:
        case t_sub:
        case t_eof:
            //cout << "predict factor_tail --> epsilon" << endl;
            break;          /*  epsilon production */
        default: error(); throw SyntaxError();
        }
    }
    catch (SyntaxError) {
        while (true)
        {
            switch (input_token)
            {
            case t_mul:
            case t_div:
                factor_tail();
                return;
            case t_less:
            case t_lesse:
            case t_ne:
            case t_e:
            case t_large:
            case t_largee:
            case t_rparen:
            case t_id:
            case t_read:
            case t_write:
            case t_if:
            case t_do:
            case t_check:
            case t_fi:
            case t_od:
            case t_add:
            case t_sub:
            case t_eof:
                return;
            default:
                input_token = scan();
            }
        }
    }
}

void factor () {
    try {
        switch (input_token) {
        case t_id:
            //cout << "predict factor --> id" << endl;
            cout << "(id \"" << token_image << "\")";
            match(t_id);
            break;
        case t_literal:
            //cout << "predict factor --> literal" << endl;
            cout << "(num \"" << token_image << "\")";
            match(t_literal);
            break;
        case t_lparen:
            //cout << "predict factor --> lparen expr rparen" << endl;
            cout << "(";
            match(t_lparen);
            expr();
            cout << ")";
            match(t_rparen);
            break;
        default: error(); throw SyntaxError();
        }
    }
    catch (SyntaxError){
        while (true)
        {
            switch (input_token)
            {
            case t_lparen:
            case t_id:
            case t_literal:
                factor();
                return;
            case t_less:
            case t_lesse:
            case t_ne:
            case t_e:
            case t_large:
            case t_largee:
            case t_rparen:
            case t_read:
            case t_write:
            case t_if:
            case t_do:
            case t_check:
            case t_fi:
            case t_od:
            case t_add:
            case t_sub:
            case t_eof:
            case t_mul:
            case t_div:
                return;
            default:
                input_token = scan();
            }
        }
    }
}

void bool_op() {
    try {
        switch (input_token) {
        case t_less:
            //cout << "predict relation_op --> less" << endl;
            cout << " < ";
            match(t_less);
            break;
        case t_lesse:
            //cout << "predict relation_op --> less_or_equal" << endl;
            cout << " <= ";
            match(t_lesse);
            break;
        case t_large:
            //cout << "predict relation_op --> greater" << endl;
            cout << " > ";
            match(t_large);
            break;
        case t_largee:
            //cout << "predict relation_op --> greater_or_equal" << endl;
            cout << " >= ";
            match(t_largee);
            break;
        case t_ne:
            //cout << "predict relation_op --> not_equal" << endl;
            cout << " <> ";
            match(t_ne);
            break;
        case t_e:
            //cout << "predict relation_op --> equal" << endl;
            cout << " == ";
            match(t_e);
            break;
        default: error(); throw SyntaxError();
        }
    }
    catch (SyntaxError) {
        while (true) {
            switch (input_token)
            {
            case t_less:
            case t_lesse:
            case t_large:
            case t_largee:
            case t_ne:
            case t_e:
                bool_op();
                return;
            case t_lparen:
            case t_id:
            case t_literal:
                return;
            default:
                input_token = scan();
            }
        }
    }
}

void add_op () {
    try {
        switch (input_token) {
        case t_add:
            //cout << "predict add_op --> add" << endl;
            cout << " + ";
            match(t_add);
            break;
        case t_sub:
            //cout << "predict add_op --> sub" << endl;
            cout << " - ";
            match(t_sub);
            break;
        default: error(); throw SyntaxError();
        }
    }
    catch (SyntaxError) {
        while (true) {
            switch (input_token)
            {
            case t_add:
            case t_sub:
                add_op();
                return;
            case t_lparen:
            case t_id:
            case t_literal:
                return;
            default:
                input_token = scan();
            }
        }
    }
}

void mul_op () {
    try {
        switch (input_token) {
        case t_mul:
            //cout << "predict mul_op --> mul" << endl;

            cout << " * ";
            match(t_mul);
            break;
        case t_div:
            //cout << "predict mul_op --> div" << endl;
            cout << " / ";
            match(t_div);
            break;
        default: error(); throw SyntaxError();
        }
    }
    catch (SyntaxError) {
        while (true) {
            switch (input_token)
            {
            case t_mul:
            case t_div:
                mul_op();
                return;
            case t_lparen:
            case t_id:
            case t_literal:
                return;
            default:
                input_token = scan();
            }
        }
    }
}

int main () {
    input_token = scan ();
    program ();
    return 0;
}
