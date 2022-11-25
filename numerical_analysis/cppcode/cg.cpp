#include <Eigen/Core>
#include <iostream>
using namespace Eigen;

/*
Solve Ax=b with Conjugate Gradient method
*/
VectorXd CG(const MatrixXd& A, const VectorXd& b) {
    int n = b.size();
    VectorXd x(n);
    VectorXd r = b - A * x;
    VectorXd p = r;
    while (r.norm() > 1e-4) {
        double alpha = r.dot(r) / p.dot(A * p);
        x += alpha * p;
        VectorXd new_r = b - A * x;
        double beta = new_r.dot(new_r) / r.dot(r);
        p = new_r + beta * p;
        r = new_r;
    }
    return x;
}

int main() {
    MatrixXd A {{3, 1}, {1, 2}};
    VectorXd b {{5, 5}};
    VectorXd x = CG(A, b);
    std::cout << x;
}