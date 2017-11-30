open Types;

let component = ReasonReact.statelessComponent("Control");

let make = (~game, ~reducer, _children) => {
  ...component,
  render: (_self) =>
    <div>
      <a href="#" onClick=(reducer((_) => RestartGame))>
        (ReasonReact.stringToElement("Restart Game"))
      </a>
      <div>
        (ReasonReact.stringToElement("Current Moves : "))
        (ReasonReact.stringToElement(string_of_int(game.totalMoves)))
      </div>
    </div>
};
