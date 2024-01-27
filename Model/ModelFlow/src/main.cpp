/**
 * @file main.cpp
 * @author John Obi (johnobi2003@gmail.com)
 * @brief The main entry for the executable. Right now its for tests
 * @version 0.1.0
 * @date 2024-01-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Preprocessing.hpp"

int main()
{
    std::vector<std::string> Thelist = {"Arts", "Automotive", "Cell_Phones_&_Accessories", "Gourmet_Foods", "Industrial_&_Scientific", "Jewelry", "Musical_Instruments", "Office_Products", "Software", "Watches", "Clothing_&_Accessories"};

    Preprocessor review = Preprocessor(FileType::JSON);
    review.addList(Thelist);
    review.printType();
    review.viewList();

    return 0;
}