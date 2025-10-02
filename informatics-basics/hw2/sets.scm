(define (my-element? x xs)
  (and (not (equal? xs '()))
       (or (equal? (car xs ) x)
           (my-element? x (cdr xs)))))


(define (list->set xs) ;;O(n^2)
   (define (loop xs s)
      (if (equal? xs '())
         s
         (if (not (my-element? (car xs) (cdr xs)))
            (loop (cdr xs) (append (list (car xs)) s))
            (loop (cdr xs) s))))
   (loop xs '()))


(define (set? xs) ;;O(n^2)
   (= (length xs) (length (list->set xs))))


(define (union xs ys) ;;O(len(xs) + 2*len(ys))
   (list->set (append xs ys)))


(define (intersection xs ys) ;;O(len(xs) * len(ys))
   (define (loop ys s)
      (if (equal? ys '())
         s
         (if (my-element? (car ys) xs)
            (loop (cdr ys) (append (list (car ys)) s))
            (loop (cdr ys) s))))
  (loop ys '()))


(define (difference xs ys) ;;O(len(xs) * len(ys) + len(xs))
   (define (loop xs zs s)
      (if (equal? xs '())
         s
         (if (my-element? (car xs) zs)
            (loop (cdr xs) zs s)
            (loop (cdr xs) zs (append s (list (car xs)))))))
  (loop xs (intersection xs ys) '()))


;;O(2 * len(xs) * len(ys) + len(xs) + len(ys) + n)
;;n -количество элементов в списке 2-ой разности
(define (symmetric-difference xs ys)
   (append (difference xs ys) (difference ys xs)))


(define (set-eq? xs ys) ;;O(len(xs) * len(ys) * 2)
   (and (= (length (intersection xs ys)) (length xs))
        (= (length (intersection xs ys)) (length ys))))


;;Tests
(list->set '(1 1 2 3))                      
(set? '(1 2 3))                              
(set? '(1 2 3 3))                            
(set? '())                                   
(union '(1 2 3) '(2 3 4))                    
(intersection '(1 2 3) '(2 3 4))             
(difference '(1 2 3 4 5) '(2 3))             
(symmetric-difference '(1 2 3 4) '(3 4 5 6)) 
(set-eq? '(1 2 3) '(3 2 1))                 
(set-eq? '(1 2) '(1 3))
