#include "ModelFlow.hpp"

std::string encoderTypeToString(EncoderType type)
{
    switch (type)
    {
    case BOW:
        return "BOW";
    case TFID:
        return "TFID";
    default:
        return "UNKNOWN";
    }
}

std::string tokenTypeToString(TheTokenType type)
{
    switch (type)
    {
    case SPLITBYCHAR:
        return "SPLITBYCHAR";
    case CHAREXTRACT:
        return "CHAREXTRACT";
    default:
        return "UNKNOWN";
    }
}

std::string scalerMethodToString(scaler_methods method)
{
    switch (method)
    {
    case STANDARD_SCALAR:
        return "STANDARD_SCALAR";
    case MINMAX_SCALAR:
        return "MINMAX_SCALAR";
    case MAX_ABS_SCALAR:
        return "MAX_ABS_SCALAR";
    case MEAN_NORM:
        return "MEAN_NORM";
    case NONE:
        return "NONE";
    default:
        return "UNKNOWN";
    }
}