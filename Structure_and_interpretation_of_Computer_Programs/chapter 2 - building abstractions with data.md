home [[SICP]]
previous [[chapter 1 - building abstractions with procedures]]
next

----

concepts: compound data = data abstraction. (how it is used vs how it is constructed, isolate both parts)
**closure**: combine primitive and compound data together. can use this as a "conventional interface"

symbolic expressions (data which are symbols, not numbers)

then we will see generic operations, which will handle different types of data in a program. 

modularity is the ability to build a system into separate chunks that can be modified independently. 

data-directed programming

set of procedures: selectors vs constructors (implements abstract data in terms of the concrete representation)


## 2.1 introduction to data abstraction 

data abstraction: how it is used vs how it is constructed on primitive procedures, isolate both parts)

set of procedures: **selectors vs constructors** (implements abstract data in terms of the concrete representation)

data objects constructed from pairs are called: list-structured data


ex 2.1

```
(define (numer x) (car x))
(define (denom x) (cdr x))


(define (make-rat n d)
  (let ((g (gcd n d)))
    (let ((sign (if (< d 0)
                    -1
                    1)))
      (cons (* sign (/ n g))  (* sign (/ d g))))))


(define (print-rat x)
  (newline)
  (display (numer x))
  (display "/")
  (display (denom x)))


(define one-half (make-rat -1 2))
(define one-third (make-rat -1 3))
(print-rat one-half)

```

normalizing the sign by negating both n and d when d < 0. claude was fucking with me for this exercise.

ex 2.2 

```
(define make-point cons)
(define x-point car)
(define y-point cdr)




(define (make-segment start-point end-point)
  (cons start-point end-point))

(define start-segment car)
(define end-segment cdr)


(define (mid-point s)
  (make-point  (/ (+ (x-point (start-segment s)) (x-point (end-segment s))) 2) ; average x
               (/ (+ (y-point (start-segment s)) (y-point (end-segment s))) 2))) ; average y




(define (print-point p)
  (newline)
  (display "(")
  (display (x-point p))
  (display ",")
  (display (y-point p))
  (display ")"))

(define p1 (make-point 2 3))
(define p2 (make-point 5 6))
(define s1 (make-segment p1 p2))
(print-point (mid-point s1))
```

finally got that shit done, im stupid i know. 
had to understand how constructors / selectors worked, and know how to use them in other functions, creating abstractions. 

We use make-point around the expressions to create a new point, the mid-point.

also 
(x-point (start-segment)) takes the start-point from make-segment. gosh


ex 2.3

first representation (with points and segments)

```
; first representation

(define make-rect cons)
(define bottom-left car)
(define upper-right cdr)

(define (width-rectangle r)
  (abs (- (x-point (upper-right r)) (x-point (bottom-left r)))))


(define (height-rectangle r)
  (abs (- (y-point (upper-right r)) (y-point (bottom-left r)))))


; second representation

(define (area-rectangle r)
  (* (width-rectangle r) (height-rectangle r)))

(define (perimeter-rectangle r)
  (* 2 (+ (width-rectangle r) (height-rectangle r))))


;(define make-rectangle cons) (define width-rectangle car) (define height-rectangle cdr)

(area-rectangle (make-rect 7 4 ))
(perimeter-rectangle (make-rect 7 4))

```

ye need to fix this asap

second representation
```
(define (area-rectangle r)
  (* (width-rectangle r) (height-rectangle r)))

(define (perimeter-rectangle r)
  (* 2 (+ (width-rectangle r) (height-rectangle r))))



(define make-rectangle cons)
(define width-rectangle car)
(define height-rectangle cdr)

(area-rectangle (make-rectangle 7 4))
(perimeter-rectangle (make-rectangle 7 4))

```