let rec count (n : int) = 
  if n = 1 then 0 else
    if n mod 2 = 0 then 1 + count (n / 2)
    else 1 + count (3 * n + 1)