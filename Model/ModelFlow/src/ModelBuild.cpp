#include "ModelBuild.hpp"

std::tuple<std::vector<std::string>, std::vector<int>> getVectorDataset()
{
    // magic variable here
    Preprocessor rawtext = Preprocessor(FileType::TXT, {"equalhightext_combined.txt"});
    rawtext.viewList();

    int total = (int)(countLines(rawtext.getList()[0]));
    int half = total / 2;
    std::cout << "[INFO] " << std::setw(4) << " Full raw is " << total << std::endl;
    std::cout << "[INFO] " << std::setw(4) << " High and low is " << half << std::endl;

    std::vector<int> raw_score;
    for (int i = 0; i < total; i++)
    {
        if (i < half)
        {
            raw_score.push_back(1); // top is high
        }
        else
        {
            raw_score.push_back(0); // bottom is low
        }
    }
    if (raw_score.size() != total)
    {
        std::cerr << "Not same size with raw vector and string file" << std::endl;
    }
    auto rawcorpus = file_to_vector(rawtext.getList()[0], total);
    return std::make_tuple(rawcorpus, raw_score);
}

std::tuple<std::vector<std::string>, std::vector<int>> getVectorDatasetFromFile(std::string filename)
{
    Preprocessor rawtext = Preprocessor(FileType::TXT, {filename});
    rawtext.viewList();

    int total = (int)(countLines(rawtext.getList()[0]));
    int half = total / 2;
    std::cout << "[INFO] " << std::setw(4) << " Full raw is " << total << std::endl;
    std::cout << "[INFO] " << std::setw(4) << " High and low is " << half << std::endl;

    std::vector<int> raw_score;
    for (int i = 0; i < total; i++)
    {
        if (i < half)
        {
            raw_score.push_back(1); // top is high
        }
        else
        {
            raw_score.push_back(0); // bottom is low
        }
    }
    if (raw_score.size() != total)
    {
        std::cerr << "Not same size with raw vector and string file" << std::endl;
    }
    auto rawcorpus = file_to_vector(rawtext.getList()[0], total);
    return std::make_tuple(rawcorpus, raw_score);
}

arma::mat convertVectorStringToMatrix(std::vector<std::string> &vector_of_strings, EncoderType ET, TheTokenType TTT, bool saveEncoder, mlpack::data::TfIdfEncodingPolicy::TfTypes MDTT, bool boolean)
{
    arma::mat result;
    if (ET == EncoderType::BOW)
    {
        if (TTT == TheTokenType::SPLITBYCHAR)
        {
            mlpack::data::SplitByAnyOf tokenizers(" .,\"");
            mlpack::data::BagOfWordsEncoding<mlpack::data::SplitByAnyOf::TokenType> encoder;
            encoder.Encode(vector_of_strings, result, tokenizers);
            if (saveEncoder)
                mlpack::data::Save("BOW_SPLIT_ENCODER.bin", "encoder-BOW-split", encoder);
        }
        if (TTT == TheTokenType::CHAREXTRACT)
        {
            auto tokenizers = mlpack::data::CharExtract();
            mlpack::data::BagOfWordsEncoding<mlpack::data::CharExtract::TokenType> encoder;
            encoder.Encode(vector_of_strings, result, tokenizers);
            if (saveEncoder)
                mlpack::data::Save("BOW_CHAREXTRACT_ENCODER.bin", "encoder-BOW-char", encoder);
        }
    }
    if (ET == EncoderType::TFID)
    {
        if (TTT == TheTokenType::SPLITBYCHAR)
        {
            mlpack::data::SplitByAnyOf tokenizers(" .,\"");
            using TFID = mlpack::data::TfIdfEncoding<mlpack::data::SplitByAnyOf::TokenType>;
            TFID encoder(MDTT, boolean);
            encoder.Encode(vector_of_strings, result, tokenizers);
            if (saveEncoder)
                mlpack::data::Save("TFID_SPLIT_ENCODER.bin", "encoder-TFID-split", encoder);
        }
        if (TTT == TheTokenType::CHAREXTRACT)
        {
            auto tokenizers = mlpack::data::CharExtract();
            using TFID = mlpack::data::TfIdfEncoding<mlpack::data::CharExtract::TokenType>;
            TFID encoder(MDTT, boolean);
            encoder.Encode(vector_of_strings, result, tokenizers);
            if (saveEncoder)
                mlpack::data::Save("TFID_CHAREXTRACT_ENCODER.bin", "encoder-TFID-char", encoder);
        }
    }
    return result;
}

arma::Row<size_t> vectorToIntRow(const std::vector<int> &vec)
{
    arma::Row<size_t> result(vec.size());
    for (size_t i = 0; i < vec.size(); ++i)
    {
        result(i) = static_cast<size_t>(vec[i]);
    }
    return result;
}

double ComputePrecision(const size_t truePos, const size_t falsePos)
{
    return (double)truePos / (double)(truePos + falsePos);
}

double ComputeRecall(const size_t truePos, const size_t falseNeg)
{
    return (double)truePos / (double)(truePos + falseNeg);
}

double ComputeF1Score(const size_t truePos, const size_t falsePos, const size_t falseNeg)
{
    double prec = ComputePrecision(truePos, falsePos);
    double rec = ComputeRecall(truePos, falseNeg);
    return 2 * (prec * rec) / (prec + rec);
}

double ComputeAccuracy(const arma::Row<size_t> &yPreds, const arma::Row<size_t> &yTrue)
{
    const size_t correct = arma::accu(yPreds == yTrue);
    return (double)correct / (double)yTrue.n_elem;
}

void ClassificationReport(const arma::Row<size_t> &yPreds, const arma::Row<size_t> &yTrue)
{
    arma::Row<size_t> uniqs = arma::unique(yTrue);
    std::cout << std::setw(29) << "precision" << std::setw(15) << "recall"
              << std::setw(15) << "f1-score" << std::setw(15) << "support"
              << std::endl
              << std::endl;

    for (auto val : uniqs)
    {
        size_t truePos = arma::accu(yTrue == val && yPreds == val && yPreds == yTrue);
        size_t falsePos = arma::accu(yPreds == val && yPreds != yTrue);
        size_t trueNeg = arma::accu(yTrue != val && yPreds != val && yPreds == yTrue);
        size_t falseNeg = arma::accu(yPreds != val && yPreds != yTrue);

        std::cout << std::setw(15) << val
                  << std::setw(12) << std::setprecision(2) << ComputePrecision(truePos, falsePos)
                  << std::setw(16) << std::setprecision(2) << ComputeRecall(truePos, falseNeg)
                  << std::setw(14) << std::setprecision(2) << ComputeF1Score(truePos, falsePos, falseNeg)
                  << std::setw(16) << truePos
                  << std::endl;
    }
}

void pickScalarMethod(scaler_methods SM, arma::mat &train, arma::mat &test)
{
    switch (SM)
    {
    case scaler_methods::MINMAX_SCALAR:
    {
        mlpack::data::MinMaxScaler minmax;
        minmax.Fit(train);
        minmax.Transform(train, train);
        minmax.Transform(test, test);
        break;
    }
    case scaler_methods::STANDARD_SCALAR:
    {
        mlpack::data::StandardScaler stanscale;
        stanscale.Fit(train);
        stanscale.Transform(train, train);
        stanscale.Transform(test, test);
        break;
    }
    case scaler_methods::MAX_ABS_SCALAR:
    {
        mlpack::data::MaxAbsScaler maxabs;
        maxabs.Fit(train);
        maxabs.Transform(train, train);
        maxabs.Transform(test, test);
        break;
    }
    case scaler_methods::MEAN_NORM:
    {
        mlpack::data::MeanNormalization mean;
        mean.Fit(train);
        mean.Transform(train, train);
        mean.Transform(test, test);
        break;
    }
    default:
        std::cout << "[INFO] " << std::setw(4) << " No Scaler methods used" << std::endl;
        break;
    }
}