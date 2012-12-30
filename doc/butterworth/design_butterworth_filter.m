function design_butterworth_filter(order, T, f0, bw)
freq_interval = bw*T
freq_max = round((bw+f0)*2)
omega = [0:freq_interval:freq_max];


z = exp(i*omega*T);
% Gain is 0


% Try using the bilinear transform
% TODO
ang_band_width = bw*2*pi;
ang_centre_freq = f0*2*pi;
w1w2_base = sqrt(0.25*ang_band_width*ang_band_width+ang_centre_freq*ang_centre_freq);
w1 = w1w2_base-0.5*ang_band_width;
w2 = w1w2_base+0.5*ang_band_width;
pre_warped_w1 = bilinear_pre_warp(w1, T);
pre_warped_w2 = bilinear_pre_warp(w2, T);
pre_warped_w0 = sqrt(pre_warped_w1*pre_warped_w2);
pre_warped_Q = pre_warped_w0/(pre_warped_w2-pre_warped_w1);

wc = 1;

denom_polynomial =  [1];
num_polynomial = [1];

denom_factor = 1;

poles = exp(i*pi()*(2*[1:order]+order-1)/(2*order))
% expect a pole and a zero at the 

for pn = 1:order
  t1 = wc*pre_warped_Q*pre_warped_w0*(T^2)/4;
  t2 = poles(pn)*T/2;
  t3 = wc*pre_warped_Q/pre_warped_w0;

  t1
  t2
  t3

  a = (t1-t2+t3)
  b = (2*t1 -2*t3)
  c = (t1+t2+t3)

  this_denom_magnitude = norm([a b c]);
  denom_factor = denom_factor/this_denom_magnitude;
  denom_polynomial = conv(denom_polynomial, ([a b c]/this_denom_magnitude));
end

for pn = 1:order
  num_polynomial = conv(num_polynomial, [1 0 -1]);
end

num_polynomial*denom_factor*(T/2)^order
denom_polynomial

discrete_result_bt = ones(size(omega));
for index = 1:length(omega)

  numerator = 0;
  denominator = 0;

  for nn=1:length(num_polynomial)
    numerator = numerator + num_polynomial(nn)*exp(i*omega(index)*(1-nn)*T);
  end

  for dn=1:length(denom_polynomial)
    denominator = denominator + denom_polynomial(dn)*exp(i*omega(index)*(1-dn)*T);
%    foo = exp(i*omega(index)*(dn-1)*T);
%    printf('Z^%d = %f + %fi\n', dn-1, real(foo), imag(foo));
  end

  discrete_result_bt(index) = ((T/2)^order)*(numerator/denominator)*denom_factor;
  foo = discrete_result_bt(index);

%  foo

end

printf('Filter poles:');
roots(denom_polynomial)
printf('Filter zeroes:');
roots(num_polynomial)

% Work out the continuous-time frequency response

continuous_result = ones(size(omega));
for index = 1:length(omega)
  for pn = 1:order
    continuous_result(index) = continuous_result(index)/(i*omega(index)-poles(pn));
  end
end

% Plot the result
clf;
hold on;
plot(log(omega)/log(2), log(abs(continuous_result))*20/log(10));
plot(log(omega)/log(2), log(abs(discrete_result_bt))*20/log(10));

