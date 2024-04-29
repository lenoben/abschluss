#ifndef MODEL_FLOW_MF_MEIN_NMC_HPP
#define MODEL_FLOW_MF_MEIN_NMC_HPP

#include "ModelBuild.hpp"

namespace mf
{
    double mein_nmc(
        EncoderType ET, scaler_methods SM = scaler_methods::NONE);

    void mein_nmc2(
        EncoderType ET, scaler_methods SM = scaler_methods::NONE);
};

#endif