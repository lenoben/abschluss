#include <iostream>
#include <fstream>
#include <string>
#include <set>

int main()
{
    std::string real = "stopwords.txt";
    std::ifstream inputFile(real);
    std::set<std::string> uniqueWords;

    if (inputFile.is_open())
    {
        std::string word;
        while (inputFile >> word)
        {
            uniqueWords.insert(word);
        }
        inputFile.close();

        std::ofstream outputFile(real); // Overwrites the file.
        if (outputFile.is_open())
        {
            for (const std::string &word : uniqueWords)
            {
                outputFile << word << std::endl;
            }
            outputFile.close();
            std::cout << "Duplicates removed and file updated successfully.\n";
        }
        else
        {
            std::cerr << "Failed to open output file.\n";
        }
    }
    else
    {
        std::cerr << "Failed to open input file.\n";
    }

    return 0;
}
