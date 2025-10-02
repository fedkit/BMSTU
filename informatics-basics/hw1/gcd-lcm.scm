(define (my-gcd a b)
   (if (= b 0)
      a
      (my-gcd (abs b) (remainder (abs a) (abs b)))))


(define (my-lcm a b)
   (quotient (* a b) (my-gcd a b)))


(define (prime? n)
   (define (loop n k)
      (or (not (>= k 2))
               (and (= 1 (my-gcd n k))
                    (loop n (- k 1)))))
   (loop n (truncate (sqrt n))))



(my-gcd 3542 2464)
(my-gcd 17 86)
(my-lcm 32 36)
(my-lcm 3 4) 
(prime? 1)
(prime? 2)
(prime? 11) 
(prime? 12)
(prime? 2017)
(prime? 2023)
