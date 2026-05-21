#pragma once
#include <Eigen/Dense>
#include <Eigen/SVD>


Eigen::VectorXd grad_c(const Eigen::MatrixXd A , const Eigen::VectorXd b , const double res_tol , const unsigned int it_max) {
    unsigned int n = A.rows() ;

    Eigen::VectorXd x = Eigen::VectorXd::Zero(n) ;
    Eigen::VectorXd res = b - A * x ;
    Eigen::VectorXd p = res ;

    int it = 0 ;

    while(res.norm() > res_tol && it < it_max) {
        double alpha_k = ((p.transpose() * res) / (p.transpose() * A * p)).value() ;
        x = x + alpha_k * p ;
        res = b - A * x ;
        double beta_k = ((p.transpose() * A * res) / (p.transpose() * A * p)).value() ;
        p = res - beta_k * p ;
        it++ ;
    }

    return x ;
}