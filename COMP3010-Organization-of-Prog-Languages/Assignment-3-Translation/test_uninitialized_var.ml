#use "translator.ml";;

let uninitialized_var_prog = "
write a / 2";;

let ast = ast_ize_P(parse ecg_parse_table uninitialized_var_prog) in
print_string (snd (translate ast));