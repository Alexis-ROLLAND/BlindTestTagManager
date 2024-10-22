#ifndef __TAG_MANAGER_HPP__
#define __TAG_MANAGER_HPP__

/** inclusions for TagLib  */
#include <tag.h>
#include <fileref.h>
#include <tpropertymap.h>

class tagManager{
    private:
        

    public:
        tagManager() = delete;
        virtual ~tagManager()=default;

        tagManager(std::string FileName, bool Verbose);

};

#endif  /* __TAG_MANAGER_HPP__ */

