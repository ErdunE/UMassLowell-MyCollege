
masm_mrd: mic1symasm_mrd.o lex.yy.o
	gcc -o masm_mrd mic1symasm_mrd.o lex.yy.o
mic1symasm_mrd.o:  mic1symasm_mrd.c
	gcc -c -g mic1symasm_mrd.c
lex.yy.c: mic1symasm_mrd.ll
	flex mic1symasm_mrd.ll
lex.yy.o:  lex.yy.c
	gcc -c -g lex.yy.c
clean:
	rm lex.yy.o lex.yy.c mic1symasm_mrd.o masm_mrd
