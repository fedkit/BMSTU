;;Task1
;;<выражение> ::= <пробелы> <токен> <пробелы> <выражение> | .
;;<пробелы> ::= " " <пробелы> | .
;;<токен>   ::=  <скобки> | <переменная> | <число> | <действие>
;;<скобки> ::= ( | )
;;<действие> ::= + | - | * | / | ^
;;<число> ::= - <цифра> <цифры> | <цифра> <цифры>
;;<цифра> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
;;<цифры> ::= <цифра> <цифры> | . <цифры>| e <цифры> | .
;;<переменная> ::= <буква> <хвост переменной> 
;;<буква>  ::= a | b | ... | Z
;;<хвост переменной> ::= <буква> <хвост переменной> | .

(define action (list #\+ #\- #\* #\/ #\^))
(define digit (list #\0 #\1 #\2 #\3 #\4 #\5 #\6 #\7 #\8 #\9))
(define (peek s)
  (if (null? (car s))
      (cadr s)
      (caar s)))

(define (next s)
   (let ((n (peek s)))
       (if (not (equal? (car s) '()))
          (set-car! s (cdr (car s))))
       n))

(define (take s a)
   (if (equal? (car a) (peek s))
      (begin
        (next s)
        (string->symbol (list->string (list (car a)))))
      (take s (cdr a))))

(define (take-1 s a)
   (if (equal? (car a) (peek s))
      (begin
        (next s)
        (list->string (list (car a))))
      (take-1 s (cdr a))))

(define (take-2 s a)
   (if (equal? (car a) (peek s))
      (begin
        (next s)
        (car a))
      (take-2 s (cdr a))))

(define (ok-digit? s)
   (or (equal? s #\.)
       (equal? s #\e)
       (equal? s #\-)
       (member s digit)))

(define (ok-letter? s)
   (letter? s))

(define (take-3 s)
   (define (loop a)
      (if (ok-digit? (peek s))
         (let ((k (peek s)))
            (begin
               (next s)
               (loop (append a (list k)))))
         a))
   (loop '()))

(define (big->small s)
   (integer->char (+ 32 (char->integer s))))


(define (big? s)
  (and (>= (char->integer s) 65)
       (<= (char->integer s) 90)))

(define (take-4 s)
   (define (loop a)
      (if (ok-letter? (peek s))
         (if (big? (peek s))
             (let ((k (big->small (peek s))))
               (begin (next s)
                      (loop (append a (list k)))))
             (let ((k (peek s)))
               (begin (next s)
                      (loop (append a (list k))))))
         a))
   (loop '()))

(define (not-ok? s)
  (and (not (< (length s) 2))
       (or (and (member (car s) digit)
                (letter? (cadr s))
                (not (equal? (cadr s) #\e)))
           (not-ok? (cdr s)))))

(define (letter? char)
    (or (and (>= (char->integer char) 65)
             (<= (char->integer char) 90))
        (and (>= (char->integer char) 97)
             (<= (char->integer char) 122))))

(define (vir s error a)
   (if (not-ok? (car s))
       (error #f)
       (cond ((equal? (peek s) #\space)
                 (begin (next s)
                        (vir s error a)))
             ((equal? (peek s) #\😡)
                 a)
             ((member (peek s) action)
                 (let ((t-action (take s action)))
                    (vir s error (append a (list t-action)))))
             ((member (peek s) (list #\( #\) ))
                 (let ((t-par (take-1 s (list #\( #\) ))))
                     (vir s error (append a (list t-par)))))
             ((member (peek s) digit)
                 (letrec ((t-a (take-3 s)))
                    (vir s error (append a (list (string->number (list->string t-a)))))))
             ((letter? (peek s))
                 (letrec ((t-a (take-4 s)))
                    (vir s error (append a (list (string->symbol (list->string t-a)))))))
             (else (error #f)))))

(define (tokenize prog)
    (define s (list (string->list prog) #\😡))
    (call-with-current-continuation
        (lambda (error)
           (let ((res (vir s error '())))
              (and (equal? (peek s) #\😡)
              res)))))

(tokenize "1") 
(tokenize "-a")
(tokenize "-a + b * x^2 + dy")
(tokenize "(a - 12)/(b + 34)")
(tokenize "  - a+b*x ^ 2+dy  ")
(tokenize "  (a-1)/(b+1)   ")
(tokenize "6.022e23 * 1.38e-23 is R")
(tokenize "!@#$%^&*()") 
(tokenize "12x34 56y78") 
(tokenize "            ")


;;Task2
;;Expr    ::= Term Expr' .
;;Expr'   ::= AddOp Term Expr' | .
;;Term    ::= Factor Term' .
;;Term'   ::= MulOp Factor Term' | .
;;Factor  ::= Power Factor' .
;;Factor' ::= PowOp Power Factor' | .
;;Power   ::= value | "(" Expr ")" | unaryMinus Power .


(define (parse token)

  (define s (list token #\😡))

  (define (p-expr s error)
    (p-exprs s error (p-term s error)))
      
  (define (p-exprs s error t)
    (if (or (equal? (peek s) '+) (equal? (peek s) '-))
          (p-exprs s error (list t (next s) (p-term s error)))
          t))

  (define (p-term s error)
    (p-terms s error (p-factor s error)))

  (define (p-terms s error f)
    (if (or (equal? (peek s) '*) (equal? (peek s) '/))
          (p-terms s error (list f (next s) (p-factor s error)))
          f))
    

  (define (p-factor s error)
    (let ((p (p-power s error)) )
      (if (equal? (peek s) '^)
          (list p (next s) (p-factor s error))
          p)))
    


  (define (p-power s error)
    (cond
      ((equal? (peek s) #\😡) (error #f))
      ((equal? (peek s) '-) (list (next s) (p-power s error)))
      ((equal? (peek s) "(") (let ((t-a (next s)) (t (p-expr s error)))
                                 (if (equal? (next s) ")")
                                     t
                                     (error #f))))
      ((symbol? (peek s)) (next s))
      ((number? (peek s)) (next s))
      
      (else (error #f))))

  (call-with-current-continuation
   (lambda (error)
     (let ((res (p-expr s error)))
       (and (equal? (peek s) #\😡)
            res)))))
                           



;------------------------

;;Task3
(define (dop s)
  (if (equal? s '^)
      'expt
      s))

(define (tree->scheme tree)
  (if (and (list? tree) (= (length tree) 3))
     (list (dop (cadr tree))
           (tree->scheme (car tree))
           (tree->scheme (caddr tree)))
     tree))

