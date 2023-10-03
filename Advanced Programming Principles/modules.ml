module type TreeSignature =
sig
  (** The type of binary trees. *)
  type 'a t = Leaf | Node of 'a * 'a t * 'a t

  (** [empty] is [Leaf]. *)
  val empty : 'a t

  (** takes a single item and puts it in a node *)
  val singleton : 'a -> 'a t

  (** [size t] returns the size of [t] (leaves don't count for this lab). *)
  val size : 'a t -> int

  (** gets the leftmost value of a tree, returns Some a if found, None if not *)
  val leftmost : 'a t -> 'a option

  (** gets the rightmost value of a tree, returns Some a if found, None if not *)
  val rightmost : 'a t -> 'a option

  (** [reverse t] flips the tree [t] horizontally. (This is [flip] but renamed for this lab.) *)
  val reverse : 'a t -> 'a t

  (** takes in a tree and applies a given function to the value of each node *)
  val map : ('a -> 'b) -> 'a t -> 'b t
end

module Tree = 
struct
   type 'a t = Leaf | Node of 'a * 'a t * 'a t
   let empty = Leaf
   let singleton = function a -> Node(a, Leaf, Leaf)
   let rec size = function 
      | Leaf -> 0 
      | Node(a, l, r) -> 1 + size l + size r
   let rec leftmost = function 
      | Leaf -> None 
      | Node(a, Leaf, r) -> Some a 
      | Node(a, l, r) -> leftmost l
   let rec rightmost = function 
      | Leaf -> None 
      | Node(a, l, Leaf) -> Some a 
      | Node(a, l, r) -> leftmost l
   let rec reverse = function 
      | Leaf -> Leaf 
      | Node(a, l, r) -> Node(a, reverse r, reverse l)
   let rec map f = function 
      | Leaf -> Leaf
      | Node(a, l, r) -> Node(f a, map f l, map f r)
end 

module type ListSignature =
sig
  (** generic list type *)
  type 'a t = 'a list

  (** takes an empty list and returns an empty list *)
  val empty : 'a t

  (** takes single value, and puts that in a list *)
  val singleton : 'a -> 'a t

  (** takes a list, and counts each item in that list *)
  val size : 'a t -> int

  (** takes a list and returns None or Some first_value *)
  val leftmost : 'a t -> 'a option

  (** takes a list and returns None or Some last_value *)
  val rightmost : 'a t -> 'a option

  (** reverses a list through concatination *)
  val reverse : 'a t -> 'a t

  (** takes in a list and applies a function f to every value in it *)
  val map : ('a -> 'b) -> 'a t -> 'b t
end

module MyList = 
struct
   type 'a t = 'a list
   let empty = []
   let singleton = function a -> [a]
   let rec size = function 
      | [] -> 0 
      | h :: t -> 1 + size t
   let leftmost = function 
      | [] -> None 
      | h :: t -> Some h 
   let rec rightmost = function 
      | [] -> None 
      | h :: [] -> Some h
      | h :: t -> rightmost t 
   let rec reverse = function 
      | [] -> [] 
      | h :: t -> reverse t @ [h]
   let rec map f = function 
      | [] -> []
      | h :: t -> f h :: map f t
end 

module type Sequence =
sig
   (** The abstract type of sequences. *)
   type 'a t

   (** returns an empty sequence *)
   val empty : 'a t
   (** returns a sequence with only one a *)
   val singleton : 'a -> 'a t

   (** returns the number of elements in the sequence *)
   val size : 'a t -> int

   (** returns none for an empty sequence but the leftmost value otherwise *)
   val leftmost : 'a t -> 'a option

   (** returns none for an empty sequence but the rightmost value otherwise *)
   val rightmost : 'a t -> 'a option

   (** reverse would flip the sequence horizontally *)
   val reverse : 'a t -> 'a t

   (** map f a applies every function f to the old sequence 'a a and turns it into the new sequence 'b a *)
   val map : ('a -> 'b) -> 'a t -> 'b t
end
