#include "mein_knn.hpp"

/**
 * @brief implementation of Euclidean distance for 1 column dataset
 *
 * @param matrix
 * @param newmatrix
 * @return arma::Col<double>
 */
arma::Col<double> Euclidean_distance(arma::mat &matrix, arma::mat &newmatrix)
{
    arma::Col<double> sumdistance(matrix.n_cols);
    double powered, squaredSum = 0.0;

    for (arma::uword j = 0; j < matrix.n_cols; j++)
    {
        for (arma::uword i = 0; i < matrix.n_rows; i++)
        {
            powered = std::pow(
                (newmatrix(i, 0) - matrix(i, j)), 2);
            squaredSum += powered;
        }
        sumdistance(j) = std::sqrt(squaredSum);
        squaredSum = 0.0;
    }
    return sumdistance;
}

/**
 * @brief Gets the class from the pair
 *
 * @param distance_out std::vector<std::pair<double, size_t>>
 * @param k number of points to classify
 * @return int
 */
int Mein_KNN::class_occurrences(std::vector<std::pair<double, size_t>> &distance_out, int k)
{
    std::unordered_map<int, int> class_count;
    for (size_t i = 0; i < k; ++i)
    {
        class_count[distance_out[i].second]++;
    }

    // find the majority class
    int max_count = 0;
    int max_class = -1;
    for (const auto &pair : class_count)
    {
        if (pair.second > max_count)
        {
            max_count = pair.second;
            max_class = pair.first;
        }
    }

    return max_class;
}

/**
 * @brief Construct a new Mein_KNN object
 *
 */
Mein_KNN::Mein_KNN(){};

/**
 * @brief Construct a new Mein_KNN object
 *
 * @param matt matrix dataset
 * @param matrow dataset labels
 */
Mein_KNN::Mein_KNN(arma::mat &matt, arma::Row<size_t> &matrow) : matrix(matt), matrix_label(matrow){};

/**
 * @brief Construct a new Mein_KNN object
 *
 * @param matt matrix dataset
 * @param matrow dataset labels
 * @param deqn distance equation type
 */
Mein_KNN::Mein_KNN(arma::mat &matt, arma::Row<size_t> &matrow, DistanceEQN deqn) : matrix(matt), matrix_label(matrow), Deqn(deqn){};

/**
 * @brief classifies matrix dataset
 *
 * @param predmat matrix to classify
 * @param k number of neighbours
 * @param deqn distance equation type
 * @return int
 */
int Mein_KNN::Classify(arma::mat &predmat, int k, DistanceEQN deqn)
{
    arma::Col<double> sumdistance = Euclidean_distance(matrix, predmat);

    std::vector<std::pair<double, size_t>> dist_label;
    for (size_t j = 0; j < matrix_label.n_cols; j++)
    {
        for (size_t i = 0; i < matrix_label.n_rows; i++)
        {
            dist_label.push_back({sumdistance(j, i),
                                  matrix_label(i, j)});
        }
    }

    // sort
    std::sort(
        dist_label.begin(), dist_label.end(),
        [](const std::pair<double, size_t> &a, const std::pair<double, size_t> &b)
        {
            return a.first < b.first;
        });

    // count occurrances
    if (dist_label.size() < k)
        std::cerr << "K is greater than dataset size" << std::endl;

    return class_occurrences(dist_label, k);
}

/**
 * @brief Computes the accuracy of the class
 *
 * @param matt matrix of the dataset
 * @param matrow real labels
 * @return double : max is 1, mini is 0
 */
double Mein_KNN::Evaluate(arma::mat &matt, arma::Row<size_t> &matrow)
{
    arma::Row<size_t> res(matt.n_cols);
    for (arma::uword i = 0; i < matt.n_cols; i++)
    {
        arma::mat col = matt.col(i);
        res(i) = Classify(col);
    }
    return ComputeAccuracy(res, matrow);
}

/**
 * @brief returns a more comprehensive report of the class evaluation
 *
 * @param matt matrix of the dataset
 * @param matrow real labels
 */
void Mein_KNN::ClassReport(arma::mat &matt, arma::Row<size_t> &matrow)
{
    arma::Row<size_t> res(matt.n_cols);
    for (arma::uword i = 0; i < matt.n_cols; i++)
    {
        arma::mat col = matt.col(i);
        res(i) = Classify(col);
    }
    double result = ComputeAccuracy(res, matrow);
    std::cout << "[INFO] " << std::setw(4) << "Accurracy - " << result << std::endl;
    ClassificationReport(res, matrow);
}