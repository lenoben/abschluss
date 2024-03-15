#ifndef MODEL_FLOW_MF_LINEAR_REGRESSION_HPP
#define MODEL_FLOW_MF_LINEAR_REGRESSION_HPP

#include "ModelBuild.hpp"

// LINEAR REGRESSION
#include <mlpack/methods/linear_regression/linear_regression.hpp>

namespace mf
{
    double linearRegressionSetup(EncoderType ET, scaler_methods SM = scaler_methods::NONE, bool intercept = true);
};

#endif
