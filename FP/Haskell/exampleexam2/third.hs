--             shop    cat     price
type Order = ([Char], [Char], Double)
order1::Order
order1 = ("asd", "cat1", 3.2)
order2::Order
order2 = ("asd", "cat1", 3.4)
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

groupBy :: Eq a => (a -> a -> Bool) -> (a -> a -> a) -> [a] -> [a]
groupBy p term [] = []
groupBy p term [a] = [a]
groupBy p term (x:xs) = folded : groupBy p term remaining where
    grouped = x : filter (p x) xs
    folded = if length grouped == 1 then head grouped else foldr1 term grouped
    remaining = subtractSets xs grouped

organize :: [Order] -> [Order]
organize = groupBy (\x y -> getShop x == getShop y && getCat x == getCat y) (\x y -> (getShop x, getCat x, getPrice x + getPrice y))

getMax = groupBy (\x y -> getCat x == getCat y) (\ x y -> if getPrice x > getPrice y then x else y)

final orders = map (\ x -> (getCat x, getPrice x, getShop x)) maxedOut where
    maxedOut = getMax $ organize orders
