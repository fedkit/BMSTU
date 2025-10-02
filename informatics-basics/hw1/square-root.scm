(define (square-equation a b c)
   (cond ((< (- (* b b) (* 4 a c)) 0) (list))
         ((= (- (* b b) (* 4 a c)) 0) (list (/ (* -1 b) (* 2 a))))
         (else (list (/ (- (* -1 b) (sqrt (- (* b b) (* 4 a c)))) (* 2 a))
                     (/ (+ (* -1 b) (sqrt (- (* b b) (* 4 a c)))) (* 2 a))))))


(square-equation 1 1 1)
(square-equation 1 2 1)
(square-equation 1 1 -2)
(square-equation 4 5 -21)
