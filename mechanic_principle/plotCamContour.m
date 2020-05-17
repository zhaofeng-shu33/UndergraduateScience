s=@(theta) -160*sin(theta-pi/2)+120*sqrt(1-(4*cos(theta-pi/2)/3-1)^2);
theta_0=fzero(@(theta_0) (-130*cos(theta_0)+110*sin(theta_0))^2-4*4750,pi/2);
s_start=s(theta_0);
s_end=s_start+80;
s_middle=mean([s_start,s_end]);
N=360;%unit:degree
phi_array=linspace(0,2*pi,N);
acceleration=2*(s_middle-s_start)/60^2;
for i=1:60
    s_array(i)=s_start+0.5*acceleration*i^2;%s(0)=s_start;
end
v_middle=60*acceleration;
for i=61:120
    s_array(i)=s_middle+v_middle*(i-60)-0.5*acceleration*(i-60)^2;%s(0)=s_start;
end
for i=121:150
    s_array(i)=s_end;
end
acceleration=2*(s_middle-s_start)/30^2;
for i=151:180
    s_array(i)=s_end-0.5*acceleration*(i-150)^2;
end
v_middle=30*acceleration;
for i=181:210
    s_array(i)=s_middle-v_middle*(i-180)+0.5*acceleration*(i-180)^2;
end
for i=211:360
    s_array(i)=s_start;
end
theta_array(1)=fzero(@(theta) s(theta)-s_array(1),theta_0);
for i=2:360
    theta_array(i)=fzero(@(theta) s(theta)-s_array(i),theta_array(i-1));
end
AB=sqrt(65^2+55^2-50^2);
OA=65-55j;
polar_rho_theta=exp(-1j*phi_array).*(OA+AB*exp(1j*(theta_array)));