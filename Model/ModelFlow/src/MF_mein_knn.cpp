#include "MF_mein_knn.hpp"
#include "mein_knn.hpp"

namespace mf
{
    double mein_knn(
        EncoderType ET, scaler_methods SM)
    {
        arma::Row<size_t> trainLabel, testLabel;
        arma::mat mtrainMat, mtestMat;
        std::tie(mtrainMat, mtestMat, trainLabel, testLabel) = getMatrixDataset(ET);

        
        // pick scalar method
        pickScalarMethod(SM, mtrainMat, mtestMat);
        
        //convert to sp_mat
        arma::sp_mat trainMat(mtrainMat), testMat(mtestMat);

        Mein_KNN<arma::sp_mat> knn(trainMat, trainLabel, DistanceEQN::MANHATTAN);
        std::cout << "KNN. " << encoderTypeToString(ET) << " " << scalerMethodToString(SM) << std::endl;
        knn.ClassReport(testMat, testLabel);
        return knn.Evaluate(testMat, testLabel);
    }

    void mein_knn2(
        EncoderType ET, scaler_methods SM)
    {
        arma::Row<size_t> trainLabel, testLabel;
        arma::mat mtrainMat, mtestMat;
        std::tie(mtrainMat, mtestMat, trainLabel, testLabel) = getMatrixDataset(ET);

        
        // pick scalar method
        pickScalarMethod(SM, mtrainMat, mtestMat);
        
        //convert to sp_mat
        arma::sp_mat trainMat(mtrainMat), testMat(mtestMat);

        Mein_KNN<arma::sp_mat> knn(trainMat, trainLabel, DistanceEQN::MANHATTAN);
        std::cout << "KNN. " << encoderTypeToString(ET) << " " << scalerMethodToString(SM) << std::endl;
        knn.RClassReport(testMat, testLabel);
    }
};