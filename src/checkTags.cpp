#include <print>

#include "tagManager.hpp"


std::vector<std::string> charArrayToVector(char** array, int size) {
    std::vector<std::string> vec;
    for (int i = 0; i < size; ++i) {
        vec.push_back(std::string(array[i])); // Convertit char* en std::string
    }
    return vec;
}

int main(int argc, char* argv[]){

    std::vector<std::string>    tabFiles = charArrayToVector(argv,argc);
    tabFiles.erase(tabFiles.begin());   /** Removes the first argument, exe filemane */

    for (const auto& arg : tabFiles ) std::println("{}",arg);



}