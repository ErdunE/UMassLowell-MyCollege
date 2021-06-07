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
od
$$