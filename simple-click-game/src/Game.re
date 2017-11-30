open Types;

let generateBoard = (size) => {
  let rec helper = (n, acc) =>
    switch n {
    | 0 => acc
    | _ =>
      let t = Random.bool() ? {key: n, color: Red} : {key: n, color: Green};
      helper(n - 1, [t, ...acc])
    };
  helper(size * size, [])
};

let newGame = (size) => {tiles: generateBoard(size), rowSize: size, totalMoves: 0, state: Running};

let partitionOnKey = (key, tiles) => List.partition((i) => i.key == key, tiles);

let flipState = (tile) =>
  switch tile.color {
  | Red => {key: tile.key, color: Green}
  | Green => {key: tile.key, color: Red}
  };

let update = (game, selected) => {
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
       (all, i) => {
         let ([one], others) = partitionOnKey(i, all);
         let flipped = flipState(one);
         List.append(others, [flipped])
       },
       game.tiles
     )
  |> List.sort((a, b) => compare(a.key, b.key))
};

let isGameOver = (tiles) => {
  let outcome =
    List.for_all((t) => t.color == Red, tiles) || List.for_all((t) => t.color == Green, tiles);
  outcome ? GameOver : Running
};

let component = ReasonReact.reducerComponent("Game");

let make = (_children) => {
  ...component,
  initialState: () => newGame(3),
  reducer: (action, state) =>
    switch action {
    | OnClick(n) =>
      let tiles = update(state, n);
      let gameState = isGameOver(tiles);
      ReasonReact.Update({...state, tiles, totalMoves: state.totalMoves + 1, state: gameState})
    | RestartGame => ReasonReact.Update(newGame(state.rowSize))
    },
  render: (self) =>
    <div>
      <Control game=self.state reducer=self.reduce />
      <Board game=self.state reducer=self.reduce />
    </div>
};
