#include "OpenConnection.h"

OpenConnection::OpenConnection()
{
}

OpenConnection::~OpenConnection()
{
    delete m_lw;
}

int OpenConnection::setInputParameters(int port)
{
    if (port < 1)
    {
        std::cout << "Incorrect a port number";
        return -1;
    }
    m_port = port;


    m_lw = new LogWritter();
    int status = m_lw->createFile("");

    if (status < 0)
    {
        delete m_lw;

        return -2;
    }

    return 0;

}

void OpenConnection::ListenConnection()
{
    int mainSocket, passSocket; // Ведущий и ведомый сокеты
    
    struct sockaddr_in addrSourceIn;

    socklen_t addrLen = sizeof(addrSourceIn);

    addrSourceIn.sin_family = AF_INET;
    addrSourceIn.sin_addr.s_addr = INADDR_ANY;
    addrSourceIn.sin_port = htons(m_port);

    mainSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mainSocket < 0)
    {
        return;
    }

    int bindStatus = bind(mainSocket, (struct sockaddr*)&addrSourceIn, sizeof(addrSourceIn) );
    if (bindStatus < 0)
    {
        std::string outStr = "Couldn't bind " + std::to_string(bindStatus) + std::string(strerror(errno));
        std::cout << outStr << std::endl;
        m_lw->saveRow(outStr);
        exit(EXIT_FAILURE);
    }

    int listenStatus = listen(mainSocket, 10);
    if (listenStatus < 0)
    {
        std::string outStr = "Couldn't listen to " + std::to_string(listenStatus) + std::string(strerror(errno));
        std::cout << outStr << std::endl;
        m_lw->saveRow(outStr);
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        addrLen = sizeof(addrSourceIn);
        passSocket = accept(mainSocket, (struct sockaddr*)&addrSourceIn, &addrLen);
        if (passSocket < 0)
        {
            std::string outStr = "passSocket is incorrect = " + std::string(strerror(errno) );
            std::cout << outStr << std::endl;
            m_lw->saveRow(outStr);
            exit(EXIT_FAILURE);
        }


        std::thread thr(&OpenConnection::dataProcessing, this, passSocket);
        thr.detach();
    }
}

void OpenConnection::dataProcessing(int sock)
{
    int bytesRead;
    char buf[100];
    memset(buf, 0, sizeof buf);

    while (bytesRead = read(sock, buf, sizeof(buf)))
    {
        if (bytesRead > 0)
        {
            m_lock_mutex.lock();
            
            std::string inRow = std::string(buf);
            std::cout << "The input row is " << inRow << std::endl;
            
            m_lw->saveRow(inRow);
            m_lock_mutex.unlock();
        }
    }
    close(sock);
}

