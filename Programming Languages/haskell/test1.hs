isPrime n = ip n [2..(isqrt (n))]
 where
 ip _ [] = True
 ip n (x:xs)
  | n `mod` x == 0 = False
  | otherwise = ip n xs
isqrt :: Integral i => i -> i
isqrt = floor . sqrt . fromIntegral
isPalin x = (x /= read (reverse (show x)))
problem1 n = [x | x <- [2..n], isPalin x && isPrime x && (last (show x)) == '3']

pop n = [x | x <- n, x /= (last n)]
predicate1 n = ((show (n) !! 0) == '4')
problem2 n = pop (filter predicate1 (map (*3) (fib n 1 1 1)))
 where
 fib n f s z
  | z > n = []
  | otherwise = ((f+s)) : fib n s (f+s) (z+1)

leftRight n = n (length (show n)) 0
 where
 poz n z i
  | i > z = True
  | isPrime n = False
  | otherwise = poz (pop n) z (i+1)

problem3 start end = [x | x <- [start..end], leftRight x] 