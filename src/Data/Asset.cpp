#include "./Asset.h"

Asset::Asset(std::string type, std::string id, std::string filePath)
{
    this->type = type;
    this->id = id;
    this->filePath = filePath;
}

Asset::Asset(std::string type, std::string id, std::string filePath, int fontSize)
{
    this->type = type;
    this->id = id;
    this->filePath = filePath;
    this->fontSize = fontSize;
}

Asset::~Asset()
{
}

std::string Asset::GetType() const
{
    return this->type;
}

std::string Asset::GetId() const
{
    return this->id;
}

std::string Asset::GetFilePath() const
{
    return this->filePath;
}

int Asset::GetFontSize() const
{
    return this->fontSize;
}