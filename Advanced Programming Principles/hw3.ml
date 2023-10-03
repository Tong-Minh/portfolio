type 'a tree = Leaf | Node of 'a * 'a tree * 'a tree

let rec fold_tree init f = function
  | Leaf -> init
  | Node(x, left, right) -> f x (fold_tree init f left) (fold_tree init f right)

let for_all_tree f tree = let helper x left right = f x && left && right in fold_tree true helper tree
