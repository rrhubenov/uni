
foldr' :: (a -> b -> b) -> b -> [a] -> b
foldr' _ nv [] = nv
foldr' op nv (x:xs) = op x (foldr' op nv xs)

-- scanr и scanl да се реализират чрез foldr и foldl ?
-- dropWhile с foldr? може да се ползва zip

max' :: Ord a => [a] -> a
max' = foldr1 (\x y -> if x > y then x else y)