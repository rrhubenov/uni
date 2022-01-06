import Data.Maybe (fromMaybe, fromJust)

data Someone = Me | You
    deriving (Show)


whoAmI :: String -> Someone
whoAmI "Tommy" = Me
whoAmI _       = You


data Car = Car {
    getMake :: String,
    getModel :: String,
    getYear :: Int
}
instance Show Car where
    show (Car make model year) = "This is a " ++ make ++ " " ++ model ++ " from " ++ show year


car :: Car
car = Car "Volkswagen" "Golf" 2019

data Day = Monday | Tuesday | Wednesday | Thursday | Friday | Saturday | Sunday
    deriving (Show, Read, Eq, Ord, Enum, Bounded)

lastDayOfWeek = maxBound :: Day



find :: (a -> Bool) -> [a] -> Maybe a
find _ [] = Nothing
find p (x:xs) 
    | p x = Just x
    | otherwise = find p xs

getSomeDay :: Maybe Day -> Day
getSomeDay Nothing = Monday
getSomeDay (Just d) = d
