#include "bttParser.hpp"


bttParser::bttParser(int argc, char *argv[]):argc{argc},argv{argv}{

    cxxopts::value<std::string>()->default_value("");

    this->options.add_options()
        ("d,dump","Dump all file tags")
        ("h,help", "Print help")
        ("filename", "The filename to process", cxxopts::value<std::string>());

    this->options.parse_positional({"filename"});
    
    // Parse options the usual way
    this->result = this->options.parse(this->argc, this->argv);

    // Check file's existence
    this->setFileName(this->getStrResult("filename"));
    if (!std::filesystem::exists(this->getFileName())) throw bttParserFileNotFoundException{};

}

void    bttParser::processArgs(){
    if (result.count("help") > 0) {
        std::println("{}", options.help());
        return;
    }
}




