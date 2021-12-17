

(define sample-alist '((a . 3) (b . 4) (c . 5)))

(define (get-keys alist)
  (map car alist))

(define (get-values alist)
  (map cdr alist))

(define (1+ x) (+ 1 x))

(define (map-alist f keys)
  (map (lambda (x) (cons x (f x))) keys))

(define graph '((a . (b e))
                (b . (d c))
                (c . (f))
                (d . (c))
                (f . ())
                (e . ())))

(define vertices get-keys)

(define (get-edges v g)
  (cdr (filter (labbda (x) (equal? (car x) v)) g)))

(define (contains? x l)
  (cond  ((null? l) #f)
         ((equal? x (car l)) #t)
         (else (contains? x (cdr l)))))

(define (children v g)
  (cdr (assoc v g)))

(define (edge? v1 v2 g)
  (and (member v2 (cdr (assoc v1 g))) #t))

(define (out-degree v g)
  (length (children v g)))

(define (in-degree v g)
  (cond ((null? g) 0)
        ((contains? v (children (caar g) g)) (+ 1 (in-degree v (cdr g))))
        (else (in-degree v (cdr g)))))

(define (degree v g)
  (+ (out-degree v g) (in-degree v g)))

(define (parents v g)
  (if (null? g) '() 
      (let ((top (caar g))
            (remaining (cdr g)))
        (if (contains? v (children top g)) (cons top (parents v remaining))
            (parents v remaining))
        )))

(define (create-stack l)
  (define (self prop . params)
    (cond ((equal? prop 'empty?) (null? l))
          ((equal? prop 'top) (car l))
          ((equal? prop 'push) (append (reverse params) l))
          ((equal? prop 'pop) (cdr l))))
  self)

(define (dfs a g)
  (define (dfs-helper visited stack)
    (if (stack 'empty?) visited
        (let ((top (stack 'top))
              (tail (stack 'pop)))
          (if (contains? top visited) (dfs-helper visited (create-stack tail))
              (dfs-helper (cons top visited) (create-stack (append (children top g) tail)))))))
  (dfs-helper '() (create-stack (list a))))

