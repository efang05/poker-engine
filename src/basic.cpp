#include <iostream>
#include <fstream>

int main() {
    // Define the file path
    const char* filePath = "test_output.txt";

    // Open a file in write mode (this will create the file if it does not exist)
    std::ofstream outFile(filePath);
    if (!outFile) {
        std::cerr << "Error: Could not open the file for writing!" << std::endl;
        return 1;
    }

    // Write some text to the file
    outFile << "Hello, this is a test." << std::endl;

    // Close the file
    outFile.close();

    // Open the file in read mode
    std::ifstream inFile(filePath);
    if (!inFile) {
        std::cerr << "Error: Could not open the file for reading!" << std::endl;
        return 1;
    }

    // Read the text from the file
    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }

    // Close the file
    inFile.close();

    return 0;
}
