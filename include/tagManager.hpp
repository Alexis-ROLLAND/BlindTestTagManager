#ifndef __TAG_MANAGER_HPP__
#define __TAG_MANAGER_HPP__


/** Standard inclusions     */
#include <exception>
#include <filesystem>
#include <print>

/** inclusions for TagLib  */
#include <tag.h>
#include <fileref.h>
#include <tpropertymap.h>

const   std::string   tagTitre{"TITLE"};
const   std::string   tagInterprete{"ARTIST"};
const   std::string   tagDate{"DATE"};
const   std::string   tagLangue{"LANGUAGE"};
const   std::string   tagExtra{"EXTRA"};
const   std::string   tagExtraTitle{"EXTRA_TITLE"};
const   std::string   tagExtraDate{"EXTRA_DATE"};


class tagManagerException : public std::exception{
    private:
        const char* Message{};
    public:
        tagManagerException(const char* msg) : Message(msg) {};
        const char* what() const noexcept override {return this->Message;};
};

class FileNotFoundException : public tagManagerException{
    public:
        FileNotFoundException() : tagManagerException("File not found."){};
};

class FileErrorException : public tagManagerException{
    public:
        FileErrorException() : tagManagerException("File error."){};
};

class NoTagsInFileException : public tagManagerException{
    public:
        NoTagsInFileException() : tagManagerException("No Tags in the file error."){};
};

class UnknownTagException : public tagManagerException{
    public:
        UnknownTagException() : tagManagerException("Tag provided is not a valid bt Tag."){};
};

class TagNotInTheFileException : public tagManagerException{
    public:
        const std::string tag{}; 
        TagNotInTheFileException(const std::string tag) : tagManagerException("Tag provided is not in the file metadata."),tag{tag}{};
};

class BadTagValueException : public tagManagerException{
    public:
        BadTagValueException() : tagManagerException("Tag provided is not in the file metadata."){};
};

class tagManager{
    public:
        

        enum class btPeriod{    OLDIES,     /**< Avant 1970 (DATE < 1970) */
                                SEVENTIES,  /**< DATE entre 1970 et 1979 */
                                EIGHTIES,   /**< DATE entre 1980 et 1989*/
                                NINETIES,   /**< DATE entre 1990 et 1999 */
                                MILLENIUM,  /**< DATE entre 2000 et 2012 */
                                NOVELTY     /**< Après 2021 (DATE > 2012) */
        };

        enum class btLanguage{  FRA,        /**< FRAnçais */
                                INT         /**< INTernational */
        };

        enum class btExtraMask : uint8_t {    
            MOVIE_STRACK = 0x01,
            TV_SHOW = 0x02,
            MASTERPIECE = 0x04,
            SBIG = 0x08
        };
    private:
    
        const std::string   FileName{};
        
        TagLib::FileRef file{};
        TagLib::PropertyMap tags{};

        
        /**
         * @brief   Getter for the file attribute, wich is a reference to the mp3 file
         * @return  TagLib::FileRef
         */
        [[nodiscard]]   TagLib::FileRef getFile() const noexcept {return this->file;};

        [[nodiscard]]   bool isTagExisting(const std::string &Tag) noexcept;

        [[nodiscard]]   uint8_t getExtraTagValue(bool CreateEmptyIfNotExist = false);
        void    setExtraTagValue(uint8_t Byte);                    

        [[nodiscard]]   btPeriod    toPeriod(unsigned int year) const noexcept;
    public:
        tagManager() = delete;          /** Default CTOR is deleted */
        virtual ~tagManager()=default;  /** DTOR is defaulted */

        /**
         * @brief   Standard CTOR
         * @param   
         */
        tagManager(const std::string &FileName);

        [[nodiscard]]   std::string getFileName()  noexcept {return this->FileName;};
        [[nodiscard]]   std::size_t getNbTags()  noexcept {return this->tags.size();};
        void    dump()  noexcept;

        [[nodiscard]]   std::string getTitre(bool fc) ;
        [[nodiscard]]   std::string getExtraTitle(bool fc); 
        [[nodiscard]]   std::string getInterprete(bool fc);

        [[nodiscard]]   btPeriod        getPeriod()  {return this->toPeriod(this->getDate());};
        [[nodiscard]]   btPeriod        getExtraPeriod()  {return this->toPeriod(this->getExtraDate());};
        [[nodiscard]]   unsigned int    getDate(bool fc);
        [[nodiscard]]   unsigned int    getExtraDate()  ;
        [[nodiscard]]   btLanguage      getLangue() ;

        void    setLangue(btLanguage Langue);
        void    setDate(unsigned int year);
        void    setExtraDate(unsigned int year);
        void    setInterprete(std::string artist);
        void    setTitre(std::string titre);
        void    setExtraTitle(std::string titre);

        [[nodiscard]] bool    isMovieSoundTrack() ;
        void    setMovieSoundTrackFlag(bool isMovieSt);

        [[nodiscard]] bool    isTvShow() ;
        void    setTvShowFlag(bool isTvs);

        [[nodiscard]] bool    isMasterPiece() ;
        void    setMasterPieceFlag(bool isMstpce);

        [[nodiscard]] bool    isSbig() ;
        void    setSbigFlag(bool isSb);

        [[nodiscard]]   std::string     makeFileName() ;


        [[nodiscard]]   bool    update() {this->getFile().setProperties(this->tags); return this->getFile().save();};
};

#endif  /* __TAG_MANAGER_HPP__ */

