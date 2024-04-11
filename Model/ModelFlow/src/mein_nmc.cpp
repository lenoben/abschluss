#include "mein_nmc.hpp"

/**
 * @brief Construct a new Mein_NMC object
 *
 */
Mein_NMC::Mein_NMC(){};

/**
 * @brief Fits the dataset and its labels in a pair
 *
 * @param matx matrix of the dataset
 * @param rowy labels
 */
void Mein_NMC::Fit(arma::mat &matx, arma::Row<size_t> &rowy)
{
    // rowy has 2, unique-labels 2 ncols 1 rows ..ex
    arma::Row<size_t> unique_labels = arma::unique(rowy);
    arma::uword distinct = unique_labels.n_elem;

    std::vector<arma::mat> map_matrix(distinct);

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

    std::vector<std::pair<int, arma::mat>> vect_pair_matT;
    for (arma::uword i = 0; i < distinct; i++)
    {
        // class index
        arma::mat hold(map_matrix[i].n_rows, 1);
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
 * @brief predicts or classify the class from the dataset. initially made of just 1 set of dataset
 *
 * @param matx matrix to predict
 * @return int : class from the label
 */
int Mein_NMC::Predict(arma::mat &matx)
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
 * @brief Computes the accuracy of the class
 *
 * @param matx matrix of the dataset
 * @param rowy real labels
 * @return double : max is 1, mini is 0
 */
double Mein_NMC::Evaluate(arma::mat &matx, arma::Row<size_t> &rowy)
{
    arma::Row<size_t> res(matx.n_cols);
    for (arma::uword i = 0; i < matx.n_cols; i++)
    {
        arma::mat col = matx.col(i);
        res(i) = Predict(col);
    }
    return ComputeAccuracy(res, rowy);
};

/**
 * @brief returns a more comprehensive report of the class evaluation
 *
 * @param matx matrix of the dataset
 * @param rowy real labels
 */
void Mein_NMC::ClassReport(arma::mat &matx, arma::Row<size_t> &rowy)
{
    arma::Row<size_t> res(matx.n_cols);
    for (arma::uword i = 0; i < matx.n_cols; i++)
    {
        arma::mat col = matx.col(i);
        res(i) = Predict(col);
    }
    ClassificationReport(res, rowy);
};