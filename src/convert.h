#include <cstdlib> // atof function 
#include <iostream>   // input and output
#include <fstream>
#include <string>

#include <ctime> // Import the ctime library


void compileLatexToPDF(const std::string&, const std::string&);
void convertPDFToPNG(const std::string&, const std::string&);
void cropPNG(const std::string&, const std::string&);
std::string convertDateToString();

void compileLatexToPDF(const std::string& latexCode, const std::string& outputTexPath, const std::string& outputGeneral) {
    std::ofstream texFile(outputTexPath);
    texFile << latexCode;
    texFile.close();

    std::string command = "pdflatex -output-directory=" + outputGeneral +  "  -interaction=nonstopmode " + outputTexPath;
    int result = std::system(command.c_str());
    std::cout << "debog 1111"<< result << std::endl;
    if (result != 0) {
        throw std::runtime_error("Failed to compile LaTeX to PDF.");
    }
}

void convertPDFToPNG(const std::string& pdfPath, const std::string& pngPath) {
    std::string command = "magick -density 300 " + pdfPath + " -quality 90 " + pngPath;
    int result = std::system(command.c_str());
    std::cout << "debog 2222" << std::endl;
    if (result != 0) {
        throw std::runtime_error("Failed to convert PDF to PNG.");
    }
}

void cropPNG(const std::string& inputPNGPath, const std::string& outputPNGPath) {
    std::string command = "magick " + inputPNGPath + " -trim +repage " + outputPNGPath;
    int result = std::system(command.c_str());
    std::cout << "debog 33333" << std::endl;
    if (result != 0) {
        throw std::runtime_error("Failed to crop PNG.");
    }
}

std::string convertDateToString() {
    time_t timestamp = std::time(nullptr);
    std::string myStr = std::asctime(std::localtime(&timestamp));

    myStr.erase(myStr.find_last_not_of("\n") + 1); // Remove trailing newline

    std::string stringDate;
    // Get a different random number each time the program runs
    srand(time(0));
    int randomNumber = rand() % 999;
    std::string s = std::to_string(randomNumber);

    for(char c : myStr) {
        if(c == ' ') {
            stringDate += "_";
        }
        else if (c == ':') {
            stringDate+= "-";
        }
        else {
            stringDate += c;
        }
    }
    return stringDate + s;
}
