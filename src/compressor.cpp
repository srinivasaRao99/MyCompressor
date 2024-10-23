#include "compressor.h"
#include <miniz.h>
#include <fstream>
#include <iostream>
#include <vector>

bool Compressor::compress(const std::string& inputFile, const std::string& outputFile) {
    // Call ZIP compression
    return compressZip(inputFile, outputFile);
}

bool Compressor::decompress(const std::string& inputFile, const std::string& outputFile) {
    // Call ZIP decompression
    return decompressZip(inputFile, outputFile);
}

bool Compressor::compressZip(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening input file for compression: " << inputFile << std::endl;
        return false;
    }

    mz_zip_archive zipArchive;
    memset(&zipArchive, 0, sizeof(zipArchive));

    if (!mz_zip_writer_init_file(&zipArchive, outputFile.c_str(), 0)) {
        std::cerr << "Error initializing ZIP archive for writing!" << std::endl;
        return false;
    }

    std::vector<char> buffer((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    if (!mz_zip_writer_add_mem(&zipArchive, inputFile.c_str(), buffer.data(), buffer.size(), MZ_DEFAULT_COMPRESSION)) {
        std::cerr << "Error adding file to ZIP archive!" << std::endl;
        mz_zip_writer_end(&zipArchive);
        return false;
    }

    mz_zip_writer_finalize_archive(&zipArchive);
    mz_zip_writer_end(&zipArchive);
    return true;
}

bool Compressor::decompressZip(const std::string& inputFile, const std::string& outputFile) {
    mz_zip_archive zipArchive;
    memset(&zipArchive, 0, sizeof(zipArchive));

    if (!mz_zip_reader_init_file(&zipArchive, inputFile.c_str(), 0)) {
        std::cerr << "Error opening ZIP archive for reading: " << inputFile << std::endl;
        return false;
    }

    mz_zip_archive_file_stat fileStat;
    if (!mz_zip_reader_file_stat(&zipArchive, 0, &fileStat)) {
        std::cerr << "Error getting file information from ZIP archive!" << std::endl;
        mz_zip_reader_end(&zipArchive);
        return false;
    }

    std::vector<char> buffer(fileStat.m_uncompressed_size);
    if (!mz_zip_reader_extract_to_mem(&zipArchive, 0, buffer.data(), buffer.size(), 0)) {
        std::cerr << "Error extracting file from ZIP archive!" << std::endl;
        mz_zip_reader_end(&zipArchive);
        return false;
    }

    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening output file for decompression: " << outputFile << std::endl;
        mz_zip_reader_end(&zipArchive);
        return false;
    }

    outFile.write(buffer.data(), buffer.size());
    mz_zip_reader_end(&zipArchive);
    return true;
}
