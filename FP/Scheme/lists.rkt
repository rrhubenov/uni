(define (list-length lst)
  (if (null? lst)
      0
      (+ 1 (list-length (cdr lst)))))

(define (contains? lst x)
  (if (null? lst)
      #f
      (if ( equal? (car lst) x) #t (contains? (cdr lst) x))))

(define (reverse-list lst)
  (define (helper current result)
    (if (null? current) result
        (helper (cdr current) (cons (car current) result))))
  (helper lst '()))
     

(define (mappend l1 l2)
  (if (null? l1) l2
      (cons (car l1) (mappend (cdr l1) l2))))

(define (reverse-rec l)
  (if (null? l) l
      (mappend (reverse-rec (cdr l)) (list (car l)))))

(define (mlist-tail l n)
  (if (or (null? l) (= n 0)) l
      (mlist-tail (cdr l) (- n 1))))


(define (mlist-ref l n)
  (if (= n 0) (car l)
      (mlist-ref (cdr l) (- n 1))))


(define (mmember x l)
  (cond
      ((null? l) #f)
      ((equal? (car l) x) l)
      (else (member x (cdr l)))))

(define (from-to a b)
  (define (helper curr result)
    (if (equal? curr (+ b 1)) result
    (helper (+ curr 1) (append result (list curr)))))
  (helper a '()))

(define (from-to-rec a b)
  (if (> a b) '()
      (cons a (from-to-rec (+ a 1) b))))

(define (id x) x)
(define (1+ x) (+ 1 x))

(define (mmap f l)
  (if (null? l) '()
      (cons (f (car l)) (mmap f (cdr l)))))

(define (accumulate op nv a b term next)
  (if (> a b) nv
      (op (term a) (accumulate op nv (next a) b term next))))

(define (mfilter p? l)
  (cond ((null? l) '())
        ((p? (car l)) (cons (car l) (mfilter p? (cdr l))))
        (else (mfilter p? (cdr l)))))
  
(define (foldr op nv l)
  (if (null? l) nv
      (op (car l) (foldr op nv (cdr l)))))
      
(define (mfilter-foldr p? l)
  (foldr (lambda (h r) (if (p? h) (cons h r) r)) '() l))

(define (foldl op nv l)
  (if (null? l) nv
      (foldl op (op nv (car l)) (cdr l))))

(define (reverse-foldl l)
  (foldl (lambda (u v) (cons v u)) '() l))

; стигнахме до имплементация на foldl

(define (max-foldl l)
  (foldl (lambda (u v) (if (> v u) v u)) (car l) l))

(define (max-foldr l)
  (foldr (lambda (u v) (if (> v u) v u)) (car l) l))

(define (foldr1 op l)
  (if (null? (cdr l)) (car l)
      (op (car l) (foldr1 op (cdr l)))))

(define (foldl1 op l)
  (if (null? (cdr l)) (car l)
      (foldl1 op (cons (op (car l) (cadr l)) (cddr l)))))

(define (foldl1-2 op l)
  (foldl op (car l) (cdr l)))


(define (atom? x)
  (not (or (null? x) (pair? x))))

(define (deep-reverse dl)
  (cond ((null? dl) '())
        ((atom? dl) dl)
        (else (list (deep-reverse (cdr dl)) (deep-reverse (car dl))))))

(define (deep-foldr op term nv dl)
  (cond ((null? dl) nv)
        ((atom? dl) (term dl))
        (else (op (deep-foldr op term nv (car dl)) (deep-reverse op term nv (cdr dl))))))

(define (snoc x y)
  (append y x))

(define (count-attoms dl)
  (deep-foldr + (lambda (x) 1) 0))

(define (flatten dl)
  (deep-foldr append list '()))

(define (deep-reverse dl)
  (deep-foldr snoc id  '()))

(define (deep-foldr op term nv dl)
  (foldr op nv (map
                (lambda (x)
                  (if (atom? x) (termx)
                   (deep-foldr op term nv x))) dl) dl))

; deep-foldl за домашно

; многоаргументни функции



