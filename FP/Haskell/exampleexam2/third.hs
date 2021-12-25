--             shop    cat     price
type Order = ([Char], [Char], Double)
order1::Order
order1 = ("asd", "cat1", 3.2)
order2::Order
order2 = ("bbb", "cat1", 3.4)
order3::Order
order3 = ("dsa", "cat2", 2.5)

getShop :: Order -> [Char]
getShop (a, _, _) = a

getCat :: Order -> [Char]
getCat (_, a, _) = a

getPrice :: Order -> Double
getPrice (_, _, a) = a

subtractSets xs [] = xs
subtractSets [] _ = []
subtractSets (x:xs) ys = if x `elem` ys then subtractSets xs ys else x : subtractSets xs ys

foldBy :: Eq a => (a -> a -> Bool) -> (a -> a -> a) -> [a] -> [a]
foldBy p f [] = []
foldBy p f [a] = [a]
foldBy p f (x:xs) = folded : foldBy p f remaining where
    grouped = x : filter (p x) xs
    folded = if length grouped == 1 then head grouped else foldr1 f grouped
    remaining = subtractSets xs grouped

organize :: [Order] -> [Order]
organize = foldBy (\x y -> getShop x == getShop y && getCat x == getCat y) (\x y -> (getShop x, getCat x, getPrice x + getPrice y))

getMax = foldBy (\x y -> getCat x == getCat y) (\ (s1, c1, p1) (s2, c2, p2) -> if p1 > p2 then (s1, c1, p1+p2) else (s2, c2, p1+p2))

final orders = map (\ x -> (getCat x, getPrice x, getShop x)) maxedOut where
    maxedOut = getMax $ organize orders
