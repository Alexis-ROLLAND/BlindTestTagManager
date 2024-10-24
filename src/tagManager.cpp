#include "tagManager.hpp"

tagManager::tagManager(const std::string &FileName, bool Verbose):FileName{FileName},Verbose{Verbose}{
    if (std::filesystem::exists(this->getFileName()) == false) throw FileNotFoundException{};
    if (this->getVerbose()) std::println("Opening File {}",this->getFileName());

    this->file = TagLib::FileRef(this->getFileName().c_str(),false);
    if (this->getFile().isNull()) throw FileErrorException{};

    if (this->getFile().tag() == nullptr) throw NoTagsInFileException{};

    this->tags = this->getFile().properties();
    if (this->tags.isEmpty()) throw NoTagsInFileException{};



}

void    tagManager::dump() const noexcept{
    for(auto tag : this->tags){
        std::println("{} = {}",tag.first.to8Bit(),tag.second.toString().to8Bit());
    }
}

bool tagManager::isTagExisting(const std::string &Tag) const noexcept {
    if (this->tags.find(Tag) == this->tags.end()) return false;
    else return true;
}

unsigned int    tagManager::getDate() const{
    if (this->isTagExisting(tagDate) == false) throw TagNotInTheFileException{};  
    std::string strDate = this->tags.value(tagDate).toString().to8Bit();
    return std::stoi(strDate);
}

unsigned int    tagManager::getExtraDate() const{
    if (this->isTagExisting(tagExtraDate) == false) throw TagNotInTheFileException{};  
    std::string strDate = this->tags.value(tagExtraDate).toString().to8Bit();
    return std::stoi(strDate);
}

tagManager::btPeriod    tagManager::toPeriod(unsigned int year) const noexcept{
    if (year < 1970) return btPeriod::OLDIES;
    else if (year < 1980) return btPeriod::SEVENTIES; 
    else if (year < 1990) return btPeriod::EIGHTIES;
    else if (year < 2000) return btPeriod::NINETIES;
    else if (year < 2013) return btPeriod::MILLENIUM;
    else return btPeriod::NOVELTY;
}

tagManager::btLanguage      tagManager::getLangue() const{
    if (this->isTagExisting(tagLangue) == false) throw TagNotInTheFileException{};   
    std::string strLanguage = this->tags.value(tagLangue).toString().to8Bit(); 
    if (strLanguage == "FRA") return tagManager::btLanguage::FRA;
    else if (strLanguage == "INT") return tagManager::btLanguage::INT;
    else throw BadTagValueException{}; 
}

void    tagManager::setLangue(tagManager::btLanguage Langue){
    TagLib::String Value;
    switch (Langue){
        case btLanguage::FRA : Value = "FRA";break;
        case btLanguage::INT : Value = "INT";break;
        default : Value = "ERR";break;
    }
    
    if (this->isTagExisting(tagLangue) == false) this->tags.insert(tagLangue,Value);   
    else this->tags.replace(tagLangue,Value);
}

void    tagManager::setDate(unsigned int year){
    TagLib::String Value = std::to_string(year);
    if (this->isTagExisting(tagDate) == false) this->tags.insert(tagDate,Value);   
    else this->tags.replace(tagDate,Value); 
} 

void    tagManager::setExtraDate(unsigned int year){
    TagLib::String Value = std::to_string(year);
    if (this->isTagExisting(tagExtraDate) == false) this->tags.insert(tagExtraDate,Value);   
    else this->tags.replace(tagExtraDate,Value);    
}

void    tagManager::setInterprete(std::string artist){
    TagLib::String Value = artist;
    if (this->isTagExisting(tagInterprete) == false) this->tags.insert(tagInterprete,Value);   
    else this->tags.replace(tagInterprete,Value);    
}

void    tagManager::setTitre(std::string titre){
    TagLib::String Value = titre;
    if (this->isTagExisting(tagTitre) == false) this->tags.insert(tagTitre,Value);   
    else this->tags.replace(tagTitre,Value);    
}

void    tagManager::setExtraTitle(std::string titre){
    TagLib::String Value = titre;
    if (this->isTagExisting(tagExtraTitle) == false) this->tags.insert(tagExtraTitle,Value);   
    else this->tags.replace(tagExtraTitle,Value);       
}

uint8_t tagManager::getExtraTagValue(bool CreateEmptyIfNotExist) {
    uint8_t Byte;

    if (this->isTagExisting(tagExtra) == false) {
        if (CreateEmptyIfNotExist == false) throw TagNotInTheFileException{}; 
        else this->setExtraTagValue(0x00);
    }
    
    
    std::string strExtra = this->tags.value(tagExtra).toString().to8Bit(); /** The 2 digits hexadecimal value is copied into strExtra */

    if (strExtra.length() != 2) throw BadTagValueException{}; /** String size MUST be 2 (digits) */

    auto [ptr, ec] = std::from_chars(strExtra.data(), strExtra.data() + strExtra.size(), Byte, 16);
    if ( ec != std::errc() ) throw BadTagValueException{}; 

    return Byte;
}

void    tagManager::setExtraTagValue(uint8_t Byte){
    TagLib::String Value = std::format("{:02X}", Byte);
    if (this->isTagExisting(tagExtra) == false) this->tags.insert(tagExtra,Value);   
    else this->tags.replace(tagExtra,Value);
}

void    tagManager::setMovieSoundTrackFlag(bool isMovieSt){
    uint8_t Byte;
    try{
        Byte = this->getExtraTagValue();
    }
    catch (const TagNotInTheFileException &e){
        Byte = 0x00;
    }

    uint8_t Mask = std::to_underlying(btExtraMask::MOVIE_STRACK);

    if (isMovieSt) Byte |= Mask;    /** Sets the "Movie Soundtrack" flag  */
    else Byte &= ~Mask;

    this->setExtraTagValue(Byte);
}

void    tagManager::setTvShowFlag(bool isTvs){
    uint8_t Byte;
    try{
        Byte = this->getExtraTagValue();
    }
    catch (const TagNotInTheFileException &e){
        Byte = 0x00;
    }

    uint8_t Mask = std::to_underlying(btExtraMask::TV_SHOW);

    if (isTvs) Byte |= Mask;    
    else Byte &= ~Mask;

    this->setExtraTagValue(Byte);    
}

void    tagManager::setMasterPieceFlag(bool isMstpce){
    uint8_t Byte;
    try{
        Byte = this->getExtraTagValue();
    }
    catch (const TagNotInTheFileException &e){
        Byte = 0x00;
    }

    uint8_t Mask = std::to_underlying(btExtraMask::MASTERPIECE);

    if (isMstpce) Byte |= Mask;    
    else Byte &= ~Mask;

    this->setExtraTagValue(Byte); 
}

void    tagManager::setSbigFlag(bool isSb){
    uint8_t Byte;
    try{
        Byte = this->getExtraTagValue();
    }
    catch (const TagNotInTheFileException &e){
        Byte = 0x00;
    }

    uint8_t Mask = std::to_underlying(btExtraMask::SBIG);

    if (isSb) Byte |= Mask;    
    else Byte &= ~Mask;

    this->setExtraTagValue(Byte); 
}

bool    tagManager::isMovieSoundTrack() {
    uint8_t Byte = this->getExtraTagValue(false);

    if ((Byte & std::to_underlying(btExtraMask::MOVIE_STRACK)) == std::to_underlying(btExtraMask::MOVIE_STRACK) ) return true;
    else return false;

}

bool    tagManager::isTvShow() {
    uint8_t Byte = this->getExtraTagValue(false);

    if ((Byte & std::to_underlying(btExtraMask::TV_SHOW)) == std::to_underlying(btExtraMask::TV_SHOW) ) return true;
    else return false;    
}

bool    tagManager::isMasterPiece() {
    uint8_t Byte = this->getExtraTagValue(false);

    if ((Byte & std::to_underlying(btExtraMask::MASTERPIECE)) == std::to_underlying(btExtraMask::MASTERPIECE) ) return true;
    else return false;     
}

bool    tagManager::isSbig() {
    uint8_t Byte = this->getExtraTagValue(false);

    if ((Byte & std::to_underlying(btExtraMask::SBIG)) == std::to_underlying(btExtraMask::SBIG) ) return true;
    else return false;      
}

std::string     tagManager::makeFileName() {
    std::string Name{};
    tagManager::btPeriod    Periode;

    uint8_t Byte = this->getExtraTagValue(true);
    if (this->getVerbose()) std::println("EXTRA Tag Value = {:02X}",Byte);

    if ( (this->isMovieSoundTrack()) || (this->isTvShow())) Periode = this->getExtraPeriod();
    else    Periode = this->getPeriod();

    switch (Periode){
        case tagManager::btPeriod::OLDIES : Name += "O"; break;
        case tagManager::btPeriod::SEVENTIES : Name += "7"; break;
        case tagManager::btPeriod::EIGHTIES : Name += "8"; break;
        case tagManager::btPeriod::NINETIES : Name += "9"; break;
        case tagManager::btPeriod::MILLENIUM : Name += "M"; break;
        case tagManager::btPeriod::NOVELTY : Name += "N"; break;
        default: Name += "x";break;
    }
  
    tagManager::btLanguage Langue = this->getLangue();
    switch(Langue){
        case tagManager::btLanguage::FRA : Name+="F";break;
        case tagManager::btLanguage::INT : Name+="I";break;
        default : Name += "x";
    }

    Name += std::format("{:02X}", this->getExtraTagValue());
    Name += "_";
    Name += this->getInterprete();
    Name += "_";
    Name += this->getTitre();

    if ( (this->isMovieSoundTrack()) || (this->isTvShow()) ) {
        Name += "_";
        Name += this->getExtraTitle(); 
    }

    Name += ".mp3";
    
    return Name;
}