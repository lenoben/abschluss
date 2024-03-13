#include "MF_RandomForest.hpp"

namespace mf
{
    double randomForestSetup(EncoderType ET, scaler_methods SM, int numClasses, int numTrees)
    {
        arma::Row<size_t> trainLabel, testLabel, pred;
        arma::mat trainMat, testMat, prob;
        std::tie(trainMat, testMat, trainLabel, testLabel) = getMatrixDataset(ET);

        trainMat.brief_print("Train Matrix 🧩");
        trainLabel.brief_print("Test Label 🧩");

        pickScalarMethod(SM, trainMat, testMat);

        // model
        if (numTrees == 0)
            numTrees = trainMat.n_rows;
        mlpack::RandomForest<> mrf(trainMat, trainLabel, numClasses, numTrees);
        std::string modelname = "RandomForest_" + encoderTypeToString(ET) + "_" + scalerMethodToString(SM) + "_" + std::to_string((int)trainMat.n_rows);
        mlpack::data::Save(modelname + "_model.bin", "RandomForest", mrf);

        mrf.Classify(testMat, pred, prob);
        pred.brief_print("Prediction Label");
        prob.brief_print("Probabilities Matrix");
        mlpack::data::Save(modelname + "_pred.csv", pred);
        mlpack::data::Save(modelname + "_pred_prob.csv", prob);

        // evaluate
        double result = ComputeAccuracy(pred, testLabel);
        std::cout << "[INFO] " << std::setw(4) << "Accurracy - " << result << std::endl;
        ClassificationReport(pred, testLabel);

        return result;
    }
};
