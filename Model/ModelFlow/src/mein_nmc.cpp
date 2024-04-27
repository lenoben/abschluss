#include "mein_nmc.hpp"

// Explicit template instantiation for arma::mat and arma::sp_mat
template class Mein_NMC<arma::mat>;
template class Mein_NMC<arma::sp_mat>;

/**
 * @brief Construct a new Mein_NMC object
 *
 */
template <typename MatrixType>
Mein_NMC<MatrixType>::Mein_NMC(){};

/**
 * @brief Fits the dataset and its labels in a pair
 * 
 * @tparam MatrixType arma::mat/arma::sp_mat
 * @param matx matrix of the dataset
 * @param rowy labels
 */
template <typename MatrixType>
void Mein_NMC<MatrixType>::Fit(MatrixType &matx, arma::Row<size_t> &rowy)
{
    // rowy has 2, unique-labels 2 ncols 1 rows ..ex
    arma::Row<size_t> unique_labels = arma::unique(rowy);
    arma::uword distinct = unique_labels.n_elem;

    std::vector<MatrixType> map_matrix(distinct);

    for (arma::uword j = 0; j < matx.n_cols; j++)
    {
        for (arma::uword k = 0; k < distinct; k++)
        {
            if (unique_labels(k) == rowy(j))
            {
                // find indices where rowy matches
                arma::uvec indices = arma::find(rowy == unique_labels(k));

                // extract columns based on indices
                map_matrix[k] = matx.cols(indices);
                break;
            }
        }
    }

    // calculating the class means

    std::vector<std::pair<int, MatrixType>> vect_pair_matT;
    for (arma::uword i = 0; i < distinct; i++)
    {
        // class index
        MatrixType hold(map_matrix[i].n_rows, 1);
        for (arma::uword j = 0; j < map_matrix[i].n_cols; j++)
        {
            // total number of data in class
            for (arma::uword k = 0; k < map_matrix[i].n_rows; k++)
            {
                hold(k, 0) += map_matrix[i](k, j);
            }
        }
        hold /= map_matrix[i].n_cols;
        vect_pair_matT.push_back(
            std::make_pair(
                unique_labels(i),
                hold));
    }

    vect_pair_mat = vect_pair_matT;
};

/**
 * @brief Fits the dataset and its labels in a pair
 * 
 * @tparam MatrixType arma::mat/arma::sp_mat
 * @param matx matrix of the dataset
 * @param rowy labels
 */
template <typename MatrixType>
void Mein_NMC<MatrixType>::RFit(MatrixType &matx, arma::Row<size_t> &rowy)
{
    arma::Row<size_t> unique_labels = arma::unique(rowy);
    arma::uword distinct = unique_labels.n_elem;

    vect_pair_mat.resize(distinct);

    for (arma::uword k = 0; k < distinct; k++) {
        arma::uvec indices = arma::find(rowy == unique_labels(k));
        MatrixType class_data = matx.cols(indices);
        MatrixType mean = arma::mean(class_data, 1);
        vect_pair_mat[k] = { static_cast<int>(unique_labels(k)), mean };
    }
};

/**
 * @brief predicts or classify the class from the dataset. initially made of just 1 set of dataset
 * 
 * @tparam MatrixType arma::mat/arma::sp_mat
 * @param matx matrix to predict
 * @return int : class from the label
 */
template <typename MatrixType>
int Mein_NMC<MatrixType>::Predict(MatrixType &matx)
{
    std::vector<std::pair<double, int>> dist_label;
    double powered, sumSquared = 0.0;

    for (size_t i = 0; i < vect_pair_mat.size(); i++)
    {
        // class distinct type
        for (size_t j = 0; j < vect_pair_mat[i].second.n_rows; j++)
        {
            // rows uncertain, cols always 1
            powered = std::pow(matx(j, 0) - vect_pair_mat[i].second(j, 0), 2);
            sumSquared += powered;
        }
        dist_label.push_back({std::sqrt(sumSquared), vect_pair_mat[i].first});
        sumSquared = 0.0;
    }

    std::sort(
        dist_label.begin(), dist_label.end(), [](const std::pair<double, int> &a, const std::pair<double, int> &b)
        { return a.first < b.first; });

    return dist_label[0].second;
};

/**
 * @brief predicts or classify the class from the dataset. initially made of just 1 set of dataset
 * 
 * @tparam MatrixType arma::mat/arma::sp_mat
 * @param matx matrix to predict
 * @return int : class from the label
 */
template <typename MatrixType>
int Mein_NMC<MatrixType>::RPredict(MatrixType &matx)
{
    double min_distance = std::numeric_limits<double>::max();
        int predicted_class = -1;

        for (const auto& class_mean : vect_pair_mat) {
            double distance = arma::norm(class_mean.second - matx, 2);
            
            if (distance < min_distance) {
                min_distance = distance;
                predicted_class = class_mean.first;
            }
        }

        return predicted_class;
};

/**
 * @brief Computes the accuracy of the class
 * 
 * @tparam MatrixType arma::mat/arma::sp_mat
 * @param matx matrix of the dataset
 * @param rowy real labels
 * @return double : max is 1, mini is 0
 */
template <typename MatrixType>
double Mein_NMC<MatrixType>::Evaluate(MatrixType &matx, arma::Row<size_t> &rowy)
{
    arma::Row<size_t> res(matx.n_cols);
    for (arma::uword i = 0; i < matx.n_cols; i++)
    {
        MatrixType col = matx.col(i);
        res(i) = Predict(col);
    }
    return ComputeAccuracy(res, rowy);
};

/**
 * @brief returns a more comprehensive report of the class evaluation
 * 
 * @tparam MatrixType arma::mat/arma::sp_mat
 * @param matx matrix of the dataset
 * @param rowy real labels
 */
template <typename MatrixType>
void Mein_NMC<MatrixType>::ClassReport(MatrixType &matx, arma::Row<size_t> &rowy)
{
    arma::Row<size_t> res(matx.n_cols);
    for (arma::uword i = 0; i < matx.n_cols; i++)
    {
        MatrixType col = matx.col(i);
        res(i) = Predict(col);
    }
    double result = ComputeAccuracy(res, rowy);
    std::cout << "[INFO] " << std::setw(4) << "Accurracy - " << result << std::endl;
    ClassificationReport(res, rowy);
};

/**
 * @brief returns a more comprehensive report of the class evaluation
 * 
 * @tparam MatrixType arma::mat/arma::sp_mat
 * @param matx matrix of the dataset
 * @param rowy real labels
 */
template <typename MatrixType>
void Mein_NMC<MatrixType>::RClassReport(MatrixType &matx, arma::Row<size_t> &rowy)
{
    arma::Row<size_t> res(matx.n_cols);
    for (arma::uword i = 0; i < matx.n_cols; i++)
    {
        MatrixType col = matx.col(i);
        res(i) = RPredict(col);
    }
    double result = ComputeAccuracy(res, rowy);
    std::cout << "[INFO] " << std::setw(4) << "Accurracy - " << result << std::endl;
    ClassificationReport(res, rowy);
};