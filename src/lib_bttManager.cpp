#include "lib_bttManager.hpp"

cxxopts::Options options("bttManager","Tag manager for Blind Test files");


void initApp(){
    options.add_options()
        ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
        ("l,list", "List registered tags")
        ("filename","Filename of the music file to process", cxxopts::value<std::string>());
        
    
    options.parse_positional({"filename"});

}

void    parseInput(int argc, char *argv[]){
    try{
        
        auto result = options.parse(argc,argv);
        bool Verbose = result.count("v");

        if (Verbose) std::println("-- Verbose output --");
        std::string FileName = result["filename"].as<std::string>();
        
        if (Verbose) std::println("FileName : {}",FileName);

        if (result.count("list")) listTags();
    }
    catch(const cxxopts::exceptions::exception &e){
        std::println(std::cerr,"An error occured : {}",e.what());
        throw;
    }
}


void    listTags(){
    std::println("Taglist");
}





