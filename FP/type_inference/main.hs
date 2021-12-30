import Data.Kind ()

data Term
    = Var String
    | App Term Term
    | Lam String Term
    deriving (Show, Eq)

data Type
    = TVar String
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

fnResult (Fun from to) = to
fnResult _ = error "only for functions"

-- map of variables to types
type Context = (String, Type)
-- map of type variables to types
type Substitution = (String, Type)

find :: (p -> Bool) -> [p] -> p
find p []     = error "Not found"
find p (x:xs) = if p x then x else find p xs

findAssumption :: String -> [Context] -> Type
findAssumption term ctx = snd $ find (\ (var, ty) -> var == term) ctx

findSubstitution :: String -> [Substitution] -> Type
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

s1 :: Substitution
s1 = ("a", TVar "a")
s2 :: Substitution
s2 = ("a", TVar "b")
s3 :: Substitution
s3 = ("a", Fun (TVar "b") (TVar "a"))

composeSubstitutions :: [Substitution] -> [Substitution] -> [Substitution]
composeSubstitutions s1 s2 = substUnion (reverse (map (\ (tvar, ty) -> (tvar, applySubstitution s1 ty)) s2)) s1

-- [("x",TFun (TVar "a") (TVar "b")),("y",TVar "b")]

uniq [] = []
uniq (x:xs) = if x `elem` xs then uniq xs else x:uniq xs

freeTypeVars :: Type -> [String]
freeTypeVars (TVar var) = [var]
freeTypeVars (Fun t1 t2) = uniq $ (freeTypeVars t1) ++ (freeTypeVars t2)

varBind :: String -> Type -> [Substitution]
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

infer :: Term -> [Context] -> Char -> ([Substitution], Type)
infer (Var var) ctx sv = ([], findAssumption var ctx)
infer (Lam var body) ctx sv = (s1, Fun (applySubstitution s1 tyVar) tyBody)
    where
        tyVar = TVar [sv]
        newctx = (var, tyVar):ctx
        (s1, tyBody) = infer body newctx (succ sv)
infer (App fun arg) ctx sv = (subst, applySubstitution s3 tyRes)
    where
        tyRes = TVar [sv]
        (s1, tyFun) = infer fun ctx (succ sv)
        (s2, tyArg) = infer arg (applySubstitutionCtx s1 ctx) (succ $ succ sv)
        s3 = unify (applySubstitution s2 tyFun) (Fun tyArg tyRes)
        subst = composeSubstitutions s3 (composeSubstitutions s2 s1)

-- ПРОБЛЕМИ:
-- Не знам как да генерирам нови уникални tvar имена. Засега ползвам succ с някакъв начален char, но това очевидно няма да работи коректно
-- Трябва да разбера по-подробно какво се случва


