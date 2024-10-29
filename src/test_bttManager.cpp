#include <print>

#include "tagManager.hpp"
#include "bttParser.hpp"


int main(int argc, char* argv[]){

    bttParser   parser{argc,argv};

    parser.processArgs();



    return EXIT_SUCCESS;
}

