#include "lib_bttManager.hpp"

const   char    PROGRAM_NAME[]="bttManager";;
const   char    PROGRAM_DESC[]="Blint Test Tag Manager software";

std::unique_ptr<bttParser> parser;

void initApp(int argc, char *argv[]){
    try{
        parser=std::make_unique<bttParser>(argc,argv);
    }
    catch(const cxxopts::exceptions::option_has_no_value &e){
        std::println(std::cerr,"ERROR:Filename was not provided");
        exit(EXIT_FAILURE);
    }
    catch(const cxxopts::exceptions::no_such_option &e){
        std::println(std::cerr,"ERROR:no such option ({})",e.what());
        exit(EXIT_FAILURE);
    }
    catch(const bttParserFileNotFoundException &e){
        std::println(std::cerr,"ERROR:File not found");
        exit(EXIT_FAILURE);  
    }
    catch(const cxxopts::exceptions::specification &e){
        std::println(std::cerr,"ERROR:Unregistered specification exception ({})",e.what());
        exit(EXIT_FAILURE);
    }
    catch(const cxxopts::exceptions::parsing &e){
        std::println(std::cerr,"ERROR:Unregistered parsing execption ({})",e.what());
        exit(EXIT_FAILURE);
    }
    catch(const bttParserHelpAskedException &e){
        exit(EXIT_SUCCESS);
    }

}

void runApp(){
    try{
        parser->processArgs();
    }
    catch(const TagNotInTheFileException &e){
        std::println(std::cerr,"ERROR:Tag ({}) is not int the file. use --force-create to force creation on en empty tag",e.tag);
    }
}




