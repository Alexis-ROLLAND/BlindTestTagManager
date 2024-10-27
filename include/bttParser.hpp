#ifndef __BTT_PARSER_HPP__
#define __BTT_PARSER_HPP__

#include <filesystem>
#include <print>

/** inclusion of cxxopts argument parser */
#include "cxxopts.hpp"      


class bttParserFileNotFoundException : public std::exception{};



const   char    PROGRAM_NAME[]="bttManager";;
const   char    PROGRAM_DESC[]="Blint Test Tag Manager software";

class bttParser{
    private:
        cxxopts::Options options{PROGRAM_NAME, PROGRAM_DESC};
        cxxopts::ParseResult    result;

        int argc;
        char **argv;

        std::string filename{};
                
        void    setFileName(const std::string &fname) noexcept {this->filename = fname;};

        std::size_t count(const std::string &arg) noexcept {return this->result.count(arg);};
        std::string getStrResult(const std::string &arg) {return this->result[arg].as<std::string>();};
        

    public:
        bttParser() = delete;
        virtual ~bttParser() = default;

        bttParser(int argc, char *argv[]);

        std::string getFileName() noexcept {return this->filename;};

        void    processArgs();

};




#endif  /*  __BTT_PARSER_HPP__ */

