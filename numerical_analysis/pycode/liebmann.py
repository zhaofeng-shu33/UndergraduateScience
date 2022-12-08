import numpy as np

def liebmann_5(u, k):
    # solving 2D elliptic PDE
    # u is modified in place
    m, n = u.shape
    for _ in range(k):
        for i in range(1, m - 1):
            for j in range(1, n - 1):
                u[i, j] = (u[i - 1, j] + u[i + 1, j] + u[i, j - 1] + u[i, j + 1]) / 4

def liebmann_possion(u, num_iter, const, H, uS, w=1.0):
    m, n = u.shape
    for _ in range(num_iter):
        for i in range(0, m): # row iteration
            for j in range(1, n - 1): # column iteration
                if i == 0:
                    tmp = (2 *  u[i + 1, j] + uS + u[i, j - 1] + u[i, j + 1]) / 4 + const
                    tmp /= (1 + H / 4)
                elif i == m - 1:
                    tmp = (2 * u[i - 1, j] - 30 + u[i, j - 1] + u[i, j + 1]) / 4 + const
                else:
                    tmp = (u[i - 1, j] + u[i + 1, j] + u[i, j - 1] + u[i, j + 1]) / 4 + const
                u[i, j] = w * tmp + (1 - w) * u[i, j]


if __name__ == '__main__':
    Q = 0.6
    k = 0.16
    tau = 0.5
    h = 1
    const = Q * (h ** 2) / (k * tau)
    H = 0.073 * 2 * h / k
    uS = H * 25
    u = np.zeros([6, 10])
    u[:, 0] = 20
    u[:, -1] = 20
    liebmann_possion(u, 28, const, H, uS, 1.57)
    print(u)