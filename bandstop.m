fs=[110  200];
fp=[100 210];
a1=10;
a2=20;
Fs=500;
wp=(2*pi*fp)/Fs;
ws=(2*pi*fs)/Fs;
Wp=2*Fs*tan(wp/2);
Ws=2*Fs*tan(ws/2);
[N,Wc]=buttord(Wp,Ws,a1,a2,'s')
[b,a]=butter(N,Wc,'stop','s')
[bz,az]=bilinear(b,a,Fs);
H=tf(bz,az,-1)

subplot(141)
zplane(bz,az)
[H2,f]=freqz(bz,az,512,Fs)
subplot(142)
plot(f,abs(H2))
title('Magnitude')
subplot(143)
plot(f,angle(H2))
title('Phase')
subplot(144)
Gain=20*log(abs(H2))
plot(f,Gain)
title('Gain')
