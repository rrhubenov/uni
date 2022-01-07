
naturalNums = 1:map (1+) naturalNums
isArithmeticSequence :: [Int] -> Bool
isArithmeticSequence [] = False
isArithmeticSequence [_] = False
isArithmeticSequence [a, b] = True
isArithmeticSequence (a:b:c:rest) = b - a == c - b && isArithmeticSequence (b:c:rest)

generateNumber :: Integral a => a -> Int
generateNumber n = head [x | x <- naturalNums, satisfiesCondition x] where
    satisfiesCondition elem = null ([k | k <- [1..n `div` 2] , isArithmeticSequence[generateNumber(n - 2*k), generateNumber(n-k), elem] ])

forestFire = [generateNumber (n-1) | n <- naturalNums]

-- Двоично дърво наричаме “пълно”, ако има 2n елемента на ниво n. 
-- Да се напише функция growingTrees, която генерира безкраен поток от пълни дървета 
-- с височини съответно 1, 2, 3,..., като всички елементи на ниво n са със стойност n.

data Tree a = EmptyTree | TreeNode a (Tree a) (Tree a) deriving Show

isEmpty EmptyTree = True
isEmpty _         = False

createLeaf n = TreeNode n EmptyTree EmptyTree


isLeaf (TreeNode _ t1 t2) = isEmpty t1 && isEmpty t2
isLeaf _              = False

genFull n val
    | n > 0  = TreeNode val (genFull (n - 1) (val + 1)) (genFull (n - 1) (val + 1))
    | otherwise = createLeaf val

trees = [genFull x 0 | x <- [0..]]