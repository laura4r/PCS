#include <iostream>
#include "gradiente_coniugato.hpp"

int main(void) {
    const double tol = 1.0e-15;
    const unsigned int it_max = 1000;
    unsigned int n = 3;

    Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);
    if (abs(B.determinant()) < tol) {
        return EXIT_FAILURE ;
    }

    Eigen::MatrixXd A = B.transpose() * B ;        /*A definita così per averla def positiva*/
    Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n) ;    /*Vogliamo che la soluzione vera sia (1,1,1)*/

    Eigen::VectorXd b = A * x_ex ;      /*Vettore dei termini noti*/

    const double res_tol = 1.0e-12;

    Eigen::VectorXd x = grad_c(A , b , res_tol , it_max) ;

    Eigen::VectorXd res = b - A * x ;

    if(res.norm() <= res_tol){
        return EXIT_SUCCESS ;
    }
    else {
        return EXIT_FAILURE ;
    }
}