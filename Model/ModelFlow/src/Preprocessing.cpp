#include "Preprocessing.hpp"
#include "StringManipulation.hpp"
#include "TxtgzToTxt.hpp"
#include "TxtgzToJson.hpp"

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
        std::cout << "[INFO] " << std::setw(4) << ""
                  << "TXT FileType" << std::endl;
        return;
    case TXTGZ:
        std::cout << "[INFO] " << std::setw(4) << ""
                  << "TXTGZ FileType" << std::endl;
        return;
    case JSON:
        std::cout << "[INFO] " << std::setw(4) << ""
                  << "JSON FileType" << std::endl;
        return;
    default:
        std::cerr << "[INFO] " << std::setw(4) << ""
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
        std::cerr << "[WARN] " << std::setw(4) << "Empty List" << std::endl;
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
        std::cout << "[INFO] " << std::setw(4) << "List Empty" << std::endl;
        return;
    }
    size_t count = 0;
    for (const auto &List : DatasetList)
    {
        std::cout << "[INFO] " << std::setw(4) << "[" << count << "]" << std::setw(4) << "" << List << std::endl;
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
        std::cerr << "[WARN] " << std::setw(4) << ""
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
        combineJsonLineByLine(DatasetList);
        return;
    }
    if (FT == FileType::TXT)
    {
        if (DatasetList.empty())
        {
            std::cerr << "[WARN]" << std::setw(4) << "No Lists of [<filename>].txt available" << std::endl;
            return;
        }
        if (DatasetList.size() == 2)
        {
            if (DatasetList[0] == "hightext.txt" || DatasetList[0] == "equalhightext.txt" || DatasetList[0] == "train_equalhightext.txt" || DatasetList[0] == "test_equalhightext.txt")
            {
                combineTXT(DatasetList);
                std::cout << "[INFO] " << std::setw(4) << "Combined - " << DatasetList[0] << std::endl;
            }
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

/**
 * @brief Removes the stopwords from the files contained in the datasetlist
 */
void Preprocessor::removeStopWords()
{
    auto it = std::find(DatasetList.begin(), DatasetList.end(), "text.txt");
    if (it != DatasetList.end())
    {
        if (!removeStop(DatasetList))
        {
            std::cerr << "[WARN] " << std::setw(4) << " Could not remove stopWords\nCheck if text.txt exists, stopwords.txt exists and if the DatasetList is text.txt only " << std::endl;
        }
    }
    else
    {
        std::cout << "[WARN] " << std::setw(4) << " Can only perform this if text.txt exists" << std::endl;
        return;
    }
}

/**
 * @brief Converts .txt.gz to .txt
 * @param directory The directory to save it, default is ''
 */
void Preprocessor::ConvertTxtgzToTxt(std::string directory = "")
{
    if (FT != FileType::TXTGZ)
    {
        std::cerr << "[WARN]" << std::setw(4) << "Cannot convert to TXT" << std::endl;
        return;
    }

    for (auto filename : DatasetList)
    {
        std::string outputData = {};
        if (gzTotzt::decompressGzip(filename + ".txt.gz", outputData))
        {
            removeNonFilename(filename);
            if (gzTotzt::saveToFile(directory + filename + ".txt", outputData))
            {
                std::cout << "[INFO]" << std::setw(4) << ""
                          << "Decompressed data saved to " << filename + ".txt" << std::endl;
                // change filetype
                FT = FileType::TXT;
            }
            else
            {
                std::cerr << "[WARN]" << std::setw(4) << "Error saving data" << std::endl;
            }
        }
    }
}

void Preprocessor::ConvertTxtgzToJson()
{
    if (FT != FileType::TXTGZ)
    {
        std::cerr << "[WARN]" << std::setw(4) << ""
                  << " Cannot use this to convert to json" << std::endl;
        return;
    }
    gzTojson::initializeScript(initializeScript);
    for (const auto &dataset : DatasetList)
    {
        gzTojson::convert(dataset, extractFilename(dataset));
    }
    for (auto &dataset : DatasetList)
    {
        dataset = extractFilename(dataset) + ".json";
    }
    FT = FileType::JSON;
}

void Preprocessor::ConvertJsonToTxt()
{
    if (DatasetList.size() == 1)
    {
        sm_convertJsonToTxt(DatasetList[0], DatasetList);
        FT = FileType::TXT;
        return;
    }
    else
    {
        std::cerr << "[WARN]" << std::setw(4) << ""
                  << "Can only do it for one, make sure you combine it" << std::endl;
        return;
    }
}
