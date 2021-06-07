#use "translator.ml";;

let zero_denominator_prog = "
a := 10
write a / 0";;

let t = ast_ize_P(parse ecg_parse_table zero_denominator_prog) in
print_string (snd (translate t));