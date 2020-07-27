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
    Asset(std::string type, std::string id, std::string filePath);
    Asset(std::string type, std::string id, std::string filePath, int fontSize);
    ~Asset();

    std::string GetType() const;
    std::string GetId() const;
    std::string GetFilePath() const;
    int GetFontSize() const;
};

#endif