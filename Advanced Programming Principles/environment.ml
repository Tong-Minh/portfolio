    type 'a t = (string * 'a item) list
      and 'a item = Value of 'a | Module of 'a t

    (** [empty] is the empty environment. *)
    (* t is a type with a list of string item tuples and items are a type of either value 'a or module of 'a t *)
    let empty = []
    
    (** [lookup_module] takes a list of names and recursively
        resolves the names to find the module. It returns an
        environment that has all the bindings exported by
        the module.
    
        For example, [lookup_module ["M"; "N"; "O"]] will
        locate and return an environment having all the
        bindings exported by the module [M.N.O]. Say,
        if [M.N.O.P.x] and [M.N.O.y] are defined, then
        the resulting environment will have a value binding [y]
        and a module binding that binds [P] to the environment
        that binds [x] to a value. (Think about how OCaml
        modules work.)
        
        @raise Not_found if it cannot find the module binding. *)
    let rec lookup_module lst = match lst with
        | [] -> raise Not_found
        | h :: t -> 
          if h =  then 
        
    (** [lookup_value] is similar to [lookup_module]
        except that it returns a value instead.
    
        For example, [lookup_value ["M"; "N"; "x"]]
        will locate and return the value that [M.N.x]
        is bound to.
    
        @raise Not_found if it cannot find the binding. *)
    val lookup_value : string list -> 'a t -> 'a
    
    (** [bind_value ("x", v) e] returns a new environment
        that extends the old environment [e] with
        a new value binding that binds [x] to [v].
    
        For simplicity, you may assume value names will not
        collide with module names. In OCaml, values must start
        with a lowercase letter (except some special cases),
        and modules must start with an uppercase letter.
    *)
    val bind_value : string * 'a -> 'a t -> 'a t
    
    (** [bind_module ("M", m) e] returns a new environment
        that extends the old environment [e] with
        a new module binding that binds [M] to [m].
    
        In terms of OCaml, the environment [m] represents
        all the bindings exported by a module.
    
        For simplicity, you may assume module names will not
        collide with value names. In OCaml, modules must start
        with an uppercase letter, and values must start with
        a lowercase letter (except some special cases). *)
    val bind_module : string * 'a t -> 'a t -> 'a t
    
    (** [append] concatenates two environments together.
    
        In the new environment returned by [append e1 e2],
        the bindings in [e2] will shadow the bindings in [e1].
        That is, the concatenation is done is the textual order.
        Or, in other words, if both [e1] and [e2] bind the
        same name, the binding in [e2] prevails. *)
    val append : 'a t -> 'a t -> 'a t
    