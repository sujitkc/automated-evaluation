data = dlmread('output-t4.csv', ',')
xs = 1:101;

for row = 1:15
  ys = data(row, 2:102);
  plot(xs, ys);
  hold on
end
