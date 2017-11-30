type state =
  | On
  | Off;

type tile = {
  key: int,
  state
};

type game = {
  tiles: list(tile),
  rowSize: int,
  totalMoves: int
};

type action =
  | OnClick(int)
  | RestartGame;
