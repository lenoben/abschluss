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