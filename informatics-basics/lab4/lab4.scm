(define k #f)

(define-syntax use-assertions
  (syntax-rules ()
    ((use-assertations)
       (call-with-current-continuation
          (lambda (stack) (set! k stack))))))

(define-syntax assert
  (syntax-rules ()
    ((assert exp)
     (and (not exp)
          (begin (display "FAILED: ")
             (display (quote exp))
             (newline)
             (k))))))

(use-assertions)

(define (1/x x)
   (assert (not (zero? x)))
   (/ 1 x))

(define (save-data s f)
   (with-output-to-file f
      (lambda ()
         (write s)
         (newline)) 
   #:exists 'append))


(define (load-data f)
   (with-input-from-file f
      (lambda ()
         (read))))


(define (num p)
   (let loop ((s 0) (tok 0))
      (if (eof-object? (peek-char p))
         (begin (if (or (> tok 1) (and (= tok 1) (not (equal? (read-char p) #\newline))))
                   (+ s 1)
                   s))
         (if (equal? (read-char p) #\newline)
            (if (> tok 1)
               (loop (+ s 1) 0)
               (loop s 0))
            (loop s (+ tok 1))))))


(define (count-line f)
   (let ((port (open-input-file f)))
      (define x (num port))
      (close-input-port port)
      x))


(define (trib n)
   (cond
      ((<= n 1) 0)
      ((= n 2) 1)
      ( (+ (trib (- n 1)) (trib (- n 2)) (trib (- n 3))))))


(define trib-memo
   (let ((known-results '()))
      (lambda (n)
         (let* ((arg n)
            (res (assoc arg known-results)))
         (if res
            (cadr res)
            (let ((res (cond
                         ((<= n 1) 0)
                         ((= n 2) 1)
                         ((> n 2) (+ (trib-memo (- n 1)) (trib-memo (- n 2)) (trib-memo (- n 3)))))))
               (set! known-results (cons (list arg res) known-results))
               res))))))


(define-syntax my-if
  (syntax-rules ()
    ((my-if conf t f)
       (force (or (and conf (delay t))
                  (delay f))))))


(define counter
   (let ((n 0))
      (lambda ()
         (set! n (+ 1 n))
         n)))


(define-syntax my-let
   (syntax-rules ()
      ((my-let ((a exp) ...) act ...)
         ((lambda (a ...) act ...) exp ...))))


(define-syntax my-let*
   (syntax-rules ()
      ((my-let* ((a exp)) act ...)
         (my-let ((a exp)) act ...))
      ((my-let* ((a1 exp1) (a2 exp2) ...) act ...)
         (my-let ((a1 exp1))
            (my-let* ((a2 exp2) ...) act ...)))))
