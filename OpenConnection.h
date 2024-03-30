#pragma once

#include <iostream>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <mutex>

#include "LogWritter.h"

class OpenConnection
{
private:
    int m_port;

    void dataProcessing(int sock);

    LogWritter* m_lw;

    std::mutex m_lock_mutex;

public:
    OpenConnection();
    ~OpenConnection();

    int setInputParameters(int port);    

    void ListenConnection();
};

