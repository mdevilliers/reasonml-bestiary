open Types;

[%bs.raw {|require('./Board.css')|}];

module Tile = {
  let component = ReasonReact.statelessComponent("Tile");
  let make = (~tile, ~reducer, ~gameState, _children) => {
    ...component,
    render: (_self) =>
      switch (tile.color, gameState) {
      | (Red, Running) => <div className="tile red" onClick=(reducer((_) => OnClick(tile.key))) />
      | (Green, Running) =>
        <div className="tile green" onClick=(reducer((_) => OnClick(tile.key))) />
      | (Red, GameOver) => <div className="tile red" />
      | (Green, GameOver) => <div className="tile green" />
      }
  };
};

let component = ReasonReact.statelessComponent("Board");

let make = (~game, ~reducer, _children) => {
  ...component,
  render: (_self) => {
    let rows = Utils.split(game.rowSize, game.tiles);
    let gameState = game.state;
    let drawCells = (cells) =>
      List.map((tile) => <Tile tile reducer gameState />, cells)
      |> Array.of_list
      |> ReasonReact.arrayToElement;
    let drawRows =
      List.map((i) => <div> (drawCells(i)) </div>, rows)
      |> Array.of_list
      |> ReasonReact.arrayToElement;
    <div> drawRows </div>
  }
};
