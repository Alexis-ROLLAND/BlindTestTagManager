#include "bttParser.hpp"


bttParser::bttParser(int argc, char *argv[]):argc{argc},argv{argv}{

    cxxopts::value<std::string>()->default_value("");

    this->options.add_options()
        (this->getCmdArg(arg_id_t::DUMP),this->getCmdDesc(arg_id_t::DUMP))
        (this->getCmdArg(arg_id_t::NO_SAVE),this->getCmdDesc(arg_id_t::NO_SAVE))
        (this->getCmdArg(arg_id_t::TITLE),this->getCmdDesc(arg_id_t::TITLE), cxxopts::value<std::string>()->implicit_value(""))
        (this->getCmdArg(arg_id_t::EXTRA_TITLE),this->getCmdDesc(arg_id_t::EXTRA_TITLE), cxxopts::value<std::string>()->implicit_value(""))
        (this->getCmdArg(arg_id_t::ARTIST),this->getCmdDesc(arg_id_t::ARTIST), cxxopts::value<std::string>()->implicit_value(""))
        (this->getCmdArg(arg_id_t::DATE),this->getCmdDesc(arg_id_t::DATE), cxxopts::value<int>()->implicit_value("9999"))

        (this->getCmdArg(arg_id_t::FILENAME),this->getCmdDesc(arg_id_t::FILENAME), cxxopts::value<std::string>());

    /**  Parse positionnal arguments    */
    this->options.parse_positional(this->getCmdArg(arg_id_t::FILENAME));
    
    /**  Parse options the usual way    */
    this->result = this->options.parse(this->argc, this->argv);
    
    /** Check file's existence  */ 
    this->setFileName(this->getStrResult(this->getCmdArg(arg_id_t::FILENAME)));
    if (!std::filesystem::exists(this->getFileName())) throw bttParserFileNotFoundException{};

    /** Create tagManager (RAII) */
    this->manager = std::make_unique<tagManager>(this->getFileName());

}

void    bttParser::processArgs(){
    std::string tmpString{};

    /** Dump tags  */
    if (this->count(this->getCmdArg(arg_id_t::DUMP))){
        this->manager->dump();
        exit(EXIT_SUCCESS);
    }

    /** Title management part */
    if (this->count(this->getCmdArg(arg_id_t::TITLE))){
        if (this->getStrResult(this->getCmdArg(arg_id_t::TITLE)) == ""){
            std::println("Titre (get) = {}",this->manager->getTitre());
        }
        else{
            this->manager->setTitre(this->getStrResult(this->getCmdArg(arg_id_t::TITLE)));
            this->setFileHasBeenChanged(true);
            std::println("Titre (set) = {}",this->manager->getTitre());
        }
    }

    /** Extra Title management part */
    if (this->count(this->getCmdArg(arg_id_t::EXTRA_TITLE))){
        if (this->getStrResult(this->getCmdArg(arg_id_t::EXTRA_TITLE)) == ""){
            std::println("Extra Titre (get) = {}",this->manager->getExtraTitle());
        }
        else{
            this->manager->setExtraTitle(this->getStrResult(this->getCmdArg(arg_id_t::EXTRA_TITLE)));
            this->setFileHasBeenChanged(true);
            std::println("Extra Titre (set) = {}",this->manager->getExtraTitle());
        }
    }

    /** Artist management part */
    if (this->count(this->getCmdArg(arg_id_t::ARTIST))){
        if (this->getStrResult(this->getCmdArg(arg_id_t::ARTIST)) == ""){
            std::println("Interprète (get) = {}",this->manager->getInterprete());
        }
        else{
            this->manager->setInterprete(this->getStrResult(this->getCmdArg(arg_id_t::ARTIST)));
            this->setFileHasBeenChanged(true);
            std::println("Interprète (set) = {}",this->manager->getInterprete());
        }
    }

    /** Date management part  */
     if (this->count(this->getCmdArg(arg_id_t::DATE))){
        if (this->getIntResult(this->getCmdArg(arg_id_t::DATE)) == 9999){
            std::println("Date (get) = {0:d}",this->manager->getDate());
        }
        else{
            this->manager->setDate(this->getIntResult(this->getCmdArg(arg_id_t::DATE)));
            this->setFileHasBeenChanged(true);
            std::println("Date (set) = {0:d}",this->manager->getDate());
        }
     
     }

    /** Updating file  */
    if (this->count(this->getCmdArg(arg_id_t::NO_SAVE))>0){
        std::println("Test mode - File {0:s} won't be written.",this->getFileName());
    }
    else if (this->hasFileChanged()){
        if (this->manager->update()){
            std::println("File succesfully written.");
        } 
        else{
            std::println("Error while writing the file.");
        }
    }

}











