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
        TagNotInTheFileException() : tagManagerException("Tag provided is not in the file metadata."){};
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
        const bool  Verbose{false};
        TagLib::FileRef file{};
        TagLib::PropertyMap tags{};

        /**
         * @brief   Getter for the "Verbose" attribute  
         * @return  bool
         */
        [[nodiscard]]   bool getVerbose() const noexcept {return this->Verbose;};

        /**
         * @brief   Getter for the file attribute, wich is a reference to the mp3 file
         * @return  TagLib::FileRef
         */
        [[nodiscard]]   TagLib::FileRef getFile() const noexcept {return this->file;};

        [[nodiscard]]   bool isTagExisting(const std::string &Tag) const noexcept;

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
        tagManager(const std::string &FileName, bool Verbose=false);

        [[nodiscard]]   std::string getFileName() const noexcept {return this->FileName;};
        [[nodiscard]]   std::size_t getNbTags() const noexcept {return this->tags.size();};
        void    dump() const noexcept;

        

        [[nodiscard]]   std::string getTitre() const {if (this->tags.find(tagTitre) == this->tags.end()) throw TagNotInTheFileException{};
                                                        else return this->tags.value(tagTitre).toString().to8Bit();};
        
        [[nodiscard]]   std::string getExtraTitle() const {if (this->tags.find(tagExtraTitle) == this->tags.end()) throw TagNotInTheFileException{};
                                                        else return this->tags.value(tagExtraTitle).toString().to8Bit();};

        [[nodiscard]]   std::string getInterprete() const {if (this->tags.find(tagInterprete) == this->tags.end()) throw TagNotInTheFileException{};
                                                        else return this->tags.value(tagInterprete).toString().to8Bit();};

        [[nodiscard]]   btPeriod        getPeriod() const {return this->toPeriod(this->getDate());};
        [[nodiscard]]   btPeriod        getExtraPeriod() const {return this->toPeriod(this->getExtraDate());};
        [[nodiscard]]   unsigned int    getDate() const ;
        [[nodiscard]]   unsigned int    getExtraDate() const ;
        [[nodiscard]]   btLanguage      getLangue() const;

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

        std::string     makeFileName() ;

        bool    update() {this->getFile().setProperties(this->tags); return this->getFile().save();};
};

#endif  /* __TAG_MANAGER_HPP__ */

