#include <iostream>
#include "OpenConnection.h"


int main(int argc, char* argv[])
{
    int port = 0;

    // Check input parameters
    if (argc < 2)
    {
        std::cout << "The input parameters are incorrect !\n";
    }
    else
    {
        port = std::stoi(argv[1]);
        OpenConnection *oc = new OpenConnection();

        int status = oc->setInputParameters(port);
        if (status < 0)
        {
            std::cout << "The input data are incorrect. The status is " << status << std::endl;
        }
        else
        {
            oc->ListenConnection();
        }

        delete oc;
    }

    return 0;
}