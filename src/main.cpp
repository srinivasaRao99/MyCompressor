#include <iostream>
#include <string>
#include "compressor.h"

void printHelp() {
    std::cout << "Usage:\n";
    std::cout << "compress <input_file> <output_file.zip> - Compress a file to ZIP format\n";
    std::cout << "decompress <input_file.zip> <output_file> - Decompress a ZIP file\n";
    std::cout << "help - Show this help message\n";
    std::cout << "exit - Exit the application\n";
}

int main() {
    Compressor compressor;
    std::string command, inputFile, outputFile;

    std::cout << "Welcome to MyCompressor! Type 'help' for commands.\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        } else if (command == "help") {
            printHelp();
        } else {
            std::istringstream iss(command);
            std::string action;
            iss >> action >> inputFile >> outputFile;

            if (action == "compress") {
                if (compressor.compress(inputFile, outputFile)) {
                    std::cout << "File compressed successfully to " << outputFile << "!\n";
                }
            } else if (action == "decompress") {
                if (compressor.decompress(inputFile, outputFile)) {
                    std::cout << "File decompressed successfully to " << outputFile << "!\n";
                }
            } else {
                std::cout << "Unknown command! Type 'help' for available commands.\n";
            }
        }
    }

    return 0;
}
