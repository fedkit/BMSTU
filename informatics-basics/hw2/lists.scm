(define (my-range a b d) ;;O((b - a) / d)
  (define (loop a s)
    (if (< a b)
        (loop (+ a d) (append s (list a)))
        s))
  (loop a '()))


(define (my-element? x xs) ;;O(len(xs))
  (and (not (equal? xs '()))
       (or (equal? (car xs ) x)
           (my-element? x (cdr xs)))))


(define (my-filter pred? xs) ;;O(len(xs))
   (define (loop xs s)
      (if (not (equal? xs '()))
         (if (pred? (car xs))
            (loop (cdr xs) (append s (list (car xs))))
            (loop (cdr xs) s))
         s))
   (loop xs '()))


(define (my-fold-left op xs) ;;O(len(xs))
   (define (loop xs a)
      (if (equal? xs '())
          a
          (loop (cdr xs) (op a (car xs)))))
   (loop (cdr xs) (car xs)))

  
(define (my-fold-right op xs) ;;O(len(xs))
   (define (loop xs a)
      (if (equal? xs '())
          a
          (loop (cdr xs) (op (car xs) a))))
   (loop (cdr (reverse xs)) (car (reverse xs))))


(define (my-flatten xs) ;;O(len(xs)^2)
  (if (equal? xs '())
      xs
      (if (list? (car xs))
          (append (my-flatten (car xs)) (my-flatten (cdr xs)))
          (cons (car xs) (my-flatten (cdr xs))))))


;;Tests
(my-range  0 11 3) 

(my-flatten '((1) 2 (3 (4 5)) 6))

(my-element? 1 '(3 2 1))
(my-element? 4 '(3 2 1))

(my-filter odd? (my-range 0 10 1))
(my-filter (lambda (x) (= (remainder x 3) 0)) (my-range 0 13 1))

(my-fold-left  quotient '(16 2 2 2 2))
(my-fold-left  quotient '(1))         
(my-fold-right expt     '(2 3 4))     
(my-fold-right expt     '(2))
