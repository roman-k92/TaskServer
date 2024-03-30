#include "LogWritter.h"

LogWritter::LogWritter():
    m_fileName("log.txt")
{
}

LogWritter::~LogWritter()
{
    m_fs << "--==== Good bye! ====--" << std::endl;
    m_fs.close();
}

int LogWritter::createFile(std::string filePath)
{
    if (filePath.empty())
    {
        char cwd[512];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            m_filePath = std::string(cwd);
            std::cout << "The input path is " << m_filePath << std::endl;
        }
        else
        {
            return -1;
        }
    }

    std::string fullFileName = m_filePath + "//" + m_fileName;
    m_fs.open(fullFileName, std::ios::app);

    if (!m_fs.is_open() )
    {
        return -2;
    }

    m_fs << "--==== Welcome! ====--" << std::endl;
}

void LogWritter::saveRow(std::string inputString)
{
    m_fs << inputString << std::endl;
}