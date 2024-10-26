#ifndef __BTT_PARSER_HPP__
#define __BTT_PARSER_HPP__

/** inclusion of cxxopts argument parser */
#include "cxxopts.hpp"      

const   char    PROGRAM_NAME[]="bttManager";;
const   char    PROGRAM_DESC[]="Blint Test Tag Manager software";


class bttParser{
    private:
        cxxopts::Options options{PROGRAM_NAME, PROGRAM_DESC};

    public:
        bttParser() = delete;
        virtual ~bttParser() = default;

        bttParser(int argc, const char *argv[]);



};




#endif  /*  __BTT_PARSER_HPP__ */

