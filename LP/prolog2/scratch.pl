% remove X LIST RESULT
remove(X, [X|TAIL], TAIL).
remove(X, [HEAD|TAIL], [HEAD|NEWTAIL]) :- remove(X, TAIL, NEWTAIL).

% remove all
removeAll(_, [], []).
removeAll(X, [X|TAIL], NEWTAIL) :- remove(X, TAIL,NEWTAIL).
removeAll(X, [HEAD|TAIL], [HEAD|NEWTAIL]) :- remove(X, TAIL, NEWTAIL).


isSorted([]).
isSorted([_|[]]).
isSorted([X,Y|TAIL]) :- X =< Y, isSorted(TAIL).

pair(LIST, [X,Y]) :- append(_, [X,Y|_], LIST).

lessOrEqual(X, Y) :- X =< Y.
isSorted2(LIST) :- not((pair(LIST, [X,Y]), not(lessOrEqual(X, Y)))).


% p1(X, Y) <-> има ел. на Х, който е в ел. на Y
p1(X, Y) :- member(X1, X), member(Y1, Y), member(X1, Y1), !.
% p2(X, Y) <-> има ел. на Х, който е във всеки ел. на Y
p2(X, Y) :- member(X1, X), not((member(Y1, Y), not(member(X1, Y1)))), !.
% p3(X, Y) <-> всеки ел. на Х, е в ел. на Y
p3(X, Y) :- not((member(X1, X), not((member(Y1, Y), member(X1, Y1))))).
% p4(X, Y) <-> всеки ел. на Х, е във всеки ел. на Y
p4(X, Y) :- not((member(X1, X), member(Y1, Y), not(member(X1, Y1)))).


prefix(P, L) :- append(P, _, L).
suffix(S, L) :- append(_, S, L).
infix(I, L) :- prefix(P, L), suffix(I, P).


% Нивка - Краен списък от двуелементни списъци,
% вторият член на всеки от които е число и всеки два различни члена на L имат различни първи членове.
% Парче от една нивка L множестов, чиито елементи са първи членове от елементи на L.
% Размер на едно парче A = {a1,a2,...,an} на нивката L е числото RL(A) = p1 + p2 + .. + pn,
% където [a1, p1],[a2, p2],..,[an,pn] са членове на L.
% Да се дефинира на пролог предикат indepen(L), който по дадена нивка L  разпознава дали поне две такива
% различни парчета A и B на L, A ссечение В != 0 и RL(A сечение B) = RL(A)RL(B)

different([X | _], [Y | _]) :- X =\= Y.

car([X | _], X).
cdr([_ | X], X).

equal([X, X], [X, X]).

unique([]).
unique([X | T]) :- not((member(Y, T), X == Y)), unique(T).

nivka([]).
nivka([X | T]) :- nivka(T), not((member(Y, T), car(X, X1), car(Y, Y1), X1 == Y1)).

piece([], []).
piece([_|NT], P) :- piece(NT, P).
piece([[NHH| _] |NT], [NHH|PT]) :- piece(NT, PT).

subset([], _).
subset([H|T], Y) :- member(H, Y), subset(T, Y).

equalSets(X, Y) :- subset(X, Y), subset(Y, X).

intersect([], _, []).
intersect(_, [], []).
intersect([X|T1], L2, [X|IT]) :- member(X, L2), intersect(T1, L2, IT).
intersect([X|T1], L2, I) :- not(member(X, L2)), intersect(T1, L2, I).

isEmptySet([]).

rl([], _, 0).
rl([H|T], N, S) :- member([H , Val | _], N), rl(T, N, P), S is Val + P. 

asd(N) :- piece(N, A1), piece(N, A2), not(equalSets(A1, A2)), intersect(A1,A2,I), not(isEmptySet(I)), rl(I, N, Irl), rl(A1, N, A1rl), rl(A2, N, A2rl), Irl is A1rl * A2rl.

lCheck(L, X, Y, C) :- member([X | FX], L), member([Y | FY], L), abs(FX - FY) =< C * abs(X - Y).
isLip(L, C) :- not((member([X1|_], L), member([X2|_], L), not(lCheck(L,X1,X2,C)))).

isAcceptableBase([], _).
isAcceptableBase([[_|Author] | T], S2) :- not(member([_ | Author], S2)), isAcceptableBase(T, S2).
isAcceptable(Shelf1, Shelf2, Shelf3) :- isAcceptableBase(Shelf1, Shelf2), isAcceptableBase(Shelf1, Shelf3), isAcceptableBase(Shelf2, Shelf3).

disbalance(S1, S2, S3, D) :- length(S1, S1L), length(S2, S2L), length(S3, S3L), 
                        abs(S1L - S2L, S12), abs(S1L - S3L, S13), abs(S2L - S3L, S23),
                        D is (S12 + S13 + S23) / 3.

exUnique([], []).
exUnique([H | T], Res) :- member(H, T), exUnique(T, Res), !.
exUnique([H | T], Res) :- not(member(H, T)), exUnique(T, R), append([H], R, Res).


isList([]).
isList([_|_]).

flatten1([], []).
flatten1(X, [X]) :- not(isList(X)).
flatten1([H|T], R) :- flatten1(H, FH), flatten1(T, FT), append(FH, FT, R).

flatten(L, R) :- isList(L), flatten1(L, R).

nat(0).
nat(N) :- nat(X), N is X + 1.

% between(A, A, B) :- A =< B.
% between(X, A, B) :- A < B, A1 is A + 1, between(X, A1, B).

gen_pair_nats(X, Y) :- nat(N), between(X, 0, N), Y is N - X.

% gen_fin_subset_Nat(S) :- 

% partition(L, P) :- P is a partitioning of L. Ex. L = [1,2,3], P = [[1], [2,3]]
partition([], []).
partition([LH | LT], [[LH] | PT]) :- partition(LT, PT).
% partition([LH | LT], [NewPart | PT]) :- partition(LT, [PH | PT]), append([LH], PH, NewPart).
partition([LH | LT], [ [LH | HP] | TP]) :- partition(LT, [HP | TP]).


r(A, _, A).
r(A, B, M) :- A < M, NewVal is 5 * B * B + 3 * A * A * A, r(B, NewVal, M).

p(A) :- not(r(0, 1, A)).

helper(A, B, X) :- X is 5 * B * B + 3 * A * A * A.
helper(A, B, X) :- Curr is 5 * B * B + 3 * A * A * A, helper(B, Curr, X).
gen(0).
gen(1).
gen(X) :- helper(0, 1, X).


gcd(X, 0, X).
gcd(X, Y, GCD) :-
    Y > 0,
    R is X mod Y,
    gcd(Y, R, GCD).

isPrime(X) :- L is X - 1, not((between(2, L, A), not(gcd(X, A, 1)))).

isGayPrime(N) :- isPrime(N), N mod 6 =:= 1.

primes1counter(I, Curr, 0) :- Curr >= I.
primes1counter(I, Curr, Count) :- Curr < I, isGayPrime(Curr), Curr1 is Curr + 1, primes1counter(I, Curr1, Count1), Count is Count1 + 1.
primes1counter(I, Curr, Count) :- Curr < I, not(isGayPrime(Curr)), Curr1 is Curr + 1, primes1counter(I, Curr1, Count).

xi(I, C) :- primes1counter(I, 2, C).

su(X) :- between(1, X, I), xi(I, C), X =:= I + C.

nats(0).
nats(X) :- nats(X1), X is 1 + X1.

sugen(N) :- nats(N), not(su(N)).

gen_KS(1, S, [S]).
gen_KS(K, S, [H | T]) :-
    K > 0,
    between(0, S, H),
    NS is S - H,
    K1 is K - 1,
    gen_KS(K1, NS, T).

nat_pairs(X, Y) :- nats(N), gen_KS(2, N, [X, Y]).


gen_triples(X, Y, Z) :- nat(N), gen_KS(3, N, [X, Y, Z]).

gen_arith_progression(_, _, 0, []).
gen_arith_progression(Start, _, 1, [Start]).
gen_arith_progression(Start, Jump, Length, [Start | T]) :- 
    Length > 1,
    NewStart is Start + Jump,
    NewLength is Length - 1,
    gen_arith_progression(NewStart, Jump, NewLength, T).

gen_arith(X) :- gen_triples(Start, Jump, Length), Length =\= 0, gen_arith_progression(Start, Jump, Length, X), not((member(X1, X), isPrime(X1))).

my_member(X, [X | _]).
my_member(X, [Y | T]) :- X =\= Y, my_member(X, T).
