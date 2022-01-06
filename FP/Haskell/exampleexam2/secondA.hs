
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
