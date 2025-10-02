(define (make-multi-vector sizes . fill)
   (if (equal? fill '())
      (cons sizes (list (make-vector (apply * sizes))))
      (cons sizes (list (make-vector (apply * sizes) (car fill))))))


(define (multi-vector? m)
   (and (list? m)
        (list? (car m))
        (vector? (cadr m))
        (= 2 (length m))
        (= (apply * (car m)) (vector-length (cadr m)))))


(define (multi-vector-ref m indices)
   (define (loop xs indices n index)
      (if (equal? indices '())
         (vector-ref (cadr m) index)
         (loop (cdr xs) (cdr indices) (quotient n (car xs))
               (+ index (* (quotient n (car xs)) (car indices))))))
   (loop (car m) indices (vector-length (cadr m)) 0))


(define (multi-vector-index m indices)
   (define (loop xs indices n index)
      (if (equal? indices '())
         index
         (loop (cdr xs) (cdr indices) (quotient n (car xs))
               (+ index (* (quotient n (car xs)) (car indices))))))
   (loop (car m) indices (vector-length (cadr m)) 0))


(define (multi-vector-set! m indices x)
  (vector-set! (cadr m) (multi-vector-index m indices) x))


;;TESTS
(define m (make-multi-vector '(11 12 9 16)))
(multi-vector? m) 
(multi-vector-set! m '(10 7 6 12) 'test)
(multi-vector-ref m '(10 7 6 12)) 

; Индексы '(1 2 1 1) и '(2 1 1 1) — разные индексы
(multi-vector-set! m '(1 2 1 1) 'X)
(multi-vector-set! m '(2 1 1 1) 'Y)
(multi-vector-ref m '(1 2 1 1)) 
(multi-vector-ref m '(2 1 1 1)) 

(define m (make-multi-vector '(3 5 7) -1))
(multi-vector-ref m '(0 0 0))
