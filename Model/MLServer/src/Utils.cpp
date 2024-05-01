#include "Utils.hpp"

int getPORTenv()
{
    // default port
    int port = 3000;
    const char *port_env_var = "PORT";
    const char *port_value = std::getenv(port_env_var);

    if (port_value == nullptr)
    {
        std::cout << "PORT environment variable not set. Using default port 3000." << std::endl;
    }
    else
    {
        try
        {
            port = std::stoi(port_value);
            std::cout << "Parsed port as integer: " << port << std::endl;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: Invalid argument. " << e.what() << std::endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << "Error: Out of range. " << e.what() << std::endl;
        }
    }

    return port;
}

bool checkCustomheader(std::string_view str){
    return (str != "senml().");
}

bool checkContentlength(std::string_view strn){
    return (std::stoi(std::string(strn)) <= 0);
}

void modelpredToString(int classes, std::string &values){
    //apparently for just two classes
    if(classes){
        values = R"({"result": "1"})";
    }else{
        values = R"({"result": "0"})";
    }
}