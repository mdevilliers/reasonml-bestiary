type tileColor =
  | Red
  | Green;

type tile = {
  key: int,
  color: tileColor
};

type gameState =
  | Running
  | GameOver;

type game = {
  tiles: list(tile),
  rowSize: int,
  totalMoves: int,
  state: gameState
};

type action =
  | OnClick(int)
  | RestartGame;
