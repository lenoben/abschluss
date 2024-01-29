#include "Preprocessing.hpp"
#include <iomanip>

/**
 * @brief Construct a new Preprocessor object
 * FileType is undefined, DatasetList is empty
 */
Preprocessor::Preprocessor() : DatasetList({}){};

/**
 * @brief Construct a new Preprocessor object
 *
 * @param FT FileType of the preprocessor class
 * DatasetList is empty
 */
Preprocessor::Preprocessor(FileType FT) : FT(FT), DatasetList({}){};

/**
 * @brief Construct a new Preprocessor object
 *
 * @param FT FileType
 * @param List Copy of the list
 */
Preprocessor::Preprocessor(FileType FT, std::vector<std::string> List) : FT(FT), DatasetList(List){};

/**
 * @brief Prints the FileType of the class
 */
void Preprocessor::printType()
{
    switch (FT)
    {
    case TXT:
        std::cout << "[INFO]" << std::setw(4) << ""
                  << "TXT FileType" << std::endl;
        return;
    case TXTGZ:
        std::cout << "[INFO]" << std::setw(4) << ""
                  << "TXTGZ FileType" << std::endl;
        return;
    case JSON:
        std::cout << "[INFO]" << std::setw(4) << ""
                  << "JSON FileType" << std::endl;
        return;
    default:
        std::cerr << "[INFO]" << std::setw(4) << ""
                  << "NO FileType" << std::endl;
        return;
    }
}

/**
 * @brief Appends to the already existing DatasetList of the class
 *
 * @param List new list, must not be the same as the existing DatasetList and not empty
 */
void Preprocessor::addList(std::vector<std::string> List)
{
    if (List.empty())
    {
        std::cerr << "[WARN]" << std::setw(4) << "Empty List" << std::endl;
        return;
    }
    DatasetList = List;
    return;
}

/**
 * @brief Prints the DatasetList of the class
 */
void Preprocessor::viewList()
{
    if (DatasetList.empty())
    {
        std::cout << "[INFO]" << std::setw(4) << "List Empty" << std::endl;
        return;
    }
    size_t count = 0;
    for (const auto &List : DatasetList)
    {
        std::cout << "[INFO]" << std::setw(4) << "[" << count << "]" << std::setw(4) << "" << List << std::endl;
        count++;
    }
    return;
}

/**
 * @brief Combines the existing DatasetList into a singular DatasetList of the same FileType
 */
void Preprocessor::Combine()
{
    if (FT == FileType::TXTGZ)
    {
        std::cerr << "[WARN]" << std::setw(4) << ""
                  << "No implementation for TXTGZ to combine!\nConvert to Json/Txt before combining" << std::endl;
        return;
    }
    if (FT == FileType::JSON)
    {
        if (DatasetList.empty())
        {
            std::cerr << "[WARN]" << std::setw(4) << "No Lists of [<filename>].json available" << std::endl;
            return;
        }
        // TODO
        return;
    }
    if (FT == FileType::TXT)
    {
        if (DatasetList.empty())
        {
            std::cerr << "[WARN]" << std::setw(4) << "No Lists of [<filename>].txt available" << std::endl;
            return;
        }
        // TODO
        return;
    }
    std::cout << "[WARN]" << std::setw(4) << ""
              << "Invalid!" << std::endl;
    return;
}

/**
 * @brief Combines and transform into another FileType
 * Limited Supported File Types to combine to
 *
 * @param FT FileType to combine to
 */
void Preprocessor::Combine(FileType FileType_to_combine_to)
{
    if (FileType_to_combine_to == FileType::TXT)
    {
        if (FT == FileType::JSON)
        {
            // TODO
        }
    }
}

/**
 * @brief Appends the list to the existing DatasetList and combines them
 *
 * @param List
 */
void Preprocessor::Combine(std::vector<std::string> list)
{
    if (DatasetList.empty())
    {
        if (!list.empty())
        {
            DatasetList = list;
        }
        else
        {
            std::cerr << "[WARN]" << std::setw(4) << ""
                      << "Both Lists are empty" << std::endl;
            return;
        }
    }
    else
    {
        // Add two vectors together
        DatasetList.insert(DatasetList.end(), list.begin(), list.end());
    }

    Combine();
    return;
}