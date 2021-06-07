/* Simple ad-hoc scanner for the calculator language.
    Michael L. Scott, 2008-2017.
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>

#include "scan.h"
using namespace std;

char token_image[100];

token scan() {
    static int c = ' ';
        /* next available char; extra (int) width accommodates EOF */
    int i = 0;              /* index into token_image */

    /* skip white space */
    while (isspace(c)) {
        c = getchar();
    }
    if (c == EOF)
        return t_eof;
    if (isalpha(c)) {
        do {
            token_image[i++] = c;
            c = getchar();
        } while (isalpha(c) || isdigit(c) || c == '_');
        token_image[i] = '\0';
        if (!strcmp(token_image, "read")) return t_read;
        else if (!strcmp(token_image, "write")) return t_write;
        else if (!strcmp(token_image, "if")) return t_if;
        else if (!strcmp(token_image, "fi")) return t_fi;
        else if (!strcmp(token_image, "do")) return t_do;
        else if (!strcmp(token_image, "od")) return t_od;
        else if (!strcmp(token_image, "check")) return t_check;
        else return t_id;
    }
    else if (isdigit(c)) {
        do {
            token_image[i++] = c;
            c = getchar();
        } while (isdigit(c));
        token_image[i] = '\0';
        return t_literal;
    } else switch (c) {
        case ':':
            if ((c = getchar()) != '=') {
                fprintf(stderr, "error\n");
                exit(1);
            } else {
                c = getchar();
                return t_gets;
            }
            break;
        case '+': c = getchar(); return t_add;
        case '-': c = getchar(); return t_sub;
        case '*': c = getchar(); return t_mul;
        case '/': c = getchar(); return t_div;
        case '(': c = getchar(); return t_lparen;
        case ')': c = getchar(); return t_rparen;
        case '$':
            c = getchar();
            if (c == '$') {
                c = getchar();
                return t_eof;
            }
            else
            {
                fprintf(stderr, "error\n");
                exit(1);
            }
        case '<': 
            c = getchar();
            if (c == '=') {
                c = getchar();
                return t_lesse;
            }
            else if(c == '>') {
                c = getchar();
                return t_ne;
            }
            else {
                return t_less;
            }
        case '>':
            c = getchar();
            if (c == '=') {
                c = getchar();
                return t_largee;
            }
            else {
                return t_large;
            }
        case '=':
            c = getchar();
            if (c == '=') {
                c = getchar();
                return t_e;
            }
            else
            {
                fprintf(stderr, "error\n");
                exit(1);
            }
        default:
            cout << "error" << endl;
            exit(1);
    }
}
