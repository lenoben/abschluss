/**
 * @file main.cpp
 * @author John Obi (johnobi2003@gmail.com)
 * @brief The main entry for the executable
 * @version 0.1.0
 * @date 2024-01-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Preprocessing.hpp"

/**
 * @brief Just a function that appends "../data/raw/" to every item in a list
 * I mainly use this since i was lazy
 * @example Clothing -->> ../data/raw/Clothing
 * @param notmod List to modify
 * @return vector of modified strings
 */
std::vector<std::string> mod(std::vector<std::string> notmod)
{
    std::vector<std::string> willgo;
    for (auto item : notmod)
    {
        willgo.push_back("../data/raw/" + item);
    }
    return willgo;
}

int main()
{
    std::vector<std::string> Thelist = {"Arts", "Automotive", "Cell_Phones", "Gourmet_Foods", "Industrial", "Jewelry", "Musical_Instruments", "Office_Products", "Software", "Watches", "Clothing"};

    Preprocessor review = Preprocessor(FileType::JSON);
    review.addList(mod({"Arts"}));
    review.Combine();
    review.viewList();

    Preprocessor text = Preprocessor(FileType::TXT);
    text.addList({Thelist[5]});
    text.Combine();
    text.viewList();

    return 0;
}