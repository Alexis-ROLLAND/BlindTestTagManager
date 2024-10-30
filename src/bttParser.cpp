#include "bttParser.hpp"




//----------------------------------------------------------------------------
bttParser::bttParser(int argc, char *argv[]):argc{argc},argv{argv}{

    cxxopts::value<std::string>()->default_value("");

    /** Adding options (arguments) */
    this->options.add_options()
        /** arguments with no values */
        (this->getCmdArg(arg_id_t::HELP),this->getCmdDesc(arg_id_t::HELP))
        (this->getCmdArg(arg_id_t::DUMP),this->getCmdDesc(arg_id_t::DUMP))
        (this->getCmdArg(arg_id_t::NO_SAVE),this->getCmdDesc(arg_id_t::NO_SAVE))
        (this->getCmdArg(arg_id_t::FORCE_CREATE),this->getCmdDesc(arg_id_t::FORCE_CREATE))
        (this->getCmdArg(arg_id_t::GET_PERIOD),this->getCmdDesc(arg_id_t::GET_PERIOD))
        (this->getCmdArg(arg_id_t::GET_EXTRA_PERIOD),this->getCmdDesc(arg_id_t::GET_EXTRA_PERIOD))

        /** arguments with string values */
        (this->getCmdArg(arg_id_t::TITLE),this->getCmdDesc(arg_id_t::TITLE), cxxopts::value<std::string>()->implicit_value(""))
        (this->getCmdArg(arg_id_t::EXTRA_TITLE),this->getCmdDesc(arg_id_t::EXTRA_TITLE), cxxopts::value<std::string>()->implicit_value(""))
        (this->getCmdArg(arg_id_t::ARTIST),this->getCmdDesc(arg_id_t::ARTIST), cxxopts::value<std::string>()->implicit_value(""))
        (this->getCmdArg(arg_id_t::IS_MOVIE),this->getCmdDesc(arg_id_t::IS_MOVIE), cxxopts::value<std::string>()->implicit_value(""))
        (this->getCmdArg(arg_id_t::IS_TVSHOW),this->getCmdDesc(arg_id_t::IS_TVSHOW), cxxopts::value<std::string>()->implicit_value(""))
        (this->getCmdArg(arg_id_t::IS_MASTERPIECE),this->getCmdDesc(arg_id_t::IS_MASTERPIECE), cxxopts::value<std::string>()->implicit_value(""))
        (this->getCmdArg(arg_id_t::IS_SBIG),this->getCmdDesc(arg_id_t::IS_SBIG), cxxopts::value<std::string>()->implicit_value(""))

        /** arguments with integer values */
        (this->getCmdArg(arg_id_t::DATE),this->getCmdDesc(arg_id_t::DATE), cxxopts::value<int>()->implicit_value("9999"))
        (this->getCmdArg(arg_id_t::EXTRA_DATE),this->getCmdDesc(arg_id_t::EXTRA_DATE), cxxopts::value<int>()->implicit_value("9999"))

        /** Usefull arguments/commands */
        (this->getCmdArg(arg_id_t::DELETE_TAG),this->getCmdDesc(arg_id_t::DELETE_TAG), cxxopts::value<std::string>()->implicit_value(""))

        /** positionnal argument (filename) */
        (this->getCmdArg(arg_id_t::FILENAME),this->getCmdDesc(arg_id_t::FILENAME), cxxopts::value<std::string>());
    /** END making options structure */
    

    /**  Parse positionnal arguments    */
    this->options.parse_positional(this->getCmdArg(arg_id_t::FILENAME));
    
    /**  Parse options the usual way    */
    this->result = this->options.parse(this->argc, this->argv);
    
    /** Is the help argument provided ? */
    if (this->count(this->getCmdArg(arg_id_t::HELP))) {
        this->help_handler();   /** throws bttParserHelpAskedException  exception */
    }
    
    /** Try to get filename from CLI */
    this->setFileName(this->getStrResult(this->getCmdArg(arg_id_t::FILENAME))); /** throws cxxopts::exceptions::no_such_option if option is not set */
    
    /** Check file's existence  */ 
    if (!std::filesystem::exists(this->getFileName())) throw bttParserFileNotFoundException{};
        
    /** Create tagManager (RAII) */
    this->manager = std::make_unique<tagManager>(this->getFileName());
}
//----------------------------------------------------------------------------
void    bttParser::processArgs(){
    std::string tmpString{};
    if (this->count(this->getCmdArg(arg_id_t::DUMP))) this->dump_handler(); /** Dump tags  */
    if (this->count(this->getCmdArg(arg_id_t::FORCE_CREATE))) this->force_create_handler(); /** Dump tags  */
    if (this->count(this->getCmdArg(arg_id_t::DELETE_TAG))) this->delete_tag_handler(); /** Deletes a tag */
    if (this->count(this->getCmdArg(arg_id_t::GET_PERIOD))) this->get_period_handler(); /** get-period management part */
    if (this->count(this->getCmdArg(arg_id_t::GET_EXTRA_PERIOD))) this->get_extra_period_handler(); /** get-extra-period management part */
    if (this->count(this->getCmdArg(arg_id_t::TITLE))) this->title_handler();   /** Title management part */
    if (this->count(this->getCmdArg(arg_id_t::EXTRA_TITLE))) this->extra_title_handler();   /** Extra Title management part */
    if (this->count(this->getCmdArg(arg_id_t::ARTIST))) this->artist_handler(); /** Artist management part */
    if (this->count(this->getCmdArg(arg_id_t::LANGUAGE))) this->language_handler(); /** Language management part */
    if (this->count(this->getCmdArg(arg_id_t::IS_MOVIE))) this->ismovie_handler();  /** ismovie management part */
    if (this->count(this->getCmdArg(arg_id_t::IS_TVSHOW))) this->istvshow_handler();    /** istvshow management part */
    if (this->count(this->getCmdArg(arg_id_t::IS_MASTERPIECE))) this->ismasterpiece_handler();  /** ismasterpiece management part */
    if (this->count(this->getCmdArg(arg_id_t::IS_SBIG))) this->issbig_handler();    /** issbig management part */
    if (this->count(this->getCmdArg(arg_id_t::DATE))) this->date_handler(); /** Date management part  */
    if (this->count(this->getCmdArg(arg_id_t::EXTRA_DATE))) this->extra_date_handler(); /** Extra-Date management part  */

    
    /** Updating file ? */
    this->update_handler();
}
//----------------------------------------------------------------------------
/** local Handlers */
//----------------------------------------------------------------------------
void    bttParser::help_handler(){
    std::println(std::cout,"{}",options.help());
    throw bttParserHelpAskedException{};    
}
//----------------------------------------------------------------------------
void    bttParser::dump_handler(){
    this->manager->dump();
    exit(EXIT_SUCCESS);
}
//----------------------------------------------------------------------------
void    bttParser::force_create_handler(){
    this->setForceCreate();
}
//----------------------------------------------------------------------------
void    bttParser::get_period_handler(){
    std::string tmpString{};
    bool error{false};

    switch(this->manager->getPeriod(this->getForceCreate())){
        case tagManager::btPeriod::OLDIES : tmpString="OLDIES";break;
        case tagManager::btPeriod::SEVENTIES : tmpString="SEVENTIES";break;
        case tagManager::btPeriod::EIGHTIES : tmpString="EIGHTIES";break;
        case tagManager::btPeriod::NINETIES : tmpString="NINETIES";break;
        case tagManager::btPeriod::MILLENIUM : tmpString="MILLENIUM";break;
        case tagManager::btPeriod::NOVELTY : tmpString="NOVELTY";break;
        case tagManager::btPeriod::INVALID : tmpString="INVALID";break;
        default : tmpString = "ERROR:PERIOD ERROR";error = true;break;
    }

    if (!error) {
        std::println(std::cout,"Period=[{}]",tmpString);
        this->setFileHasBeenChanged(this->manager->gettagsHaveChanged());
    }
    else std::println(std::cerr,"{}",tmpString);
}
//----------------------------------------------------------------------------
void    bttParser::get_extra_period_handler(){
    std::string tmpString{};
    bool error{false};
    switch(this->manager->getExtraPeriod(this->getForceCreate())){
        case tagManager::btPeriod::OLDIES : tmpString="OLDIES";break;
        case tagManager::btPeriod::SEVENTIES : tmpString="SEVENTIES";break;
        case tagManager::btPeriod::EIGHTIES : tmpString="EIGHTIES";break;
        case tagManager::btPeriod::NINETIES : tmpString="NINETIES";break;
        case tagManager::btPeriod::MILLENIUM : tmpString="MILLENIUM";break;
        case tagManager::btPeriod::NOVELTY : tmpString="NOVELTY";break;
        default : tmpString = "ERROR:EXTRA PERIOD ERROR";error = true;break;
    }
    if (!error) {
        std::println(std::cout,"Extra-Period=[{}]",tmpString);
        this->setFileHasBeenChanged(this->manager->gettagsHaveChanged());
    }
    else std::println(std::cerr,"{}",tmpString);
}
//----------------------------------------------------------------------------
void    bttParser::title_handler(){
    
    if (this->getStrResult(this->getCmdArg(arg_id_t::TITLE)) == ""){
        std::println(std::cout,"Titre=[{}]",this->manager->getTitre(this->getForceCreate()));
        if (this->getForceCreate()) this->setFileHasBeenChanged(true);
    }
    else{
        this->manager->setTitre(this->getStrResult(this->getCmdArg(arg_id_t::TITLE)));
        this->setFileHasBeenChanged(true);
        std::println(std::cout,"OK:Titre set to [{}]",this->manager->getTitre(this->getForceCreate()));
    }
}
//----------------------------------------------------------------------------
void    bttParser::extra_title_handler(){

    if (this->getStrResult(this->getCmdArg(arg_id_t::EXTRA_TITLE)) == ""){
        std::println(std::cout,"ExtraTitre=[{}]",this->manager->getExtraTitle(this->getForceCreate()));
        if (this->getForceCreate()) this->setFileHasBeenChanged(true);
    }
    else{
        this->manager->setExtraTitle(this->getStrResult(this->getCmdArg(arg_id_t::EXTRA_TITLE)));
        this->setFileHasBeenChanged(true);
        std::println(std::cout,"OK:ExtraTitre set to [{}]",this->manager->getExtraTitle(this->getForceCreate()));
    }
}
//----------------------------------------------------------------------------
void    bttParser::artist_handler(){
    if (this->getStrResult(this->getCmdArg(arg_id_t::ARTIST)) == ""){
        std::println(std::cout,"Interprete=[{}]",this->manager->getInterprete(this->getForceCreate()));
        if (this->getForceCreate()) this->setFileHasBeenChanged(true);
    }
    else{
        this->manager->setInterprete(this->getStrResult(this->getCmdArg(arg_id_t::ARTIST)));
        this->setFileHasBeenChanged(true);
        std::println(std::cout,"OK:Interprète set to [{}]",this->manager->getInterprete(this->getForceCreate()));
    }
}
//----------------------------------------------------------------------------
void    bttParser::language_handler(){
    std::string tmpString{};
    tagManager::btLanguage Language;
    
    if (this->getStrResult(this->getCmdArg(arg_id_t::LANGUAGE)) == ""){
        Language = this->manager->getLangue(this->getForceCreate());
        if (this->getForceCreate()) this->setFileHasBeenChanged(true);
        switch(Language){
            case tagManager::btLanguage::FRA : std::println(std::cout,"Language=[FRA]");break;
            case tagManager::btLanguage::INT : std::println(std::cout,"Language=[INT]");break;    
            default : std::println(std::cerr,"ERROR:LANGUAGE ERROR");break;
        }
    }
    else{
        tmpString = this->getStrResult(this->getCmdArg(arg_id_t::LANGUAGE));
        if (tmpString == "FRA") {
            this->manager->setLangue(tagManager::btLanguage::FRA);
            std::println(std::cout,"OK:Language set to [FRA]");
            this->setFileHasBeenChanged(true);
        }
        else if (tmpString == "INT") {
            this->manager->setLangue(tagManager::btLanguage::INT);
            std::println(std::cout,"OK:Language set to [INT]");
            this->setFileHasBeenChanged(true);
        }
        else std::println(std::cerr,"ERROR:LANGUAGE SET ERROR");
    }   
}
//----------------------------------------------------------------------------
void    bttParser::ismovie_handler(){
    std::string tmpString{};

    if (this->getStrResult(this->getCmdArg(arg_id_t::IS_MOVIE)) == ""){
        if (this->manager->isMovieSoundTrack(this->getForceCreate()) == true) std::println(std::cout,"ismovie=YES");
        else std::println(std::cout,"ismovie=NO");
        this->setFileHasBeenChanged(this->manager->gettagsHaveChanged());
    }
    else{
        tmpString = this->getStrResult(this->getCmdArg(arg_id_t::IS_MOVIE));
        if (tmpString == "YES"){
            this->manager->setMovieSoundTrackFlag(true);
            std::println(std::cout,"OK:ISMOVIE flag set to 1");
            this->setFileHasBeenChanged(true);
        }
        else if (tmpString == "NO"){
            this->manager->setMovieSoundTrackFlag(false);
            std::println(std::cout,"OK:ISMOVIE flag set to 0");
            this->setFileHasBeenChanged(true);  
        }
        else std::println(std::cerr,"ERROR:ISMOVIE SET ERROR");
    }
}
//----------------------------------------------------------------------------
void    bttParser::istvshow_handler(){
    std::string tmpString{};

    if (this->getStrResult(this->getCmdArg(arg_id_t::IS_TVSHOW)) == ""){
        if (this->manager->isTvShow(this->getForceCreate()) == true) std::println(std::cout,"istvshow=YES");
        else std::println(std::cout,"istvshow=NO");
        this->setFileHasBeenChanged(this->manager->gettagsHaveChanged());
    }
    else{
        tmpString = this->getStrResult(this->getCmdArg(arg_id_t::IS_TVSHOW));
        if (tmpString == "YES"){
            this->manager->setTvShowFlag(true);
            std::println(std::cout,"OK:ISTVSHOW flag set to 1");
            this->setFileHasBeenChanged(true);
        }
        else if (tmpString == "NO"){
            this->manager->setTvShowFlag(false);
            std::println(std::cout,"OK:ISTVSHOW flag set to 0");
            this->setFileHasBeenChanged(true);  
        }
        else std::println(std::cerr,"ERROR:ISTVSHOW SET ERROR");
    }
}
//----------------------------------------------------------------------------
void    bttParser::ismasterpiece_handler(){
    std::string tmpString{};
   
    if (this->getStrResult(this->getCmdArg(arg_id_t::IS_MASTERPIECE)) == ""){
        if (this->manager->isMasterPiece(this->getForceCreate()) == true) std::println(std::cout,"ismasterpiece=YES");
        else std::println(std::cout,"ismasterpiece=NO");
        this->setFileHasBeenChanged(this->manager->gettagsHaveChanged());
    }
    else{
        tmpString = this->getStrResult(this->getCmdArg(arg_id_t::IS_MASTERPIECE));
        if (tmpString == "YES"){
            this->manager->setMasterPieceFlag(true);
            std::println(std::cout,"OK:ISMASTERPICE flag set to 1");
            this->setFileHasBeenChanged(true);
        }
        else if (tmpString == "NO"){
            this->manager->setMasterPieceFlag(false);
            std::println(std::cout,"OK:ISMASTERPIECE flag set to 0");
            this->setFileHasBeenChanged(true);  
        }
        else std::println(std::cerr,"ERROR:ISMASTERPIECE SET ERROR");
    }
}
//----------------------------------------------------------------------------
void    bttParser::issbig_handler(){
    std::string tmpString{};

    if (this->getStrResult(this->getCmdArg(arg_id_t::IS_SBIG)) == ""){
        if (this->manager->isSbig(this->getForceCreate()) == true) std::println(std::cout,"issbig=YES");
        else std::println(std::cout,"issbig=NO");
        this->setFileHasBeenChanged(this->manager->gettagsHaveChanged());
    }
    else{
        tmpString = this->getStrResult(this->getCmdArg(arg_id_t::IS_SBIG));
        if (tmpString == "YES"){
            this->manager->setSbigFlag(true);
            std::println(std::cout,"OK:ISSBIG flag set to 1");
            this->setFileHasBeenChanged(true);
        }
        else if (tmpString == "NO"){
            this->manager->setSbigFlag(false);
            std::println(std::cout,"OK:ISSBIG flag set to 0");
            this->setFileHasBeenChanged(true);  
        }
        else std::println(std::cerr,"ERROR:ISSBIG SET ERROR");
    }
}
//----------------------------------------------------------------------------
void    bttParser::date_handler(){
    if (this->getIntResult(this->getCmdArg(arg_id_t::DATE)) == 9999){
        std::println(std::cout,"Date=[{0:d}]",this->manager->getDate(this->getForceCreate()));
        if (this->getForceCreate()) this->setFileHasBeenChanged(true);
    }
    else{
        this->manager->setDate(this->getIntResult(this->getCmdArg(arg_id_t::DATE)));
        this->setFileHasBeenChanged(true);
        std::println(std::cout,"OK:Date set to [{0:d}]",this->manager->getDate(false));
    }
}
//----------------------------------------------------------------------------
void    bttParser::extra_date_handler(){

    if (this->getIntResult(this->getCmdArg(arg_id_t::EXTRA_DATE)) == 9999){
        std::println("ExtraDate=[{0:d}]",this->manager->getExtraDate(this->getForceCreate()));
        if (this->getForceCreate()) this->setFileHasBeenChanged(true);
    }
    else{
        this->manager->setExtraDate(this->getIntResult(this->getCmdArg(arg_id_t::EXTRA_DATE)));
        this->setFileHasBeenChanged(true);
        std::println("OK:Extra-Date set to [{0:d}]",this->manager->getExtraDate(false));
    }
}
//----------------------------------------------------------------------------
void    bttParser::delete_tag_handler(){
    std::string tag{};
    tag = this->getStrResult(this->getCmdArg(arg_id_t::DELETE_TAG));
    this->manager->deleteTag(tag);
    this->setFileHasBeenChanged(true);
}
//----------------------------------------------------------------------------
void    bttParser::update_handler(){
    if (this->count(this->getCmdArg(arg_id_t::NO_SAVE))>0) {
        std::println(std::cout,"INFO:Test mode - File {0:s} won't be written.",this->getFileName());
    }
    else if (this->hasFileChanged()){
        if (this->manager->update()){
            std::println(std::cout,"OK:File succesfully written.");
        } 
        else{
            std::println(std::cerr,"ERROR:Error while writing the file.");
        }
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------






