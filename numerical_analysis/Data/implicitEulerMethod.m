function y=implicitEulerMethod(lambda,h)
y(1)=1;
N=ceil(10/h)+1;
for i=2:N
    y(i)=(y(i-1)+h*((1-lambda)*cos((i-1)*h)-(1+lambda)*sin((i-1)*h)))/(1-h*lambda);
end