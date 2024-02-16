
#ifndef MODEL_FLOW_HPP
#define MODEL_FLOW_HPP

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

#include <tuple>

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <typeinfo>

#include <stdexcept>
#include <array>
#include <cstdlib>

#include <zlib.h>

#include "json.hpp"

using Json = nlohmann::json;
enum FileType
{
    TXTGZ,
    JSON,
    TXT
};

enum EncoderType
{
    BOW,
    TFID
};

std::string encoderTypeToString(EncoderType type);

enum TheTokenType
{
    SPLITBYCHAR,
    CHAREXTRACT
};

std::string tokenTypeToString(TheTokenType type);

enum scaler_methods
{
    STANDARD_SCALAR,
    MINMAX_SCALAR,
    MAX_ABS_SCALAR,
    MEAN_NORM,
    NONE
};

std::string scalerMethodToString(scaler_methods method);
#endif