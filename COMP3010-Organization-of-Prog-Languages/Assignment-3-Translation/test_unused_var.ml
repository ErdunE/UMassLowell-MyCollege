#use "translator.ml";;

let unused_var_prog = "
read a
b := 1
read c
write a / 2";;

let ast = ast_ize_P(parse ecg_parse_table unused_var_prog) in
print_string (fst (translate ast));