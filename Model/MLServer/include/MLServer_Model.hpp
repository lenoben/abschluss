#ifndef MLSERVER_MODEL_HPP
#define MLSERVER_MODEL_HPP

#include "MLServer.hpp"

#define MLPACK_ENABLE_ANN_SERIALIZATION                              // Enable loading and saving of models
#include <mlpack/methods/ann/ffn.hpp>                                //mlpack::FFN
#include <mlpack/methods/ann/init_rules/he_init.hpp>                 //mlpack::HeInitialization
#include <mlpack/methods/ann/loss_functions/mean_squared_error.hpp>  //mlpack::MeanSquaredError
#include <mlpack/methods/ann/loss_functions/cross_entropy_error.hpp> //mlpack::mlpack::CrossEntropyError --* from local mlpack::BCELoss
#include <mlpack/core/data/load.hpp>                                 //mlpack::data::Load
#include <mlpack/core/data/string_encoding.hpp>
#include <mlpack/base.hpp> //in include, sus for MLPACK_STRING_VIEW, thats just std::string_view

#include <mlpack/methods/random_forest/random_forest.hpp>             //mlpack::RandomForest<>
#include <mlpack/methods/logistic_regression/logistic_regression.hpp> //mlpack::LogisticRegression<>
#include <mlpack/methods/linear_regression/linear_regression.hpp>     //mlpack::LinearRegression

#include <mlpack/core/data/scaler_methods/standard_scaler.hpp>
#include <mlpack/core/data/scaler_methods/min_max_scaler.hpp>
#include <mlpack/core/data/scaler_methods/max_abs_scaler.hpp>
#include <mlpack/core/data/scaler_methods/mean_normalization.hpp>

#include <mlpack/core/data/tokenizers/char_extract.hpp>
#include <mlpack/core/data/tokenizers/split_by_any_of.hpp>
#include <mlpack/core/data/string_encoding_policies/bag_of_words_encoding_policy.hpp>
#include <mlpack/core/data/string_encoding_policies/tf_idf_encoding_policy.hpp>

#include <armadillo>

using DictionaryType = mlpack::data::StringEncodingDictionary<MLPACK_STRING_VIEW>;

enum MLSERVER_MODEL
{
    FFN_MEAN_HE,
    LOG_REG,
    RANDOM_FOREST
};

std::string mlserverModelToString(MLSERVER_MODEL);

enum scaler_methods
{
    STANDARD_SCALAR,
    MINMAX_SCALAR,
    MAX_ABS_SCALAR,
    MEAN_NORM,
    NONE
};

enum TheTokenType
{
    SPLITBYCHAR,
    CHAREXTRACT
};

enum EncoderType
{
    BOW,
    TFID
};

void to_lower_str(std::string &cleaned);

/**
 * @brief converts string vectors to lower case vectors of strings
 *
 * @param string_vector
 */
void to_lower_vec(std::vector<std::string> &string_vector);

std::string cleanString(std::string dirty);

void cleanStringFile(std::vector<std::string> &vector_of_string);

void removeStop(std::vector<std::string> &vector_of_string);

void cleanTextForPrediction(std::string &text,
                            DictionaryType const &dictionary,
                            mlpack::data::SplitByAnyOf const &tokenizer);

void convertVectorStringToMatrix(std::vector<std::string> vector_of_strings, 
                                arma::mat &matrix, EncoderType ET, TheTokenType TTT, 
                                mlpack::data::TfIdfEncodingPolicy::TfTypes MDTT = mlpack::data::TfIdfEncodingPolicy::TfTypes::TERM_FREQUENCY, 
                                bool boolean = false);

void scalerTransform(scaler_methods SM, arma::mat &matrix);

void _convertToRow(const arma::mat &matrix, arma::Row<size_t> &matrixRow, double threshold = 0.5);

mlpack::FFN<mlpack::CrossEntropyError, mlpack::HeInitialization> getFFN_CH(
    std::string modelpath = "FFN_TFID_STANDARD_SCALAR_nn_regressor.bin",
    std::string modelname = "NNRegressor");

mlpack::FFN<mlpack::MeanSquaredError, mlpack::HeInitialization> &getFFN_MH(
    std::string modelpath = "FFN_BOW_MINMAX_SCALAR_nn_regressor.bin",
    std::string modelname = "NNRegressor");

mlpack::RandomForest<> &getRF(
    std::string modelpath = "RandomForest_TFID_MINMAX_SCALAR_model.bin",
    std::string modelname = "RandomForest");

#endif
