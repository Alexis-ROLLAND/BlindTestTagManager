#include "bttParser.hpp"

//----------------------------------------------------------------------------
bttParser::bttParser(int argc, char *argv[]):argc{argc},argv{argv}{

    cxxopts::value<std::string>()->default_value("");

    
    this->options.add_options()
        /** arguments with no values */
        (this->getCmdArg(arg_id_t::HELP),this->getCmdDesc(arg_id_t::HELP))
        (this->getCmdArg(arg_id_t::DUMP),this->getCmdDesc(arg_id_t::DUMP))
        (this->getCmdArg(arg_id_t::NO_SAVE),this->getCmdDesc(arg_id_t::NO_SAVE))
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
        
        /** positionnal argument (filename) */
        (this->getCmdArg(arg_id_t::FILENAME),this->getCmdDesc(arg_id_t::FILENAME), cxxopts::value<std::string>());

    

    /**  Parse positionnal arguments    */
    this->options.parse_positional(this->getCmdArg(arg_id_t::FILENAME));
    
    
    /**  Parse options the usual way    */
    this->result = this->options.parse(this->argc, this->argv);
    std::println("standard Options parsed");

    /** Is the help argument provided ? */
    auto    nbhelp = this->count(this->getCmdArg(arg_id_t::HELP)); 
    std::println("Number of help options : {}",nbhelp);

    if (this->count(this->getCmdArg(arg_id_t::HELP))) {
        std::println("Calling help handler");
        this->help_handler();
    }
    

    /** Check file's existence  */ 
    //this->setFileName(this->getStrResult(this->getCmdArg(arg_id_t::FILENAME)));
    //if (!std::filesystem::exists(this->getFileName())) throw bttParserFileNotFoundException{};

    /** Create tagManager (RAII) */
    //this->manager = std::make_unique<tagManager>(this->getFileName());
}
//----------------------------------------------------------------------------
void    bttParser::processArgs(){
    std::string tmpString{};
    if (this->count(this->getCmdArg(arg_id_t::DUMP))) this->dump_handler(); /** Dump tags  */
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
    std::println(std::cout,"Help handler");
    std::println(std::cout,"{}",options.help());
    //exit(EXIT_SUCCESS);    
}
//----------------------------------------------------------------------------
void    bttParser::dump_handler(){
    this->manager->dump();
    exit(EXIT_SUCCESS);
}
//----------------------------------------------------------------------------
void    bttParser::get_period_handler(){
    std::string tmpString{};
    switch(this->manager->getPeriod()){
        case tagManager::btPeriod::OLDIES : tmpString="OLDIES";break;
        case tagManager::btPeriod::SEVENTIES : tmpString="SEVENTIES";break;
        case tagManager::btPeriod::EIGHTIES : tmpString="EIGHTIES";break;
        case tagManager::btPeriod::NINETIES : tmpString="NINETIES";break;
        case tagManager::btPeriod::MILLENIUM : tmpString="MILLENIUM";break;
        case tagManager::btPeriod::NOVELTY : tmpString="NOVELTY";break;
        default : tmpString = "PERIOD ERROR";break;
    }
    std::println("Period = {}",tmpString);
}
//----------------------------------------------------------------------------
void    bttParser::get_extra_period_handler(){
    std::string tmpString{};
    switch(this->manager->getExtraPeriod()){
        case tagManager::btPeriod::OLDIES : tmpString="OLDIES";break;
        case tagManager::btPeriod::SEVENTIES : tmpString="SEVENTIES";break;
        case tagManager::btPeriod::EIGHTIES : tmpString="EIGHTIES";break;
        case tagManager::btPeriod::NINETIES : tmpString="NINETIES";break;
        case tagManager::btPeriod::MILLENIUM : tmpString="MILLENIUM";break;
        case tagManager::btPeriod::NOVELTY : tmpString="NOVELTY";break;
        default : tmpString = "EXTRA PERIOD ERROR";break;
    }
    std::println("Extra-Period = {}",tmpString);
    
}
//----------------------------------------------------------------------------
void    bttParser::title_handler(){
    
    if (this->getStrResult(this->getCmdArg(arg_id_t::TITLE)) == ""){
        std::println("Titre (get) = {}",this->manager->getTitre());
    }
    else{
        this->manager->setTitre(this->getStrResult(this->getCmdArg(arg_id_t::TITLE)));
        this->setFileHasBeenChanged(true);
        std::println("Titre (set) = {}",this->manager->getTitre());
    }
    
}
//----------------------------------------------------------------------------
void    bttParser::extra_title_handler(){

    if (this->getStrResult(this->getCmdArg(arg_id_t::EXTRA_TITLE)) == ""){
        std::println("Extra Titre (get) = {}",this->manager->getExtraTitle());
    }
    else{
        this->manager->setExtraTitle(this->getStrResult(this->getCmdArg(arg_id_t::EXTRA_TITLE)));
        this->setFileHasBeenChanged(true);
        std::println("Extra Titre (set) = {}",this->manager->getExtraTitle());
    }
}
//----------------------------------------------------------------------------
void    bttParser::artist_handler(){
    if (this->getStrResult(this->getCmdArg(arg_id_t::ARTIST)) == ""){
        std::println("Interprète (get) = {}",this->manager->getInterprete());
    }
    else{
        this->manager->setInterprete(this->getStrResult(this->getCmdArg(arg_id_t::ARTIST)));
        this->setFileHasBeenChanged(true);
        std::println("Interprète (set) = {}",this->manager->getInterprete());
    }
}
//----------------------------------------------------------------------------
void    bttParser::language_handler(){
    std::string tmpString{};
    tagManager::btLanguage Language;
    
    if (this->getStrResult(this->getCmdArg(arg_id_t::LANGUAGE)) == ""){
        Language = this->manager->getLangue();
        switch(Language){
            case tagManager::btLanguage::FRA : std::println("Language (get) = FRA");break;
            case tagManager::btLanguage::INT : std::println("Language (get) = INT");break;    
            default : std::println("LANGUAGE ERROR");break;
        }
        
    }
    else{
        tmpString = this->getStrResult(this->getCmdArg(arg_id_t::LANGUAGE));
        if (tmpString == "FRA") {
            this->manager->setLangue(tagManager::btLanguage::FRA);
            std::println("Language set to FRA");
            this->setFileHasBeenChanged(true);
        }
        else if (tmpString == "INT") {
            this->manager->setLangue(tagManager::btLanguage::INT);
            std::println("Language set to INT");
            this->setFileHasBeenChanged(true);
        }
        else std::println("LANGUAGE SET ERROR");
    }   
}
//----------------------------------------------------------------------------
void    bttParser::ismovie_handler(){
    std::string tmpString{};

    if (this->getStrResult(this->getCmdArg(arg_id_t::IS_MOVIE)) == ""){
        if (this->manager->isMovieSoundTrack() == true) std::println("ismovie = YES");
        else std::println("ismovie = NO");
    }
    else{
        tmpString = this->getStrResult(this->getCmdArg(arg_id_t::IS_MOVIE));
        if (tmpString == "YES"){
            this->manager->setMovieSoundTrackFlag(true);
            std::println("ISMOVIE flag set to 1");
            this->setFileHasBeenChanged(true);
        }
        else if (tmpString == "NO"){
            this->manager->setMovieSoundTrackFlag(false);
            std::println("ISMOVIE flag set to 0");
            this->setFileHasBeenChanged(true);  
        }
        else std::println("ISMOVIE SET ERROR");
    }
}
//----------------------------------------------------------------------------
void    bttParser::istvshow_handler(){
    std::string tmpString{};

    if (this->getStrResult(this->getCmdArg(arg_id_t::IS_TVSHOW)) == ""){
        if (this->manager->isTvShow() == true) std::println("istvshow = YES");
        else std::println("istvshow = NO");
    }
    else{
        tmpString = this->getStrResult(this->getCmdArg(arg_id_t::IS_TVSHOW));
        if (tmpString == "YES"){
            this->manager->setTvShowFlag(true);
            std::println("ISTVSHOW flag set to 1");
            this->setFileHasBeenChanged(true);
        }
        else if (tmpString == "NO"){
            this->manager->setTvShowFlag(false);
            std::println("ISTVSHOW flag set to 0");
            this->setFileHasBeenChanged(true);  
        }
        else std::println("ISTVSHOW SET ERROR");
    }
}
//----------------------------------------------------------------------------
void    bttParser::ismasterpiece_handler(){
    std::string tmpString{};
   
    if (this->getStrResult(this->getCmdArg(arg_id_t::IS_MASTERPIECE)) == ""){
        if (this->manager->isMasterPiece() == true) std::println("ismasterpiece = YES");
        else std::println("ismasterpiece = NO");
    }
    else{
        tmpString = this->getStrResult(this->getCmdArg(arg_id_t::IS_MASTERPIECE));
        if (tmpString == "YES"){
            this->manager->setMasterPieceFlag(true);
            std::println("ISMASTERPICE flag set to 1");
            this->setFileHasBeenChanged(true);
        }
        else if (tmpString == "NO"){
            this->manager->setMasterPieceFlag(false);
            std::println("ISMASTERPIECE flag set to 0");
            this->setFileHasBeenChanged(true);  
        }
        else std::println("ISMASTERPIECE SET ERROR");
    }
}
//----------------------------------------------------------------------------
void    bttParser::issbig_handler(){
    std::string tmpString{};

    if (this->getStrResult(this->getCmdArg(arg_id_t::IS_SBIG)) == ""){
        if (this->manager->isSbig() == true) std::println("issbig = YES");
        else std::println("issbig = NO");
    }
    else{
        tmpString = this->getStrResult(this->getCmdArg(arg_id_t::IS_SBIG));
        if (tmpString == "YES"){
            this->manager->setSbigFlag(true);
            std::println("ISSBIG flag set to 1");
            this->setFileHasBeenChanged(true);
        }
        else if (tmpString == "NO"){
            this->manager->setSbigFlag(false);
            std::println("ISSBIG flag set to 0");
            this->setFileHasBeenChanged(true);  
        }
        else std::println("ISSBIG SET ERROR");
    }
}
//----------------------------------------------------------------------------
void    bttParser::date_handler(){
    if (this->getIntResult(this->getCmdArg(arg_id_t::DATE)) == 9999){
        std::println("Date (get) = {0:d}",this->manager->getDate());
    }
    else{
        this->manager->setDate(this->getIntResult(this->getCmdArg(arg_id_t::DATE)));
        this->setFileHasBeenChanged(true);
        std::println("Date (set) = {0:d}",this->manager->getDate());
    }
}
//----------------------------------------------------------------------------
void    bttParser::extra_date_handler(){

    if (this->getIntResult(this->getCmdArg(arg_id_t::EXTRA_DATE)) == 9999){
        std::println("Extra-Date (get) = {0:d}",this->manager->getExtraDate());
    }
    else{
        this->manager->setExtraDate(this->getIntResult(this->getCmdArg(arg_id_t::EXTRA_DATE)));
        this->setFileHasBeenChanged(true);
        std::println("Extra-Date (set) = {0:d}",this->manager->getExtraDate());
    }
}
//----------------------------------------------------------------------------
void    bttParser::update_handler(){
    if (this->count(this->getCmdArg(arg_id_t::NO_SAVE))>0) {
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
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------






