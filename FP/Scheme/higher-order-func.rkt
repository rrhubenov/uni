(define (sum-interval start end)
  (define (sum-helper curr acc)
    (if (= curr (+ end 1))
        acc
        (sum-helper (+ curr 1) (+ curr acc))))
  (sum-helper start 0)
  )

(define (product-interval start end)
  (define (product-interval-helper curr acc)
    (if (= curr (+ end 1))
        acc
        (product-interval-helper (+ curr 1) (* curr acc))))
  (product-interval-helper start 1)
  )

(define (sum-cubes start end)
  (define (sum-cubes-helper curr acc)
    (if (= curr (+ end 1))
        acc
        (sum-cubes-helper (+ curr 1) (+ acc (expt curr  3)))))
  (sum-cubes-helper start 0)
  )

; not finished
(define (sum-interval-even start end)
  (define (helper curr acc)
    (if (= curr (+ end 1))
        acc
        (helper (+ curr 1) (+ acc (expt curr  3)))))
  (helper start 0)
  )

;higher-order functions

;accumulate-iterative

(define (plus1 x) (+ x 1))

(define (accumulate-iterative start end op term next null-value)
  (define (helper curr acc)
    (if (> curr end)
        acc
        (helper (next curr) (+ acc (op curr term))))
    )
  (helper start null-value))


;lambda-functions
(lambda (x) (+ x 1))

;функция, която ни казва дали число е по-голямо от 10
(lambda (x) (> x 10))
;функция, която ни дава остатък при делене с 5
(lambda (x) (modulo x 5))
;функция, която приема друга такава и я извиква с 6
(lambda (f) (f 6))

; compose - ((f . g) x) -> (f (g x))
(define (compose f g)
  (lambda (x) (f (g x))))

; repeat f n
(define (repeat f n)
  (if (= n 1) f
      (compose (repeat f (- n 1)) f)))


(define (1+ x) (+ x 1))
(define (id x) x)

(define (acc-it op nv start end term next)
  (define (helper curr acc)
    (if (= curr end) acc
        (helper (next curr) (+ acc (op curr term)))))
  (helper start nv))

(define (accumulate op nv a b next term)
  (if (> a b)
      nv
      (accumulate op (op nv (term a)) (next a) b next term)))

(define (fact x)
  (accumulate * 1 1 x 1+ id))


(define (all? p? a b)
  (accumulate (lambda (x y) (and x y)) #t a b 1+ p?))

(define (count-divisors n)
  (accumulate + 0 1 n 1+ (lambda (x) (if (= (remainder n x) 0) 1 0))))




    