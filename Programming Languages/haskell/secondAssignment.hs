isPrime n = ip n [2..(isqrt (n))]
 where
 ip _ [] = True
 ip n (x:xs)
  | n `mod` x == 0 = False
  | otherwise = ip n xs
isqrt :: Integral i => i -> i
isqrt = floor . sqrt . fromIntegral

primeList n = take (2*n) [x | x <- [1..], isPrime x]

problem1 n = everyOther (primeList n)
 where 
 everyOther (x:y:xs) = y : everyOther xs
 everyOther _ = []
 
problem2 n = fib n 1 1
 where
 fib n f s
  | (f+s) > n = []
  | (last (show (f+s)) /= '3') = fib n s (f+s)
  | otherwise = (f+s) : fib n s (f+s)

factors x = [ y | y <- [1..x], x `mod` y == 0]
problem3 n = [x | x <- [1..n], (x `mod` 5 == 0) || length (factors x) == 3]
