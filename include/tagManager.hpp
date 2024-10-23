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
        enum class btTag{   TITRE,
                            INTERPRETE,
                            PERIODE,
                            LANGUE
        };

        enum class btPeriod{    OLDIES,
                                SEVENTIES,
                                EIGHTIES,
                                NINETIES,
                                MILLENIUM,
                                NOVELTY
        };

        enum class btLanguage{  FRA,
                                INT
        };

    private:
    
        const std::string   FileName{};
        const bool  Verbose{false};
        TagLib::FileRef file{};
        TagLib::PropertyMap tags{};

        [[nodiscard]]   bool getVerbose() const noexcept {return this->Verbose;};
        [[nodiscard]]   TagLib::FileRef getFile() const noexcept {return this->file;};

        
    public:
        tagManager() = delete;
        virtual ~tagManager()=default;

        tagManager(std::string FileName, bool Verbose=false);

        [[nodiscard]]   std::string getFileName() const noexcept {return this->FileName;};
        [[nodiscard]]   std::size_t getNbTags() const noexcept {return this->tags.size();};
        void    dump() const noexcept;

        

        [[nodiscard]]   std::string getTitre() const {if (this->tags.find("TITLE") == this->tags.end()) throw TagNotInTheFileException{};
                                                        else return this->tags.value("TITLE").toString().to8Bit();};
        
        [[nodiscard]]   std::string getInterprete() const {if (this->tags.find("ARTIST") == this->tags.end()) throw TagNotInTheFileException{};
                                                        else return this->tags.value("ARTIST").toString().to8Bit();};

        [[nodiscard]]   btPeriod        getPeriode() const ;
        [[nodiscard]]   unsigned int    getDate() const ;

        [[nodiscard]]   btLanguage      getLangue() const;

        void    setLangue(btLanguage Langue);
        void    setDate(unsigned int year);
        void    setInterprete(std::string artist);
        void    setTitre(std::string titre);

        bool    update() {this->getFile().setProperties(this->tags); return this->getFile().save();};
};

#endif  /* __TAG_MANAGER_HPP__ */

