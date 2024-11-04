#include <print>

#include "tagManager.hpp"


std::vector<std::string> charArrayToVector(char** array, int size) {
    std::vector<std::string> vec;
    for (int i = 0; i < size; ++i) {
        vec.push_back(std::string(array[i])); // Convertit char* en std::string
    }
    return vec;
}

bool    isMaskMatch(uint16_t value, uint16_t mask){
    return value & mask;
}

int main(int argc, char* argv[]){

    std::vector<std::string>    tabFiles = charArrayToVector(argv,argc);
    tabFiles.erase(tabFiles.begin());   /** Removes the first argument, exe filemane */

    for (const auto& arg : tabFiles ) {
        std::string cr{};
        std::print("File {} - ",arg);
        tagManager  myManager(arg);
        missingtagmask_t res = myManager.checkTags();
        if (res == 0x0000) cr="OK:No missing tag";
        else{
            cr="ERROR:";
            if (isMaskMatch(res, std::to_underlying(tagManager::btMissignTagMask::TITLE))) cr+="[TITLE],"; 
            if (isMaskMatch(res, std::to_underlying(tagManager::btMissignTagMask::ARTIST))) cr+="[ARTIST],";
            if (isMaskMatch(res, std::to_underlying(tagManager::btMissignTagMask::DATE))) cr+="[DATE],"; 
            if (isMaskMatch(res, std::to_underlying(tagManager::btMissignTagMask::LANGUAGE))) cr+="[LANGUE],"; 
            if (isMaskMatch(res, std::to_underlying(tagManager::btMissignTagMask::EXTRA))) cr+="[EXTRA],";
            if (isMaskMatch(res, std::to_underlying(tagManager::btMissignTagMask::EXTRA_TITLE))) cr+="[EXTRA_TITLE],"; 
            if (isMaskMatch(res, std::to_underlying(tagManager::btMissignTagMask::EXTRA_ARTIST))) cr+="[EXTRA_ARTIST],"; 
            if (isMaskMatch(res, std::to_underlying(tagManager::btMissignTagMask::EXTRA_DATE))) cr+="[EXTRA_DATE],";
            cr+=" are missing.";
        }
        std::println("{}",cr);
    }



}