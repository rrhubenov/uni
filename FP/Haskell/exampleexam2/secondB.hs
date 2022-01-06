transform :: (Num a) => [a] -> (a -> a -> a) -> [a]
transform [] gen = []
transform [x] gen = [x]
transform (x:xs) gen = [x, gen x y] ++ transform xs gen
    where
        y = head xs

merge :: [a] -> [a] -> [[a]]
merge xs ys = [xs, ys]

ls :: [[Integer]]
ls = [1,1]:map (`transform` (+)) ls

stern = concat [ init x | x <- init ls ]