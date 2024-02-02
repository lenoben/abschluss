#include "ModelFlow.hpp"

namespace gzTotzt
{

    bool decompressGzip(const std::string &inputFileName, std::string &outputData)
    {
        std::ifstream file(inputFileName, std::ios::binary);
        if (!file.is_open())
        {
            std::cerr << "Error opening input file: " << inputFileName << std::endl;
            return false;
        }

        // Read the compressed data
        std::stringstream compressedData;
        compressedData << file.rdbuf();
        file.close();

        const std::string &compressedString = compressedData.str();
        const size_t bufferSize = 4096;
        char buffer[bufferSize];

        z_stream zStream;
        zStream.zalloc = Z_NULL;
        zStream.zfree = Z_NULL;
        zStream.opaque = Z_NULL;
        zStream.avail_in = 0;
        zStream.next_in = Z_NULL;

        if (inflateInit2(&zStream, 16 + MAX_WBITS) != Z_OK)
        {
            std::cerr << "Error initializing zlib for decompression." << std::endl;
            return false;
        }

        zStream.avail_in = static_cast<uInt>(compressedString.size());
        zStream.next_in = reinterpret_cast<Bytef *>(const_cast<char *>(compressedString.c_str()));

        do
        {
            zStream.avail_out = bufferSize;
            zStream.next_out = reinterpret_cast<Bytef *>(buffer);

            if (inflate(&zStream, Z_NO_FLUSH) < 0)
            {
                std::cerr << "Error decompressing data." << std::endl;
                inflateEnd(&zStream);
                return false;
            }

            outputData.append(buffer, bufferSize - zStream.avail_out);

        } while (zStream.avail_out == 0);

        inflateEnd(&zStream);

        return true;
    }

    bool saveToFile(const std::string fileName, const std::string &data)
    {
        std::ofstream file(fileName);
        if (!file.is_open())
        {
            std::cerr << "Error opening output file: " << fileName << std::endl;
            return false;
        }

        file << data;
        file.close();
        return true;
    }
}