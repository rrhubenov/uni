
-- Generata all possible compositions of functions given a list of functions

comp l = [ (help n l) | n <- [0..]]

f :: Num a => a -> a
f x = x + 1
g :: Num a => a -> a
g x = x + 2

help :: Int -> String -> String
help 0 l = "id"
help n l = [func] ++ "." ++ help (div (n - 1) len) l
    where
        len = length l
        func = l !! mod (n-1) len
