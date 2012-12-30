function sequence
T = 1/44100;
time = [0:0.01:1];

denominator = [ 0.41065  -0.81648   0.40585];
numerator = [ 0.0023993   0.0000000  -0.0023993];

start_time = max(length(denominator), length(numerator));
input = zeros(1, length(time));
input(start_time) = 1;


output = zeros(1, length(time));

for i = start_time:length(time)
  output(i) = 0;
  for j = 1:length(numerator)
    output(i) = output(i) + numerator(j)*input(i-j+1);
  end
  for j = 2:length(denominator)
    output(i) = output(i) - denominator(j)*output(i-j+1);
  end
  output(i) = output(i)/denominator(1);
end

hold off;
clf;
plot(time, input, output)
