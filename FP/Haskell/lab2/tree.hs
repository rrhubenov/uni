module Tree where

data Tree a = EmptyTree | TreeNode a (Tree a) (Tree a) deriving (Show)

nullTree :: Tree a -> Bool
nullTree EmptyTree = True
nullTree _ = False

isLeaf :: Tree a -> Bool
isLeaf EmptyTree = False
isLeaf (TreeNode _ left right) = nullTree left && nullTree right

makeLeaf :: a -> Tree a
makeLeaf x = TreeNode x EmptyTree EmptyTree

treeMap :: (a -> b) -> Tree a -> Tree b
treeMap _ EmptyTree = EmptyTree
treeMap f (TreeNode x left right) = TreeNode (f x) (treeMap f left) (treeMap f right)

tree = TreeNode 4 (TreeNode 2 EmptyTree (TreeNode 3 EmptyTree EmptyTree))  (TreeNode 5 EmptyTree EmptyTree)


traverseInOrder :: Tree a -> [a]
traverseInOrder EmptyTree = []
traverseInOrder (TreeNode x left right) = traverseInOrder left ++ [x] ++ traverseInOrder right

findTree :: (Eq a, Ord a) => a -> Tree a -> Maybe a
findTree _ EmptyTree = Nothing
findTree val (TreeNode x left right)
    | x == val = Just x
    | x > val  = findTree val left
    | otherwise = findTree val right
