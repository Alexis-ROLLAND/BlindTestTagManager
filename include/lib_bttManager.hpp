#ifndef __LIB_BTT_MANAGER_HPP__
#define __LIB_BTT_MANAGER_HPP__

/** standard inclusions */
#include <iostream>
#include <print>
#include <exception>
#include <filesystem>

/** inclusion of cxxopts argument parser */
#include "cxxopts.hpp"      

/** Specific types inclusion */
#include "types.h"
#include "tagManager.hpp" 

void    initApp();

void    parseInput(int argc, char *argv[]);

void    listTags();


#endif  /*  __LIB_BTT_MANAGER_HPP__ */

