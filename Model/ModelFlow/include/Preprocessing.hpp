/**
 * @file Preprocessing.hpp
 * @author John Obi (johnobi2003@gmail.com)
 * @brief The preprocessor class header file
 * @version 0.1
 * @date 2024-01-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODEL_FLOW_PREPROCESSING_HPP
#define MODEL_FLOW_PREPROCESSING_HPP

#include "ModelFlow.hpp"

/**
 * @class Preprocessor
 *
 * @brief The preprocessor class as the name entails deals with preprocessing the dataset gotten from
 * https://snap.stanford.edu/data/web-Amazon-links.html into formats that we can use.
 */
class Preprocessor
{
public:
    /**
     * @brief Construct a new Preprocessor object
     * FileType is undefined, DatasetList is empty
     */
    Preprocessor();

    /**
     * @brief Construct a new Preprocessor object
     *
     * @param FT FileType of the preprocessor class
     * DatasetList is empty
     */
    Preprocessor(FileType FT);

    /**
     * @brief Construct a new Preprocessor object
     *
     * @param FT FileType
     * @param List Copy of the list
     */
    Preprocessor(FileType FT, std::vector<std::string> List);

    /**
     * @brief Prints the FileType of the class
     */
    void printType();

    /**
     * @brief Appends to the already existing DatasetList of the class
     *
     * @param List new list, must not be the same as the existing DatasetList and not empty
     */
    void addList(std::vector<std::string> List);

    /**
     * @brief Prints the DatasetList of the class
     */
    void viewList();

    /**
     * @brief Combines the existing DatasetList into a singular DatasetList of the same FileType
     */
    void Combine();

    /**
     * @brief Combines and transform into another FileType
     *
     * @param FT FileType to combine to
     */
    void Combine(FileType FT);

    /**
     * @brief Appends the list to the existing DatasetList and combines them
     *
     * @param List
     */
    void Combine(std::vector<std::string> List);

    /**
     * @brief Removes the stopwords from the files contained in the datasetlist
     */
    void removeStopWords();

    /**
     * @brief Converts .txt.gz to .txt
     * @param directory The directory to save it, default is ''
     */
    void ConvertTxtgzToTxt(std::string directory);

    /**
     * @brief converts .txt.gz to .json
     * The datasetList can be a list of .txt.gz files and be converted to list of .json
     *
     */
    void ConvertTxtgzToJson();

    /**
     * @brief usually works after combine()
     * save the combined.json file into score.txt and text.txt
     *
     */
    void ConvertJsonToTxt();

private:
    Json Dataset = {};                    // Json object???
    FileType FT;                          // File type
    std::vector<std::string> DatasetList; // List of Dataset
    bool initializeScript = false;        // installs the python package required to run the parser script
};

#endif