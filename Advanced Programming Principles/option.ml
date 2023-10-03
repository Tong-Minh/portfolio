(* A function last of type int list -> int option that returns the last element of the list. However, when the list is empty, it returns None. For example,
last [1; 3; 2] is Some 2
last [] is None because the list is empty
A function collect_some of type int option list -> int list that extracts all numbers from the input list and drops all None. For example,
collect_some [Some 100; None; None; Some 200] is [100; 200]
collect_some [Some 10] is [10]
collect_some [None; None; None] is [] because all elements are None *)

(* type option = | *)
let rec last (x : int list) : int option = 
  match x with
  | [] -> None
  | h :: t -> 
    if t = [] then Some h else last t

let rec collect_some (x : int option list) : int list =
    match x with
    | [] -> []
    | Some h :: t -> h :: collect_some t
    | None :: t -> collect_some t