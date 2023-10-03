type 'a tree = Leaf | Node of 'a * 'a tree * 'a tree

let singleton x = Node(x, Leaf, Leaf)

let rec rightmost =
  function
  | Leaf -> None
  | Node(value, l, r) -> if r = Leaf then Some value else rightmost r

let rec flip =
  function
  | Leaf -> Leaf
  | Node(x, l, r) -> Node(x, flip r, flip l)

let rec exists_tree p x =
  match x with
  |Leaf -> false
  |Node(value, l, r) ->
    if p value then true
    else (exists_tree p l) || (exists_tree p r)