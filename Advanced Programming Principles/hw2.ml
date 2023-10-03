(** @param num: the recent h, lst: remaining list to compare to
    @returns a smaller list of grouped elements that is appeneded to the main functions output*)
let rec group_aux (num : int) lst =
  match lst with
  |[] -> []
  |h :: t -> 
    if h = num then h :: group_aux num t
    else []

(** @param num: the recent h, lst: remaining list to compare to
    @returns a smaller list that contains the ungrouped elements for [group] to use *)
let rec removal (num : int) lst =
  match lst with
  |[] -> []
  |h :: t -> 
    if h = num then removal h t
    else h::t

(** Function that groups together adjacent equal ints with the helper functions [group_aux] and [removal] *)
let rec group lst =
  match lst with
  |[] -> []
  |h :: t -> (h :: group_aux h t) :: group (removal h t)
