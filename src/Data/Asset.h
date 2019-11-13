#ifndef ASSET_H
#define ASSET_H

#include <iostream>

class Asset
{
private:
    std::string type;
    std::string id;
    std::string filePath;
    int fontSize;

public:
    Asset(std::string type, std::string id, std::string filePath)
    {
        this->type = type;
        this->id = id;
        this->filePath = filePath;
    }

    Asset(std::string type, std::string id, std::string filePath, int fontSize)
    {
        this->type = type;
        this->id = id;
        this->filePath = filePath;
        this->fontSize = fontSize;
    }

    ~Asset()
    {
    }
};

#endif