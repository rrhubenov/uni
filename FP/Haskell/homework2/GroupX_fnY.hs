module GroupX_fnY where

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
lookUp ct codon = snd $ head $ filter (\(c,a) -> c == codon) ct

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

{-

    map every codon c:
        Let A = set of equivelent codons to c (equivalent meaning they map to the same aminoacid)
        from A find the most different codon from our codon c (meaning most changes will be needed to make them equal)
        get the number of changes (mutations) that this gives us.
        map to this number.
    sum the resulting list
        

-}

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


maxMutations :: CodingTable -> GeneticCode -> Int
maxMutations ct gc = sum $ map (getMaxMutations ct) codons
    where
        codons = toCodons gc

-- Need to handle stop codons

standardCoding :: CodingTable
standardCoding =
    map (\(c, n) -> (c, Aminoacid n))
        [ (Codon T T T, 1),    (Codon T C T, 6),    (Codon T A T, 10),    (Codon T G T, 17)
        , (Codon T T C, 1),    (Codon T C C, 6),    (Codon T A C, 10),    (Codon T G C, 17)
        , (Codon T T A, 2),    (Codon T C A, 6) {-, (Codon T A A, !!),    (Codon T G A, !!) -}
        , (Codon T T G, 2),    (Codon T C G, 6), {- (Codon T A G, !!), -} (Codon T G G, 18)

        , (Codon C T T, 2),    (Codon C C T, 7),    (Codon C A T, 11),    (Codon C G T, 19)
        , (Codon C T C, 2),    (Codon C C C, 7),    (Codon C A C, 11),    (Codon C G C, 19)
        , (Codon C T A, 2),    (Codon C C A, 7),    (Codon C A A, 12),    (Codon C G A, 19)
        , (Codon C T G, 2),    (Codon C C G, 7),    (Codon C A G, 12),    (Codon C G G, 19)

        , (Codon A T T, 3),    (Codon A C T, 8),    (Codon A A T, 13),    (Codon A G T,  6)
        , (Codon A T C, 3),    (Codon A C C, 8),    (Codon A A C, 13),    (Codon A G C,  6)
        , (Codon A T A, 3),    (Codon A C A, 8),    (Codon A A A, 14),    (Codon A G A, 19)
        , (Codon A T G, 4),    (Codon A C G, 8),    (Codon A A G, 14),    (Codon A G G, 19)

        , (Codon G T T, 5),    (Codon G C T, 9),    (Codon G A T, 15),    (Codon G G T, 20)
        , (Codon G T C, 5),    (Codon G C C, 9),    (Codon G A C, 15),    (Codon G G C, 20)
        , (Codon G T A, 5),    (Codon G C A, 9),    (Codon G A A, 16),    (Codon G G A, 20)
        , (Codon G T G, 5),    (Codon G C G, 9),    (Codon G A G, 16),    (Codon G G G, 20)
        ]
