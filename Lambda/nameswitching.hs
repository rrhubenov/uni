data NLL = NLVar Int | NLApp NLL NLL | NLAbs NLL
        deriving Show

data NL = NVar String | NApp NL NL | NAbs String NL
        deriving Show

type Context = [String]

addName :: NLL -> Context -> NL
addName (NLVar x) c     = NVar $ c !! x
    where lc = length c
addName (NLApp m1 m2) c = NApp (addName m1 c) (addName m2 c)
addName (NLAbs m) c     = NAbs xn (addName m newContext)
    where
        cl = length c
        xn = "x" ++ show cl
        newContext = xn:c

findVarIndex :: Context -> String -> Int
findVarIndex c name = snd $ head $ filter (\x -> name == fst x) (zip c [0..])

removeName :: NL -> Context -> NLL
removeName (NVar x) c     = NLVar $ findVarIndex c x
removeName (NApp m1 m2) c = NLApp (removeName m1 c) (removeName m2 c)
removeName (NAbs bv m) c  = NLAbs (removeName m (bv:c))


