module Group2_fn45708 where

data Base = C | G | A | T
    deriving (Eq, Show)

data GeneticCode = GeneticCode [Base]
    deriving (Eq, Show)

data Codon = Codon Base Base Base
    deriving (Eq, Show)

data Aminoacid = Aminoacid Int
    deriving (Eq, Ord, Show)

type CodingTable = [(Codon, Aminoacid)]
type Gene = [Codon]
type Protein = [Aminoacid]


isEncoded :: CodingTable -> Codon -> Bool
isEncoded ct codon = not $ null $ filter (\(c,_) -> c == codon) ct

toCodons :: GeneticCode -> [Codon]
toCodons (GeneticCode []) = []
toCodons (GeneticCode (x:y:z:xs)) = Codon x y z:toCodons (GeneticCode xs)
toCodons _ = error "Should be divisible by 3"

toGenes :: CodingTable -> [Codon] -> [Gene]
toGenes ct [] = []
toGenes ct cds = slice: toGenes ct (drop (length slice + 1) cds)
    where
        slice :: [Codon]
        slice = takeWhile (isEncoded ct) cds

lookUp :: CodingTable -> Codon -> Aminoacid
lookUp ct codon = if null result then Aminoacid 0 else snd $ head result
    where
        result = filter (\(c,a) -> c == codon) ct

toAminoacid :: CodingTable -> Gene -> Protein
toAminoacid ct = map (lookUp ct)

toAminoacids :: CodingTable -> [Gene] -> [Protein]
toAminoacids ct = map (toAminoacid ct)

existsRepeating :: (Eq a) => [a] -> Bool
existsRepeating [] = False
existsRepeating (x:xs)
    | x `elem` xs = True
    | otherwise   = existsRepeating xs

hasSameProteins :: CodingTable -> GeneticCode -> Bool
hasSameProteins ct gc = existsRepeating $ toAminoacids ct $ toGenes ct $ toCodons gc

difference (Codon x1 y1 z1) (Codon x2 y2 z2) = dx + dy + dz
    where
        dx = if x1 /= x2 then 1 else 0
        dy = if y1 /= y2 then 1 else 0
        dz = if z1 /= z2 then 1 else 0

getMaxMutations :: CodingTable -> Codon -> Int
getMaxMutations ct codon = maximum $ map (difference codon) equivelentCodons
    where
        equivelentCodons = map fst $ filter (\(_, a) -> a == argCodonAminoacid) ct
        argCodonAminoacid = lookUp ct codon

permutations = [  Codon x y z | x <- [C,G,A,T], y <- [C,G,A,T], z <- [C,G,A,T]]

transformCt :: CodingTable -> CodingTable
transformCt ct = [ (c, value c) | c <- permutations]
    where
        value c = lookUp ct c

maxMutations :: CodingTable -> GeneticCode -> Int
maxMutations ct gc = sum $ map (getMaxMutations (transformCt ct)) codons
    where
        codons = toCodons gc
