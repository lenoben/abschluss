/**
 * @file main.cpp
 * @author John Obi (johnobi2003@gmail.com)
 * @brief The main entry for the executable
 * @version 0.1.0
 * @date 2024-01-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Preprocessing.hpp"
#include "ModelBuild.hpp"
#include "MF_RandomForest.hpp"
#include "MF_Fnn.hpp"
#include "MF_LogisticRegression.hpp"
#include "MF_mein_nmc.hpp"
#include "MF_mein_knn.hpp"

std::vector<std::string> mod(std::vector<std::string> notmod)
{
    std::vector<std::string> willgo;
    for (auto item : notmod)
    {
        willgo.push_back("../data/raw/" + item);
    }
    return willgo;
}

// vectorize the string from .txt.gz to arma::mat
void Vmain(bool fromStart = false);

int main()
{
    // std::cout << "🧩" << std::endl;
    Vmain(true);
    // Vmain();

    // // // ? could use a nested for loop, looping through a container/vector of values to be inserted into the model parameter

    std::cout << "[[[[[[[[[[[------------FFN-----------]]]]]]]]]]]]]]]" << std::endl;
    mf::fnnSetup(EncoderType::TFID, scaler_methods::MINMAX_SCALAR, 1);
    mf::fnnSetup(EncoderType::TFID, scaler_methods::STANDARD_SCALAR, 1);
    mf::fnnSetup(EncoderType::BOW, scaler_methods::MINMAX_SCALAR, 1);
    mf::fnnSetup(EncoderType::BOW, scaler_methods::STANDARD_SCALAR, 1);

    // std::cout << "[[[[[[[[[[[------------RF-----------]]]]]]]]]]]]]]]" << std::endl;
    // mf::randomForestSetup(EncoderType::TFID, scaler_methods::MINMAX_SCALAR, 2);
    // mf::randomForestSetup(EncoderType::BOW, scaler_methods::MINMAX_SCALAR, 2);
    // mf::randomForestSetup(EncoderType::BOW, scaler_methods::STANDARD_SCALAR, 2);
    // mf::randomForestSetup(EncoderType::TFID, scaler_methods::STANDARD_SCALAR, 2);

    std::cout << "[[[[[[[[[[[------------LOGR-----------]]]]]]]]]]]]]]]" << std::endl;
    double boundDecision = 0.5;
    double penalty = 0.5;
    bool intercept = true;
    mf::logRegressionSetup(EncoderType::TFID, scaler_methods::STANDARD_SCALAR, boundDecision, intercept, penalty);
    mf::logRegressionSetup(EncoderType::TFID, scaler_methods::MINMAX_SCALAR, boundDecision, intercept, penalty);
    intercept = false;
    mf::logRegressionSetup(EncoderType::BOW, scaler_methods::STANDARD_SCALAR, boundDecision, intercept, penalty);
    mf::logRegressionSetup(EncoderType::BOW, scaler_methods::MINMAX_SCALAR, boundDecision, intercept, penalty);
    boundDecision = 0.52;
    mf::logRegressionSetup(EncoderType::BOW, scaler_methods::MINMAX_SCALAR, boundDecision, intercept, penalty);
    mf::logRegressionSetup(EncoderType::TFID, scaler_methods::MINMAX_SCALAR, boundDecision, intercept, penalty);
    penalty = 0.3;
    intercept = true;
    boundDecision = 0.51;
    mf::logRegressionSetup(EncoderType::TFID, scaler_methods::MINMAX_SCALAR, boundDecision, intercept, penalty);
    mf::logRegressionSetup(EncoderType::BOW, scaler_methods::MINMAX_SCALAR, boundDecision, intercept, penalty);

    std::cout << "[[[[[[[[[[[------------NMC-----------]]]]]]]]]]]]]]]" << std::endl;
    mf::mein_nmc(EncoderType::BOW, scaler_methods::MINMAX_SCALAR);
    mf::mein_nmc(EncoderType::BOW, scaler_methods::STANDARD_SCALAR);
    mf::mein_nmc(EncoderType::BOW, scaler_methods::MAX_ABS_SCALAR);
    mf::mein_nmc(EncoderType::BOW, scaler_methods::MEAN_NORM);
    mf::mein_nmc(EncoderType::BOW);
    mf::mein_nmc(EncoderType::TFID);
    mf::mein_nmc(EncoderType::TFID, scaler_methods::MEAN_NORM);
    mf::mein_nmc(EncoderType::TFID, scaler_methods::MAX_ABS_SCALAR);
    mf::mein_nmc(EncoderType::TFID, scaler_methods::MINMAX_SCALAR);
    mf::mein_nmc(EncoderType::TFID, scaler_methods::STANDARD_SCALAR);

    std::cout << "[[[[[[[[[[[------------KNN-----------]]]]]]]]]]]]]]]" << std::endl;
    mf::mein_knn(EncoderType::BOW, scaler_methods::MINMAX_SCALAR);
    mf::mein_knn(EncoderType::BOW, scaler_methods::STANDARD_SCALAR);
    mf::mein_knn(EncoderType::BOW, scaler_methods::MEAN_NORM);
    mf::mein_knn(EncoderType::BOW, scaler_methods::MAX_ABS_SCALAR);
    mf::mein_knn(EncoderType::BOW);
    mf::mein_knn(EncoderType::TFID);
    mf::mein_knn(EncoderType::TFID, scaler_methods::MAX_ABS_SCALAR);
    mf::mein_knn(EncoderType::TFID, scaler_methods::MEAN_NORM);
    mf::mein_knn(EncoderType::TFID, scaler_methods::MINMAX_SCALAR);
    mf::mein_knn(EncoderType::TFID, scaler_methods::STANDARD_SCALAR);

    if (false)
    {
        std::cout << "[[[[[[[[[[[------------NMC-----------]]]]]]]]]]]]]]]" << std::endl;
        mf::mein_nmc2(EncoderType::BOW, scaler_methods::MINMAX_SCALAR);
        mf::mein_nmc2(EncoderType::BOW, scaler_methods::STANDARD_SCALAR);
        mf::mein_nmc2(EncoderType::BOW, scaler_methods::MAX_ABS_SCALAR);
        mf::mein_nmc2(EncoderType::BOW, scaler_methods::MEAN_NORM);
        mf::mein_nmc2(EncoderType::BOW);
        mf::mein_nmc2(EncoderType::TFID);
        mf::mein_nmc2(EncoderType::TFID, scaler_methods::MEAN_NORM);
        mf::mein_nmc2(EncoderType::TFID, scaler_methods::MAX_ABS_SCALAR);
        mf::mein_nmc2(EncoderType::TFID, scaler_methods::MINMAX_SCALAR);
        mf::mein_nmc2(EncoderType::TFID, scaler_methods::STANDARD_SCALAR);

        std::cout << "[[[[[[[[[[[------------KNN-----------]]]]]]]]]]]]]]]" << std::endl;
        mf::mein_knn2(EncoderType::BOW, scaler_methods::MINMAX_SCALAR);
        mf::mein_knn2(EncoderType::BOW, scaler_methods::STANDARD_SCALAR);
        mf::mein_knn2(EncoderType::BOW, scaler_methods::MEAN_NORM);
        mf::mein_knn2(EncoderType::BOW, scaler_methods::MAX_ABS_SCALAR);
        mf::mein_knn2(EncoderType::BOW);
        mf::mein_knn2(EncoderType::TFID);
        mf::mein_knn2(EncoderType::TFID, scaler_methods::MAX_ABS_SCALAR);
        mf::mein_knn2(EncoderType::TFID, scaler_methods::MEAN_NORM);
        mf::mein_knn2(EncoderType::TFID, scaler_methods::MINMAX_SCALAR);
        mf::mein_knn2(EncoderType::TFID, scaler_methods::STANDARD_SCALAR);
    };

    return 0;
}

void Vmain(bool fromStart)
{

    // create an instance of the class
    Preprocessor full;

    if (fromStart)
    {
        // Vectoring the string from start
        std::vector<std::string> Thelist = {"Arts", "Automotive", "Cell_Phones", "Gourmet_Foods", "Industrial", "Jewelry", "Musical_Instruments", "Office_Products", "Software", "Watches", "Clothing"};

        full.over_rideFileType(FileType::TXTGZ);
        full.over_rideList(mod(Thelist));
        // view all elements in the list
        full.printType();
        full.viewList();

        // Cant combine TXTGZ so convert to JSON and combine
        // No combine implementation for TXT
        // FileType changes to JSON too
        // DatasetList gets updated too; arts -> arts.json
        full.ConvertTxtgzToJson();
        full.printType();
        full.viewList();

        // combine JSON into 1
        // DatasetList changes to just "combined.json"
        full.Combine();
        full.printType();
        full.viewList();

        // Save the combined.json into DatasetList; score.txt and text.txt
        // As its implemented to do it for only one
        full.ConvertJsonToTxt();
        full.printType();
        full.viewList();

        //  takes text.txt and makes nostopword.txt
        full.removeStopWords();
        full.printType();
        full.viewList();

        full.stem(full.getList()[1]);

        // removes unwanted characters from [1] or text.tx or nostopword.txt to cleaned.txt
        full.removech();
        full.printType();
        full.viewList();

        // Takes score.txt and either text.txt or nostopword.txt
        // divides it and list is hightext.txt, lowtext.txt
        full.dividePostiveandNegative(3);
        full.printType();
        full.viewList();

        // output => equalhightext.txt, equallowtext.txt
        full.saveEqualdivided();
        full.printType();
        full.viewList();

        // set a limit
        full.setLimit(1288);

        full.Combine();
        full.printType();
        full.viewList();
    }
    else
    {
        full.over_rideFileType(FileType::JSON);
        full.printType();
        full.viewList();

        full.over_rideList({"../data/books_small_10000.json"});
        full.printType();
        full.viewList();

        full.Combine(true);
        full.printType();
        full.viewList();

        full.ConvertJsonToTxt();
        full.removeStopWords();
        full.stem(full.getList()[1]);
        full.removech();
        full.printType();
        full.viewList();

        full.dividePostiveandNegative(3);
        full.printType();
        full.viewList();

        full.saveEqualdivided();
        full.printType();
        full.viewList();

        full.Combine();
        full.printType();
        full.viewList();
    }

    /*
    Now İt can be used to vectorize
    */
    std::string file = full.getList()[0];

    /*
    convert the file into vector of string and vector of scores
    */
    std::vector<std::string> corpus;
    std::vector<int> scores;
    std::tie(corpus, scores) = getVectorDatasetFromFile(file);

    /*
    get the matrix
    */
    arma::mat Bmat, // Bag of word, charExtract
        Tmat;       // TFID, charExtract
    // Bmat = convertVectorStringToMatrix(corpus, EncoderType::BOW, TheTokenType::CHAREXTRACT);
    // Tmat = convertVectorStringToMatrix(corpus, EncoderType::TFID, TheTokenType::CHAREXTRACT);

    /*
    SAVE THE MATRIXES
    */
    // mlpack::data::Save("FULL_BOW_CHAREXTRACT_MAT.csv", Bmat);
    // mlpack::data::Save("FULL_TFID_CHAREXTRACT_MAT.csv", Tmat);

    Bmat = convertVectorStringToMatrix(corpus, EncoderType::BOW, TheTokenType::SPLITBYCHAR);
    Tmat = convertVectorStringToMatrix(corpus, EncoderType::TFID, TheTokenType::SPLITBYCHAR);

    /*
    SAVE THE MATRIXES
    */
    mlpack::data::Save("FULL_BOW_SPLITBYCHAR_MAT.csv", Bmat);
    mlpack::data::Save("FULL_TFID_SPLITBYCHAR_MAT.csv", Tmat);

    /*
    convert vector<int> to arma::Row<size_t>
    */
    arma::Row<size_t> label;
    label = vectorToIntRow(scores);

    /*
    save the label row
    */
    mlpack::data::Save("FULL_LABEL.csv", label);

    /*
    Split the data into train and test, and save it
    */
    double ratio = 0.1;
    arma::mat BTmat,           // BOW-TRAIN-MAT
        BTTmat,                // BOW-TEST-MAT
        TTmat,                 // TFID-TRAIN-MAT
        TTTmat;                // TFID-TEST-MAT
    arma::Row<size_t> BTlabel, // BOW-TRAIN-LABEL
        BTTlabel,              // BOW-TEST-LABEL
        TTlabel,               // TFID-TRAIN-LABEL
        TTTlabel;              // TFID-TEST-LABEL
    mlpack::data::Split(Bmat, label, BTmat, BTTmat, BTlabel, BTTlabel, ratio, true);
    mlpack::data::Split(Tmat, label, TTmat, TTTmat, TTlabel, TTTlabel, ratio, true);

    // saved to the same directory as the binary
    // used by other functions to work with
    mlpack::data::Save("BOW_train_mat.csv", BTmat);
    mlpack::data::Save("BOW_test_mat.csv", BTTmat);
    mlpack::data::Save("BOW_train_label.csv", BTlabel);
    mlpack::data::Save("BOW_test_label.csv", BTTlabel);
    mlpack::data::Save("TFID_train_mat.csv", TTmat);
    mlpack::data::Save("TFID_test_mat.csv", TTTmat);
    mlpack::data::Save("TFID_train_label.csv", TTlabel);
    mlpack::data::Save("TFID_test_label.csv", TTTlabel);
}
