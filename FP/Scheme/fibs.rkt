(define (iterative-fib n)
  (define (helper prev1 prev2 curr)
    (if (< curr n)
        (helper prev2 (+ prev1 prev2) (+ curr 1))
        prev2))
  (helper 0 1 1))

(define (linear-fib n)
  (cond
    ((= n 1) 1)
    ((= n 2) 1)
    (else (+ (linear-fib (- n 2)) (linear-fib (- n 1))))))