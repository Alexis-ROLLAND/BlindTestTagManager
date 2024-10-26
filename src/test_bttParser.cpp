#define  DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "bttParser.hpp"

#include <iostream>
#include <print>

// Variables globales pour stocker argc et argv
int g_argc;
char** g_argv;

// Utiliser les valeurs de argc et argv dans un test
TEST_CASE("Test des arguments de la ligne de commande") {
    // Utilisation des variables globales g_argc et g_argv
    CHECK(g_argc > 0); // Vérifie que g_argv[0] contient le nom du programme
    if (g_argc > 1) CHECK(std::string(g_argv[1]) == "argument1");
    if (g_argc > 2) CHECK(std::string(g_argv[2]) == "argument2");
}


/**     main nécessaire pour récupérer les arguments de la ligne de commande */
int main(int argc, char** argv) {
    doctest::Context context;
    context.applyCommandLine(argc, argv);

    // Assigner les valeurs aux variables globales
    g_argc = argc;
    g_argv = argv;

    int result = context.run(); // Exécuter les tests

    if (context.shouldExit()) { // Vérifie si doctest doit terminer
        return result;
    }

    // Exécution du code principal si nécessaire
    return result; // Code de retour en fonction du résultat des tests
}




