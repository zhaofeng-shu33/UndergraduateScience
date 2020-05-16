function y=trapezoidalMethod(lambda,h)
y(1)=1;
N=ceil(10/h)+1;
f=@(t) (1-lambda)*cos(t)-(1+lambda)*sin(t);
for i=2:N
    y(i)=(y(i-1)+0.5*h*(lambda*y(i-1)+f((i-2)*h)+f((i-1)*h)))/(1-0.5*h*lambda);
end

