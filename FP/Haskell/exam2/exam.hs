-- n-permutation
isSubset [] _ = True
isSubset (x:xs) s
    | x `elem` s = isSubset xs s
    | otherwise = False

isNPerm n f = codomainL == domainL && isInjective
    where
        domain = [0..n-1]
        domainL = length domain
        codomain = map f [0..n-1]
        codomainL = length codomain
        isInjective = isSubset domain codomain

followCycle :: (Eq a) => a -> (a -> a) -> [a]
followCycle x f = helper x f [x]
    where
        helper x f l
            | f x == last l = reverse l
            | otherwise = helper (f x) f (f x:l)

maxCycle n f = helper [0..n-1] f []
    where
        helper :: (Eq a) => [a] -> (a -> a) -> [a] -> [a]
        helper [] f maxCycle = maxCycle
        helper l@(x:xs) f maxCycle
            | length (followCycle x f) > length maxCycle = helper xs f (followCycle x f)
            | otherwise = helper xs f maxCycle

-- moving average

-- Can't seem to cast the result ot length to float so
-- this nasty trick does the job
mean :: [Float] -> Float
mean l = sum l / len
    where len = foldl (\x y -> x + 1.0) 0.0 l

movingAverage :: [Float] -> Int -> [Float]
movingAverage s n = [ average x | x <- zip s [0..]]
    where average x = mean $ take n $ drop (snd x) s

allAverages s = [gen x | x <- [2..]]
    where gen x = movingAverage s x

-- Иван
type Box = (String, [String])

boxes = [ ("docs", ["ids", "invoices"]), ("ids", ["passport"]),  ("invoices", []), ("memes", []),
        ("family", ["new year", "birthday"]), ("funny", ["memes"]), ("pics", ["family", "funny"]) ]

getBoxes boxes = foldl (\ l (box, _) -> box:l) [] boxes

allObjects :: [Box] -> [String]
allObjects boxes = foldl (\ l (_, items) -> l ++ filter (`notElem` boxNames) items) [] boxes
    where
        boxNames = getBoxes boxes

removeBox :: String -> [Box] -> [Box]
removeBox box [] = []
removeBox box (b:bs)
    | box == fst b = removeBox box bs
    | box `elem` snd b = clean box b:removeBox  box bs
    | otherwise = b:removeBox box bs
        where
            clean box b = (fst b, filter (/= box) (snd b))

isEmpty box = null (snd box)

cleanUp [] = []
cleanUp boxes
    | not (any isEmpty boxes) = boxes
    | otherwise = helper [] boxes
    where
        helper curr [] = reverse curr
        helper curr (b:bs)
            | isEmpty b = helper (removeBox (fst b) curr) (removeBox (fst b) bs)
            | otherwise = helper (b:curr) bs