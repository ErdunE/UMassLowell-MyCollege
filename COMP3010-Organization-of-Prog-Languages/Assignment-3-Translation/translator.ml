(*******************************************************************
   This file ("translator.ml") provides stub functions for the extra
   code you need to write for this assignment.

   There are two major stub functions in "translator.ml":
   "ast_ize_P" (which transforms a parse tree for a program into
                an abstract syntax tree[AST]); and
   "translate" (which translates an AST into an equivalent C program).

   You are also being provided with a file called "parser.ml" which
   contains working code to produce a parse tree for a program.
   Everything in the file "parser.ml" is complete and usable as-is.

   The major entry point for the parser provided in "parser.ml" is
   a function called "parse" invoked with two parameters: A parse table,
   and a string containing a calculator language program.

   The file "parser.ml" constructs two example parse tables:
   "cg_parse_table" (for the original calculator language grammar), and
   "ecg_parse_table" (for the extended calculator language grammar).

   Here are two parser examples which will work as-is:

      parse cg_parse_table sum_ave_prog;;
      parse ecg_parse_table primes_prog;;
   		
   "sum_ave_prog" and "primes_prog" are provided at the end of this
   file (as strings). "sum_ave_prog" uses the original calculator
   language grammar, while "primes_prog" uses the extended calculator
   language grammar.

   When complete, your translator code should work when invoked as
   follows:

      print_string
        (snd
          (translate
            (ast_ize_P
              (parse ecg_parse_table primes_prog)
            )
          )
        );;
   	
   The result of this invocation should be a C program on standard
   output, which can be compiled and run to produce the first N primes
   (where N is a number typed by the user).
 *******************************************************************)


#use "parser.ml";;


(*******************************************************************
   Declarations and functions to transform a parse tree into an
   abstract syntax tree (AST)
 *******************************************************************)

type ast_sl = ast_s list
and ast_s =
    | AST_error
    | AST_assign of (string * ast_e)
    | AST_read of string
    | AST_write of ast_e
    | AST_if of (ast_e * ast_sl)
    | AST_do of ast_sl
    | AST_check of ast_e
and ast_e =
    | AST_binop of (string * ast_e * ast_e)
    | AST_id of string
    | AST_num of string;;

	
let rec ast_ize_P (p:parse_tree) : ast_sl =
  match p with
    | PT_nt ("P", [sl; PT_term "$$"]) -> ast_ize_SL sl
    | _ -> raise (Failure "malformed parse tree in ast_ize_P")

and ast_ize_SL (sl:parse_tree) : ast_sl =
  match sl with
    | PT_nt ("SL", []) -> []
    | PT_nt ("SL", [h; t]) -> ast_ize_S h::ast_ize_SL t
    | _ -> raise (Failure "malformed parse tree in ast_ize_SL")

and ast_ize_S (s:parse_tree) : ast_s =
  match s with
    | PT_nt ("S", [PT_id id; PT_term ":="; expr]) -> AST_assign (id, (ast_ize_expr expr))
    | PT_nt ("S", [PT_term "read"; PT_id id]) -> AST_read(id)
    | PT_nt ("S", [PT_term "write"; expr]) -> AST_write(ast_ize_expr expr)
    | PT_nt ("S", [PT_term "if"; rel; sl; PT_term "fi"]) -> AST_if(ast_ize_expr rel, ast_ize_SL sl)
    | PT_nt ("S", [PT_term "do"; sl; PT_term "od"]) -> AST_do(ast_ize_SL sl)
    | PT_nt ("S", [PT_term "check"; rel]) -> AST_check(ast_ize_expr rel)
    | _ -> raise (Failure "malformed parse tree in ast_ize_S")

and ast_ize_expr (e:parse_tree) : ast_e =
  (* e is an R, E, T, or F parse tree node *)
  match e with
    | PT_nt ("R", [e; et]) -> ast_ize_reln_tail (ast_ize_expr e) et
    | PT_nt ("E", [t; tt]) -> ast_ize_expr_tail (ast_ize_expr t) tt
    | PT_nt ("T", [f; ft]) -> ast_ize_expr_tail (ast_ize_expr f) ft
    | PT_nt ("F", [PT_id id]) -> AST_id(id)
    | PT_nt ("F", [PT_num num]) -> AST_num(num) 
    | PT_nt ("F", [PT_term "("; e; PT_term ")"]) -> ast_ize_expr(e)
    | _ -> raise (Failure "malformed parse tree in ast_ize_expr")

and ast_ize_reln_tail (lhs:ast_e) (tail:parse_tree) : ast_e =
  (* lhs is an inherited attribute.
     tail is an ET parse tree node *)
  match tail with
    | PT_nt ("ET", [PT_nt("ro", [PT_term "=="]); rhs]) -> AST_binop ("==", lhs, ast_ize_expr rhs)
    | PT_nt ("ET", [PT_nt("ro", [PT_term "<>"]); rhs]) -> AST_binop ("<>", lhs, ast_ize_expr rhs)
    | PT_nt ("ET", [PT_nt("ro", [PT_term "<"]); rhs]) -> AST_binop ("<", lhs, ast_ize_expr rhs)
    | PT_nt ("ET", [PT_nt("ro", [PT_term ">"]); rhs]) -> AST_binop (">", lhs, ast_ize_expr rhs)
    | PT_nt ("ET", [PT_nt("ro", [PT_term "<="]); rhs]) -> AST_binop ("<=", lhs, ast_ize_expr rhs)
    | PT_nt ("ET", [PT_nt("ro", [PT_term ">="]); rhs]) -> AST_binop (">=", lhs, ast_ize_expr rhs)    
    | PT_nt ("ET", []) -> lhs
    | _ -> raise (Failure "malformed parse tree in ast_ize_reln_tail")

and ast_ize_expr_tail (lhs:ast_e) (tail:parse_tree) : ast_e =
  (* lhs is an inherited attribute.
     tail is a TT or FT parse tree node *)
  match tail with
    | PT_nt ("TT", [PT_nt ("ao", [PT_term "+"]); t; tt]) -> 
        ast_ize_expr_tail (AST_binop ("+", lhs, ast_ize_expr t)) tt
    | PT_nt ("TT", [PT_nt ("ao", [PT_term "-"]); t; tt]) ->
        ast_ize_expr_tail (AST_binop ("-", lhs, ast_ize_expr t)) tt
    | PT_nt ("TT", []) -> lhs
    | PT_nt ("FT", [PT_nt ("mo", [PT_term "*"]); f; ft]) ->
        ast_ize_expr_tail (AST_binop ("*", lhs, ast_ize_expr f)) ft
    | PT_nt ("FT", [PT_nt ("mo", [PT_term "/"]); f; ft]) ->
        ast_ize_expr_tail (AST_binop ("/", lhs, ast_ize_expr f)) ft    
    | PT_nt ("FT", []) -> lhs
    | _ -> raise (Failure "malformed parse tree in ast_ize_expr_tail")
;;


(*******************************************************************
   Functions to translate an AST into C
 *******************************************************************)

(* The code below is (obviously) a bare stub. The intent is that when
   you run translate on a full, correct AST, you'll get back code for an
   equivalent C program. If there are any variables that are written in
   the program but never read, you'll also get a warning message
   indicating their names and the lines on which the writes occur. Your
   C program should contain code to check for dynamic semantic errors. *)
 
 (* The prologue codes for the output C program. It is based on the helper codes 
    given in the assignment spec. Error checking has been added for EOF and 
    non-numeric input in the getint(). In addition, a zero_divisor_checker() 
    function is provided to detect the divide by zero semantic error. *)
let program_prologue =
"\
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getint() {
    char digits[64];
    if (scanf(\"%s\", digits) == EOF) {
        fprintf(stderr, \"Error: EOF is met. Please input an integer\\n\");
        exit(-1);
    }
    int i = 0;
    for (i = 0; i < strlen(digits); i++) {
        // Valid characters consist of 0-9 and '-'
        if (!isdigit(digits[i]) && digits[i] != '-') {
            fprintf(stderr, \"Error: Non-numeric character is detected. Please input an integer\\n\");
            exit(-1);
        }
    }
    return atoi(digits);
}

void putint(int n) {
    printf(\"%d\\n\", n);
}

int zero_divisor_checker(int n) {
    if (n == 0) {
        printf(\"Error: Divide by 0.\\n\");
        exit(-1);
    }
    return n;
}

int main() {
"

(* Epilogue for the output C program *)
let program_epilogue = "return 0;\n}\n"

let rec translate (ast:ast_sl)
:  string   * string
(* warnings   output_program *) = 

(* Collect all assigned variables - Note: read counts as assigned *)
  let rec all_assigned_variables (ast:ast_sl) : string list =
    match ast with
    | [] -> []
    | h :: t ->
      match h with
      | AST_assign (id, expr)  -> id::all_assigned_variables t
      | AST_read (id)          -> id::all_assigned_variables t
      | AST_write (expr)       -> all_assigned_variables t
      | AST_if (expr, sl)      ->
          all_assigned_variables sl @ all_assigned_variables t
      | AST_do (sl)            ->
          all_assigned_variables sl @ all_assigned_variables t
      | AST_check (expr)       -> all_assigned_variables t
      | AST_error              -> raise (Failure "error: all_assigned_variables")
  in
  
  (* Collect all used variables *)
  let rec all_used_variables (ast:ast_sl) : string list =

    (* Collect all (used) variables occuring in an expr *)
    let rec vars_in_expr (expr:ast_e) : string list = 
      match expr with
      | AST_id (id) -> [id]
      | AST_num (n) -> []
      | AST_binop (op, lhs, rhs) -> vars_in_expr lhs @ vars_in_expr rhs
    in
      
    match ast with
    | [] -> []
    | h :: t ->
      match h with
      | AST_assign (id, expr)  -> vars_in_expr expr @ all_used_variables t
      | AST_read (id)          -> all_used_variables t
      | AST_write (expr)       -> vars_in_expr expr @ all_used_variables t
      | AST_if (expr, sl)      ->
          vars_in_expr expr @ all_used_variables sl @ all_used_variables t
      | AST_do (sl)            ->
          all_used_variables sl @ all_used_variables t      
      | AST_check (expr)       -> vars_in_expr expr @ all_used_variables t
      | AST_error              -> raise (Failure "error: all_used_variables")
  in
  
  let assigned_variables = unique_sort (all_assigned_variables ast) in
  let used_variables = unique_sort (all_used_variables ast) in  

  (* Generate warnings for variables that are assigned to (or read) but never used. *)
  let generate_warning_msg used assigned = 
    let unused = List.filter (fun x -> not (List.mem x used)) assigned in
    if unused = [] 
    then ""
    else 
    let rec unused_string l = 
      match l with
      | [] -> ""
      | h::t -> h ^ " " ^ unused_string t
    in
    "Unused variables: " ^ (unused_string unused) ^ "\n"
  in
  
  (* Generate variables declarations for the program *)
  let rec generate_program_var_declarations l = 
    match l with
    | [] -> ""
    | h::t -> "int " ^ h ^ ";\n" ^ generate_program_var_declarations t
  in
  
  (* Returns the warning * program tuple *)
  (generate_warning_msg used_variables assigned_variables, 
  program_prologue 
  ^ generate_program_var_declarations assigned_variables 
  ^ translate_sl ast 
  ^ program_epilogue)
  
and translate_sl (ast:ast_sl) : string =
  match ast with
    | [] -> ""
    | h :: t -> translate_s h ^ translate_sl t

and translate_s (s:ast_s) : string =
  match s with
    | AST_assign(id, expr)  -> translate_assign id expr
    | AST_read(id)          -> translate_read id
    | AST_write(expr)       -> translate_write expr
    | AST_if(rel, sl)       -> translate_if rel sl
    | AST_do(sl)            -> translate_do sl
    | AST_check(rel)        -> translate_check rel
    | AST_error             -> raise (Failure "error: translate_s")

and translate_assign (id:string) (expr:ast_e) : string =
  id ^ " = " ^ (translate_expr expr) ^ ";\n"

and translate_read (id:string) : string =
  id ^ " = getint();\n"

and translate_write (expr:ast_e) : string =
  "putint(" ^ translate_expr(expr) ^ ");\n"

and translate_if (rel:ast_e) (sl:ast_sl) : string =
  "if (" ^ translate_expr(rel) ^ ") {\n" ^ translate_sl(sl) ^ "}\n"

and translate_do (ast:ast_sl) : string =
  "while(1) {\n" ^ translate_sl(ast) ^ "}\n"

and translate_check (rel:ast_e) : string =
  "if (!" ^ translate_expr(rel) ^ ") break;\n"

and translate_expr (expr:ast_e) : string =
  match expr with
    | AST_num(n) -> n
    | AST_id(id) -> id
    | AST_binop(op, lhs, rhs) ->
      (* Wrap the divisor with zero_divisor_checker *)
      if op = "/" then "(" ^ translate_expr(lhs) ^ op ^ "zero_divisor_checker(" ^ translate_expr(rhs) ^ "))"
      else "(" ^ translate_expr(lhs) ^ op ^ translate_expr(rhs) ^ ")"


(*******************************************************************
   Sample programs in the calculator language
 *******************************************************************)

let sum_ave_prog = "
  read a
  read b
  sum := a + b
  write sum
  write sum / 2";;
	 
let primes_prog = "
  read n
  cp := 2
  do check n > 0
    found := 0
    cf1 := 2
    cf1s := cf1 * cf1
    do check cf1s <= cp
      cf2 := 2
      pr := cf1 * cf2
      do check pr <= cp
        if pr == cp
          found := 1
        fi
        cf2 := cf2 + 1
        pr := cf1 * cf2
      od
      cf1 := cf1 + 1
      cf1s := cf1 * cf1
    od
    if found == 0
      write cp
      n := n - 1
    fi
    cp := cp + 1
  od";;
