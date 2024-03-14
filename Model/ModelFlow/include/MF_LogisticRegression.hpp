#ifndef MODEL_FLOW_MF_LOGISTIC_REGRESSION_HPP
#define MODEL_FLOW_MF_LOGISTIC_REGRESSION_HPP

#include "ModelBuild.hpp"

// LOGISTIC REGRESSION
#include <mlpack/methods/logistic_regression/logistic_regression.hpp>

namespace mf
{
    double logRegressionSetup(EncoderType ET, scaler_methods SM = scaler_methods::NONE, double bound = 0.5, bool intercept = true, double penalty = 0.0);
};

#endif
