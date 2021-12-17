
fact :: Integer -> Integer
fact n   | n > 0 = n * fact (n - 1)
         | n == 0 = 1
         | otherwise = error "Invalid input"

sumRange :: Int -> Int -> Int
sumRange x y 
    | x == y = x
    | x < y = x + sumRange (x + 1) y
    | x > y = error "Invalid"
    | otherwise = error "Wut"

fastPow :: Num a => a -> Int -> a
fastPow x p
    | p == 0 = 1
    | p == 1 = x
    | even p = fastPow x (div p 2) ^ 2
    | otherwise = x * fastPow x (p - 1)

elem' :: Eq a => a -> [a] -> Bool 
elem' _ [] = False 
elem' a (x:xs)
    | x == a = True
    | otherwise = elem' a xs

reverseNum :: Int -> Int 
reverseNum x = reverseHelper x 0 where
    reverseHelper n acc = if n == 0 then acc else reverseHelper (div n 10) (10 * acc + mod n 10)

rangeToList :: (Enum a, Ord a) => a -> a -> [a]
rangeToList a b
    | a > b = []
    | a <=  b = a:rangeToList (succ a) b
    | otherwise = error "Invalid"

-- prime
-- palindrome
-- intersection of two lists