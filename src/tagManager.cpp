#include "tagManager.hpp"

tagManager::tagManager(std::string FileName, bool Verbose):FileName{FileName},Verbose{Verbose}{
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

unsigned int    tagManager::getDate() const{
    if (this->tags.find("DATE") == this->tags.end()) throw TagNotInTheFileException{};    
    std::string strDate = this->tags.value("DATE").toString().to8Bit();
    return std::stoi(strDate);
}

tagManager::btPeriod    tagManager::getPeriode() const {
              
    unsigned int year = this->getDate();
    if (year < 1970) return btPeriod::OLDIES;
    else if (year < 1980) return btPeriod::SEVENTIES; 
    else if (year < 1990) return btPeriod::EIGHTIES;
    else if (year < 2000) return btPeriod::NINETIES;
    else if (year < 2013) return btPeriod::MILLENIUM;
    else return btPeriod::NOVELTY;
          
}

tagManager::btLanguage      tagManager::getLangue() const{
    if (this->tags.find("LANGUAGE") == this->tags.end()) throw TagNotInTheFileException{};   
    std::string strLanguage = this->tags.value("LANGUAGE").toString().to8Bit(); 
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
    if (this->tags.find("LANGUAGE") == this->tags.end()) this->tags.insert("LANGUAGE",Value);   
    else this->tags.replace("LANGUAGE",Value);
}

void    tagManager::setDate(unsigned int year){
    TagLib::String Value = std::to_string(year);

    if (this->tags.find("DATE") == this->tags.end()) this->tags.insert("DATE",Value);   
    else this->tags.replace("DATE",Value); 
} 

void    tagManager::setInterprete(std::string artist){
    TagLib::String Value = artist;
    if (this->tags.find("ARTIST") == this->tags.end()) this->tags.insert("ARTIST",Value);   
    else this->tags.replace("ARTIST",Value);    
}

void    tagManager::setTitre(std::string titre){
    TagLib::String Value = titre;
    if (this->tags.find("TITLE") == this->tags.end()) this->tags.insert("TITLE",Value);   
    else this->tags.replace("TITLE",Value);    
}

