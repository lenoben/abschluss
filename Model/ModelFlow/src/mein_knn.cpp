#include "mein_knn.hpp"

// Explicit template instantiation for arma::mat and arma::sp_mat
template class Mein_KNN<arma::mat>;
template class Mein_KNN<arma::sp_mat>;

/**
 * @brief implementation of Euclidean distance for 1 column dataset
 * 
 * @tparam MatrixType arma::mat/arma::sp_mat
 * @param matrix
 * @param newmatrix
 * @return arma::Col<double>
 */
template <typename MatrixType>
arma::Col<double> Mein_KNN<MatrixType>::Euclidean_distance(MatrixType &matrix, MatrixType &newmatrix)
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


template <typename MatrixType>
arma::Col<double> Mein_KNN<MatrixType>::Cosine_distance(MatrixType &matrix, arma::Row<double> &newmatrix){
    arma::Col<double> distances(matrix.n_cols);
    double dotProduct, normA, normB;

    for(arma::uword j = 0; j < matrix.n_cols; j++){
        dotProduct = normA = normB = 0.0;

        for(arma::uword i = 0; i < matrix.n_rows; i++){
            if(matrix(i, j) != 0 && newmatrix(i,0) != 0){
                dotProduct += matrix(i, j) * newmatrix(i);
                normA += std::pow(matrix(i, j),2);
                normB += std::pow(newmatrix(i),2);
            }
        }

        normA = std::sqrt(normA);
        normB = std::sqrt(normB);

        if(normA != 0 && normB != 0){
            //1 - cosine similarity
            distances(j) = (dotProduct / (normA * normB));
        }else{
            distances(j) = 0;
            //if normA/normB = 0, cosine similarity is 0
        }
    }

    return distances;
}

template <typename MatrixType>
arma::Col<double> Mein_KNN<MatrixType>::Cosine_distance(MatrixType &matrix, MatrixType &newmatrix){
    arma::Col<double> distances(matrix.n_cols);
    double dotProduct, normA, normB;

    for(arma::uword j = 0; j < matrix.n_cols; j++){
        dotProduct = normA = normB = 0.0;

        for(arma::uword i = 0; i < matrix.n_rows; i++){
            if(matrix(i, j) != 0 && newmatrix(i,0) != 0){
                dotProduct += matrix(i, j) * newmatrix(i, 0);
                normA += std::pow(matrix(i, j),2);
                normB += std::pow(newmatrix(i, 0),2);
            }
        }

        normA = std::sqrt(normA);
        normB = std::sqrt(normB);

        if(normA != 0 && normB != 0){
            //1 - cosine similarity
            distances(j) = (dotProduct / (normA * normB));
        }else{
            distances(j) = 0;
            //if normA/normB = 0, cosine similarity is 0
        }
    }

    return distances;
}

template <typename MatrixType>
arma::Col<double> Mein_KNN<MatrixType>::CosineDis_distance(MatrixType &matrix, MatrixType &newmatrix){
    arma::Col<double> distances(matrix.n_cols);
    double dotProduct, normA, normB;

    for(arma::uword j = 0; j < matrix.n_cols; j++){
        dotProduct = normA = normB = 0.0;

        for(arma::uword i = 0; i < matrix.n_rows; i++){
            if(matrix(i, j) != 0 && newmatrix(i,0) != 0){
                dotProduct += matrix(i, j) * newmatrix(i, 0);
                normA += std::pow(matrix(i, j),2);
                normB += std::pow(newmatrix(i, 0),2);
            }
        }

        normA = std::sqrt(normA);
        normB = std::sqrt(normB);

        if(normA != 0 && normB != 0){
            //1 - cosine similarity
            distances(j) = 1 - (dotProduct / (normA * normB));
        }else{
            distances(j) = 1;
            //if normA/normB = 0, cosine similarity is 0
        }
    }

    return distances;
}

template <typename MatrixType>
arma::Col<double> Mein_KNN<MatrixType>::Manhattan_distance(MatrixType &matrix, MatrixType &newmatrix){
    arma::Col<double> distances(matrix.n_cols);
    double absDiff, sumDiff = 0.0;

    for(arma::uword j = 0; j < matrix.n_cols; j++){
        for(arma::uword i = 0; i < matrix.n_rows; i++){
            absDiff = std::abs(newmatrix(i,0) - matrix(i,j));
            sumDiff += absDiff;
        }
        distances(j) = sumDiff;
        sumDiff = 0.0;
    }

    return distances;
}

/**
 * @brief Gets the class from the pair
 * 
 * @tparam MatrixType arma::mat/arma::sp_mat
 * @param distance_out std::vector<std::pair<double, size_t>>
 * @param k number of points to classify
 * @return int
 */
template <typename MatrixType>
int Mein_KNN<MatrixType>::class_occurrences(std::vector<std::pair<double, size_t>> &distance_out, int k)
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
template <typename MatrixType>
Mein_KNN<MatrixType>::Mein_KNN(): k(1), Deqn(DistanceEQN::MANHATTAN) {};

/**
 * @brief Construct a new Mein_KNN object
 *
 * @param matt matrix dataset
 * @param matrow dataset labels
 */
template <typename MatrixType>
Mein_KNN<MatrixType>::Mein_KNN(MatrixType &matt, arma::Row<size_t> &matrow) : matrix(matt), matrix_label(matrow), k(1){};

/**
 * @brief Construct a new Mein_KNN object
 *
 * @param matt matrix dataset
 * @param matrow dataset labels
 * @param deqn distance equation type
 */
template <typename MatrixType>
Mein_KNN<MatrixType>::Mein_KNN(MatrixType &matt, arma::Row<size_t> &matrow, DistanceEQN deqn) : matrix(matt), matrix_label(matrow), Deqn(deqn), k(1) {};

/**
 * @brief Construct a new Mein_KNN object
 *
* @param matt matrix dataset
* @param matrow dataset labels
* @param kn number of neigbours
* @param deqn distance equation type
*/
template <typename MatrixType>
Mein_KNN<MatrixType>::Mein_KNN(MatrixType &matt, arma::Row<size_t> &matrow, int kn, DistanceEQN deqn) : matrix(matt), matrix_label(matrow), k(kn), Deqn(deqn){};

/**
 * @brief classifies matrix dataset
 * 
 * @tparam MatrixType arma::mat/arma::sp_mat
 * @param predmat matrix to classify
 * @param k number of neighbours
 * @param deqn distance equation type
 * @return int
 */
template <typename MatrixType>
int Mein_KNN<MatrixType>::Classify(MatrixType &predmat, int k, DistanceEQN deqn)
{
    arma::Col<double> sumdistance;
    
    switch (deqn)
    {
    case DistanceEQN::EUCLIDEAN:
        sumdistance = Euclidean_distance(matrix, predmat);
        break;
    case DistanceEQN::COSINE:
        sumdistance = Cosine_distance(matrix, predmat);
        break;
    case DistanceEQN::MANHATTAN:
        sumdistance = Manhattan_distance(matrix, predmat);
        break;
    case DistanceEQN::COSINE_DISSIMILARITY:
        sumdistance = Manhattan_distance(matrix, predmat);
        break;
    
    default:
        sumdistance = Euclidean_distance(matrix, predmat);
        break;
    }

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
 * @tparam MatrixType arma::mat/arma::sp_mat
 * @param matt matrix of the dataset
 * @param matrow real labels
 * @return double : max is 1, mini is 0
 */
template <typename MatrixType>
double Mein_KNN<MatrixType>::Evaluate(MatrixType &matt, arma::Row<size_t> &matrow)
{
    arma::Row<size_t> res(matt.n_cols);
    for (arma::uword i = 0; i < matt.n_cols; i++)
    {
        MatrixType col = matt.col(i);
        res(i) = Classify(col,k,Deqn);
    }
    return ComputeAccuracy(res, matrow);
}

/**
 * @brief returns a more comprehensive report of the class evaluation
 * 
 * @tparam MatrixType arma::mat/arma::sp_mat
 * @param matt matrix of the dataset
 * @param matrow real labels
 */
template <typename MatrixType>
void Mein_KNN<MatrixType>::ClassReport(MatrixType &matt, arma::Row<size_t> &matrow)
{
    arma::Row<size_t> res(matt.n_cols);
    for (arma::uword i = 0; i < matt.n_cols; i++)
    {
        MatrixType col = matt.col(i);
        res(i) = Classify(col,k,Deqn);;
    }
    double result = ComputeAccuracy(res, matrow);
    std::cout << "[INFO] " << std::setw(4) << "Accurracy - " << result << std::endl;
    ClassificationReport(res, matrow);
}