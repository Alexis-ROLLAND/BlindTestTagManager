/** inclusion of cxxopts argument parser */
#include "cxxopts.hpp"      

#include "lib_bttManager.hpp"

cxxopts::Options options("dumpTags","Tags viewer for Blind Test files");

int main(int argc, char *argv[]) {
    options.add_options()
        ("filename","Filename of the music file to process", cxxopts::value<std::string>());
        
    
    options.parse_positional({"filename"});
    auto result = options.parse(argc,argv);

    tagManager  myManager(result["filename"].as<std::string>());

    myManager.dump();


    return 0;
}

