#ifndef __BTT_PARSER_HPP__
#define __BTT_PARSER_HPP__

#include <iostream>
#include <filesystem>
#include <print>

/** inclusion of cxxopts argument parser */
#include "cxxopts.hpp"      

#include "tagManager.hpp"

using   arg_desc_t = std::pair<std::string,std::string>; /** Pair for full argument description  */

//----------------------------------------------------------------------------
/** Exceptions */
class bttParserFileNotFoundException : public std::exception{};
class bttParserHelpAskedException : public std::exception{};
//----------------------------------------------------------------------------

extern  const   char    PROGRAM_NAME[];
extern const   char    PROGRAM_DESC[];

class bttParser{
    private:
        enum class arg_id_t{
            HELP,
            DUMP,
            NO_SAVE,
            FORCE_CREATE,
            TITLE,
            EXTRA_TITLE,
            ARTIST,
            DATE,
            EXTRA_DATE,
            LANGUAGE,
            IS_MOVIE,
            IS_TVSHOW,
            IS_MASTERPIECE,
            IS_SBIG,
            GET_PERIOD,    
            GET_EXTRA_PERIOD,   
            DELETE_TAG, 
            FILENAME
        };

        const std::map<arg_id_t, arg_desc_t> tabArgs{
            {arg_id_t::HELP,{"help","Prints help"}},
            {arg_id_t::DUMP,{"dump","Dump all file tags"}},
            {arg_id_t::NO_SAVE,{"no-save","Test mode. The file won't be written"}},
            {arg_id_t::FORCE_CREATE,{"force-create","Force the creation of a non-existing tag in read mode"}},
            {arg_id_t::TITLE,{"title","Gets or Sets the TITLE tag (titre)"}},
            {arg_id_t::EXTRA_TITLE,{"extra-title","Gets or Sets the EXTRA_TITLE tag"}},
            {arg_id_t::ARTIST,{"artist","Gets or Sets the ARTIST tag (interprètre)"}},
            {arg_id_t::DATE,{"date","Gets or Sets the DATE tag"}},
            {arg_id_t::EXTRA_DATE,{"extra-date","Gets or Sets the EXTRA_DATE tag"}},
            {arg_id_t::LANGUAGE,{"language","Gets or Sets the LANGUAGE tag"}},
            {arg_id_t::IS_MOVIE,{"ismovie","Gets or Sets the EXTRA_TAG value for the MOVIE indicator (YES/NO)"}},
            {arg_id_t::IS_TVSHOW,{"istvshow","Gets or Sets the EXTRA_TAG value for the TVSHOW indicator (YES/NO)"}},
            {arg_id_t::IS_MASTERPIECE,{"ismasterpiece","Gets or Sets the EXTRA_TAG value for the MASTERPIECE indicator (YES/NO)"}},
            {arg_id_t::IS_SBIG,{"issbig","Gets or Sets the EXTRA_TAG value for the SBIG indicator (YES/NO)"}},

            {arg_id_t::GET_PERIOD,{"get-period","Gets period information (\"OLDIES\", \"SEVENTIES\"...)"}},
            {arg_id_t::GET_EXTRA_PERIOD,{"get-extra-period","Gets extra-period information (\"OLDIES\", \"SEVENTIES\"...)"}},

            {arg_id_t::DELETE_TAG,{"delete-tag","Deletes a tag"}},

            {arg_id_t::FILENAME,{"filename", "The filename to process"}}
        };

        cxxopts::Options options{PROGRAM_NAME, PROGRAM_DESC};
        cxxopts::ParseResult    result;

        std::unique_ptr<tagManager>  manager;

        int argc;
        char **argv;

        std::string filename{};
        bool    FileHasBeenChanged{false};

        bool    ForceCreate{false};
        void    setForceCreate() {this->ForceCreate = true;};
        bool    getForceCreate() {return this->ForceCreate;};
                
        void    setFileName(const std::string &fname) noexcept {this->filename = fname;};

        bool    hasFileChanged() {return this->FileHasBeenChanged;};
        void    setFileHasBeenChanged(bool val) {this->FileHasBeenChanged = val;};

        std::size_t count(const std::string &arg) noexcept {return this->result.count(arg);};
        std::string getStrResult(const std::string &arg) {return this->result[arg].as<std::string>();};
        int         getIntResult(const std::string &arg) {return this->result[arg].as<int>();};
        
        std::string getCmdArg(arg_id_t id) {return this->tabArgs.at(id).first;};
        std::string getCmdDesc(arg_id_t id) {return this->tabArgs.at(id).second;};

        void    help_handler();
        void    dump_handler();
        void    force_create_handler();
        void    get_period_handler();
        void    get_extra_period_handler();
        void    title_handler();
        void    extra_title_handler();
        void    artist_handler();
        void    language_handler();
        void    ismovie_handler();
        void    istvshow_handler();
        void    ismasterpiece_handler();
        void    issbig_handler();
        void    date_handler();
        void    extra_date_handler();
        void    update_handler();
        void    delete_tag_handler();

    public:
        bttParser() = delete;
        virtual ~bttParser() = default;

        /**
         * @brief   Standard CTOR for bttParser
         * 
         * @param   int argc : argument count
         * @param   char* argv[] : argument values
         * 
         * @throw   cxxopts::exceptions::option_has_no_value if filename is not provided
         * @throw   bttParserFileNotFoundException if Filemane refers to a non-existent file
         * @throw   bttParserHelpAskedException if help is asked
         */
        bttParser(int argc, char *argv[]);

        std::string getFileName() noexcept {return this->filename;};

        void    processArgs();


};




#endif  /*  __BTT_PARSER_HPP__ */

