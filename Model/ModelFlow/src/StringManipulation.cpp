/**
 * @file StringManipulation.cpp
 * @author John Obi (johnobi2003@gmail.com)
 * @brief A header file to house string manipulations that will be used
 * @version 0.1.0
 * @date 2024-01-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "StringManipulation.hpp"

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

/**
 * @brief Converts strings to lower case
 *
 * @param cleaned
 */
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

/**
 * @brief removes certain characters from the string and replaces it with whitespace
 * the characters to remove are stored in configs/removechar.txt
 *
 * @param dirty
 * @return std::string
 */
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

/**
 * @brief removes stopwords from the string
 * stopwords are stored in configs/stopwords.txt
 * modifies the second index in the DatasetList to "noStopword.txt"
 *
 * @param DatasetList
 * @return true if successful
 */
bool removeStop(std::vector<std::string> &DatasetList)
{
    // DatasetList looks like this {score.txt, text.txt}
    // Read stop words from file
    std::ifstream stopWordsFile("../configs/stopwords.txt");
    if (!stopWordsFile.is_open() || !std::filesystem::exists(DatasetList[1]))
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

    std::ifstream inputFile(DatasetList[1]);
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
            // to_lower_str(word);
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
    DatasetList[1] = "noStopWord.txt";
    return true;
}

/**
 * @brief removes characters from the string file
 * modifies the DatasetList
 */
void cleanStringFile(const std::string filename, std::vector<std::string> &DatasetList)
{
    std::ifstream file(filename);
    std::string newname = "cleaned.txt";
    std::ofstream outfile(newname);
    std::string line;
    while (std::getline(file, line))
    {
        outfile << cleanString(line) << "\n";
    }
    file.close();
    outfile.close();
    std::cout << "[INFO] " << std::setw(4) << filename << " changed to " << newname << std::endl;
    DatasetList[1] = newname;
}

/**
 * @brief combines json line by line and modify the DatasetList
 *
 * @param DatasetList
 */
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

/**
 * @brief saves a vector of strings into a file
 * modifies the DatasetList
 * @param vector
 * @param filename
 */
void saveVectors(std::vector<std::string> &vector, std::string filename)
{
    std::ofstream File(filename);
    std::cout << " Saving to " << filename << std::endl;
    for (const auto &vectorUnit : vector)
    {
        File << vectorUnit << std::endl;
    }
    File.close();
    std::cout << " Saved " << filename << std::endl;
}

/**
 * @brief converts Json into a two files, score.txt and text.txt
 * prefarebly done after combineJsonLineByLine
 * modifies the DatasetList
 * @param JsonFile
 * @param DatasetList
 */
void sm_convertJsonToTxt(std::string JsonFile, std::vector<std::string> &DatasetList)
{
    // errorenous ??
    std::ifstream file(JsonFile);

    /**
     * @brief This variable is to know which type of field it holds
     *  True - means ["score"], False - means []"review/score"]
     */
    bool whichfield = false;
    std::cout << DatasetList[0] << " about to be json parsed " << std::endl;
    Json JsonBuffer = Json::parse(file);
    std::cout << DatasetList[0] << " parsed " << std::endl;

    // fields needed; score and text
    std::vector<std::string> score, text;

    if (!JsonBuffer.is_array())
    {

        // change it back to empty buffer;
        JsonBuffer = {};

        std::string line;
        while (std::getline(file, line))
        {

            JsonBuffer = Json::parse(line);

            if (JsonBuffer.is_null() || JsonBuffer.empty())
                continue;

            if (JsonBuffer.contains("review/score"))
            {
                whichfield = false;
                score.push_back(std::to_string(JsonBuffer["review/score"].get<int>()));
            }
            if (JsonBuffer.contains("score"))
            {
                whichfield = true;
                score.push_back(std::to_string(JsonBuffer["score"].get<int>()));
            }

            if (JsonBuffer.contains("review/text"))
            {
                text.push_back(JsonBuffer["review/text"]);
            }
            if (JsonBuffer.contains("text"))
            {
                text.push_back(JsonBuffer["text"]);
            }
        }
        saveVectors(text, "text.txt");
        saveVectors(score, "score.txt");
        DatasetList = {"score.txt", "text.txt"};

        return;
    }
    else
    {
        if (JsonBuffer[0].contains("score"))
            whichfield = true;
        // true - score, false - review/score
        if (whichfield)
        {

            for (Json &field : JsonBuffer)
            {
                text.push_back(field["text"]);
                score.push_back(std::to_string(field["score"].get<int>()));
            }
            saveVectors(text, "text.txt");
            saveVectors(score, "score.txt");
            DatasetList = {"score.txt", "text.txt"};
            return;
        }
        else
        {
            for (const auto &field : JsonBuffer)
            { // in here as "json.hpp" dont want to all composition
                std::string temp_text = field["review/text"], temp_score = field["review/score"];
                text.push_back(temp_text);
                score.push_back(temp_score);
            }
            saveVectors(text, "text.txt");
            saveVectors(score, "score.txt");
            DatasetList = {"score.txt", "text.txt"};
            return;
        }
    }
}

/**
 * @brief combines multiple .txt files into one .txt file
 * modifies DatasetList
 * @param DatasetList
 */
void combineTXT(std::vector<std::string> &DatasetList)
{
    // Open a new file to combine the contents
    std::string newname = (extractFilename(DatasetList[0]) + "_combined.txt");
    std::ofstream combinedFile(newname);

    for (const auto &fileName : DatasetList)
    {
        // Open each input file
        std::ifstream inputFile(fileName);
        if (!inputFile.is_open())
        {
            std::cerr << "Error opening input file: " << fileName << std::endl;
            return;
        }

        // Append the contents of the input file to the combined file
        combinedFile << inputFile.rdbuf();

        // Close the input file
        inputFile.close();
    }

    // Close the combined file
    combinedFile.close();

    std::cout << "Files combined successfully." << std::endl;
    DatasetList = {newname};
}

/**
 * @brief creates two .txt files that are categorized according to the positive integer
 * modifes the DataSetList
 *
 * @param DatasetList must contain [score.txt, noStopWord.txt || text.txt]
 * @param positive the value used as decision boundary
 */
void categorizeByScore(std::vector<std::string> &DatasetList, int positive)
{
    std::ifstream scoreFile(DatasetList[0]); // score.txt
    std::ifstream textFile(DatasetList[1]);  // text.txt or noStopWord.txt or cleaned.txt

    if (!scoreFile.is_open() || !textFile.is_open())
    {
        std::cerr << "Error opening input files." << std::endl;
        return;
    }

    std::ofstream highTextFile("hightext.txt");
    std::ofstream lowTextFile("lowtext.txt");

    if (!highTextFile.is_open() || !lowTextFile.is_open())
    {
        std::cerr << "Error opening output files." << std::endl;
        return;
    }

    std::vector<int> scores;
    int score;
    while (scoreFile >> score)
    {
        scores.push_back(score);
    }

    std::string line;
    for (size_t i = 0; i < scores.size(); ++i)
    {
        std::getline(textFile, line);

        if (line.empty())
            continue;
        if (scores[i] >= positive)
        {
            highTextFile << line << std::endl;
        }
        else
        {
            lowTextFile << line << std::endl;
        }
    }

    std::cout << "Categorization completed." << std::endl;
    DatasetList = {"hightext.txt", "lowtext.txt"};

    scoreFile.close();
    textFile.close();
    highTextFile.close();
    lowTextFile.close();
}

/**
 * @brief Function to count the number of lines in a file
 *
 * @param fileName
 * @return int total number of lines
 */
int countLines(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Error opening file for line counting: " << fileName << std::endl;
        return 0;
    }

    int lineCount = 0;
    std::string line;
    while (std::getline(file, line))
    {
        ++lineCount;
    }

    file.close();
    return lineCount;
}

/**
 * @brief Function to write the first n lines from one file to another
 *
 * @param inputFileName infput file name
 * @param output output file stream
 * @param n decision equalizer
 */
void equalizeLines(const std::string &inputFileName, std::ofstream &output, int n)
{
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening input file for equalization: " << inputFileName << std::endl;
        return;
    }

    std::string line;
    for (int i = 0; i < n; ++i)
    {
        std::getline(inputFile, line);
        output << line << std::endl;
    }

    inputFile.close();
}