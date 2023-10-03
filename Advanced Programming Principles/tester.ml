(** This signature was adapted from the textbook
    https://cs3110.github.io/textbook/chapters/modules/functional_data_structures.html#maps *)
module type STRING_MAP = sig
  (** ['a t] is the type of string-indexed maps
      with value type ['a]. *)
  type 'a t

  (** [empty] is an empty map. *)
  val empty  : 'a t

  (** [insert k v m] is the map [m] augmented with
      the mapping from [k] to [v]. *)
  val insert : string -> 'a -> 'a t -> 'a t

  (** [lookup k m] returns the value [k] maps to in [m].

      @raise Not_found if [k] is not bound in [m]. *)
  val lookup : string -> 'a t -> 'a
end

(** The type of recipes to build a map. *)
type 'a build =
  | Empty
  (** [Empty] means calling [empty] to get a map. *)
  | Insert of string * 'a * 'a build
  (** [Insert (k, v, b)] means building a map [m]
      from the recipe [b] and then calling
      [insert k v m] to get a map. *)

(** The type of checks on a map. *)
type 'a check =
  | Lookup of string * ('a -> bool) option
  (** [Lookup (k, None)] means calling [lookup]
      with the key [k] on the map should fail.

      [Lookup (k, Some p)] means calling [lookup]
      with the key [k] on the map should succeed,
      and the obtained value [v] should satisfy [p].
      That is, [p v] should be [true]. *)

module StringMapTester (StringMap : STRING_MAP) :
sig
  (** [build b] follows the recipe [b] and
      build the map. *)
  val build : 'a build -> 'a StringMap.t

  (** [test m c] tests whether the map [m]
      satisfies the check [c]. *)
  val test : 'a StringMap.t -> 'a check -> bool
end
=
struct
  open StringMap
  
 let rec build = function
 | Empty -> empty
 | Insert (k, v, b) -> insert k v (build b)

 let test m c = 
  match c with
    | Lookup (k, None) -> 
      (match StringMap.lookup k m with
      | exception Not_found -> true
      | _ -> false)
    | Lookup (k, Some p) -> 
      (match StringMap.lookup k m with
      | exception Not_found -> false
      | x -> p x )
  (* 👉 Complete this module. *)
end

(* After finishing the above functor, you might wonder how to
   test a tester. You should implement a few modules of the
   signature [STRING_MAP] (the textbook has one) and check
   whether you can use your functor to test them. The code
   could be:

   {[
     module MyStringMap1 : STRING_MAP =
     struct
       (* implementation of STRING_MAP *)
     end

     module MyStringMap1Tester = StringMapTester (MyStringMap1)

     let () = assert MyStringMap1Tester.(test (build Empty) (Lookup ("hi", None)))
   ]}

   The [assert expr] is a convenient built-in syntax that
   raises an exception when [expr] is not true. Ask a TA
   if you are confused.
*)
