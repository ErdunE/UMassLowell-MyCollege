#use "translator.ml";;

let ast = ast_ize_P(parse ecg_parse_table primes_prog) in
print_string (snd (translate ast));