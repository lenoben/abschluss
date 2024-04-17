#include "MLServer_Model.hpp"

std::string mlserverModelToString(MLSERVER_MODEL MM)
{
    switch (MM)
    {
    case MLSERVER_MODEL::FFN_MEAN_HE:
        return "FNN_Meansquarederror_Heinitialztion";
    case MLSERVER_MODEL::LOG_REG:
        return "Logistic Regression";
    case MLSERVER_MODEL::RANDOM_FOREST:
        return "Random Forest";
    default:
        return "UNKNOWN";
    }
}

void to_lower_str(std::string &cleaned)
{
    // Convert the string to lowercase.
    std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(), [](unsigned char c)
                   { return std::tolower(c); });
}

/**
 * @brief converts string vectors to lower case vectors of strings
 *
 * @param string_vector
 */
void to_lower_vec(std::vector<std::string> &string_vector)
{
    for (auto &word : string_vector)
    {
        to_lower_str(word);
    }
}

std::string cleanString(std::string dirty)
{
    std::string cleaned;
    std::ifstream rem("../configs/removechars.txt");
    std::string symbols_line;
    while (std::getline(rem, symbols_line))
    {
        for (char c : dirty)
        {
            // Check if the character is not in the symbols string.
            if (symbols_line.find(c) == std::string::npos)
            {
                // Append the character to the new string.
                cleaned += c;
            }
        }
    }
    // to_lower_str(cleaned);
    return cleaned;
}

void cleanStringFile(std::vector<std::string> &vector_of_string)
{
    for (std::string &str : vector_of_string)
    {
        str = cleanString(str);
    }
}

void removeStop(std::vector<std::string> &vector_of_string)
{
    // Read stop words from file
    std::ifstream stopWordsFile("../configs/stopwords.txt");
    if (!stopWordsFile.is_open())
    {
        std::cerr << "ERROR OPENING STOPWORDS.TXT" << std::endl;
        return;
    }

    std::vector<std::string> stopWords;
    std::string stopWord;
    while (stopWordsFile >> stopWord)
    {
        stopWords.push_back(stopWord);
    }
    stopWordsFile.close();
    to_lower_vec(stopWords);

    // Iterate over each string in the vector
    for (std::string &str : vector_of_string)
    {
        std::istringstream iss(str);
        std::string word;
        std::string modifiedString;

        // Process each word in the string
        while (iss >> word)
        {
            // Remove punctuation or other unwanted characters
            word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());

            // Convert the word to lowercase for case-insensitive comparison
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);

            // Check if the word is not a stop word and add it to the modified string
            if (std::find(stopWords.begin(), stopWords.end(), word) == stopWords.end())
            {
                modifiedString += word + " ";
            }
        }

        // Save the modified string back to the vector
        str = modifiedString;
    }
}

void cleanTextForPrediction(std::string &text,
                            DictionaryType const &dictionary,
                            mlpack::data::SplitByAnyOf const &tokenizer)
{

    MLPACK_STRING_VIEW strView(text);
    auto token = tokenizer(strView);
    std::string processedText = "";
    while (!tokenizer.IsTokenEmpty(token))
    {
        /* MLPACK encoder will expand the dictionary if unknown tokens are present in the prediction - text.
         * To avoid that, simply remove the unknown ones.*/
        if (dictionary.HasToken(token))
        {
            processedText.append(" ").append(token);
        }

        token = tokenizer(strView);
    }
    text = processedText;
}

/**
 * @brief Perform encoding on the vector of strings and returns a row major matrix
 * @param vector_of_strings The string corpus it will encode
 * @param ET The encoder type [ TFID or Bag of Words ]
 * @param TTT The token type to use to encode the corpus
 * @return arma::mat The row major matrix
 */
void convertVectorStringToMatrix(std::vector<std::string> vector_of_strings, 
                                arma::mat &matrix, EncoderType ET, TheTokenType TTT, 
                                mlpack::data::TfIdfEncodingPolicy::TfTypes MDTT, 
                                bool boolean)
{
    removeStop(vector_of_strings);      // removestoopwords
    cleanStringFile(vector_of_strings); // removechar

    if (ET == EncoderType::BOW)
    {
        if (TTT == TheTokenType::SPLITBYCHAR)
        {
            mlpack::data::SplitByAnyOf tokenizers(" .,\"");
            mlpack::data::BagOfWordsEncoding<mlpack::data::SplitByAnyOf::TokenType> encoder;
            mlpack::data::Load("BOW_SPLIT_ENCODER.bin", "encoder-BOW-split", encoder);
            const DictionaryType &dictionary = encoder.Dictionary();
            for (std::string &str : vector_of_strings)
            {
                cleanTextForPrediction(str, dictionary, tokenizers);
            }
            encoder.Encode(vector_of_strings, matrix, tokenizers);
            matrix.brief_print("BOW SPLIT");
        }
        if (TTT == TheTokenType::CHAREXTRACT)
        {
            auto tokenizers = mlpack::data::CharExtract();
            mlpack::data::BagOfWordsEncoding<mlpack::data::CharExtract::TokenType> encoder;
            mlpack::data::Load("BOW_CHAREXTRACT_ENCODER.bin", "encoder-BOW-char", encoder);
            encoder.Encode(vector_of_strings, matrix, tokenizers);
        }
    }
    if (ET == EncoderType::TFID)
    {
        if (TTT == TheTokenType::SPLITBYCHAR)
        {
            mlpack::data::SplitByAnyOf tokenizers(" .,\"");
            using TFID = mlpack::data::TfIdfEncoding<mlpack::data::SplitByAnyOf::TokenType>;
            TFID encoder(MDTT, boolean);
            mlpack::data::Load("TFID_SPLIT_ENCODER.bin", "encoder-TFID-split", encoder);
            const DictionaryType &dictionary = encoder.Dictionary();
            for (std::string &str : vector_of_strings)
            {
                cleanTextForPrediction(str, dictionary, tokenizers);
            }
            encoder.Encode(vector_of_strings, matrix, tokenizers);
            matrix.brief_print("TFID SPLIT");
        }
        if (TTT == TheTokenType::CHAREXTRACT)
        {
            auto tokenizers = mlpack::data::CharExtract();
            using TFID = mlpack::data::TfIdfEncoding<mlpack::data::CharExtract::TokenType>;
            TFID encoder(MDTT, boolean);
            mlpack::data::Load("TFID_CHAREXTRACT_ENCODER.bin", "encoder-TFID-char", encoder);
            encoder.Encode(vector_of_strings, matrix, tokenizers);
        }
    }
}

void scalerTransform(scaler_methods SM, arma::mat &matrix)
{
    // pick scalar method
    switch (SM)
    {
    case scaler_methods::MINMAX_SCALAR:
    {
        mlpack::data::MinMaxScaler minmax;
        minmax.Fit(matrix);
        minmax.Transform(matrix, matrix);
        break;
    }
    case scaler_methods::STANDARD_SCALAR:
    {
        mlpack::data::StandardScaler stanscale;
        stanscale.Fit(matrix);
        stanscale.Transform(matrix, matrix);
        break;
    }
    case scaler_methods::MAX_ABS_SCALAR:
    {
        mlpack::data::MaxAbsScaler maxabs;
        maxabs.Fit(matrix);
        maxabs.Transform(matrix, matrix);
        break;
    }
    case scaler_methods::MEAN_NORM:
    {
        mlpack::data::MeanNormalization mean;
        mean.Fit(matrix);
        mean.Transform(matrix, matrix);
        break;
    }
    default:
        break;
    }
}

void _convertToRow(const arma::mat &matrix, arma::Row<size_t> &matrixRow, double threshold)
{
    arma::Row<size_t> result(matrix.n_cols);

    for (size_t i = 0; i < matrix.n_cols; ++i)
    {
        result(i) = (matrix(0, i) >= threshold) ? 1 : 0;
    }

    matrixRow = result;
}

mlpack::FFN<mlpack::CrossEntropyError, mlpack::HeInitialization> getFFN_CH(
    std::string modelpath, std::string modelname)
{
    mlpack::FFN<mlpack::CrossEntropyError, mlpack::HeInitialization> model;
    mlpack::data::Load(modelpath, modelname, model);
    return model;
}

mlpack::FFN<mlpack::MeanSquaredError, mlpack::HeInitialization> &getFFN_MH(
    std::string const modelpath, const std::string modelname)
{
    mlpack::FFN<mlpack::MeanSquaredError, mlpack::HeInitialization> *model = new mlpack::FFN<mlpack::MeanSquaredError, mlpack::HeInitialization>();
    mlpack::data::Load(modelpath, modelname, (*model));
    return *model;
}

mlpack::RandomForest<> &getRF(
    std::string modelpath,
    std::string modelname)
{
    mlpack::RandomForest<> *model = new mlpack::RandomForest<>();
    mlpack::data::Load(modelpath, modelname, (*model));
    return *model;
}