import Data.Binary.Get (isEmpty)
import Data.Sequence (Seq(Empty))


type Vertex = Char
type Neighbors = [Vertex]

type Graph = [(Vertex, Neighbors)]

graph :: Graph
graph = [
    ('a', ['b', 'e']),
    ('b', ['c', 'd']),
    ('c', ['f']),
    ('d', ['c']),
    ('e', []),
    ('f', [])
    ]



children :: Graph -> Vertex -> Neighbors
children [] _ = error "Empty Graph"
children (x:xs) v = if fst x == v then snd x else children xs v

data Stack a = EmptyStack | Stack { top::a, rest :: Stack a } deriving (Eq)
instance Show a => Show (Stack a) where
    show stack = "Stack(" ++ showHelper stack [] ++ ")" where
        showHelper EmptyStack result = show result
        showHelper stack result = showHelper (rest stack) (result ++ [top stack])

stackTest = Stack 1 (Stack 2 (Stack 3 EmptyStack))

isEmpty :: Stack a -> Bool
isEmpty EmptyStack = True
isEmpty _          = False

push :: Stack a -> a -> Stack a
push EmptyStack x = Stack x EmptyStack
push stack x      = Stack x stack

pushMultiple :: Stack a -> [a] -> Stack a
pushMultiple = foldl push


dfs :: Graph -> Vertex -> [Vertex]
dfs [] _    = error "EmptyGraph"
dfs g@(x:xs) v = dfsHelper (Stack v EmptyStack) [] where
    dfsHelper EmptyStack _        = []
    dfsHelper (Stack t r) visited
        | t `elem` visited = dfsHelper r visited
        | otherwise = t : dfsHelper (pushMultiple r (children g t)) (t:visited)

