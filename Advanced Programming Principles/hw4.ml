module type RATIONAL =
sig
  (** The abstract type of rational numbers. *)
  type t 

  (* returns 0,1 *)
  val zero : t

  (** returns 1,1 *)
  val one : t

  (** [equal x y] tests whether [x] is equal to [y]. *)
  val equal : t -> t -> bool

  (** less_than x y tests if x is less than y and returns true if it is *)
  val less_than : t -> t -> bool

  (** min x y returns x if x is smaller than y, and y otherwise *)
  val min : t -> t -> t

  (** min x y returns y if x is smaller than y, and x otherwise *)
  val max : t -> t -> t

  (** neg x returns -x *)
  val neg : t -> t

  (** [add x y] is the addition [x + y]. *)
  val add : t -> t -> t

  (** sub x y subtracts two "fractions" in the same way add works *)
  val sub : t -> t -> t

  (** mul x y returns x * y, fraction multiplication *)
  val mul : t -> t -> t

  (** [div x y] is the division [x / y]. @raise Division_by_zero when if [y] is zero. *)
  val div : t -> t -> t

  (** Convert an abstract rational number to a pair of integers [(x, y)] such that

      1. the rational number is equal to [x/y]; and
      2. [x/y] is reduced and [y] is positive.

      For example, [(-4)/6] and [2/(-3)] should all output [(-2, 3)]. *)
  val to_pair : t -> int * int

  (** Convert a pair of integers [(x, y)] into an abstract rational number [x/y].

      @raise Division_by_zero when if [y] is 0. *)
  val from_pair : int * int -> t
end

let rec gcd (p : int * int) : int =
    let (x, y) = p in
    if y = 0 then x else gcd (y, x mod y)

module Rational : RATIONAL =
struct
    type t = int * int
    let zero = (0, 1) 
    let one = (1, 1)
    let equal (x1, y1) (x2, y2) = ((x1 * y2) = (x2 * y1)) 
    let less_than (x1, y1) (x2, y2) = ((x1 * y2) * (y1 * y2)) < ((x2 * y1) * (y1 * y2))
    let min (x1, y1) (x2, y2) = if less_than (x1, y1) (x2, y2) then (x1, y1) else (x2, y2)
    let max (x1, y1) (x2, y2) = if less_than (x1, y1) (x2, y2) then (x2, y2) else (x1, y1)
    let neg (x, y) = (-x, y)
    let add (x1, y1) (x2, y2) = 
        if y1 = y2 then 
            (x1 + x2, y1)
        else
            ((x1 * y2) + (x2 * y1), y1 * y2)
    let sub (x1, y1) (x2, y2) = 
        if y1 = y2 then 
            (x1 - x2, y1)
        else
            ((x1 * y2) - (x2 * y1), y1 * y2)
    let mul (x1, y1) (x2, y2) = (x1 * x2, y1 * y2)
    let div (x1, y1) (x2, y2) = 
        if (x2, y2) = (0, 1) then 
            raise Division_by_zero 
        else 
            mul (x1, y1) (y2, x2)
    let to_pair = function
    | (x, y) -> 
        if x = 0 then
            (x,1)
        else 
            let ans = gcd(x, y) in 
                if ans < 0 then 
                    if x<0 && y<0 then
                        (-x/(-ans), -y/(-ans)) 
                    else if (x>=0 && y<0) then 
                        (-x/(-ans), -y/(-ans)) 
                    else
                        (x/(-ans), y/(-ans))
                else
                    if x<0 && y<0 then
                        (-x/(ans), -y/(ans)) 
                    else if (x>=0 && y<0) then 
                        (-x/(ans), -y/(ans)) 
                    else
                        (x/(ans), y/(ans))
        
    let from_pair = function 
    | (a, 0) -> raise Division_by_zero
    | (a, b) -> (a, b)

(** 👉 Fill out the content here. 

      You can choose whatever type [t] to implement your rational numbers. You can
      also decide when to reduce rational numbers as long as [to_pair] outputs
      correct pairs.

      For this homework, please use the built-in exception [Division_by_zero]
      instead of defining your own [Division_by_zero]. You will practice defining
      your own exceptions in the next lab/homework.

      Hint: Lecture 6 (Week 3) has code for computing greatest common divisors,
      though the code can output negative numbers. *)
end
