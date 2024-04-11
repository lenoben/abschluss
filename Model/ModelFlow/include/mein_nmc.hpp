/**
 * @file mein_nmc.hpp
 * @author John Obi (johnobi2003@gmail.com)
 * @brief The implementaion of nearest mean classifier
 * @version 0.1.0
 * @date 2024-04-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MEIN_NMC_HPP
#define MEIN_NMC_HPP

#include "ModelBuild.hpp"

/**
 * @brief Mein_NMC class is my inbuilt implementation of nearest mean classifier
 *
 */
class Mein_NMC
{
private:
    std::vector<std::pair<int, arma::mat>> vect_pair_mat;

public:
    /**
     * @brief Construct a new Mein_NMC object
     *
     */
    Mein_NMC();

    /**
     * @brief Fits the dataset and its labels in a pair
     *
     * @param matx matrix of the dataset
     * @param rowy labels
     */
    void Fit(arma::mat &matx, arma::Row<size_t> &rowy);

    /**
     * @brief predicts or classify the class from the dataset. initially made of just 1 set of dataset
     *
     * @param matx matrix to predict
     * @return int : class from the label
     */
    int Predict(arma::mat &matx);

    /**
     * @brief Computes the accuracy of the class
     *
     * @param matx matrix of the dataset
     * @param rowy real labels
     * @return double : max is 1, mini is 0
     */
    double Evaluate(arma::mat &matx, arma::Row<size_t> &rowy);

    /**
     * @brief returns a more comprehensive report of the class evaluation
     *
     * @param matx matrix of the dataset
     * @param rowy real labels
     */
    void ClassReport(arma::mat &matx, arma::Row<size_t> &rowy);
};

#endif