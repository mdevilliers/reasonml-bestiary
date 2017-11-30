type state =
  | On
  | Off;

type tileType = {
  key: int,
  state
};

type game = {
  tiles: list(tileType),
  rowSize: int
};

type action =
  | OnClick(int);
