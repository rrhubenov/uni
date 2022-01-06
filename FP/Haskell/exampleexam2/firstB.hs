type Graph a = [(a, [a])]

g = [(0, [1]), (1, [3]), (3, [2]), (2, [4]), (4, [])]

intersection :: (Eq a) => [a] -> [a] -> [a]
intersection [] _ = []
intersection _ [] = []
intersection (x:xs) l2
    | x `elem` l2 = x:intersection xs l2
    | otherwise = intersection xs l2

parents :: (Eq a) => a -> Graph a -> [a]
parents node g = map fst $ filter (\(_, children) -> node `elem` children) g

children val g = snd $ head $ filter (\(node, ch) -> val == node) g

isFamily :: (Eq a) => [a] -> Graph a -> Bool
isFamily ns g = all (\n -> conditionC n || conditionP n) ns
    where
        conditionC n = (intersection (children n g) ns == children n g) && null (intersection (parents n g) ns)
        conditionP n = (intersection (parents n g) ns == parents n g) && null (intersection (children n g) ns)

setsubtract [] s2 = []
setsubtract (x:xs) s2
    | x `elem` s2 = setsubtract xs s2
    | otherwise   = x:setsubtract xs s2


maxAvoidingHelper :: (Eq a) => [a] -> [a] -> Graph a -> [a]
maxAvoidingHelper l [] g = l
maxAvoidingHelper [] _ _ = []
maxAvoidingHelper _ _ [] = []
maxAvoidingHelper l toRemove g = maxAvoidingHelper remaining removed g
    where
        toRemoveParents = concat $ map (`parents` g) toRemove
        toRemoveChildren = concat $ map (`children` g) toRemove
        remaining = setsubtract (setsubtract l toRemoveChildren) toRemoveParents
        removed = setsubtract l remaining

maxAvoiding :: (Eq a) => [a] -> a -> Graph a -> [a]
maxAvoiding family u g
    | isFamily result g = result
    | otherwise = error "No possible family"
    where
        result = maxAvoidingHelper family [u] g

-- Eg. maxAvoiding [0,1,2,4] 4 g