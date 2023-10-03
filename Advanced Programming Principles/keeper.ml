let rec square_all l =
match l with
|[] -> []
|h :: t -> h * h :: square_all t

let rec sum_positive l =
  match l with 
  |[] -> 0
  |h :: t ->
    if h > 0 then h + sum_positive t
    else sum_positive t

let rec keep_last l = 
  match l with
  |[] -> []
  |h :: t -> 
    if List.length t = 0 then [h]
    else keep_last t

let rec remove_first_copy num l = 
  match l with 
  |[] -> false
  |h :: t -> 
    if num = h then true
    else remove_first_copy num t

let rec removal num lst =
  match lst with
  |[] -> []
  |h :: t -> 
    if h = num then removal h t
    else h::t

let rec keep_first_copies l =
  match l with
  |[] -> []
  |h :: t -> 
    if remove_first_copy h t then h :: keep_first_copies (removal h t) 
    else keep_first_copies t

