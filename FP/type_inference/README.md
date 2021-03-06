# Извод на Типове в ламбда смятането

Радослав Хубенов
ФН: 45708, Информатика
Група: 2

Линк към репо на проекта:
https://github.com/rrhubenov/uni/tree/main/FP/type_inference

### Стартиране на програмата

Програмата може да се тества като се подаде файлът на ghci и се извика функцията "run" с аргумент String под формата "{args}.{body}".
Програмата не очаква ламбда да започва с "\", но очаква да има "." между аргументите и тялото й.

### Parsing

Първата част на проекта е превръщането на входа (String) в данни, с които можем да работим.
В този случай това значи програмата да получи текст под формата "{vars}.{body}" и да го превърне в терм.

Пример:
    "yx.xy" -> (Lam x (Lam y (App (Var x) (Var y)))

Добавена е допълнителна логика, която се грижи за реда на операциите спрямо скобите.
След тази част програмата може да започне със самия алгоритъм за извод на типа.

### Общ поглед върху алгоритъма

Когато се опитваме да открием типа на ламбда терм, първа трябва да открием типа на:
    - тялото
    - аргумента

След което знаем, че типа на ламбдата ще бъде (тип на аргумент) -> (тип на тяло)

Започваме с откриването на типа на тялото.

За тази цел изпозлваме структура, която ще кръстим Context, която представлява "mapping" между променлива и типа й.
Тази структура може да се разглежда като базата ни данни за типа на всички променливи, които имаме в дадената ни програма.
Когато искаме да открием типа на дадена променлива, можем да проверим контекста.
Когато открием, че дадена променлива в същност има някой друг тип, минаваме през контекста и сменяме типа й.

Тялото е терм, който може да е от 3 различни типа:
    - ламбда
    - променлива
    - апликация

Ако тялото е променлива, търсим променливата в контекста и връщаме типа й.
Ако тялото е ламбда повтаряме горния процес.
Ако тялото е апликация трябва да открием 3 нови типа:
    - типа на аргумента на апликацията
    - типа на функцията
    - типа на резултата
На базата на тези 3 типа можем да конструираме типа на апликацията.

#### Структурата "Substitutions"

В процеса на търсенето на типа на даден терм може да открием важна информация, която е нужна за предишните типове, които вече сме открили.
Тоест когато открием типа на терм, трябва да връщаме структура, която ще ни даде обратна връзка за допълнителни изводи, които сме направили
за типа на някои термове.

"Mapping"-a между променливите, за които сме открили нова информация и самата информация "новия им тип" наричаме "Substitutions"

Substitutions играе важна роля за правилния извод на типовете. Ако структурата "Context" съдържа текущата информация за всички променливи и този контекст се "подава"
на всеки извод, който се опитваме да направим, то "Substitutions" играе важната роля на "обратна връзка" от информацията за променливите, които сме открили.
Затова след всеки извод, който открием, трябва да получим списък с полагания, които ние трябва да приложим върху контекста ни за да бъде коректен.

Структурата съдържа няколко важни операции, които се използват за правилното й менижиране. Като:
    - composeSubstitutions, която композира две субституции и запазва информацията и от двете
    - substUnion, която помага за правилното композиране на субституции

### Монадът ST
ST представлява трансформация на "state". Използва се за запомняне на последния използван генериран тип и получаването на нов,
който да може да се положи. За тази цел се използва функцията "fresh", която получава "State" (Char) и връща наследникът на този символ.
По този начин няма нужда да се подават допълнителен аргумент на функциите и да се грижим за менижирането на тази променлива.

### Използвани ресурси

От огромна ползва бе презентацията на Christoph Hegemann: [линк към презентацията](https://www.youtube.com/watch?v=ytPAlhnAKro&t)
