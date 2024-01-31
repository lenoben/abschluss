#include "ModelFlow.hpp"

namespace gzTojson
{
    /**
     * @brief This function executes the command and gets the results as a string
     *
     * @param cmd - command characters
     * @return std::string
     */
    std::string exec(const char *cmd)
    {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe)
        {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        {
            result += buffer.data();
        }
        return result;
    }

    void initializeScript(bool &goon)
    {
        if (!goon)
        {
            const char *command = "sudo apt install -y python3-pip && pip3 install -r ../data/requirements.txt";

            // Run the command using the system function
            int result = system(command);

            // Check the result
            if (result == 0)
            {
                std::cout << "[INFO]" << std::setw(4) << ""
                          << "Done setting pip3 up" << std::endl;
                goon = true;
                return;
            }
            else
            {
                std::cerr << "[WARN]" << std::setw(4) << ""
                          << "Error running pip3" << std::endl;
                return;
            }
        }
    }

    void convert(std::string inputfile, std::string outputfile)
    {
        std::string cmd = "../data/parser.py " + inputfile + ".txt.gz" + " " + outputfile + ".json";
        std::string output = exec(cmd.c_str());
        if (output.empty())
        {
            std::cerr << "[WARN]" << std::setw(4) << ""
                      << "Error Converting" << std::endl;
            return;
        }
        std::cout << "[INFO]" << std::setw(4) << ""
                  << "Conversion " << inputfile << " done!" << std::endl;
        return;
    }

}
