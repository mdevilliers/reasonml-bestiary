let rec split = (n, xs) => {
  let rec take = (k, xs, ys) =>
    switch (k, xs) {
    | (0, _) => [List.rev(ys), ...split(n, xs)]
    | (_, []) =>
      switch ys {
      | [] => []
      | _ => [ys]
      }
    | (_, [x, ...xs']) => take(k - 1, xs', [x, ...ys])
    };
  take(n, xs, [])
};
