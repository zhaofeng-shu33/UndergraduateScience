import numpy as np
from scipy.integrate import odeint

def ode_func(y, t):
    return [y[1], t + (1-t/5)*y[0]*y[1]]

def func(u_prime):
    t_range = [1.0, 3.0]
    sol = odeint(ode_func, [2, u_prime], t_range)
    return sol[1, 0] + 1

def secant_method(f, x0, x1, k):
    for i in range(k):
        f_x0 = f(x0)
        f_x1 = f(x1)
        print(x1, f_x1)
        x1_new = x1 - f_x1 * (x1 - x0) /  (f_x1 - f_x0)
        x0 = x1
        x1 = x1_new
    return x1

def muller_method(f, x0, x1, x2, k):
    # faster than secant method
    # since it uses the parabola to approximate the function
    for i in range(k):
        f2 = f(x0)
        f0 = f(x1)
        print(x1, f0)
        f1 = f(x2)
        h1 = x2 - x1
        h2 = x1 - x0
        gamma = h2 / h1
        c = f0
        a = (gamma * f1 - f0 * (1+gamma) + f2) / (gamma * h1**2 * (1+gamma))
        b = (f1 - f0 - a*h1**2) / h1
        if b > 0:
            x2_new = x1 - 2 * c / (b + np.sqrt(b*b-4*a*c))
        else:
            x2_new = x1 - 2 * c / (b + np.sqrt(b*b-4*a*c))
        if x2_new > x1:
            x0 = x1
            x1 = x2_new
        else:
            x2 = x1
            x1 = x2_new
    return x1

if __name__ == '__main__':
    secant_method(func, -1.5, -3.0, 5)
    x2 = secant_method(func, -1.5, -3.0, 1)
    print('muller')
    muller_method(func, -1.5, x2, -3.0, 3)


