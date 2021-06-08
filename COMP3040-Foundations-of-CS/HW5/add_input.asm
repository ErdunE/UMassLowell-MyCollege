start:
        loco pstr:
        push
        call showstr:
        insp 1
        call readint:
        stod binnum:
        loco pstr:
        push
        call showstr:
        insp 1
        call readint:
        addd binnum:
        jneg overflow:
        stod sum:
        loco opstr:
        push
        call showstr:
        insp 1
        lodd sum:
        push
        call shownum:
        loco 0
        jump done:
overflow:
        loco ostr:
        push
        call showstr:
        lodd cneg1:
done:
        insp 1
        halt
        retn

showstr:
        lodd on:
        stod 4095
        call xbsywt:
        lodl 1
nextw:  
        pshi
        addd c1:
        stod strptr:
        pop
        jzer crnl:
        stod 4094
        push
        subd c255:
        jneg crnl:
        call sb:
        insp 1
        push
        call xbsywt:
        pop
        stod 4094
        call xbsywt:
        lodd strptr:
        jump nextw:
crnl:
        lodd cr:
        stod 4094
        call xbsywt:
        lodd nl:
        stod 4094
        call xbsywt:
        lodd on:
        stod 4093
        insp 1
        retn
readint:
        call rbsywt:
        lodd 4092
        subd numoff:
        push
nxtdig:
        call rbsywt:
        lodd 4092
        stod nxtchr:
        subd nl:
        jzer endnum:
        mult 10
        lodd nxtchr:
        subd numoff:
        addl 0
        stol 0
        jump nxtdig:
endnum:
        pop
        retn

shownum:
        lodl 1
        stod i1:
        loco 0
        push
loop2:
        loco 10
        push
        lodd i1:
        push
        div
        pop
        stod i1:
        pop
        addd numoff:
        stod bit:
        pop
        pop
        lodd bit:
        push
        lodd i1:
        jzer output1:
        jump loop2:
output1:
        lodd on:
        stod 4095
        call xbsywt:
loop3:
        pop
        stod 4094
        jzer output2:
        jump loop3:
output2:
        lodd cr:
        stod 4094
        call xbsywt:
        lodd nl:
        stod 4094
        call xbsywt:
        retn
xbsywt:
        lodd 4095
        subd mask:
        jneg xbsywt:
        retn
rbsywt:
        lodd 4093
        subd mask:
        jneg rbsywt:
        retn
sb:
        loco 8
loop1:
        jzer finish:
        subd c1:
        stod lpcnt:
        lodl 1
        jneg add1:
        addl 1
        stol 1
        lodd lpcnt:
        jump loop1:
add1:
        addl 1
        addd c1:
        stol 1
        lodd lpcnt:
        jump loop1:
finish:
        lodl 1
        retn

numoff: 48
nxtchr: 0
binnum:	0
lpcnt:  0
mask:   10
on:     8
nl:     10
cr:     13
c1:     1
c255:   255
strptr:  0
pstr:   "PLEASE ENTER AN INTEGER BETWEEN 1 AND 32767"
opstr:	"THE SUM OF THESE INTEGERS IS:"
ostr:	"OVERFLOW, NO SUM POSSIBLE"
sum:	0
bit:	0
cneg1: -1
i1: 0
