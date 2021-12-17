#lang racket
(require rackunit rackunit/text-ui)

;### Зад 2
; Броят на наредените двойки цели числа от интервала [`a`,`b`],
; които имат най-голям общ делител равен на `n`.
(define (gen-interval a b)
  (if (> a b) '()
      (cons a (gen-interval (+ a 1) b))))

(define (gen-pairs l)
  (apply append (map (lambda (x) (map (lambda (y) (list x y)) l)) l)))

(define (count-pairs-gcd n a b)
  (define (helper pairs count)
    (cond ((null? pairs) count)
          ((= (apply gcd (car pairs)) n) (helper (cdr pairs) (+ count 1)))
          (else (helper (cdr pairs) count))))
  (helper (gen-pairs (gen-interval a b)) 0))
  

(run-tests
  (test-suite "count-pairs-gcd tests"
    (check-eq? (count-pairs-gcd 10 1 11)
               1)
    (check-eq? (count-pairs-gcd 3 1 11)
               7)
    (check-eq? (count-pairs-gcd 16 1 11)
               0)
    (check-eq? (count-pairs-gcd 4 1 11)
               3))
  'verbose)
