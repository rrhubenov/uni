-- This file contains the solutions to problems 2.5 and 2.11


-- Nameless lambda term
data NLL = NLVar Int | NLApp NLL NLL | NLAbs NLL

-- Named lambda term
data L = Var String | App L L | Abs String L

instance Show L where
        show (Var x)     = x
        show (App m1 m2) = show m1 ++ show m2
        show (Abs x m)   = "(λ" ++ x ++ "." ++ show m ++ ")"

instance Show NLL where
        show (NLVar x)     = show x
        show (NLApp m1 m2) = (show m1) ++ (show m2)
        show (NLAbs m)     = "(λ" ++ show m ++ ")"

toSet :: (Eq a) => [a] -> [a]
toSet [] = []
toSet (x:xs) 
        | elem x xs = toSet xs
        | otherwise = [x] ++ toSet xs

removeFromList x = filter (/= x) 

freeVars :: L -> [String]
freeVars (Var v) = [v]
freeVars (App m1 m2) = toSet $ freeVars m1 ++ freeVars m2 
freeVars (Abs bv m)  = removeFromList bv $ freeVars m

boundVars :: L -> [String]
boundVars (Var v) = []
boundVars (App m1 m2) = toSet $ boundVars m1 ++ boundVars m2
boundVars (Abs bv m) = bv:(boundVars m)


renameTerm (Var x) y z 
        | y == x = (Var z)
        | otherwise = (Var x)
renameTerm (App m1 m2) x y = (App (renameTerm m1 x y) (renameTerm m2 x y))
renameTerm (Abs x body) y z
        | x == y = (Abs x body)
        | otherwise = (Abs x (renameTerm body y z))

intersection [] ys = []
intersection (x:xs) ys 
        | x `elem` ys = x:(intersection xs ys)
        | otherwise = intersection xs ys

isCorrect :: L -> [String] -> Bool
isCorrect l xs = (intersection bv xs) == []
        where bv = boundVars l

correctify :: L -> [String] -> L
correctify (Var x) xs = (Var x)
correctify (App m1 m2) xs = (App (correctify m1 xs) (correctify m2 xs))
correctify (Abs x m) xs
        | x `elem` xs = (Abs newName (correctify (renameTerm m x newName) xs))
        | otherwise = (Abs x (correctify m xs))
        where newName = x ++ "1"

-- Problem 2.5
substitute :: L -> String -> L -> L
substitute (Var x) y n 
        | x == y = n
        | otherwise = (Var x)
substitute (App m1 m2) x n = (App (substitute m1 x n) (substitute m2 x n))
substitute a@(Abs x p) y n
        | x == y = (Abs x p)
        | isCorrect a (freeVars n) = (Abs x (substitute p y n))
        | otherwise = substitute (correctify a (freeVars n)) y n

badExample = (Abs "x" (Var "y"))

shift :: NLL -> Int -> Int -> NLL
shift (NLVar k) c d 
        | (0 <= k) && (k < c) = (NLVar k)
        | otherwise = (NLVar (k + d))
shift (NLApp m1 m2) c d = (NLApp (shift m1 c d) (shift m2 c d))
shift (NLAbs m) c d = (NLAbs (shift m (c + 1) d) )

-- Problem 2.11
substituteNL :: NLL -> Int -> NLL -> NLL
substituteNL (NLVar x) k n 
        | k == x = n
        | otherwise = (NLVar x)
substituteNL (NLApp m1 m2) k n = (NLApp (substituteNL m1 k n) (substituteNL m2 k n))
substituteNL (NLAbs m) k n     = (NLAbs (substituteNL m (k + 1) (shift n 0 1)))

substituteNLExample = (NLApp (NLVar 0) (NLAbs (NLApp (NLVar 0) (NLVar 1))))
