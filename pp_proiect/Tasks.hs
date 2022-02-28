{-
    PP Project 2021

    This is where you will write the implementation for the given tasks.
    You can add other modules aswell.
-}
{-# LANGUAGE ExistentialQuantification #-}
{-# LANGUAGE FlexibleInstances #-}

module Tasks where

import Dataset
import Data.List
import Text.Printf
import Data.Char
import Data.Maybe

type CSV = String
type Value = String
type Row = [Value]
type Table = [Row]

{-
    TASK SET 1
-}

my_read :: String -> Float
my_read x
     | x == "" = 0
     | otherwise = read x

my_read_2 :: String -> Int
my_read_2 x
     | x == "" = 0
     | otherwise = read x

convertRow :: Row -> [Float]
convertRow l = foldr ((:).(my_read)) [] l

convertTable :: Table -> [[Float]]
convertTable = map convertRow

compute_grade_aux :: [Float] -> Float
compute_grade_aux l = (foldr (+) 0 (take 6 l)) / 4 + (last l)

compute_and_convert :: [String] -> String
compute_and_convert = printf "%.2f".compute_grade_aux.convertRow.tail

write_row :: [String] -> [String]
write_row l = [head l]++[compute_and_convert l]

-- Task 1
compute_exam_grades :: Table -> Table
compute_exam_grades t = ["Nume","Punctaj Exam"]:map write_row (tail t)

check :: String -> Int
check x
    | (my_read x) >= 2.5 = 1
    | otherwise = 0

count :: [String] -> Int
count x = check $ last x 
 
-- Task 2
-- Number of students who have passed the exam:
get_passed_students_num :: Table -> Int
get_passed_students_num t = foldr ((+).count) 0 (tail $ compute_exam_grades t)

-- Percentage of students who have passed the exam:
get_passed_students_percentage :: Table -> Float
get_passed_students_percentage t = (fromIntegral (get_passed_students_num t)) / (fromIntegral (length t - 1))

-- Average exam grade
get_exam_avg :: Table -> Float
get_exam_avg t = (foldr ((+).my_read.last) 0 (tail $ compute_exam_grades t)) / (fromIntegral (length t - 1))

compute_hw :: [Float] -> Float
compute_hw l = foldr (+) 0 (take 3 (drop 2 l))

get_hw_score :: [String] -> Float
get_hw_score x = compute_hw (convertRow x)

get_hw_list :: Table -> [Float]
get_hw_list t = map get_hw_score (tail t)

-- Number of students who gained at least 1.5p from homework:
get_passed_hw_num :: Table -> Int
get_passed_hw_num t = length (filter (>=1.5) (get_hw_list t))

sum_lines :: [[Float]] -> [Float]
sum_lines [x] = x
sum_lines (x:xs) = zipWith (+) x (sum_lines xs)

float_line_to_string :: [Float] -> [String]
float_line_to_string l = map (printf "%.2f") (take 6 l)

print_q :: [[Float]] -> [[String]]
print_q t = map float_line_to_string t

eliminate_names_and_first_row :: Table -> Table
eliminate_names_and_first_row t = map tail (tail t)

get_sum :: Table -> [Float]
get_sum t = sum_lines (convertTable (eliminate_names_and_first_row t))

divide_list_by_number :: Float -> [Float] -> [Float]
divide_list_by_number x l = map (/x) l

number_of_students :: Table -> Int
number_of_students t = length t - 1

get_avg_q_string :: Table -> [String]
get_avg_q_string t = float_line_to_string (divide_list_by_number (fromIntegral (number_of_students t) :: Float) (get_sum t))

-- Task 3
get_avg_responses_per_qs :: Table -> Table
get_avg_responses_per_qs t = ["Q1","Q2","Q3","Q4","Q5","Q6"]:[get_avg_q_string t]

auxiliar :: [Int] -> [Int] -> [Int]
auxiliar l [] = l
auxiliar (x:y:z:xs) (p:ps) 
    | p == 0 = auxiliar ((x+1):y:z:xs) ps
    | p == 1 = auxiliar (x:(y+1):z:xs) ps
    | p == 2 = auxiliar (x:y:(z+1):xs) ps

count_matrix :: [[Int]] -> [[Int]]
count_matrix l = map  (auxiliar [0,0,0]) l

convertRow_2 :: Row -> [Int]
convertRow_2 l = foldr ((:).(round).(my_read)) [] l

convertTable_2 :: Table -> [[Int]]
convertTable_2 = map convertRow_2

parse_table :: Table -> [[Int]]
parse_table t = transpose (convertTable_2 $ eliminate_names_and_first_row t)

convert_table_to_string :: [[Int]] -> Table
convert_table_to_string t = map (map show) t

get_q_n_table :: Table -> Table
get_q_n_table t = convert_table_to_string  (count_matrix  (parse_table t))

add_q_number :: [String] -> [[String]] -> [[String]]
add_q_number a l = zipWith (:) a l

-- Task 4
get_exam_summary :: Table -> Table
get_exam_summary t = ["Q","0","1","2"]:(add_q_number (take 6 (tail $ head t)) (get_q_n_table t))

my_compare :: [String] -> [String] -> Ordering
my_compare a b 
       | a!!1 < b!!1 = LT
       | a!!1 > b!!1 = GT
       | (a!!1 == b!!1) && (a!!0 < b!!0) = LT
       | otherwise = GT

-- Task 5
get_ranking :: Table -> Table
get_ranking t = ["Nume","Punctaj Exam"]:(sortBy my_compare (tail (compute_exam_grades t)))

compute_diff_aux :: [Float] -> Float
compute_diff_aux l = abs ((compute_question_scores l) - (last l))

compute_question_scores :: [Float] -> Float
compute_question_scores l = (foldr (+) 0 (take 6 l)) / 4

get_question_scores :: [String] -> String
get_question_scores = (printf "%.2f").compute_question_scores.convertRow.tail 

compute_and_convert_diff :: [String] -> String
compute_and_convert_diff = (printf "%.2f").compute_diff_aux.convertRow.tail

write_row_diff :: [String] -> [String]
write_row_diff l = [head l]++[get_question_scores l]++[printf "%.2f" (my_read (last l))]++[compute_and_convert_diff l]

get_unsorted_table :: Table -> Table
get_unsorted_table t = map write_row_diff (tail t)

my_compare_2 :: [String] -> [String] -> Ordering
my_compare_2 a b 
       | my_read (a!!3) < my_read (b!!3) = LT
       | my_read (a!!3) > my_read (b!!3) = GT
       | (my_read (a!!3) == my_read (b!!3)) && (a!!0 < b!!0) = LT
       | otherwise = GT

-- Task 6
get_exam_diff_table :: Table -> Table
get_exam_diff_table t = ["Nume","Punctaj interviu","Punctaj scris","Diferenta"]:sortBy my_compare_2 (get_unsorted_table t) 


--TASK SET 2

split_by :: Char -> String -> [String]
split_by del l = foldr aux [""] l
    where 
        aux el (x:xs)
            | el == del = []:(x:xs)
            | otherwise = (el:x):xs

read_csv :: String  -> Table
read_csv s = map (split_by ',') (split_by '\n' s)

row_to_string :: [String] -> String
row_to_string l = (init (foldr ((++).(++",")) [] l)) ++ "\n"

write_csv :: Table -> String
write_csv t = init (foldr ((++).(row_to_string)) [] t)

thing :: String -> Table -> [String]
thing s t
    | t == [] = []
    | s == head (head t) = tail (head t)
    | otherwise = thing s (tail t)

-- Task 1
as_list :: String -> Table -> [String]
as_list s t = thing s (transpose t)

my_compare_for_task_2 :: Int -> [String] -> [String] -> Ordering
my_compare_for_task_2 i a b
       | a!!i < b!!i = LT
       | a!!i > b!!i = GT
       | a!!i == b!!i && (a!!0 < b!!0) = LT
       | a!!i == b!!i && (a!!0 == b!!0) = EQ
       | otherwise = GT

-- Task 2
tsort :: String -> Table -> Table
tsort s t = (head t):(sortBy (my_compare_for_task_2 (fromJust (elemIndex s (head t)))) (tail t))

-- Task 3
vmap :: (Value -> Value) -> Table -> Table
vmap f t = map (map f) t

-- Task 4
rmap :: (Row -> Row) -> [String] -> Table -> Table
rmap f n t = n:(map f (tail t))

get_hw_grade_total :: Row -> Row
get_hw_grade_total r = [head r] ++ [printf "%.2f" (foldl (+) 0 (tail (tail (convertRow r))))]

-- Task 5
vunion :: Table -> Table -> Table
vunion t1 t2
    | head t1 == head t2 = t1 ++ (tail t2)
    | otherwise = t1

complete :: Int -> [String] -> [String]
complete x s
    | x > (length s) = complete x (s ++ [""])
    | otherwise = s

-- Task 6
hunion :: Table -> Table -> Table
hunion t1 t2 = map (complete ((length (head t1)) + (length (head t2)))) (transpose ((transpose t1) ++ (transpose t2)))


-- Task 7
tjoin :: String -> Table -> Table -> Table
tjoin = undefined

aux_for_8 :: (Row -> Row -> Row) -> Table -> Table -> Table -> Table
aux_for_8 f [] y acc = acc
aux_for_8 f (x:xs) y acc = aux_for_8 f xs y (acc ++ (map (f x) y)) 

-- Task 8
aux_for_8_1 :: (Row -> Row -> Row) -> [String] -> Table -> Table -> Table
aux_for_8_1 f s t1 t2 = s:(aux_for_8 f t1 t2 [])

cartesian :: (Row -> Row -> Row) -> [String] -> Table -> Table -> Table
cartesian f s t1 t2 = aux_for_8_1 f s (tail t1) (tail t2) 

aux_for_9 :: [String] -> Table -> Table
aux_for_9 t [] = []
aux_for_9 [] t = []
aux_for_9 (l:ls) t = (as_list l t):(aux_for_9 ls t)

-- Task 9
projection :: [String] -> Table -> Table
projection l t = l:(transpose (aux_for_9 l t))

data Query =
    FromCSV CSV
    | ToCSV Query
    | AsList String Query
    | Sort String Query
    | ValueMap (Value -> Value) Query
    | RowMap (Row -> Row) [String] Query
    | VUnion Query Query
    | HUnion Query Query
    | TableJoin String Query Query
    | Cartesian (Row -> Row -> Row) [String] Query Query
    | Projection [String] Query
    | forall a. FEval a => Filter (FilterCondition a) Query
    | Graph EdgeOp Query
 
-- where EdgeOp is defined:
type EdgeOp = Row -> Row -> Maybe Value

data QResult = CSV CSV | Table Table | List [String]

instance Show QResult where
  show (CSV x) = show x
  show (Table x) = write_csv x
  show (List x) = show x

class Eval a where
  eval :: a -> QResult

get_table :: QResult -> Table
get_table (Table x) = x

get_list :: QResult -> [String]
get_list (List x) = x

get_CSV :: QResult -> String
get_CSV (CSV x) = x

unpack_maybe :: (Maybe String) -> String
unpack_maybe Nothing = ""
unpack_maybe (Just x) = x 

get_function f t = feval (head (get_table (eval t))) f
filter_table f t = (head (get_table (eval t))):(filter f (tail (get_table (eval t))))

-- edge_op1 (n1:l1:_) (n2:l2:_)
--             | l1 == l2 = Just l1
--             | otherwise = Nothing

-- edge_op2 l1 l2
--     | last l1 == last l2 = Just "identical"
--     | (abs $ (read (last l1) :: Float) - (read (last l1) :: Float)) < 0.1 = Just "similar"
--     | otherwise = Nothing

equal_graph_row :: Row -> Row -> Bool
equal_graph_row (x1:x2:x3:_) (y1:y2:y3:_)
  | x1 == y1 && x2 == y2 && x3 == y3 = True
  | otherwise = False

build_graph :: Table -> (Row -> Row -> Maybe Value) -> Table -> Row -> Table
build_graph [] _ acc _ = acc
build_graph (t:ts) f acc l
  | f l t == Nothing = build_graph ts f acc l
  | otherwise = build_graph ts f (([head l]++[head t]++[fromJust (f l t)]):acc) l

build_graph_2 :: Table -> (Row -> Row -> Maybe Value) -> Table -> Table
build_graph_2 [] _ acc = acc
build_graph_2 (t:ts) f acc = build_graph_2 ts f ((build_graph (t:ts) f [] t) ++ acc)

delete_duplicates :: Table -> Table
delete_duplicates [] = []
delete_duplicates (x:xs) = x:(delete_duplicates (delete x xs))
  where
    delete x [] = []
    delete x (y:ys)
      | equal_graph_row x y = delete x ys
      | otherwise = y:(delete x ys)

sort_from_to :: Table -> Table
sort_from_to t = map swap t
  where 
    swap (x:y:xs)
      | y < x = (y:x:xs)
      | otherwise = (x:y:xs)

delete_same_to_from :: Table -> Table
delete_same_to_from t = filter check t
  where 
    check (x:y:xs)
      | x == y = False
      | otherwise = True

count_q :: Row -> Row -> Int
count_q [] [] = 0
count_q (r1:rs1) (r2:rs2)
  | r1 == r2 = 1 + count_q rs1 rs2
  | otherwise = count_q rs1 rs2

similar :: Row -> Row -> (Maybe Value)
similar r1 r2
  | (head r1) == "" || (head r2) == "" = Nothing
  | (count_q (tail r1) (tail r2)) >= 5 = (Just (show (count_q (tail r1) (tail r2))))
  | otherwise = Nothing

final_graph :: Table -> (Row -> Row -> Maybe Value) -> Table
final_graph t f = ["From","To","Value"]:(reverse (delete_duplicates (sort_from_to (delete_same_to_from (build_graph_2 (tail t) f [])))))

my_compare_for_graph :: Int -> [String] -> [String] -> Ordering
my_compare_for_graph i a b
       | (my_read (a!!i)) < (my_read (b!!i)) = LT
       | (my_read (a!!i)) > (my_read (b!!i)) = GT
       | (my_read (a!!i)) == (my_read (b!!i)) && (a!!0 < b!!0) = LT
       | (my_read (a!!i)) == (my_read (b!!i)) && (a!!0 == b!!0) = EQ
       | otherwise = GT

tsort_2 :: String -> Table -> Table
tsort_2 s t = (head t):(sortBy (my_compare_for_graph (fromJust (elemIndex s (head t)))) (tail t))

similarities_query = (Sort "Value" (Graph similar (FromCSV lecture_grades_csv)))

instance Eval Query where
  eval (FromCSV x) = (Table (read_csv x))
  eval (ToCSV x) = (CSV (write_csv (get_table (eval x))))
  eval (AsList s x) = (List (as_list s (get_table (eval x))))
  eval (Sort s x) = (Table (tsort_2 s (get_table (eval x))))
  eval (ValueMap op x) = (Table (vmap op (get_table (eval x))))
  eval (RowMap op l x) = (Table (rmap op l (get_table (eval x))))
  eval (VUnion x y) = (Table (vunion  (get_table (eval x)) (get_table (eval y))))
  eval (HUnion x y) = (Table (hunion (get_table (eval x)) (get_table (eval y))))
  eval (TableJoin s x y) = (Table (tjoin s (get_table (eval x)) (get_table (eval y))))
  eval (Cartesian op s x y) = (Table (cartesian op s (get_table (eval x)) (get_table (eval y))))
  eval (Projection l x) = (Table (projection l (get_table (eval x))))
  eval (Filter f x) = (Table (filter_table (get_function f x) x))
  eval (Graph f x) = (Table (final_graph (get_table (eval x)) f))

data FilterCondition a =
    Eq String a |
    Lt String a |
    Gt String a |
    In String [a] |
    FNot (FilterCondition a) |
    FieldEq String String

type FilterOp = Row -> Bool

class FEval a where
    feval :: [String] -> (FilterCondition a) -> FilterOp

get_string :: [String] -> String -> [String] -> String
get_string [] _ _ = ""
get_string (x:xs) s (y:ys)
  | x == s = y
  | otherwise = get_string xs s ys

get_float :: [String] -> String -> [String] -> Float
get_float (x:xs) s (y:ys)
  | x == s = my_read y
  | otherwise = get_float xs s ys

column_equal_float :: [String] -> String -> String -> [String] -> Bool
column_equal_float l1 s1 s2 l2 = (get_float l1 s1 l2) == (get_float l1 s2 l2)

column_equal_string :: [String] -> String -> String -> [String] -> Bool
column_equal_string l1 s1 s2 l2 = (get_string l1 s1 l2) == (get_string l1 s2 l2)

elem' l s = elem s l

instance FEval Float where
  feval l (Eq s r) = (==r).(get_float l s)
  feval l (Lt s r) = (<r).(get_float l s)
  feval l (Gt s r) = (>r).(get_float l s)
  feval l (In s t) = (elem' t).(get_float l s)
  feval l (FieldEq s1 s2) = column_equal_float l s1 s2
  feval l (FNot (Eq s r)) = (/=r).(get_float l s)
  feval l (FNot (Lt s r)) = feval l (Gt s r)
  feval l (FNot (Gt s r)) = feval l (Lt s r)
  feval l (FNot (In s t)) = (not.elem' t).(get_float l s)
  feval l (FNot (FieldEq s1 s2)) = not.column_equal_float l s1 s2

instance FEval String where
  feval l (Eq s r) = (==r).(get_string l s)
  feval l (Lt s r) = (<r).(get_string l s)
  feval l (Gt s r) = (>r).(get_string l s)
  feval l (In s t) = (elem' t).(get_string l s)
  feval l (FieldEq s1 s2) = column_equal_string l s1 s2
  feval l (FNot (Eq s r)) = (/=r).(get_string l s)
  feval l (FNot (Lt s r)) = feval l (Gt s r)
  feval l (FNot (Gt s r)) = feval l (Lt s r)
  feval l (FNot (In s t)) = (not.elem' t).(get_string l s)
  feval l (FNot (FieldEq s1 s2)) = not.column_equal_string l s1 s2

