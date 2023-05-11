multiplyTwo x y = x * y
multiplyThree x y z = x * y * z

first_a n = [x | x <- [1..n], (x `mod` 6 == 0 || x `mod` 11 == 0)]

isMult6Or11 x = (x `mod` 6 == 0 || x `mod` 11 == 0)
first_b n = [x | x <- [1..n], isMult6Or11 x]

second_a n = [x | x <- [1..n], ((x == read (reverse (show x))) && (show x !! 0) == '3')]

isPalindromeThatStartsWithDigit3 x = (x == read (reverse (show x)) && (show x !! 0) == '3')
second_b n = [x | x <- [1..n], isPalindromeThatStartsWithDigit3 x]