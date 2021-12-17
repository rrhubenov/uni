
(define (fib n)
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fib (- n 2)) (fib (- n 1))))))

(define (fib-iter n prev curr)
  (cond ((= n 0) prev)
        ((= n 1) curr)
        (else (fib-iter (- n 1) curr (+ prev curr)))))


(define (my-gcd a b)
  (cond ((= a b) a)
        ((> a b) (my-gcd (- a b) b))
        (else (my-gcd a (- b a)))))

; [a, b]
(define (sum a b)
  (define (sum-helper current result)
    (if (> current b)
        result
        (sum-helper (+ current 1) (+ result current))))
  (sum-helper a 0))

(define (reverse-number x)
  (define (reverse-helper curr acc)
    (if (= curr 0)
        acc
        (reverse-helper (quotient curr 10) (+ (* 10 acc) (remainder curr 10)))))
  (reverse-helper x 0))

(define (is-prime? x))

; higher order functions
(define (sum-interval start end)
  (define (sum-helper acc)
    (if (= start end)
        acc
        (sum-helper (+ start 1) (+ start acc))))
  (sum-helper 0)
  )

(define (product-interval start end)

  )

(define (sum-cubes start end)

  )

(define (sum-interval-even start end)

  )