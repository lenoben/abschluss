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
std::string extractFilename(const std::string &path);

/**
 * @brief Calls the extractFilename method
 * makes the path variable a constant string
 * @param path
 */
void removeNonFilename(std::string &path);

/**
 * @brief Converts strings to lower case
 *
 * @param cleaned
 */
void to_lower_str(std::string &cleaned);

/**
 * @brief converts string vectors to lower case vectors of strings
 *
 * @param string_vector
 */
void to_lower_vec(std::vector<std::string> &string_vector);

/**
 * @brief removes certain characters from the string and replaces it with whitespace
 * the characters to remove are stored in configs/removechar.txt
 *
 * @param dirty
 * @return std::string
 */
std::string cleanString(std::string dirty);

/**
 * @brief removes stopwords from the string
 * stopwords are stored in configs/stopwords.txt
 * modifies the second index in the DatasetList to "noStopword.txt"
 *
 * @param DatasetList
 * @return true if successful
 */
bool removeStop(std::vector<std::string> &DatasetList);

/**
 * @brief removes characters from the string file
 * modifies the DatasetList
 */
void cleanStringFile(const std::string filename, std::vector<std::string> &DatasetList);

/**
 * @brief combines json line by line and modify the DatasetList
 *
 * @param DatasetList
 */
void combineJsonLineByLine(std::vector<std::string> &DatasetList);

/**
 * @brief saves a vector of strings into a file
 * modifies the DatasetList
 * @param vector
 * @param filename
 */
void saveVectors(std::vector<std::string> &vector, std::string filename);

/**
 * @brief converts Json into a two files, score.txt and text.txt
 * prefarebly done after combineJsonLineByLine
 * modifies the DatasetList
 * @param JsonFile
 * @param DatasetList
 */
void sm_convertJsonToTxt(std::string JsonFile, std::vector<std::string> &DatasetList);

/**
 * @brief combines multiple .txt files into one .txt file
 * modifies DatasetList
 * @param DatasetList
 */
void combineTXT(std::vector<std::string> &DatasetList);

/**
 * @brief creates two .txt files that are categorized according to the positive integer
 * modifes the DataSetList
 *
 * @param DatasetList must contain [score.txt, noStopWord.txt || text.txt]
 * @param positive the value used as decision boundary
 */
void categorizeByScore(std::vector<std::string> &DatasetList, int positive);

/**
 * @brief Function to count the number of lines in a file
 *
 * @param fileName
 * @return int total number of lines
 */
int countLines(const std::string &fileName);

/**
 * @brief Function to write the first n lines from one file to another
 *
 * @param inputFileName infput file name
 * @param output output file stream
 * @param n decision equalizer
 */
void equalizeLines(const std::string &inputFileName, std::ofstream &output, int n);

#endif