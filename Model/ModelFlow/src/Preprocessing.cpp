#include "Preprocessing.hpp"
#include <iomanip>

Preprocessor::Preprocessor() : DatasetList({}){};

Preprocessor::Preprocessor(FileType FT) : FT(FT), DatasetList({}){};

Preprocessor::Preprocessor(FileType FT, std::vector<std::string> &List) : FT(FT), DatasetList(List){};

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