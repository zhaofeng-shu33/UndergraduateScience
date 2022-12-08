import numpy as np
def power_method(A, u, k):
    _u = np.array(u)    
    for i in range(k):
        index = np.argmax(np.abs(_u))
        _u = _u / _u[index]
        _u = A @ _u
    index = np.argmax(np.abs(_u))
    _lambda = _u[index]
    return (_lambda, _u / _lambda)

if __name__ == '__main__':
    A = np.array([[3, -1, 0], [-2, 4, -3], [0, -1, 1]])
    u = np.array([1, 1, 1])
    print(power_method(A, u, 14))
        
    