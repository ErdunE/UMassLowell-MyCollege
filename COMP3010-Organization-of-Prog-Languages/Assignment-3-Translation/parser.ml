(*******************************************************************
    LL(1) parser generator, and parse tree builder for an extended
    calculator language.

    Author: Michael L. Scott

    This file can be "#use"-ed (or compiled and then "#load"-ed)
    into the top-level interpreter,
 *******************************************************************)

open List;;
(* The List library includes a large collection of useful functions.
   In the provided code, I've used assoc, exists, filter, find,
   fold_left, hd, length, map, and rev
*)

open Str;;      (* for split *)
(* The Str library provides a few extra string-processing routines.
   In particular, it provides "split", which I use to break program
   input into whitespace-separated words.  Note, however, that this
   library is not automatically available.  If you are using the
   top-level interpreter, you have to say
        #load "str.cma";;
   If you are generating an executable fron the shell, you have to say
        ocamlc str.cma interpreter.ml
*)

(* Surprisingly, compose isn't built in.  It's included in various
   widely used commercial packages, but not in the core libraries. *)
let compose f g x = f (g x);;

type symbol_productions = (string * string list list);;
type grammar = symbol_productions list;;
type parse_table = (string * (string list * string list) list) list;;
(*                  nt        predict_set   rhs *)

let calc_gram : grammar =
  [ ("P",  [["SL"; "$$"]])
  ; ("SL", [["S"; "SL"]; []])
  ; ("S",  [ ["id"; ":="; "E"]; ["read"; "id"]; ["write"; "E"]])
  ; ("E",  [["T"; "TT"]])
  ; ("T",  [["F"; "FT"]])
  ; ("TT", [["ao"; "T"; "TT"]; []])
  ; ("FT", [["mo"; "F"; "FT"]; []])
  ; ("ao", [["+"]; ["-"]])
  ; ("mo", [["*"]; ["/"]])
  ; ("F",  [["id"]; ["num"]; ["("; "E"; ")"]])
  ];;

let ecg : grammar =
  [ ("P",  [["SL"; "$$"]])
  ; ("SL", [["S"; "SL"]; []])
  ; ("S",  [ ["id"; ":="; "E"]; ["read"; "id"]; ["write"; "E"]
           ; ["if"; "R"; "SL"; "fi"]; ["do"; "SL"; "od"]; ["check"; "R"]
           ])
  ; ("R",  [["E"; "ET"]])
  ; ("E",  [["T"; "TT"]])
  ; ("T",  [["F"; "FT"]])
  ; ("F",  [["id"]; ["num"]; ["("; "E"; ")"]])
  ; ("ET", [["ro"; "E"]; []])
  ; ("TT", [["ao"; "T"; "TT"]; []])
  ; ("FT", [["mo"; "F"; "FT"]; []])
  ; ("ro", [["=="]; ["<>"]; ["<"]; [">"]; ["<="]; [">="]])
  ; ("ao", [["+"]; ["-"]])
  ; ("mo", [["*"]; ["/"]])
  ];;

let ecg2 : grammar =
  [ ("P",  [["SL"; "$$"]])
  ; ("SL", [["S"; "SL"]; []])
  ; ("S",  [ ["id"; ":="; "R"]; ["read"; "id"]; ["write"; "R"]
           ; ["if"; "R"; "SL"; "fi"]; ["do"; "SL"; "od"]; ["check"; "R"]
           ])
  ; ("R",  [["E"; "ET"]])
  ; ("E",  [["T"; "TT"]])
  ; ("T",  [["F"; "FT"]])
  ; ("F",  [["id"]; ["num"]; ["("; "R"; ")"]])
  ; ("ET", [["ro"; "E"]; []])
  ; ("TT", [["ao"; "T"; "TT"]; []])
  ; ("FT", [["mo"; "F"; "FT"]; []])
  ; ("ro", [["=="]; ["<>"]; ["<"]; [">"]; ["<="]; [">="]])
  ; ("ao", [["+"]; ["-"]])
  ; ("mo", [["*"]; ["/"]])
  ];;

(* is e a member of list l? *)
let member e l = exists ((=) e) l;;

(* OCaml has a built-in quicksort; this was just an exercise. *)
let rec sort l =
  let rec partition pivot l left right =
    match l with
      | []        -> (left, right)
      | c :: rest -> if (compare c pivot) < 0
          then partition pivot rest (c :: left) right
          else partition pivot rest left (c :: right) in
    match l with
      | []        -> l
      | h :: []   -> l
      | h :: rest -> let (left, right) = partition h rest [] [] in
            (sort left) @ [h] @ (sort right);;

(* leave only one of any consecutive identical elements in list *)
let rec unique l =
  match l with
    | []             -> l
    | h :: []        -> l
    | a :: b :: rest -> if a = b (* structural equivalence *)
        then unique (b :: rest)
        else a :: unique (b :: rest);;

let unique_sort l = unique (sort l);;

(* Return all individual productions in grammar. *)
let productions gram : (string * string list) list =
  let prods (lhs, rhss) = map (fun rhs -> (lhs, rhs)) rhss in
    fold_left (@) [] (map prods gram);;

(* Return all symbols in grammar. *)
let gsymbols gram : string list =
  unique_sort
    (fold_left (@) [] (map (compose (fold_left (@) []) snd) gram));;

(* Return all elements of l that are not in excluded.
   Assume that both lists are sorted *)
let list_minus l excluded =
  let rec helper rest te rtn =
    match rest with
      | []     -> rtn
      | h :: t -> match te with
        | []       -> (rev rest) @ rtn
        | h2 :: t2 -> match compare h h2 with
          | -1 -> helper t te (h :: rtn)
          |  0 -> helper t t2 rtn
          |  _ -> helper rest t2 rtn in
    rev (helper l excluded []);;

(* Return just the nonterminals. *)
let nonterminals gram : string list = map fst gram;;

(* Return just the terminals. *)
let terminals gram : string list =
  list_minus (gsymbols gram) (unique_sort (nonterminals gram));;

(* Return the start symbol.  Throw exception if grammar is empty. *)
let start_symbol gram : string = fst (hd gram);;

let is_nonterminal e gram = member e (nonterminals gram);;

let is_terminal e gram = member e (terminals gram);;

let union s1 s2 = unique_sort (s1 @ s2);;

(* return suffix of lst that begins with first occurrence of sym
   (or [] if there is no such occurrence) *)
let rec suffix sym lst = 
  match lst with
    | [] -> []
    | h :: t -> if h = sym (* structural equivalence *)
        then lst else suffix sym t;;

(* Return a list of pairs.
   Each pair consists of a symbol A and a list of symbols beta
   such that for some alpha, A -> alpha B beta. *)
type right_context = (string * string list) list;;
let get_right_context (b:string) gram : right_context =
  fold_left (@) []
    (map (fun prod ->
            let a = fst prod in
            let rec helper accum rhs =
              let b_beta = suffix b rhs in
                match b_beta with
                  | [] -> accum
                  | x :: beta  -> (* assert x = b *)
                      helper ((a, beta) :: accum) beta in
              helper [] (snd prod))
        (productions gram));;

(* parser generator starts here *)

type symbol_knowledge = string * bool * string list * string list;;
type knowledge = symbol_knowledge list;;
let symbol_field (s, e, fi, fo) = s;;
let eps_field (s, e, fi, fo) = e;;
let first_field (s, e, fi, fo) = fi;;
let follow_field (s, e, fi, fo) = fo;;

let initial_knowledge gram : knowledge =
  map (fun a -> (a, false, [], [])) (nonterminals gram);;

let get_symbol_knowledge (a:string) (kdg:knowledge) : symbol_knowledge =
  find (fun (s, e, fi, fo) -> s = a) kdg;;

(* Can word list w generate epsilon based on current estimates?
   if w is an empty list, yes
   if w is a single terminal, no
   if w is a single nonterminal, look it up
   if w is a non-empty list, "iterate" over elements *)
let rec generates_epsilon (w:string list) (kdg:knowledge) gram : bool =
  match w with
    | [] -> true
    | h :: t -> if is_terminal h gram then false
        else eps_field (get_symbol_knowledge h kdg)
             && generates_epsilon t kdg gram;;

(* Return FIRST(w), based on current estimates.
   if w is an empty list, return []  [empty set]
   if w is a single terminal, return [w]
   if w is a single nonterminal, look it up
   if w is a non-empty list, "iterate" over elements *)
let rec first (w:string list) (kdg:knowledge) gram : (string list) =
  match w with
    | [] -> []
    | x :: _ when is_terminal x gram -> [x]
    | x :: rest -> let s = first_field (get_symbol_knowledge x kdg) in
          if generates_epsilon [x] kdg gram
          then union s (first rest kdg gram)
          else s;;

let follow (a:string) (kdg:knowledge) : string list =
  follow_field (get_symbol_knowledge a kdg);;

let rec map3 f l1 l2 l3 =
  match (l1, l2, l3) with
    | ([], [], []) -> []
    | (h1 :: t1, h2 :: t2, h3 :: t3) -> (f h1 h2 h3) :: map3 f t1 t2 t3
    | _ -> raise (Failure "mismatched_lists");;

(* Return knowledge structure for grammar.
   Start with (initial_knowledge grammar) and "iterate",
   until the structure doesn't change.
   Uses (get_right_context B gram), for all nonterminals B,
   to help compute follow sets. *)
let get_knowledge gram : knowledge =
  let nts : string list = nonterminals gram in
  let right_contexts : right_context list
    = map (fun s -> get_right_context s gram) nts in
  let rec helper kdg =
    let update : symbol_knowledge -> symbol_productions
      -> right_context -> symbol_knowledge
      = fun old_sym_kdg sym_prods sym_right_context ->
        let my_first s = first s kdg gram in
        let my_eps s = generates_epsilon s kdg gram in
        let filtered_follow p = if my_eps (snd p)
          then (follow (fst p) kdg)
          else [] in
          (
            symbol_field old_sym_kdg,       (* nonterminal itself *)
            (eps_field old_sym_kdg)         (* previous estimate *)
            || (fold_left (||) false (map my_eps (snd sym_prods))),
            union (first_field old_sym_kdg) (* previous estimate *)
              (fold_left union [] (map my_first (snd sym_prods))),
            union (union
                     (follow_field old_sym_kdg)  (* previous estimate *)
                     (fold_left union [] (map my_first
                                            (map (fun p ->
                                                    match snd p with
                                                      | [] -> []
                                                      | h :: t -> [h])
                                                sym_right_context))))
              (fold_left union [] (map filtered_follow sym_right_context))
          ) in    (* end of update *)
    let new_kdg = map3 update kdg gram right_contexts in
      (* body of helper: *)
      if new_kdg = kdg then kdg else helper new_kdg in
    (* body of get_knowledge: *)
    helper (initial_knowledge gram);;

let get_parse_table (gram:grammar) : parse_table =
  let kdg = get_knowledge gram in
    map (fun (lhs, rhss) ->
          (lhs, (map (fun rhs ->
                        (union (first rhs kdg gram)
                           (if (generates_epsilon rhs kdg gram)
                            then (follow lhs kdg) else []),
                         rhs))
                    rhss)))
      gram;;

(* convert string to list of char *)
let explode (s:string) : char list =
  let rec exp i l = if i < 0 then l else exp (i-1) (s.[i] :: l) in
    exp (String.length s - 1) [];;

(* convert list of char to string
   (This uses imperative features.  It used to be a built-in.) *)
let implode (l:char list) : string =
  let res = Bytes.create (length l) in
  let rec imp i l =
    match l with
      | [] -> Bytes.to_string res
      | c :: l -> Bytes.set res i c; imp (i + 1) l in
    imp 0 l;;

(*******************************************************************
   scanner:
 *******************************************************************)

type token = string * string;;
(*         category * name *)

let tokenize (program:string) : token list =
  let get_id prog =
    let rec gi tok p =
      match p with
        | c :: rest when (('a' <= c && c <= 'z')
                          || ('A' <= c && c <= 'Z')
                          || ('0' <= c && c <= '9') || (c = '_'))
          -> gi (c :: tok) rest
        | _ -> (implode (rev tok), p) in
      gi [] prog in
  let get_int prog =
    let rec gi tok p =
      match p with
        | c :: rest when ('0' <= c && c <= '9')
          -> gi (c :: tok) rest
        | _ -> (implode (rev tok), p) in
      gi [] prog in
  let get_num prog =
    let (tok, rest) = get_int prog in
      match rest with
        | '.' :: c :: r when ('0' <= c && c <= '9')
          -> let (tok2, rest2) = get_int (c :: r) in
              ((tok ^ "." ^ tok2), rest2)
        | _ -> (tok, rest) in
  let rec get_error tok prog =
    match prog with
      | [] -> (implode (rev tok), prog)
      | c :: rest ->
          match c with
            | ':' | '+' | '-' | '*' | '/' | '(' | ')' | '_'
            | '<' | '>' | '=' | 'a'..'z' | 'A'..'Z' | '0'..'9'
              -> (implode (rev tok), prog)
            | _ -> get_error (c :: tok) rest in
  let rec skip_space prog =
    match prog with
      | [] -> []
      | c :: rest -> if (c = ' ' || c = '\n' || c = '\r' || c = '\t')
          then skip_space rest else prog in
  let rec tkize toks prog =
    match prog with
      | []                 -> (("$$" :: toks), [])
      | '\n' :: rest
      | '\r' :: rest
      | '\t' :: rest
      | ' ' :: rest        -> tkize toks (skip_space prog)
      | ':' :: '=' :: rest -> tkize (":=" :: toks) rest
      | '-' :: rest        -> tkize ("-"  :: toks) rest
      | '+' :: rest        -> tkize ("+"  :: toks) rest
      | '/' :: rest        -> tkize ("/"  :: toks) rest
      | '*' :: rest        -> tkize ("*"  :: toks) rest
      | '(' :: rest        -> tkize ("("  :: toks) rest
      | ')' :: rest        -> tkize (")"  :: toks) rest
      | '<' :: '>' :: rest -> tkize ("<>" :: toks) rest
      | '<' :: '=' :: rest -> tkize ("<=" :: toks) rest
      | '<' :: rest        -> tkize ("<"  :: toks) rest
      | '>' :: '=' :: rest -> tkize (">=" :: toks) rest
      | '>' :: rest        -> tkize (">"  :: toks) rest
      | '=' :: '=' :: rest -> tkize ("==" :: toks) rest
      | h :: t -> match h with
        | '0'..'9' -> let (t, rest) = get_num prog in
              tkize (t :: toks) rest
        | 'a'..'z'
        | 'A'..'Z'
        | '_'      -> let (t, rest) = get_id prog in
              tkize (t :: toks) rest
        | c        -> let (t, rest) = get_error [c] t in
              tkize (t :: toks) rest in
  let (toks, _) = (tkize [] (explode program)) in
  let categorize tok =
    match tok with
      | "check" | "do" | "fi"
      | "if"    | "od" | "read" | "write"
      | ":=" | "+"  | "-"  | "*"  | "/"  | "("  | ")"
      | "<"  | "<=" | ">"  | ">=" | "==" | "<>" | "$$"
        -> (tok, tok)
      | _ -> match tok.[0] with
        | '0'..'9' -> ("num", tok)
        | 'a'..'z'
        | 'A'..'Z' | '_' -> ("id", tok)
        | _ -> ("error", tok) in
    map categorize (rev toks);;

(*******************************************************************
   The main parse routine below returns a parse tree (or PT_error if
   the input program is syntactically invalid).  To build that tree it
   employs a simplified version of the "attribute stack" described in
   Section 4.5.2 (pages 50-55) on the PLP companion site.

   When it predicts A -> B C D, the parser pops A from the parse stack
   and then, before pushing D, C, and B (in that order), it pushes a
   number (in this case 3) indicating the length of the right hand side.
   It also pushes A into the attribute stack.

   When it matches a token, the parser pushes this into the attribute
   stack as well.

   Finally, when it encounters a number (say k) in the stack (as opposed
   to a character string), the parser pops k+1 symbols from the
   attribute stack, joins them together into a list, and pushes the list
   back into the attribute stack.

   These rules suffice to accumulate a complete parse tree into the
   attribute stack at the end of the parse.

   Note that everything is done functionally.  We don't really modify
   the stacks; we pass new versions to a tail recursive routine.
 *******************************************************************)

(* Extract grammar from parse-tab, so we can invoke the various routines
   that expect a grammar as argument. *)
let grammar_of (parse_tab:parse_table) : grammar =
  map (fun p -> (fst p, (fold_left (@) [] (map (fun (a, b) -> [b])
                                             (snd p))))) parse_tab;;

type parse_tree =   (* among other things, parse_trees are *)
    | PT_error          (* the elements of the attribute stack *)
    | PT_id of string
    | PT_num of string
    | PT_term of string
    | PT_nt of (string * parse_tree list);;

(* Pop rhs-len + 1 symbols off the attribute stack,
   assemble into a production, and push back onto the stack. *)
let reduce_1_prod (astack:parse_tree list) (rhs_len:int) : parse_tree list =
  let rec helper atk k prod =
    match (k, atk) with
      | (0, PT_nt(nt, []) :: rest) -> PT_nt(nt, prod) :: rest
      | (n, h :: rest) when n <> 0 -> helper rest (k - 1) (h :: prod)
      | _ -> raise (Failure "expected nonterminal at top of astack") in
    helper astack rhs_len [];;

type parse_action = PA_error | PA_prediction of string list;;
(* Double-index to find prediction (list of RHS symbols) for
   nonterminal nt and terminal t.
   Return PA_error if not found. *)
let get_parse_action (nt:string) (t:string) (parse_tab:parse_table) : parse_action =
  let rec helper l =
    match l with
      | [] -> PA_error
      | (fs, rhs) :: rest -> if member t fs then PA_prediction(rhs)
          else helper rest in
    helper (assoc nt parse_tab);;

type ps_item =
    | PS_end of int
    | PS_sym of string;;

(* Parse program according to grammar.
   [Commented-out code would
       print predictions and matches (imperatively) along the way.]
   Return parse tree if the program is in the language; PT_error if it's not. *)
let parse (parse_tab:parse_table) (program:string) : parse_tree =
  let die msg = begin
    print_string ("syntax error: " ^ msg);
    print_newline ();
    PT_error 
  end in
  let gram = grammar_of parse_tab in
  let rec helper pstack tokens astack =
    match pstack with
      | [] ->
          if tokens = [] then
            (* assert: astack is nonempty *)
            hd astack
          else die "extra input beyond end of program"
      | PS_end(n) :: ps_tail ->
          helper ps_tail tokens (reduce_1_prod astack n)
      | PS_sym(tos) :: ps_tail ->
          match tokens with
            | [] -> die "unexpected end of program"
            | (term, tok) :: more_tokens ->
                (* if tok is an individual identifier or number,
                   term will be a generic "id" or "num" *)
                if is_terminal tos gram then
                  if tos = term then
                    begin
              (*
                print_string ("   match " ^ tos);
                print_string
                    (if tos <> term      (* value comparison *)
                         then (" (" ^ tok ^ ")") else "");
                print_newline ();
              *)
                      helper ps_tail more_tokens
                        (( match term with
                            | "id"  -> PT_id tok
                            | "num" -> PT_num tok
                            | _     -> PT_term tok ) :: astack)
                    end
                    (* note push of tok into astack *)
                  else die ("expected " ^ tos ^ " ; saw " ^ tok)
                else (* nonterminal *)
                  match get_parse_action tos term parse_tab with
                    | PA_error -> die ("no prediction for " ^ tos
                                       ^ " when seeing " ^ tok)
                    | PA_prediction(rhs) ->
                        begin
                (*
                  print_string ("   predict " ^ tos ^ " ->");
                  print_string (fold_left (fun a b -> a ^ " " ^ b) "" rhs);
                  print_newline ();
                *)
                          helper ((fold_left (@) [] 
                                     (map (fun s -> [PS_sym(s)]) rhs))
                                  @ [PS_end(length rhs)] @ ps_tail)
                            tokens (PT_nt(tos, []) :: astack)
                        end in
    helper [PS_sym(start_symbol gram)] (tokenize program) [];;

let cg_parse_table = get_parse_table calc_gram;;

let ecg_parse_table = get_parse_table ecg;;

let ecg2_parse_table = get_parse_table ecg2;;
