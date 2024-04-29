/**
 * @file Stemmer.hpp
 * @author John Obi (johnobi2003@gmail.com)
 * @brief The stemmer class header file
 * @version 0.1
 * @date 2024-01-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODEL_FLOW_STEMMER_HPP
#define MODEL_FLOW_STEMMER_HPP

#include "MLServer.hpp"

#include "porter_stemmer.h"
#include <stdio.h>
#include <stdlib.h> /* for malloc, free, realloc */
#include <ctype.h>  /* for isupper, islower, tolower */

// Static members
static char *s;
static int i_max = 50; /* maximum offset in s */

#define LETTER(ch) (isupper(ch) || islower(ch))

/**
 * @brief a class for handling porter stemmer
 * 
 */
class Stemm
{
private:
    struct stemmer *z;
    const int INC = 50; /* size units in which s is increased */
    void processLines(std::vector<std::string> &lines, std::vector<std::string> &result);

public:
    Stemm(/* args */);
    ~Stemm();
    std::string stemWord(std::string &str);
    void stemfile(std::string inputFile, std::string outputFile);
};

/**
 * @brief stems a vector of strings
 * 
 * @param lines old vector of strings
 * @param result new stemmed vector of strings
 */
void Stemm::processLines(std::vector<std::string> &lines, std::vector<std::string> &result)
{
    Stemm s;
    for (const auto &line : lines)
    {
        std::stringstream ss(line);
        std::string word;
        std::string stemmedLine;
        while (ss >> word)
        {
            stemmedLine += s.stemWord(word) + " ";
        }
        result.push_back(stemmedLine);
    }
}

/**
 * @brief constructs the stem class
 * 
 */
Stemm::Stemm(/* args */)
{
    z = create_stemmer();
    s = (char *)malloc(i_max + 1);
}

Stemm::~Stemm()
{
    free(s);
    free_stemmer(z);
}

/**
 * @brief stems a string
 * 
 * @param str 
 * @return std::string 
 */
std::string Stemm::stemWord(std::string &str)
{
    const char *cstr = str.c_str();
    int i = 0;
    while (true)
    {
        if (i == i_max)
        {
            i_max += INC;
            s = (char *)realloc(s, i_max + 1);
        }
        //char ch = tolower(cstr[i]); /* forces lower case */
        char ch = cstr[i];
        s[i] = ch;
        s[i] = cstr[i];
        i++;
        if (!LETTER(ch) || i == str.length())
        {
            break;
        }
    }
    s[stem(z, s, i - 1) + 1] = 0;
    return std::string(s);
}

/**
 * @brief stems a file and saves it
 * 
 * @param inputfile 
 * @param outputfile 
 */
void Stemm::stemfile(std::string inputfile, std::string outputfile)
{
    std::ifstream inFile(inputfile);
    if (!inFile)
    {
        std::cerr << "Cannot open input file!" << std::endl;
        return;
    }

    std::ofstream outFile(outputfile);
    if (!outFile)
    {
        std::cerr << "Cannot open output file!" << std::endl;
        return;
    }
    inFile.close();
    outFile.close();
}

#endif