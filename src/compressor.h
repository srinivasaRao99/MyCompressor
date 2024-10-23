// src/compressor.h
#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <string>

class Compressor {
public:
    bool compress(const std::string& inputFile, const std::string& outputFile);
    bool decompress(const std::string& inputFile, const std::string& outputFile);
private:
    bool compressZip(const std::string& inputFile, const std::string& outputFile);
    bool decompressZip(const std::string& inputFile, const std::string& outputFile);
};

#endif // COMPRESSOR_H
