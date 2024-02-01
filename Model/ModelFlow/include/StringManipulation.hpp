/**
 * @file StringManipulation.hpp
 * @author John Obi (johnobi2003@gmail.com)
 * @brief A header file to house string manipulations that will be used
 * @version 0.1.0
 * @date 2024-01-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef STRING_MANIPULATION_HPP
#define STRING_MANIPULATION_HPP

#include "ModelFlow.hpp"

/**
 * @brief Extract the actual filename from the fullpath
 * @example ../data/parser.py -->> parser
 * @example ../data/parser.txt.gz -->> parser
 * @param path path to the file
 * @return the actual filename
 */
std::string extractFilename(const std::string &path)
{

    // Finds the last slash index ../data/arts
    size_t lastSlash = path.find_last_of("/\\");

    // Finds the last dot index => arts.txt
    size_t lastDot = path.find_last_of(".");

    if (lastDot < path.length() || lastSlash < path.length())
        return extractFilename(path.substr(lastSlash + 1, lastDot - lastSlash - 1));

    return path.substr(lastSlash + 1, lastDot - lastSlash - 1);
}

/**
 * @brief Calls the extractFilename method
 * makes the path variable a constant string
 * @param path
 */
void removeNonFilename(std::string &path)
{
    const std::string CONST_PATH = path;
    path = extractFilename(CONST_PATH);
}

void to_lower_str(std::string &cleaned)
{
    // Convert the string to lowercase.
    std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(), [](unsigned char c)
                   { return std::tolower(c); });
}

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
    // may remove later
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
    to_lower_str(cleaned);
    return cleaned;
}

bool removeStop(std::vector<std::string> &DatasetList)
{
    // Read stop words from file
    std::ifstream stopWordsFile("../configs/stopwords.txt");
    if (!stopWordsFile.is_open() || !std::filesystem::exists(DatasetList[0]))
    {
        return false;
    }

    std::vector<std::string> stopWords;
    std::string stopWord;
    while (stopWordsFile >> stopWord)
    {
        stopWords.push_back(stopWord);
    }
    stopWordsFile.close();
    to_lower_vec(stopWords);

    std::ifstream inputFile(DatasetList[0]);
    std::ofstream outputFile("noStopWord.txt");

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        return false;
    }

    // Process each line in the input file
    std::string line;
    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string word;

        // Process each word in the line
        while (iss >> word)
        {
            to_lower_str(word);
            // Remove punctuation or other unwanted characters
            word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());

            // Convert the word to lowercase for case-insensitive comparison
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);

            // Check if the word is not a stop word and write it to the output file
            if (std::find(stopWords.begin(), stopWords.end(), word) == stopWords.end())
            {
                outputFile << word << " ";
            }
        }

        outputFile << '\n';
    }

    // Close files
    inputFile.close();
    outputFile.close();
    DatasetList[0] = "noStopWord.txt";
    return true;
}

void combineJsonLineByLine(std::vector<std::string> &DatasetList)
{
    // Bad idea; storing it all in memory
    Json hugeBuffer = Json::array();
    std::string line;
    // Try checking for .extensionname / if file exists error
    for (const auto &dataset : DatasetList)
    {
        std::ifstream file(dataset);
        // open file error check sire
        while (std::getline(file, line))
        {
            Json temp_json = Json::parse(line);
            if (temp_json.is_null())
                continue;
            if (temp_json.empty())
                continue;
            // Taking only text and score and discarding the rest of garbage
            std::string score = temp_json["review/score"], text = temp_json["review/text"];
            temp_json["score"] = std::stof(score);
            temp_json["text"] = cleanString(text);
            temp_json.erase("review/summary");
            temp_json.erase("review/score");
            temp_json.erase("review/text");
            temp_json.erase("product/productId");
            temp_json.erase("product/title");
            temp_json.erase("product/price");
            temp_json.erase("review/userId");
            temp_json.erase("review/profileName");
            temp_json.erase("review/time");
            temp_json.erase("review/helpfulness");
            // Pushing an object into the json array
            hugeBuffer.push_back(temp_json);
        }
        std::cout << " Done with sending " << dataset << " into the buffer and closing it" << std::endl;
        file.close();
    }
    std::cout << " Started sending them into the combined.json" << std::endl;
    // TODO: Try checking if after opening one dataset file, out stream into it?? instead of holding huge buffer??
    std::ofstream outputFile("combined.json");
    outputFile << hugeBuffer;
    outputFile.close();
    DatasetList = {"combined.json"};
}
#endif