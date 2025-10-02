(define (all-numeric s)
   (or (equal? s '())
       (and (>= (char->integer (car s)) 48)
            (<= (char->integer (car s)) 57)
            (all-numeric (cdr s)))))


(define (numeric? s)
   (and (>= (char->integer s) 48)
        (<= (char->integer s) 57)))


(define (ok? s)
   (and (= (length s) 4)
        (or (and (= (length (car s)) 1)
                 (or (equal? (caar s) #\-)
                     (equal? (caar s) #\+)))
            (= (length (car s)) 0))
        (and (all-numeric (cadr s))
             (> (length (cadr s)) 0))
        (and (equal? (caaddr s) #\/)
             (= (length (caddr s)) 1))
        (and (all-numeric (cadddr s))
             (> (length (cadddr s)) 0))))


(define (plus1 k symb)
   (cond ((equal? symb #\/) (+ k 1))
            ((and (numeric? symb) (or (= k 1) (= k 3))) (+ k 1))
         (else k)))


(define (addition s k a)
   (cond ((and (or (equal? a #\-) (equal? a #\+)) (= k 0))
            (set-car! s (list a)))
         ((and (or (= k 1) (= k 2)) (numeric? a))
            (set-car! (cdr s) (append (cadr s) (list a))))
         ((and (or (= k 3) (= k 4)) (numeric? a))
            (set-car! (cdddr s) (append (cadddr s) (list a))))
         (else (set-car! (cddr s) (append (caddr s) (list a))))))


(define (convert s-dop)
   (define s (list '() '() '() '()))
   (let func ((k 0) (xs s-dop))
      (cond ((or (= k 5) (equal? xs '())) s)
               ((and (= k 0) (numeric? (car xs))) (func (+ k 1) xs))
            (else
               (begin (addition s k (car xs))
                      (func (plus1 k (car xs))(cdr xs)))))))


(define (check-frac s)
   (ok? (convert (string->list s))))


(define (my-eval exprs)
   (eval exprs (interaction-environment)))


(define (symbols->number s)
   (string->number (list->string s)))


(define (calculation s)
   (cond ((equal? (car s) '())
            (eval (list '/ (symbols->number (cadr s))
                        (symbols->number (cadddr s))) (interaction-environment)))
         ((equal? (caar s) #\-)
            (eval (list '/ (symbols->number (append '(#\-) (cadr s)))
                        (symbols->number (cadddr s))) (interaction-environment)))
         (else
            (eval (list '/ (symbols->number (cadr s))
                        (symbols->number (cadddr s))) (interaction-environment)))))


(define (scan-frac1 s)
  (and (check-frac s)
       (calculation (convert (string->list s)))))


(define (scan-many-fracs1 s1)
  (let func ((s (append (list #\space) (string->list s1) (list #\space))) (xs '()) (buf '()))
    (cond ((equal? s '()) xs)
          ((and (or (equal? (car s) #\space)
                    (equal? (car s) #\newline)
                    (equal? (car s) #\tab))
                (equal? buf '()))
              (func (cdr s) xs buf))
          ((and (or (equal? (car s) #\space)
                    (equal? (car s) #\newline)
                    (equal? (car s) #\tab))
                (ok? (convert buf)))
              (func (cdr s) (append xs (list (calculation (convert buf)))) '()))
          ((and (or (equal? (car s) #\space)
                    (equal? (car s) #\newline)
                    (equal? (car s) #\tab))
                (not (ok? (convert buf))))
              #f)
          (else
             (func (cdr s) xs (append buf (list (car s))))))))


(define (scan-frac s)
  (and (number? (scan-frac1 s))
       (begin
          (display (scan-frac1 s))
          (display "\n"))))


(define (scan-many-fracs s)
  (and (list? (scan-many-fracs1 s))
       (begin
          (display (scan-many-fracs1 s))
          (display "\n"))))

(define (peek s)
  (if (null? (car s))
      (cadr s)
      (caar s)))


(define (next s)
   (let ((n (peek s)))
       (if (not (null? (car s)))
          (set-car! s (cdr (car s))))
       n))


(define (article s error) ;define word <Body> end .
  (letrec ((def (if (equal? (peek s) 'define) (next s) (error #f)))
            (word (next s))
            (body (parse-body s error))
            (end (if (equal? (peek s) 'end)
                     (next s)
                     (error #f))))
            (if (and (member word '(define end if endif)))
               (error #f)
               (list word body))))


(define (articles s error) ;<Article> <Articles> | .
   (if (equal? 'define (peek s))
       (cons (article s error) (articles s error))
       '()))


(define (parse-else s error) ;else <Body> | .
  (if (equal? 'else (peek s))
     (begin
        (next s)
        (parse-body s error))
     '()))


(define (program s error) ;<Articles> <Body> .
    (list (articles s error) (parse-body s error)))


;;if <Body> <ElsePart> endif <Body> | integer <Body> | word <Body> | .
(define (parse-body s error) 
  (cond ((integer? (peek s)) (cons (next s) (parse-body s error)))
        ((equal? 'if (peek s))
         (letrec ((if1 (next s))
                  (body (parse-body s error))
                  (else1 (parse-else s error))
                  (endif (if (equal? (peek s) 'endif)
                            (next s)
                            (error #f))))
             (if (equal? else1 '())
                (cons (list 'if body) (parse-body s error))
                (cons (list 'if body else1) (parse-body s error)))))
        ((and (symbol? (peek s))
              (not (equal? (peek s) 'endif))
              (not (equal? (peek s) 'else))
              (not (equal? (peek s) 'end)))
            (cons (next s) (parse-body s error)))
        (else '())))


(define (parse s) 
  (let ((stream (list (vector->list s) #\🤪)))
    (call-with-current-continuation
        (lambda (error)
           (let ((res (program stream error)))
              (and (equal? (peek stream) #\🤪)
              res))))))
