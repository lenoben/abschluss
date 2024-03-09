#ifndef MODEL_BUILD_HPP
#define MODEL_BUILD_HPP

/// Define these to print extra informational output and warnings.
#define MLPACK_PRINT_INFO
#define MLPACK_PRINT_WARN
#define MLPACK_ENABLE_ANN_SERIALIZATION // to save models

#include "ModelFlow.hpp"
#include "Preprocessing.hpp"
#include "StringManipulation.hpp"

std::tuple<std::vector<std::string>, std::vector<int>> getVectorDataset();

std::tuple<std::vector<std::string>, std::vector<int>> getVectorDatasetFromFile(std::string filename);

#endif