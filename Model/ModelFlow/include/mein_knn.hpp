/**
 * @file mein_knn.hpp
 * @author John Obi (johnobi2003@gmail.com)
 * @brief The implementation of K-nearest neighbour
 * @version 0.1.0
 * @date 2024-04-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MEIN_KNN_HPP
#define MEIN_KNN_HPP

#include "ModelBuild.hpp"

enum DistanceEQN
{
    EUCLIDEAN
};

/**
 * @brief implementation of Euclidean distance for 1 column dataset
 *
 * @param matrix
 * @param newmatrix
 * @return arma::Col<double>
 */
arma::Col<double> Euclidean_distance(arma::mat &matrix, arma::mat &newmatrix);

/**
 * @brief Mein_KNN class for my in-built implementation of KNN algorithm
 *
 */
class Mein_KNN
{
private:
    arma::mat matrix;               // dataset
    arma::Row<size_t> matrix_label; // dataset label
    int k;
    DistanceEQN Deqn = DistanceEQN::EUCLIDEAN;

    /**
     * @brief Gets the class from the pair
     *
     * @param distance_out std::vector<std::pair<double, size_t>>
     * @param k number of points to classify
     * @return int
     */
    int class_occurrences(std::vector<std::pair<double, size_t>> &distance_out, int k);

public:
    /**
     * @brief Construct a new Mein_KNN object
     *
     */
    Mein_KNN();

    /**
     * @brief Construct a new Mein_KNN object
     *
     * @param matt matrix dataset
     * @param matrow dataset labels
     */
    Mein_KNN(arma::mat &matt, arma::Row<size_t> &matrow);

    /**
     * @brief Construct a new Mein_KNN object
     *
     * @param matt matrix dataset
     * @param matrow dataset labels
     * @param deqn distance equation type
     */
    Mein_KNN(arma::mat &matt, arma::Row<size_t> &matrow, DistanceEQN deqn);

    /**
     * @brief classifies matrix dataset
     *
     * @param predmat matrix to classify
     * @param k number of neighbours
     * @param deqn distance equation type
     * @return int
     */
    int Classify(arma::mat &predmat, int k = 7, DistanceEQN deqn = DistanceEQN::EUCLIDEAN);

    /**
     * @brief Computes the accuracy of the class
     *
     * @param matt matrix of the dataset
     * @param matrow real labels
     * @return double : max is 1, mini is 0
     */
    double Evaluate(arma::mat &matt, arma::Row<size_t> &matrow);

    /**
     * @brief returns a more comprehensive report of the class evaluation
     *
     * @param matt matrix of the dataset
     * @param matrow real labels
     */
    void ClassReport(arma::mat &matt, arma::Row<size_t> &matrow);
};

#endif