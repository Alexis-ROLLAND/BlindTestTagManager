#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <print>
#include <filesystem>

#include "tagManager.hpp"

const std::string     validFileName{"./dep_mode.mp3"};
const std::string     badFileName{"./bad_filename.mp3"};

TEST_CASE("tagManager Ctor - Validation de l'existence du fichier & dump"){
    
    REQUIRE(std::filesystem::exists(validFileName) == true);
    REQUIRE(std::filesystem::exists(badFileName) == false);
    
    SUBCASE("CTOR"){
        CHECK_THROWS_WITH_AS (tagManager myManager{badFileName}, "File not found.", FileNotFoundException);
        CHECK_NOTHROW(tagManager  myManager{validFileName,true});
    }


    SUBCASE("getNbTags & dump"){
    tagManager  myManager{validFileName,false};

    auto NbTags = myManager.getNbTags(); 
    CHECK_MESSAGE(NbTags > 0,"NbTags is not > 0");

    myManager.dump();
    }
}

TEST_CASE("get/set Trad Tags"){
    REQUIRE(std::filesystem::exists(validFileName) == true);
    tagManager  myManager{validFileName,false};

    //CHECK_THROWS_WITH_AS(myManager.getTag(static_cast<tagManager::btTag>(666)), "Tag provided is not a valid bt Tag.", UnknownTagException);

    std::string Titre;
    CHECK_NOTHROW(Titre = myManager.getTitre());
    std::println("Titre (depuis getTtitre) : {}",Titre);

    CHECK_NOTHROW(myManager.setTitre("Nouveau Titre"));
    CHECK_NOTHROW(Titre = myManager.getTitre());
    CHECK(Titre == "Nouveau Titre");

    std::string Artist;
    CHECK_NOTHROW(Artist = myManager.getInterprete());
    std::println("Interprète (depuis getInterprete) : {}",Artist);
    
    CHECK_NOTHROW(myManager.setInterprete("Toto BIDON"));
    CHECK_NOTHROW(Artist = myManager.getInterprete());
    CHECK(Artist == "Toto BIDON");

    CHECK_NOTHROW(std::println("Date = {:d}", myManager.getDate()));
    CHECK_NOTHROW(myManager.setDate(6666));
    myManager.dump();
    unsigned int Year;
    CHECK_NOTHROW(Year = myManager.getDate());
    CHECK(Year == 6666);

    tagManager::btPeriod Periode{};
    CHECK_NOTHROW(Periode = myManager.getPeriod());
    std::println("Periode (convertie en int) = {:d}", std::to_underlying(Periode));

    
    CHECK_NOTHROW(myManager.setLangue(tagManager::btLanguage::INT));
    tagManager::btLanguage Langue;
    CHECK_NOTHROW(Langue = myManager.getLangue());
    CHECK(Langue == tagManager::btLanguage::INT);

    CHECK(myManager.update() == true);
    
}


TEST_CASE("get / set Extra Tags (Flags)"){
    REQUIRE(std::filesystem::exists(validFileName) == true);
    tagManager  myManager{validFileName,false};

    bool Flag = true;

    CHECK_NOTHROW(myManager.setMovieSoundTrackFlag(false));
    REQUIRE(Flag == true);
    Flag = myManager.isMovieSoundTrack();
    CHECK(Flag == false);
    
    CHECK_NOTHROW(myManager.setMovieSoundTrackFlag(true));
    REQUIRE(Flag == false);
    Flag = myManager.isMovieSoundTrack();
    CHECK(Flag == true);

    REQUIRE(Flag == true);
    Flag = myManager.isTvShow();
    CHECK(Flag == false);
    CHECK_NOTHROW(myManager.setTvShowFlag(true));
    REQUIRE(Flag == false);
    Flag = myManager.isTvShow();
    CHECK(Flag == true);

    REQUIRE(Flag == true);
    Flag = myManager.isMasterPiece();
    CHECK(Flag == false);
    CHECK_NOTHROW(myManager.setMasterPieceFlag(true));
    REQUIRE(Flag == false);
    Flag = myManager.isMasterPiece();
    CHECK(Flag == true);

    REQUIRE(Flag == true);
    Flag = myManager.isSbig();
    CHECK(Flag == false);
    CHECK_NOTHROW(myManager.setSbigFlag(true));
    REQUIRE(Flag == false);
    Flag = myManager.isSbig();
    CHECK(Flag == true);

    myManager.dump();
}

TEST_CASE("get / set Extra games tags (EXTRA_TITLE...)"){
    REQUIRE(std::filesystem::exists(validFileName) == true);
    tagManager  myManager{validFileName,false};

    std::string xtraTitleRef="Back to the future";
    myManager.setExtraTitle(xtraTitleRef);
    std::string xtraTitle{};
    CHECK_NOTHROW(xtraTitle = myManager.getExtraTitle());
    CHECK(xtraTitleRef == xtraTitle);

    CHECK_NOTHROW(myManager.setExtraDate(1973));
    unsigned int xtrDate{};
    CHECK_NOTHROW(xtrDate = myManager.getExtraDate());
    CHECK(xtrDate == 1973);

    tagManager::btPeriod Periode{};
    CHECK_NOTHROW(Periode = myManager.getExtraPeriod());
    std::println("Extra Periode (convertie en int) = {:d}", std::to_underlying(Periode));

    myManager.dump();
}