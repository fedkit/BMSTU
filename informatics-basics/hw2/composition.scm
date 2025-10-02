(define (my-fold-right op xs)
   (define (loop xs a)
      (if (equal? xs '())
          a
          (loop (cdr xs) (op (car xs) a))))
   (loop (cdr (reverse xs)) (car (reverse xs))))


(define (o . xs)
   (cond ((equal? xs '())
             (lambda (a) a))
         ((= (length xs) 1)
             (lambda (a) ((car xs) a)))
         (else
             (lambda (a) ((car xs) ((my-fold-right o (cdr xs)) a))))))


;;Tests
(define (f x) (+ x 2))
(define (g x) (* x 3))
(define (h x) (- x))

((o f g h) 1)
((o f g) 1)   
((o h) 1)     
((o) 1)      
