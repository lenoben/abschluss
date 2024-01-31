#ifndef MODEL_FLOW_HPP
#define MODEL_FLOW_HPP

/// Define these to print extra informational output and warnings.
#define MLPACK_PRINT_INFO
#define MLPACK_PRINT_WARN

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <typeinfo>

#include <stdexcept>
#include <array>
#include <cstdlib>

#include "json.hpp"

using Json = nlohmann::json;
enum FileType
{
    TXTGZ,
    JSON,
    TXT
};

#endif