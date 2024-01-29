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

#include <string>
#include <algorithm>

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

#endif