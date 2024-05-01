#include "MLServer_Model.hpp"
#include "Stemmer.hpp"

void cleanTextForPrediction(std::string &text,
                            DictionaryType const &dictionary,
                            mlpack::data::SplitByAnyOf const &tokenizer)
{
    Stemm stemher;
    // text = stemher.stemWord(text);
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

/**
 * @brief converts the arma::mat type arma::Row with a threshold for 1's and 0's
 *        mainly used by FFN
 * 
 * @param matrix 
 * @param matrixRow 
 * @param threshold 
 */
void _convertToRow(const arma::mat &matrix, arma::Row<size_t> &matrixRow, double threshold)
{
    arma::Row<size_t> result(matrix.n_cols);

    for (size_t i = 0; i < matrix.n_cols; ++i)
    {
        result(i) = (matrix(0, i) >= threshold) ? 1 : 0;
    }

    matrixRow = result;
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

mlpack::data::BagOfWordsEncoding<mlpack::data::SplitByAnyOf::TokenType> BagOfWordsSplit()
{
    mlpack::data::BagOfWordsEncoding<mlpack::data::SplitByAnyOf::TokenType> encoder;
    mlpack::data::Load("/app/out/BOW_SPLIT_ENCODER.bin", "encoder-BOW-split", encoder);
    return encoder;
}

mlpack::data::TfIdfEncoding<mlpack::data::SplitByAnyOf::TokenType> TfidSplit()
{
    mlpack::data::TfIdfEncoding<mlpack::data::SplitByAnyOf::TokenType> encoder(mlpack::data::TfIdfEncodingPolicy::TfTypes::TERM_FREQUENCY, false);
    mlpack::data::Load("/app/out/TFID_SPLIT_ENCODER.bin", "encoder-TFID-split", encoder);
    return encoder;
}


void actualremoveStopWords(std::vector<std::string> &text, std::vector<std::string> &stopWords)
{
    for (std::string &str : text)
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

std::string actualremoveCharacters(std::string dirty, std::string &removeCharacters)
{
    std::string cleaned;

    // Loop through each character in the input string
    for (char c : dirty)
    {
        // Check if the character is not in the remove characters string
        if (removeCharacters.find(c) == std::string::npos)
        {
            // Append the character to the cleaned string
            cleaned += c;
        }
    }

    return cleaned;
}

void actualremoveCharactersList(std::vector<std::string> &text, std::string &removecharacters)
{
    for (std::string &str : text)
    {
        str = actualremoveCharacters(str, removecharacters);
    }
}


std::string returnRemoveChars(){
    std::string symbols;
    std::ifstream rem("/app/configs/removechars.txt");
    std::getline(rem, symbols);
    return symbols;
}

std::vector<std::string> returnStopWords(){
    // make stopwords empty
    std::vector<std::string> stopWords;

    std::ifstream stopWordsFile("/app/configs/stopwords.txt");
    if (!stopWordsFile.is_open())
    {
        std::cerr << "ERROR OPENING STOPWORDS.TXT" << std::endl;
    }
    std::string stopWord;
    while (stopWordsFile >> stopWord)
    {
        stopWords.push_back(stopWord);
    }
    stopWordsFile.close();
    // Convert stop words to lowercase
    std::transform(stopWords.begin(), stopWords.end(), stopWords.begin(),
                   [](std::string &str)
                   {
                       std::transform(str.begin(), str.end(), str.begin(), ::tolower);
                       return str;
                   });
    return stopWords;
}

void matrixToString(arma::mat &matrix, std::string &resultString){
    double a = matrix(0,1);
    double b = matrix(1,1);
    double c = a+b;
    double percenta = 100.0/c*a;
    double percentb = 100.0/c*b;
    if(percentb > percenta){
        resultString = "{ result: 1, positive: "+std::to_string(percentb)+" , negative: "+std::to_string(percenta)+" }";
    }else{
        resultString = "{ result: 0, positive: "+std::to_string(percentb)+" , negative: "+std::to_string(percenta)+" }";
    }
}

void rowToString(arma::Row<size_t>& row, std::string &resultString){
    resultString = "{ result: " + std::to_string(row(0,1)) + " }";
}

void turnFFNMatrixtostring(
    arma::Row<size_t> &predictionRow, 
    std::string &value){
        value = "{ result: "+ std::to_string(predictionRow(0,1)) +"}";
        return;
}

void turnRFMatrixtostring(
    arma::mat &matrix,
    arma::Row<size_t> &predictionRow, 
    std::string &value
){
    double top = matrix(0,1), bottom = matrix(1,1);
    double sum = top + bottom;
    top = 100.0/(sum) * top;
    bottom = 100.0/(sum) * bottom;
    value = "{ result: " + std::to_string(predictionRow(0,1)) + ", positive: "+ std::to_string(bottom) +", negative: "+ std::to_string(top) +"}";
    return;
}

mlpack::LogisticRegression<> &get_LogReg(){
    mlpack::LogisticRegression<> *model = new mlpack::LogisticRegression<>();
    mlpack::data::Load("logreg_bow_minimax.bin", "LogisticRegression", (*model));
    return *model;
}

std::string getpositive(){
    return "Excellent, this was a nice movie";
}

std::string getnegative(){
    return "This sucks, bad";
}

arma::mat tfidStringCleaner(std::string &text,
std::vector<std::string> &stopwords,
std::string &removecharacters,
DictionaryType const &dictionary,
mlpack::data::SplitByAnyOf &tokenizer,
mlpack::data::TfIdfEncoding<mlpack::data::SplitByAnyOf::TokenType> &encoder,
bool addbias){
    std::vector<std::string> vecString;
    if(addbias){
        vecString.push_back(getpositive());
        vecString.push_back(text);
        vecString.push_back(getnegative());
    }else{
        vecString.push_back(text);
    }
    
    actualremoveStopWords(vecString, stopwords);      // removestoopwords
    actualremoveCharactersList(vecString, removecharacters); // removechar
    for (std::string &str : vecString)
            {
                cleanTextForPrediction(str, dictionary, tokenizer);
            }
    arma::mat textmat;
    encoder.Encode(vecString, textmat, tokenizer);
    return textmat;
}

arma::mat bowStringCleaner(std::string &text,
std::vector<std::string> &stopwords,
std::string &removecharacters,
DictionaryType const &dictionary,
mlpack::data::SplitByAnyOf &tokenizer,
mlpack::data::BagOfWordsEncoding<mlpack::data::SplitByAnyOf::TokenType> &encoder,
bool addbias){
    std::vector<std::string> vecString;
    if(addbias){
        vecString.push_back(getpositive());
        vecString.push_back(text);
        vecString.push_back(getnegative());
   }else{
        vecString.push_back(text);
    }

    actualremoveStopWords(vecString, stopwords);      // removestoopwords
    actualremoveCharactersList(vecString, removecharacters); // removechar
    for (std::string &str : vecString)
            {
                cleanTextForPrediction(str, dictionary, tokenizer);
            }
    arma::mat textmat;
    encoder.Encode(vecString, textmat, tokenizer);
    return textmat;
}


void convertRowToResult(arma::Row<size_t> &row, arma::mat &prob, std::string &text){
    if(row(1) == 1) {
        text =  R"({"result": "1", "probability": ")" + std::to_string(prob(1,1)) + R"("})";
    }else{
        text =  R"({"result": "0", "probability": ")" + std::to_string(prob(0,1)) + R"("})";
    }
}