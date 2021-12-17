#lang racket
(require rackunit rackunit/text-ui)

;### Зад 3
; Намира най-малкото число, което се среща поне 2 пъти в списъка `l`.

(define (dup? x l)
  (> (length (filter (lambda (y) (equal? x y)) l)) 1))

(define (get-dup l)
  (filter (lambda (x) (dup? x l)) l))

(define (min-duplicate l)
  (apply min (get-dup l)))

(run-tests
  (test-suite "min-duplicate tests"
    (check-eq? (min-duplicate '(-8 -8))
               -8)
    (check-eq? (min-duplicate '(1 2 3 4 4 5 6))
               4)
    (check-eq? (min-duplicate '(5 1 2 3 4 5 3 6 2 3 2 3 2 3))
               2)
    (check-eq? (min-duplicate '(3 2 2 2 1 1))
               1))
  'verbose)
