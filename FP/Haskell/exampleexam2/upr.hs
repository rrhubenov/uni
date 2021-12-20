import Data.Binary.Get (remaining)

intersection :: Eq a => [a] -> [a] -> [a]
intersection _ [] = []
intersection [] _ = []
intersection lst1 lst2 = [x | x <- lst1, x `elem` lst2]

prime :: Int -> Bool
prime 1 = False
prime 2 = True
prime x = null ([divisor | divisor <- [2.. x `div` 2], x `mod` divisor == 0])

primeFactorization x
    | prime x = [x]
    | otherwise = p : primeFactorization (x `div` p)
    where primes x = [divisor | divisor <- [2.. x], prime divisor, x `mod` divisor == 0]
          p = head (primes x)

myreverse :: [Char] -> [Char]
myreverse [] = []
myreverse [a] = [a]
myreverse s = last s: myreverse (init s)

palindrome :: [Char] -> Bool
palindrome s = s == myreverse s

mymap :: (a -> b) -> [a] -> [b]
mymap f [] = []
mymap f (x:xs) = f x: mymap f xs

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter f [] = []
myfilter f (x:xs)
    | f x = x: myfilter f xs
    | otherwise = myfilter f xs

mymin :: Ord a => [a] -> a
mymin [] = error "Input"
mymin [a] = a
mymin l = foldr1 (\ x y -> if x < y then x else y) l

addToAll :: Num a => a -> [a] -> [a]
addToAll n = map (+n)

compose' :: (a -> b) -> (c -> a) -> c -> b
compose' f g x = f (g x)

toNeg = negate . abs

turnNegative :: [Int] -> [Int]
turnNegative = map toNeg

naturalNums = 1:map (1+) naturalNums
isArithmeticSequence :: [Int] -> Bool
isArithmeticSequence [] = False
isArithmeticSequence [_] = False
isArithmeticSequence [a, b] = True
isArithmeticSequence (a:b:c:rest) = b - a == c - b && isArithmeticSequence (b:c:rest)

generateNumber 1 = 1
generateNumber 2 = 1
generateNumber n = head [x | x <- naturalNums, k <- [1..n `div` 2], satisfiesCondition x k] where
    satisfiesCondition elem index = not (isArithmeticSequence[generateNumber(n - 2*index), generateNumber(n-index), elem])

forestFire = [generateNumber n | n <- naturalNums]

filterfold p = foldr (\ x acc -> if p x then x : acc else acc) []
