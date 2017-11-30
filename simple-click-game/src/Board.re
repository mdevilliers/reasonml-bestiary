open Types;

[%bs.raw {|require('./Board.css')|}];

module Tile = {
  let component = ReasonReact.statelessComponent("Tile");
  let make = (~tile, ~reducer, _children) => {
    ...component,
    render: (_self) =>
      switch tile.state {
      | On => <div className="tile on" onClick=(reducer((_) => OnClick(tile.key))) />
      | Off => <div className="tile off" onClick=(reducer((_) => OnClick(tile.key))) />
      }
  };
};

let component = ReasonReact.statelessComponent("Board");

let make = (~game: Types.game, ~reducer, _children) => {
  ...component,
  render: (_self) => {
    let rows = Utils.split(game.rowSize, game.tiles);
    let drawCells = (cells) =>
      List.map((tile) => <Tile tile reducer />, cells)
      |> Array.of_list
      |> ReasonReact.arrayToElement;
    let drawRows =
      List.map((i) => <div> (drawCells(i)) </div>, rows)
      |> Array.of_list
      |> ReasonReact.arrayToElement;
    <div> drawRows </div>
  }
};
