
(define (all? p? l)
  (foldr (lambda (x y) (and x y)) #t (map p? l)))


(define (get-rows m) (length m))
(define (get-columns m) (lenght (car m)))

(define (transpose m)
  (apply map list m))

