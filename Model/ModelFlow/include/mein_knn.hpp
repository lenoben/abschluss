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
    EUCLIDEAN,
    COSINE,
    MANHATTAN,
    COSINE_DISSIMILARITY
};



/**
 * @brief Mein_KNN class for my in-built implementation of KNN algorithm
 *  
 * @tparam MatrixType arma::mat/arma::sp_mat
 */
template <typename MatrixType>
class Mein_KNN
{
private:
    MatrixType matrix;               // dataset
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

    /**
     * @brief implementation of Euclidean distance for 1 column dataset
     *
     * @tparam MatrixType arma::mat/arma::sp_mat
     * @param matrix
     * @param newmatrix
     * @return arma::Col<double>
     */
    arma::Col<double> Euclidean_distance(MatrixType &matrix, MatrixType &newmatrix);

    /**
     * @brief implementation of cosine similarity for the distance between vectors/points
     *
     * @tparam MatrixType arma::mat/arma::sp_mat 
     * @param matrix 
     * @param newmatrix row
     * @return arma::Col<double> 
     */
    arma::Col<double> Cosine_distance(MatrixType &matrix, arma::Row<double> &newmatrix);

    /**
     * @brief implementation of 1 - cosine similarity of the distance between vector points
     *
     * @tparam MatrixType arma::mat/arma::sp_mat
     * @param matrix 
     * @param newmatrix 
     * @return arma::Col<double> 
     */
    arma::Col<double> CosineDis_distance(MatrixType &matrix, MatrixType &newmatrix);

    /**
     * @brief implementation of cosine similarity for the distance between vectors/points
     *
     * @tparam MatrixType arma::mat/arma::sp_mat
     * @param matrix 
     * @param newmatrix
     * @return arma::Col<double> 
     */
    arma::Col<double> Cosine_distance(MatrixType &matrix, MatrixType &newmatrix);

    /**
     * @brief implementation of manhattan distance between vectors/points
     *
     * @tparam MatrixType arma::mat/arma::sp_mat 
     * @param matrix 
     * @param newmatrix
     * @return arma::Col<double> 
     */
    arma::Col<double> Manhattan_distance(MatrixType &matrix, MatrixType &newmatrix);

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
    Mein_KNN(MatrixType &matt, arma::Row<size_t> &matrow);

    /**
     * @brief Construct a new Mein_KNN object
     *
     * @param matt matrix dataset
     * @param matrow dataset labels
     * @param deqn distance equation type
     */
    Mein_KNN(MatrixType &matt, arma::Row<size_t> &matrow, DistanceEQN deqn);

    /**
     * @brief Construct a new Mein_KNN object
     * 
     * @param matt matrix dataset
     * @param matrow dataset labels
     * @param kn number of neigbours
     * @param deqn distance equation type
     */
    Mein_KNN(MatrixType &matt, arma::Row<size_t> &matrow, int kn, DistanceEQN deqn = DistanceEQN::EUCLIDEAN);

    /**
     * @brief classifies matrix dataset
     *  
     * @tparam MatrixType arma::mat/arma::sp_mat
     * @param predmat matrix to classify
     * @param k number of neighbours
     * @param deqn distance equation type
     * @return int
     */
    
    int Classify(MatrixType &predmat, int k = 1, DistanceEQN deqn = DistanceEQN::EUCLIDEAN);

    /**
     * @brief Computes the accuracy of the class 
     * @tparam MatrixType arma::mat/arma::sp_mat
     * @param matt matrix of the dataset
     * @param matrow real labels
     * @return double : max is 1, mini is 0
     */
    
    double Evaluate(MatrixType &matt, arma::Row<size_t> &matrow);

    /**
     * @brief returns a more comprehensive report of the class evaluation 
     * @tparam MatrixType arma::mat/arma::sp_mat
     * @param matt matrix of the dataset
     * @param matrow real labels
     */
    
    void ClassReport(MatrixType &matt, arma::Row<size_t> &matrow);
};

#endif