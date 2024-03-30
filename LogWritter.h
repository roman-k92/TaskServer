#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream> 

class LogWritter
{
private:
    std::string m_filePath;
    const std::string m_fileName;

    std::fstream m_fs;

public:
    LogWritter();
    ~LogWritter();

    int createFile(std::string filePath);

    void saveRow(std::string inputString);
};

