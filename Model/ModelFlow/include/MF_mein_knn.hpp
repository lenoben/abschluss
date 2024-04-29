#ifndef MODEL_FLOW_MF_MEIN_KNN_HPP
#define MODEL_FLOW_MF_MEIN_KNN_HPP

#include "ModelBuild.hpp"

namespace mf
{
    double mein_knn(
        EncoderType ET, scaler_methods SM = scaler_methods::NONE);

    void mein_knn2(
        EncoderType ET, scaler_methods SM = scaler_methods::NONE);
};

#endif