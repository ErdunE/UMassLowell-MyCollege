
def cartesian(xs):
    if len(xs) == 1:
        return set((i,) for i in xs[0])
    elif not xs:
        return []
    else:
        ans = set()
        res = cartesian(xs[1:])
        for i in xs[0]:
            for j in res:
                ans.add(tuple([i] + list(j)))
        return ans

print(cartesian([[1, 2, 3], [8, 9, 0], ['a', 'b', 'c']]))
