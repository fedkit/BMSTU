(define(reverse-string s) 
   (list->string (reverse (string->list s))))


(define (string-trim-left s) 
   (if (char-whitespace? (string-ref s 0));;O(len-str(s)^2)
      (string-trim-left (substring s 1 (string-length s)))
      s))


(define (string-trim-right s) ;;O(len-str(s)^2 * 3)
   (reverse-string (string-trim-left (reverse-string s))))


(define (string-trim s) ;;O(len-str(s)^2 * 4)
   (string-trim-right (string-trim-left s)))


(define (string-prefix? a b) ;;O(len-str(a) * 3 + len-str(b) * 2)
   (and (<= (string-length a) (string-length b))
        (equal? a (substring b 0 (string-length a)))))


(define (string-suffix? a b) ;;O(len-str(a) * 4 + len-str(b) * 3)
   (and (<= (string-length a) (string-length b))
        (equal? (reverse-string a) (substring (reverse-string b) 0 (string-length a)))))

;;O((len-str(a) * 3 + len-str(b) * 3) * (len-str(b) - len-str(a)))
(define (string-infix? a b) 
   (or (and (<= (string-length a) (string-length b))
            (equal? a (substring b 0 (string-length a))))
       (and (<= (string-length a) (string-length b))
            (string-infix? a (substring b 1 (string-length b))))))


(define (obj str sep)
(cond ((or (string-prefix? sep str)
           (= (string-length str) 0))
           "")
       (else
           (string-append (make-string 1 (string-ref str 0)) (obj (substring str 1) sep)))))


(define (string-split str sep) ;;O(len-str(sек)^2)
   (cond ((= (string-length str) 0)
      '())
   ((string-prefix? sep str)
      (string-split (substring str (string-length sep)) sep))
   (else
      (cons (obj str sep) (string-split (substring str (string-length (obj str sep))) sep)))))


;;Tests
(string-trim-left  "\t\tabc def")  
(string-trim-right "abc def\t")     
(string-trim       "\t abc def \n") 

(string-prefix? "abc" "abcdef")  
(string-prefix? "bcd" "abcdef") 
(string-prefix? "abcdef" "abc") 

(string-suffix? "def" "abcdef") 
(string-suffix? "bcd" "abcdef") 

(string-infix? "def" "abcdefgh")
(string-infix? "abc" "abcdefgh")
(string-infix? "fgh" "abcdefgh")
(string-infix? "ijk" "abcdefgh")
(string-infix? "bcd" "abc")     

(string-split "x;y;z" ";")   
(string-split "x-->y-->z" "-->")
