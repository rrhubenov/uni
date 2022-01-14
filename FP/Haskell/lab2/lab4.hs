
import qualified Data.Map as Map

type FN = Int
type Name = String
type Grade = Double

type Class = [(FN, (Name, Grade))]

students :: Class
students = [
    (41111, ("Yordan"  , 5.75)),
    (41112, ("Ivana"   , 5.35)),
    (41113, ("Anton"   , 5.00)),
    (41114, ("Stefan"  , 5.35)),
    (41115, ("Sofiya"  , 3.25)),
    (41116, ("Antoniya", 4.65))
    ]

find :: FN -> Class -> Maybe (Name, Grade)
find _ [] = Nothing
find fn ((facn, info):xs) = if fn == facn then Just info else find fn xs

getFns :: Class -> [FN]
getFns = map fst

aboveAverage :: Class -> [Name]
aboveAverage c = [name | (_, (name, grade)) <- c , grade > average]
    where average  = sum (map (snd . snd) c) / fromIntegral (length c)


studentsMap :: Map.Map FN (Name, Grade)
studentsMap = Map.fromList students

findStudent :: FN -> Map.Map FN (Name, Grade) -> Maybe (Name, Grade)
findStudent = Map.lookup


scholarship :: Map.Map FN (Name, Grade) -> [Name]
scholarship = Map.elems . Map.map fst . Map.filter (\(_, g) -> g >= 5.5)