#include "MF_Fnn.hpp"

arma::Row<size_t> getLabels(const arma::mat &yPreds)
{
    arma::Row<size_t> yLabels(yPreds.n_cols);
    for (arma::uword i = 0; i < yPreds.n_cols; ++i)
    {
        yLabels(i) = yPreds.col(i).index_max();
    }
    return yLabels;
}

arma::Row<size_t> _convertToRow(const arma::mat &matrix, double threshold)
{
    arma::Row<size_t> result(matrix.n_cols);

    for (size_t i = 0; i < matrix.n_cols; ++i)
    {
        result(i) = (matrix(0, i) >= threshold) ? 1 : 0;
    }

    return result;
}

namespace mf
{
    /*
    Models Examples
        ---------------
        Layers: Input layer (29 neurons) -> Fully connected layer (64 neurons) -> ReLU activation -> Fully connected layer (32 neurons) -> ReLU activation -> Output layer (1 neuron)
        Activation Functions: ReLU for hidden layers, sigmoid for the output layer
        Loss Function: Binary cross-entropy, mlpack::BCELoss
        Initialization Rule: Random initialization
        ---------------
        Layers: Input layer (29 neurons) -> Fully connected layer (128 neurons) -> ReLU activation -> Dropout (with dropout rate 0.5) -> Fully connected layer (64 neurons) -> ReLU activation -> Dropout (with dropout rate 0.5) -> Fully connected layer (32 neurons) -> ReLU activation -> Dropout (with dropout rate 0.5) -> Output layer (1 neuron)
        Activation Functions: ReLU for hidden layers, sigmoid for the output layer
        Loss Function: Binary cross-entropy
        Initialization Rule: He initialization
        ---------------
        Layers: Input layer (29 neurons) -> Fully connected layer (64 neurons) -> Leaky ReLU activation -> Batch normalization -> Fully connected layer (32 neurons) -> Leaky ReLU activation -> Batch normalization -> Output layer (1 neuron)
        Activation Functions: Leaky ReLU for hidden layers, sigmoid for the output layer
        Loss Function: Hinge loss
        Initialization Rule: Xavier initialization
        ---------------
    */

    mlpack::FFN<mlpack::CrossEntropyError, mlpack::RandomInitialization> &binary_random(int numberOfCols)
    {
        mlpack::FFN<mlpack::CrossEntropyError, mlpack::RandomInitialization> *model = new mlpack::FFN<mlpack::CrossEntropyError, mlpack::RandomInitialization>();
        model->Add<mlpack::Linear>(numberOfCols);
        model->Add<mlpack::ReLU>();
        model->Add<mlpack::Linear>(64);
        model->Add<mlpack::ReLU>();
        model->Add<mlpack::Linear>(32);
        model->Add<mlpack::ReLU>();
        model->Add<mlpack::Linear>(1);
        model->Add<mlpack::Sigmoid>();

        return *model;
    }

    mlpack::FFN<mlpack::CrossEntropyError, mlpack::HeInitialization> &binary_he(int numberofrows)
    {
        mlpack::FFN<mlpack::CrossEntropyError, mlpack::HeInitialization> *model = new mlpack::FFN<mlpack::CrossEntropyError, mlpack::HeInitialization>();
        model->Add<mlpack::Linear>(numberofrows);
        model->Add<mlpack::Dropout>(0.5);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Linear>(32);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Linear>(64);
        model->Add<mlpack::Dropout>(0.5);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Linear>(128);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::LogSoftMax>();
        model->Add<mlpack::Linear>(64);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Dropout>(0.5);
        model->Add<mlpack::Linear>(32);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Linear>(1);
        model->Add<mlpack::Sigmoid>();

        return *model;
    }

    mlpack::FFN<mlpack::MeanSquaredError, mlpack::HeInitialization> &mean_he(int noOfrows)
    {
        mlpack::FFN<mlpack::MeanSquaredError, mlpack::HeInitialization> *model = new mlpack::FFN<mlpack::MeanSquaredError, mlpack::HeInitialization>();
        model->Add<mlpack::Linear>(noOfrows);
        model->Add<mlpack::Dropout>(0.5);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Linear>(32);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Linear>(64);
        model->Add<mlpack::Dropout>(0.5);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Linear>(128);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Linear>(64);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Dropout>(0.5);
        model->Add<mlpack::Linear>(32);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Linear>(1);
        model->Add<mlpack::Sigmoid>();

        return *model;
    }

    // theory practice tester func
    mlpack::FFN<mlpack::NegativeLogLikelihood, mlpack::HeInitialization> &neg_he(int noOfrows)
    {
        mlpack::FFN<mlpack::NegativeLogLikelihood, mlpack::HeInitialization> *model = new mlpack::FFN<mlpack::NegativeLogLikelihood, mlpack::HeInitialization>();
        model->Add<mlpack::Linear>(noOfrows);
        model->Add<mlpack::Dropout>(0.5);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Linear>(32);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Linear>(64);
        model->Add<mlpack::Dropout>(0.5);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Linear>(128);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::LogSoftMax>();
        model->Add<mlpack::Linear>(64);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Dropout>(0.5);
        model->Add<mlpack::Linear>(32);
        model->Add<mlpack::LeakyReLU>();
        model->Add<mlpack::Linear>(1);
        model->Add<mlpack::Sigmoid>();

        return *model;
    }

    void fnnSetup(EncoderType ET, scaler_methods SM, int opt)
    {
        arma::Row<size_t> trainLabel, testLabel;
        arma::mat trainMat, testMat, pred, FNN_trainLabel, FNN_testLabel;
        std::tie(trainMat, testMat, trainLabel, testLabel) = getMatrixDataset(ET);

        FNN_trainLabel = arma::conv_to<arma::mat>::from(trainLabel);
        FNN_testLabel = arma::conv_to<arma::mat>::from(testLabel);

        // pick scalar method
        pickScalarMethod(SM, trainMat, testMat);

        trainMat.brief_print("Train Matrix 🧩");
        std::cout << "Train Matrix n_rows - " << trainMat.n_rows << std::endl;
        std::cout << "Train Matrix n_cols - " << trainMat.n_cols << std::endl;
        FNN_trainLabel.brief_print("Train Label Matrix 🧩");
        std::cout << "Train Label Matrix n_rows - " << FNN_trainLabel.n_rows << std::endl;
        std::cout << "Train Label Matrix n_cols - " << FNN_trainLabel.n_cols << std::endl;

        /*
            ****
                Model training parameters
            ****
        */

        // Number of epochs for training. Increase number of epochs for better results.
        const int EPOCHS = 32;

        //! - STEP_SIZE: Step size of the optimizer. learning rate also
        constexpr double STEP_SIZE = 0.001; // 2e-5; // 0.000001; // 5e-2;

        //! - BATCH_SIZE: Number of data points in each iteration of SGD.
        constexpr int BATCH_SIZE = 16; // 32
        
        //! - STOP_TOLERANCE: Stop tolerance;
        // A very small number implies that we do all iterations.
        constexpr double STOP_TOLERANCE = 1e-8;

        mlpack::FFN<mlpack::MeanSquaredError, mlpack::HeInitialization> &model = mean_he((int)trainMat.n_rows);

        /*
            callbacks - https://www.ensmallen.org/docs.html#callback-documentation
            GradClipByNorm(0.3)
            ens::PrintLoss()
            ens::EarlyStopAtMinLoss()
            GradClipByValue(0, 1.3)
            ProgressBar()
            Report()
            StoreBestCoordinates<ModelMatType>()
        */

        ens::Adam optimizerAdam;
        ens::AdaDelta optimizerAda;
        ens::StandardSGD optimizerSGD;
        ens::Nadam optimizerNA;
        ens::RMSProp optimizerRM;

        switch (opt)
        {
        case 1:
            optimizerAdam = ens::Adam(
                STEP_SIZE,                // Step size of the optimizer.
                BATCH_SIZE,               // Batch size. Number of data points that are used in each iteration.
                0.9,                      // Exponential decay rate for the first moment estimates.
                0.999,                    // Exponential decay rate for the weighted infinity norm estimates.
                1e-8,                     // Value used to initialise the mean squared gradient parameter.
                trainMat.n_cols * EPOCHS, // Max number of iterations.
                STOP_TOLERANCE,           // Tolerance.
                true);
            model.Train(trainMat, FNN_trainLabel, optimizerAdam, ens::PrintLoss(), ens::ProgressBar(40), ens::EarlyStopAtMinLoss(20));
            break;
        case 2:
            optimizerRM = ens::RMSProp(0.01, 32, 0.88, 1e-8, trainMat.n_cols * EPOCHS, -1);
            break;
        case 3:
            optimizerSGD = ens::StandardSGD(
                STEP_SIZE,                // Step size of the optimizer.
                BATCH_SIZE,               // Batch size. Number of data points that are used in each iteration.
                trainMat.n_cols * EPOCHS, // Max number of iterations.
                STOP_TOLERANCE,           // Tolerance.
                false                     // shuffle, if not visits linearly
            );
            model.Train(trainMat, FNN_trainLabel, optimizerSGD, ens::PrintLoss(), ens::ProgressBar(40), ens::EarlyStopAtMinLoss(20));
            break;
        case 4:
            optimizerNA = ens::Nadam(
                STEP_SIZE,                // Step size of the optimizer.
                BATCH_SIZE,               // Batch size. Number of data points that are used in each iteration.
                0.9,                      // Exponential decay rate for the first moment estimates.
                0.999,                    // Exponential decay rate for the weighted infinity norm estimates.
                1e-8,                     // Value used to initialise the mean squared gradient parameter.
                trainMat.n_cols * EPOCHS, // Max number of iterations.
                STOP_TOLERANCE,           // Tolerance.
                false                     // shuffle
            );
            model.Train(trainMat, FNN_trainLabel, optimizerNA, ens::PrintLoss(), ens::ProgressBar(40), ens::EarlyStopAtMinLoss(20));
            break;
        default:
            std::cout << "Default optimizer: " << std::endl;
            model.Train(trainMat, FNN_trainLabel, ens::PrintLoss(), ens::ProgressBar(40));
            break;
        }

        model.Predict(testMat, pred);
        // File for saving the model.
        std::string modelname = "FFN_" + encoderTypeToString(ET) + "_" + scalerMethodToString(SM) + "_" + std::to_string(opt);

        mlpack::data::Save(modelname + "_nn_regressor.bin", "NNRegressor", model);

        delete &model;
        mlpack::data::Save(modelname + "_pred.csv", pred);
        mlpack::data::Save(modelname + "_test.csv", FNN_testLabel);

        double decisonboundary = 0.5;

        arma::Row<size_t> predl = _convertToRow(pred, decisonboundary);
        arma::mat thre = arma::zeros<arma::mat>(pred.n_rows, pred.n_cols);

        for (arma::uword i = 0; i < pred.n_elem; ++i){
            if (pred(i) >= decisonboundary){
                thre(i) = 1.0;
            }
            else {
                thre(i) = 0.0;
            }
        }
        pred = thre;

        pred.brief_print("FNN PREDs");
        FNN_testLabel.brief_print("FFN TEST LABEL");
        std::cout << "pred ncols - " << pred.n_cols << std::endl;
        std::cout << "pred nrows - " << pred.n_rows << std::endl;
        std::cout << "fnn testlabel ncols - " << FNN_testLabel.n_cols << std::endl;
        std::cout << "fnn testlabel nrows - " << FNN_testLabel.n_rows << std::endl;

        // Calculate MSE loss on predictions.
        double validMSE = mlpack::SquaredEuclideanDistance::Evaluate(pred, FNN_testLabel) / (FNN_testLabel.n_elem);

        std::cout << "Mean Squared Error on Prediction data points: " << validMSE << std::endl;

        double result = ComputeAccuracy(predl, testLabel);
        std::cout << "[INFO] " << std::setw(4) << "Accurracy - " << result << std::endl;
        ClassificationReport(predl, testLabel);
    }
}
