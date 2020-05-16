function y=eulerMethod(lambda,h)
y(1)=1;
N=ceil(10/h)+1;
for i=2:N
    y(i)=y(i-1)+h*(lambda*y(i-1)+(1-lambda)*cos((i-2)*h)-(1+lambda)*sin((i-2)*h));
end



% [0,1;u*(-2)*y(1)*y(2)-1,u*(1-y(1)^2)]
% ode45(@(t,y) vdp2(t,y,100),[0 1],[3,3]',options);
% xlabel('t');
% ylabel('y(t) and y''(t)');
% legend('y(t)','y''(t)');
% title('Time series diagram: u=100,relativeError=0.01')
% print('D:\Numerical Analysis\SecondCoursework\08.bmp','-dbitmap')
% 
% ode45(@(t,y) vdp2(t,y,100),[0 1],[3,3]',options2);
% xlabel('y(t)');ylabel('y''(t)');
% title('phase diagram: u=100,relativeError=0.01')
% print('D:\Numerical Analysis\SecondCoursework\07.bmp','-dbitmap')
