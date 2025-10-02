(define-syntax trace-ex
  (syntax-rules ()
    ((trace-ex a)
      (begin
         (write (quote a))
         (display " => ")
         (write a)
         (newline)
          a))))

(define (zip . xss)
  (if (or (null? xss)
          (null? (trace-ex (car xss))))
      '()
      (cons (map car xss)
            (apply zip (map cdr (trace-ex xss))))))

(define-syntax test
  (syntax-rules ()
    ((test vir x)
     (list (quote vir) x))))
            
            
(define (run-test t)
  (define a (eval (car t) (interaction-environment)))
  (if (equal? a (car (cdr t)))
      (begin
        (write (car t))
        (display " ok")
        (newline)
        #t)
      (begin
        (write (car t))
        (display " FAIL")
        (newline)
        (display "\tExpected: ")
        (write (cadr t))
        (newline)
        (display "\tReturned: ")
        (write a)
        (newline)
        #f)))


(define (all-true? xss)
  (define (loop k xss)
    (if (equal? xss '())
        k
        (loop (and k (car xss)) (cdr xss))))
  (loop #t xss))

              
(define (run-tests t)
  (define (all-true? xss)
    (and (equal? xss '()) 
        (and (car xss) (all-true? (cdr xss)))))
  (all-true? (map run-test t)))

(define (change-1 xss a)
   (cond
      ((list? xss)
         (and (> (length xss) a) (list-ref xss a)))
      ((string? xss)
         (and (> (string-length xss) a) (string-ref xss a)))
      ((vector? xss)
         (and (> (vector-length xss) a) (vector-ref xss a)))))


(define (shift xss n)
   (if (= n 0)
      '()
      (cons (car xss) (shift (cdr xss) (- n 1)))))


(define (change-2 xss a k)
   (cond
      ((list? xss)
         (if (= a 0)
             (and (>= (length xss) a) (cons k xss))
             (and (>= (length xss) a) (append (shift xss a)
                                              (list k) (list-tail xss a)))))
      ((string? xss)
         (and (>= (string-length xss) a) (or (string? k) (char? k))
              (list->string (append (shift (string->list xss) a)
                                    (list k) (list-tail (string->list xss) a)))))
      ((vector? xss)
         (and (>= (vector-length xss) a)
              (list->vector (append (shift (vector->list xss) a)
                                    (list k) (list-tail (vector->list xss) a)))))))


(define (ref xss . s)
   (if (= (length s) 1)
      (change-1 xss (car s))
      (change-2 xss (car s) (car (cdr s)))))

(define (factorize s)
   (let ((a (car (cdr (car (cdr s)))))
         (b (car (cdr (car (cdr (cdr s)))))))
      (cond
         ((and (equal? (car (cdr (cdr (car (cdr s))))) 2)
               (equal? (car s) '-))
               (list '* (list '- a b) (list '+ a b)))
         ((and (equal? (car (cdr (cdr (car (cdr s))))) 3)
               (equal? (car s) '-))
               (list '* (list '- a b) (list '+ (quote (expt a 2))
                                            (list '* a b) (quote (expt b 2)))))
         ((and (equal? (car (cdr (cdr (car (cdr s))))) 3)
               (equal? (car s) '+))
               (list '* (list '+ a b) (list '+ (quote (expt a 2))
                                            (list '- (list '* a b)) (quote (expt b 2))))))))
