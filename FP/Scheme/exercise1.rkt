

(define (foldl op nv l)
  (if (null? l) nv
  (foldl op (op nv (car l)) (cdr l))))

(define (foldr op nv l)
  (if (null? l) nv
      (op (car l) (foldr op nv (cdr l)))))

(define (flatten l)
  (apply append l)) 

(define (decart l1 l2)
  (flatten (map (lambda (x) (map  (lambda (y) (cons x y)) l2)) l1)))

(define (zip l1 l2)
  (map list l1 l2))

(define (repeat-element l)
  (foldl (lambda (x y) (append x (list y y) )) '() l))

(define (zip-multiple . lsts)
  (apply map list lsts))

(define (any? p? l)
  (foldr (lambda (x y) (or (p? x) y)) #f l))

(define (zip-multiple . ll)
  (if (any? null? ll) '()
      (cons (map car ll)
            (apply zip-multiple (map cdr ll)))))

(define (merge-sorted l1 l2)
  (cond ((null? l1) l2)
        ((null? l2) l1)
        (else
         (let ((h1 (car l1))
               (h2 (car l2)))
             (if (<= h1 h2)
                 (cons h1 (merge-sorted (cdr l1) l2))
                 (cons h2 (merge-sorted l1 (cdr l2))))))))

;(define (take n l))
;(define (drop n l))

;purva zadacha

(define (product-digits x)
  (if (= x 0) 1
      (* (remainder x 10) (product-digits (quotient x 10)))))

(define (diff x)
  (- x (product-digits x)))

(define (list-interval a b)
  (if (> a b) '()
      (cons a (list-interval (+ a 1) b))))

(define (all-difs a b)
  (let ((interval (list-interval a b)))
  (apply append (map (lambda (x) (map (lambda (y) (- (diff x) (diff y))) interval)) interval))))

(define (max-in-list l)
  (define (helper max-element lst)
    (cond ((null? lst) max-element)
          ((> (car lst) max-element) (helper (car lst) (cdr lst)))
          (else (helper max-element (cdr lst)))))
  (if (null? l) '()
  (helper (car l) (cdr l))))

(define (largest-diff a b)
  (max-in-list (all-difs a b)))

; vtora zadacha

(define (apply-metric m ll)
  (map (lambda (x) (m x)) ll))

(define (prod l) (apply * l))
(define (sum l) (apply + l))

(define (apply-sum-metric m ll)
  (sum (apply-metric m ll)))

(define (max-metric ml ll)
  (let ((val (apply-sum-metric (car ml) ll)))
  (define (helper ml max-m max-val)
    (cond ((null? ml) max-m)
          ((< max-val val) (helper (cdr ml) (car ml) val))
          (else (helper (cdr ml) max-m max-val))))
  (helper ml (car ml) val)))



        
