#include <iostream>
#include <print>

#include "bttParser.hpp"


/**     main nécessaire pour récupérer les arguments de la ligne de commande */
int main(int argc, char** argv) {
    bttParser myParser(argc,argv);

    myParser.processArgs();




}




