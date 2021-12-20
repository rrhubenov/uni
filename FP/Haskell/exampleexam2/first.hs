getChildren _ [] = []
getChildren x (l:ls)
    | x == head l = tail l
    | otherwise = getChildren x ls

g = [[1, 2, 3,7], [2, 5], [3, 5, 4], [4, 6], [5], [7, 4], [6]]

getParents :: (Eq a) => a -> [[a]] -> [a]
getParents x [] = []
getParents x (l:ls)
    | x `elem` tail l = head l : getParents x ls
    | otherwise = getParents x ls
subset [] l = False
subset xs l = foldr (\ x -> (&&) (x `elem` l)) True xs

isEmptyIntersection [] l = True
isEmptyIntersection (x:xs) l
    | x `elem` l = False
    | otherwise = isEmptyIntersection xs l

hasFamily x l g = (children `subset` l && isEmptyIntersection parents l) || (parents `subset` l && isEmptyIntersection children l)
    where children = getChildren x g
          parents  = getParents x g
          rest     = tail l

isFamilyHelper xs l g
  = foldr (\ x -> (&&) (hasFamily x l g)) True xs

isFamily [] g = True
isFamily [x] g = hasFamily x [x] g
isFamily l g = isFamilyHelper l l g
    where element = head l
          next = head (tail l)

subtractSets xs [] = xs
subtractSets [] _ = []
subtractSets (x:xs) ys = if x `elem` ys then subtractSets xs ys else x : subtractSets xs ys

eq l1 l2 = null (subtractSets l1 l2) && null (subtractSets l2 l1)

union [] l2 = l2
union (x:xs) l2 = if x `elem` l2 then xs `union` l2 else x:union xs l2

genFamily :: Eq a => [a] -> [[a]] -> Bool -> [a]
genFamily [] _ g = []
genFamily nodes g startWithChildren
    | isFamily nodes g = nodes
    | startWithChildren = if resultWithChildren `eq` nodes then nodes else genFamily resultWithChildren g False
    | otherwise = if resultWithParents `eq` nodes then nodes else genFamily resultWithParents g True
    where
        children [] = []
        children (x:xs) = getChildren x g `union` children xs
        parents [] = []
        parents (x:xs) = getParents x g `union` parents xs
        resultWithChildren = nodes `union` children nodes
        resultWithParents = nodes `union` parents nodes


addParents x g = x:getParents x g
addChildren x g = x:getChildren x g
