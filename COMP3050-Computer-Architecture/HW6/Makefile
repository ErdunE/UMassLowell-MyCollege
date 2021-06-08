entry:
	gcc linker.c -o linker

run:
	./masm_mrd -o < main.asm > main.obj
	./masm_mrd -o < rbsywt.asm > rbsywt.obj
	./masm_mrd -o < readint.asm > readint.obj
	./masm_mrd -o < xbsywt.asm > xbsywt.obj
	./linker main.obj rbsywt.obj readint.obj xbsywt.obj > target.bin
	cat target.bin