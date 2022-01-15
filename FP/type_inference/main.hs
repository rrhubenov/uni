-- State management
type State = Char
newtype ST a = S (State -> (a, State))

app :: ST a -> State -> (a, State)
app (S st) = st

instance Functor ST where
    -- fmap :: (a->b) -> ST a -> ST b
    fmap f (S st) = S(\state -> let (a, s) = st state in (f a, s))

instance Applicative ST where
    -- pure :: a -> ST a
    pure a = S(\state -> (a, state))

    -- <*> :: ST (a -> b) -> ST a -> ST b
    (<*>) (S fst) (S ast) = S(\s ->
        let
            (f, s') = fst s
            (a, s'') = ast s'
            in (f a, s'')
        )

instance Monad ST where
    -- return :: a -> ST a
    return a = S(\state -> (a, state))

    -- >>= :: ST a -> (a -> ST b) -> ST b
    st >>= f = S (\s ->
        let (a, s') = app st s
        in app (f a) s')

fresh :: ST Type
fresh = S (\c -> (TVar c, succ c))
--

data Term
    = Var String
    | App Term Term
    | Lam String Term
    deriving (Show, Eq)

data Type
    -- = TVar String
    = TVar Char
    | Fun Type Type
    deriving (Eq)


instance Show Type where
    show (Fun t1 t2) = "(" `mappend` mappend (mappend (show t1) " -> ") (show t2) `mappend` ")"
    show (TVar c) = show c


removeFirst [] e = []
removeFirst (x:xs) e = if x == e then xs else x:removeFirst xs e

parse :: String -> Term
parse [x] = Var [x]
parse ('(':xs) = parse (removeFirst xs ')')
parse ('.':xs) = parse xs
parse term
    | '.' `elem` term = Lam [left] (parse right)
    | otherwise = if rightTerm == ')' then App (parse remainingTerm) (parse extractedTerm) else App (parse leftTerm) (parse [rightTerm])
    where left = head term
          right = tail term
          leftTerm = init term
          rightTerm = last term
          remainingTerm = takeWhile (/= '(') leftTerm
          extractedTerm = tail $ init $ dropWhile (/= '(') term

-- map of variables to types
type Context = (String, Type)
-- map of type variables to types
type Substitution = (Char, Type)

find :: (p -> Bool) -> [p] -> p
find p []     = error "Not found"
find p (x:xs) = if p x then x else find p xs

findAssumption :: String -> [Context] -> Type
findAssumption term ctx = snd $ find (\ (var, ty) -> var == term) ctx

findSubstitution :: Char -> [Substitution] -> Type
findSubstitution term subs = snd $ find (\ (cterm, ctype) -> cterm == term) subs

applySubstitution :: [Substitution] -> Type -> Type
applySubstitution subst t@(TVar c) = if substitutionExists then findSubstitution c subst else t
    where
        substitutionExists = any (\(var, ty) -> var == c) subst
applySubstitution subst (Fun t1 t2) = Fun (applySubstitution subst t1) (applySubstitution subst t2)

applySubstitutionCtx :: [Substitution] -> [Context] -> [Context]
applySubstitutionCtx subst = map (\ (var, ty) -> (var, applySubstitution subst ty))

equalSubs :: Substitution -> Substitution -> Bool
equalSubs (var1, _) (var2, _) = var1 == var2

elemSubs s [] = False
elemSubs sub (s:ss) = (sub `equalSubs` s) || elemSubs sub ss

-- Left biased union of substitutions
-- Compares based on key
substUnion :: [Substitution] -> [Substitution] -> [Substitution]
substUnion s1 [] = s1
substUnion [] s2 = s2
substUnion s1 (s:ss) = if s `elemSubs` s1 then substUnion s1 ss else substUnion (s:s1) ss

composeSubstitutions :: [Substitution] -> [Substitution] -> [Substitution]
composeSubstitutions s1 s2 = substUnion (reverse (map (\ (tvar, ty) -> (tvar, applySubstitution s1 ty)) s2)) s1

uniq [] = []
uniq (x:xs) = if x `elem` xs then uniq xs else x:uniq xs

freeTypeVars :: Type -> [Char]
freeTypeVars (TVar var) = [var]
freeTypeVars (Fun t1 t2) = uniq $ freeTypeVars t1 ++ freeTypeVars t2

varBind :: Char -> Type -> [Substitution]
varBind var ty
    | ty == TVar var = []
    | var `elem` freeTypeVars ty = error "occurs check"
    | otherwise = [(var, ty)]

unify :: Type -> Type -> [Substitution]
unify (Fun arg1 res1) (Fun arg2 res2) = composeSubstitutions s1 s2
    where
        s1 = unify arg1 arg2
        s2 = unify (applySubstitution s1 res1) (applySubstitution s1 res2)
unify (TVar var) ty = varBind var ty
unify ty (TVar var) = varBind var ty

infer :: Term -> [Context] -> ST ([Substitution], Type)
infer (Var var) ctx = return ([], findAssumption var ctx)
infer (Lam var body) ctx =
    do
        tyVar <- fresh
        let newctx = (var, tyVar):ctx
        (s1, tyBody) <- infer body newctx
        return (s1, Fun (applySubstitution s1 tyVar) tyBody)
infer (App fun arg) ctx =
    do
        tyRes <- fresh
        (s1, tyFun) <- infer fun ctx
        (s2, tyArg) <- infer arg (applySubstitutionCtx s1 ctx)
        let s3 = unify (applySubstitution s2 tyFun) (Fun tyArg tyRes)
        let subst = composeSubstitutions s3 (composeSubstitutions s2 s1)
        return (subst, applySubstitution s3 tyRes)

run :: String -> Type
run input = snd $ fst $ app (infer (parse input) []) 'a'
