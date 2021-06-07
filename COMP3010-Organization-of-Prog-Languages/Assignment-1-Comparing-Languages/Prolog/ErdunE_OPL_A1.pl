:- initialization(main, main).
slist(X, [X]).
cons(X, R, [X|R]).
appendall(RS, X, RE) :- maplist(cons(X), RS, RE).

cartesian([], []).
cartesian([XS], R) :- maplist(slist, XS, R).
cartesian([X|XS], RE) :- 
  cartesian(XS, RS),
  maplist(appendall(RS), X, RES),
  append(RES, RE).


main :-
  % cartesian([[1, 2, 3], [5, 6]], R),
  cartesian([[1, 2, 3], [5, 6], [7, 8]], R),
  writeln(R).
  
