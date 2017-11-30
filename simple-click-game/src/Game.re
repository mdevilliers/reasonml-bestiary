let generateBoard = (size) => {
  let rec helper = (n, acc) =>
    switch n {
    | 0 => acc
    | _ =>
      let t = Random.bool() ? Types.{key: n, state: Types.On} : Types.{key: n, state: Types.Off};
      helper(n - 1, [t, ...acc])
    };
  helper(size * size, [])
};

let newGame = (size) => Types.{tiles: generateBoard(size), rowSize: size};

let partitionOnKey = (key: int, tiles: list(Types.tileType)) =>
  List.partition((i: Types.tileType) => i.key == key, tiles);

let flipState = (tile: Types.tileType) =>
  switch tile.state {
  | Types.On => Types.{key: tile.key, state: Types.Off}
  | Types.Off => Types.{key: tile.key, state: Types.On}
  };

let update = (game: Types.game, selected: int) => {
  let up = {
    let n = selected - game.rowSize;
    n <= 0 ? None : Some(n)
  };
  let down = {
    let n = selected + game.rowSize;
    n > game.rowSize * game.rowSize ? None : Some(n)
  };
  let left =
    switch (selected mod game.rowSize) {
    | 1 => None
    | _ => Some(selected - 1)
    };
  let right =
    switch (selected mod game.rowSize) {
    | 0 => None
    | _ => Some(selected + 1)
    };
  [up, down, left, right, Some(selected)]
  |> List.filter(
       (i) =>
         switch i {
         | None => false
         | Some(_) => true
         }
     )
  |> List.map((Some(i)) => i)
  |> List.fold_left(
       (all: list(Types.tileType), i: int) => {
         let ([one], others) = partitionOnKey(i, all);
         let flipped = flipState(one);
         List.append(others, [flipped])
       },
       game.tiles
     )
  |> List.sort((a: Types.tileType, b: Types.tileType) => compare(a.key, b.key))
};

let component = ReasonReact.reducerComponent("Game");

let make = (_children) => {
  ...component,
  initialState: () => newGame(5),
  reducer: (action, state) =>
    switch action {
    | Types.OnClick(n) =>
      let _ = Js.log("clicked!" ++ string_of_int(n));
      let tiles = update(state, n);
      ReasonReact.Update({...state, tiles})
    },
  render: (self) => <Board game=self.state reducer=self.reduce />
};
