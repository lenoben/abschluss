/**
 * @file mein_nmc.hpp
 * @author John Obi (johnobi2003@gmail.com)
 * @brief The implementaion of nearest mean classifier
 * @version 0.1.0
 * @date 2024-04-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MEIN_NMC_HPP
#define MEIN_NMC_HPP

#include "MLServer_Model.hpp"

/**
 * @brief Mein_NMC class is my inbuilt implementation of nearest mean classifier 
 * @tparam MatrixType arma::mat/arma::sp_mat
 *
 */
template <typename MatrixType>
class Mein_NMC
{
private:
    std::vector<std::pair<int, MatrixType>> vect_pair_mat;

public:
    /**
     * @brief Construct a new Mein_NMC object
     *
     */
    Mein_NMC();

    /**
     * @brief Fits the dataset and its labels in a pair
     * 
     * @tparam MatrixType arma::mat/arma::sp_mat
     * @param matx matrix of the dataset
     * @param rowy labels
     */
    
    void Fit(MatrixType &matx, arma::Row<size_t> &rowy);

    /**
     * @brief Fits the dataset and its labels in a pair
     * 
     * @tparam MatrixType arma::mat/arma::sp_mat
     * @param matx matrix of the dataset
     * @param rowy labels
     */
    
    void RFit(MatrixType &matx, arma::Row<size_t> &rowy);

    /**
     * @brief predicts or classify the class from the dataset. initially made of just 1 set of dataset
     * 
     * @tparam MatrixType arma::mat/arma::sp_mat
     * @param matx matrix to predict
     * @return int : class from the label
     */
    
    int Predict(MatrixType &matx);

        /**
     * @brief predicts or classify the class from the dataset. initially made of just 1 set of dataset
     * 
     * @tparam MatrixType arma::mat/arma::sp_mat
     * @param matx matrix to predict
     * @return int : class from the label
     */
    
    int RPredict(MatrixType &matx);
};

Mein_NMC<arma::sp_mat> &get_NMC_SP();

#endif