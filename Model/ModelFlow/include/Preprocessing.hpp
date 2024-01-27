#ifndef MODEL_FLOW_PREPROCESSING_HPP
#define MODEL_FLOW_PREPROCESSING_HPP

#include "ModelFlow.hpp"

class Preprocessor
{
public:
    Preprocessor();
    Preprocessor(FileType FT);
    Preprocessor(FileType FT, std::vector<std::string> &List);
    void printType();
    void addList(std::vector<std::string> List);
    void viewList();
private:
    Json Dataset = {};
    FileType FT;
    std::vector<std::string> DatasetList;
};

#endif