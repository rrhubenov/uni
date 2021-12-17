
Directed weighted graph

Each edge has 2 weights:
    1) Time it takes to cross edge
    2) Minimum required gear level (Integers)


Input:
    First line: n,m,k
        - n: number of vecrtices
        - m: number of edges
        - k: time to beat or meet
    Next m lines: u,v,c,t
        - u: start vertex of edge
        - v: end vertex of edge
        - c: minimum required gear level for edge
        - t: time needed to cross edge from start to end

Output:
    Minimum required gear level to beat the given time k
    -1 if impossible


# Algorithm steps

1) Find all the paths with time sum <= k. (PRINT -1 IF NONE EXISTS)
2) Print min({for every path, max({gear level of each edge in the path}})
