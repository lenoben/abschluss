#include "MF_mein_nmc.hpp"
#include "mein_nmc.hpp"

namespace mf
{
    double mein_nmc(
        EncoderType ET, scaler_methods SM)
    {
        arma::Row<size_t> trainLabel, testLabel, pred;
        arma::mat mtrainMat, mtestMat;
        std::tie(mtrainMat, mtestMat, trainLabel, testLabel) = getMatrixDataset(ET);

        
        // pick scalar method
        pickScalarMethod(SM, mtrainMat, mtestMat);
        
        //convert to sp_mat
        arma::sp_mat trainMat(mtrainMat), testMat(mtestMat);

        Mein_NMC<arma::sp_mat> nmc;
        nmc.Fit(trainMat, trainLabel);
        std::cout << "NMC. " << encoderTypeToString(ET) << " " << scalerMethodToString(SM) << std::endl;
        nmc.ClassReport(testMat, testLabel);
        return nmc.Evaluate(testMat, testLabel);
    }

    void mein_nmc2(
        EncoderType ET, scaler_methods SM)
    {
        arma::Row<size_t> trainLabel, testLabel, pred;
        arma::mat mtrainMat, mtestMat;
        std::tie(mtrainMat, mtestMat, trainLabel, testLabel) = getMatrixDataset(ET);

        
        // pick scalar method
        pickScalarMethod(SM, mtrainMat, mtestMat);
        
        //convert to sp_mat
        arma::sp_mat trainMat(mtrainMat), testMat(mtestMat);

        Mein_NMC<arma::sp_mat> nmc;
        nmc.RFit(trainMat, trainLabel);
        std::cout << "NMC. " << encoderTypeToString(ET) << " " << scalerMethodToString(SM) << std::endl;
        nmc.RClassReport(testMat, testLabel);
    }
};