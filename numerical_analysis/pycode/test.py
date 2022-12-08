import numpy as np
from muller import muller_method
from liebmann import liebmann_5

def test_muller_method():
    f = lambda x: 3*x+np.sin(x) - np.exp(x)
    root = muller_method(f, 0, 0.5, 1, 3)
    assert np.abs(root - 0.3604217) < 0.000001

def test_liebmann_method():
    u = np.zeros([5, 9])
    u[:, -1] = 100
    liebmann_5(u, 30)
    u_ref_1 = np.array([0.3530, 0.9132, 2.0103, 4.2957, 9.1531, 19.6631, 43.2101])
    np.linalg.norm(u[1, 1:-1] - u_ref_1) < 0.00027