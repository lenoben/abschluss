#include "MF_LogisticRegression.hpp"

namespace mf
{
    double logRegressionSetup(EncoderType ET, scaler_methods SM, double bound, bool intercept, double penalty)
    {
        arma::Row<size_t> trainLabel, testLabel, pred;
        arma::mat trainMat, testMat, prob;
        std::tie(trainMat, testMat, trainLabel, testLabel) = getMatrixDataset(ET);

        // pick scalar method
        pickScalarMethod(SM, trainMat, testMat);

        trainMat.brief_print("Train Matrix 🧩");
        std::cout << "Train Matrix n_rows - " << trainMat.n_rows << std::endl;
        std::cout << "Train Matrix n_cols - " << trainMat.n_cols << std::endl;

        mlpack::LogisticRegression<> model(trainMat.n_rows, penalty);
        model.Train(trainMat, trainLabel);

        std::string modelname = "LogisticRegression_" + encoderTypeToString(ET) + "_" + std::to_string(bound) + "_" + scalerMethodToString(SM);
        mlpack::data::Save(modelname + "_model.bin", "LogisticRegression", model);
        model.Classify(testMat, pred, bound);
        model.Classify(testMat, prob);

        pred.brief_print("pred");
        prob.brief_print("pred prob");
        std::cout << "pred ncols - " << pred.n_cols << std::endl;
        std::cout << "pred nrows - " << pred.n_rows << std::endl;

        // evaluate
        double result = ComputeAccuracy(pred, testLabel);
        std::cout << "[INFO] " << std::setw(4) << "Accurracy - " << result << std::endl;
        ClassificationReport(pred, testLabel);

        mlpack::data::Save(modelname + "_pred.csv", pred);
        mlpack::data::Save(modelname + "_pred_prob.csv", prob);
        return result;
    }
}
