(** This signature was copied from the textbook
    but the value [to_list] was removed.
    https://cs3110.github.io/textbook/chapters/modules/functional_data_structures.html#stacks *)
module type STACK = sig
  (** ['a t] is the type of stacks with element type ['a]. *)
  type 'a t

  (** [empty] is an empty stack. *)
  val empty : 'a t

  (** [is_empty] tests is an empty stack. *)
  val is_empty : 'a t -> bool

  (** [push x s] pushes an element [x] on top of
      the stack [s] and returns the new stack. *)
  val push : 'a -> 'a t -> 'a t

  (** [peek s] peeks the top element of the stack [s].
      If the stack is empty, [None] is returned. *)
  val peek : 'a t -> 'a option

  (** [pop s] pops the top element of the stack [s]
      and returns the resulting stack. If the stack
      was already empty, [None] is returned. *)
  val pop : 'a t -> 'a t option

  (** [size s] returns the number of elements in [s]. *)
  val size : 'a t -> int
end

(** The type of recipes to build a stack. *)
type 'a build =
  | Empty
  (** [Empty] means calling [empty] to get a stack. *)
  | Push of 'a * 'a build
  (** [Push (x, b)] means building a stack [s] using [b],
      and then calling [push x s] to get a stack. *)
  | Pop of 'a build
  (** [Pop b] means building a stack [s] using [b],
      and then calling [pop s] to get a stack.
      If [pop s] returns [None], the building fails
      and an exception should be raised. +*)

(** The type of checks on a stack. *)
type 'a check =
  | IsEmpty of bool
  (** [IsEmpty b] means that calling [is_empty] on the
      stack should get the answer [b]. *)
  | Peek of ('a -> bool) option
  (** [Peek None] means that calling [peek] on the stack
      should get [None].

      [Peek (Some p)] means that calling [peek] on the stack
      should get [Some x] and [p x] should be true. *)
  | Pop of unit option
  (** [Pop None] means that calling [pop] on the stack
      should get [None].

      [Pop (Some ())] means that calling [pop] on the stack
      should get [Some s] for some stack [s]. *)
  | Size of int
  (** [Size i] means that calling [size] on the stack
      should get the answer [i]. *)

module StackTester (Stack : STACK) :
sig
  (** The exception in indicate that the building fails. *)
  exception BuildFailure

  (** [build b] builds a stack using the recipe [b].

      @raise BuildFailure if the building fails. *)
  val build : 'a build -> 'a Stack.t

  (** [test s c] tests whether the stack [s] satisfies
      the check [c]. *)
  val test : 'a Stack.t -> 'a check -> bool
end
=
struct
    exception BuildFailure
    (* 👉 Complete this module. *)
    let rec build = function
    (* | exception BuildFailure -> exception BuildFailure *)
    | Empty -> Stack.empty
    | Push (x, b) -> Stack.push x (build b)
    | Pop x -> 
    (match Stack.pop (build x) with
        | None -> raise BuildFailure
        | Some s -> s)

let test s c = 
    match c with 
    | IsEmpty b -> Stack.is_empty s = b 
    | Peek None -> Stack.peek s = None
    | Peek (Some p) -> 
        (match Stack.peek s with
        | None -> false
        | Some x -> p x)
    | Pop None -> Stack.pop s = None
    | Pop (Some ()) -> 
        if Stack.pop s = None then false
        else true 
    | Size i -> Stack.size s = i
end
