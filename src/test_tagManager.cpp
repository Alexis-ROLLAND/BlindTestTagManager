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
        CHECK_NOTHROW(tagManager  myManager{validFileName});
    }


    SUBCASE("getNbTags & dump"){
    tagManager  myManager{validFileName};

    auto NbTags = myManager.getNbTags(); 
    CHECK_MESSAGE(NbTags > 0,"NbTags is not > 0");

    myManager.dump();
    }
}

TEST_CASE("get/set Trad Tags"){
    REQUIRE(std::filesystem::exists(validFileName) == true);
    tagManager  myManager{validFileName};

    //CHECK_THROWS_WITH_AS(myManager.getTag(static_cast<tagManager::btTag>(666)), "Tag provided is not a valid bt Tag.", UnknownTagException);

    std::string Titre;
    CHECK_NOTHROW(Titre = myManager.getTitre(false));
    std::println("Titre (depuis getTtitre) : {}",Titre);

    CHECK_NOTHROW(myManager.setTitre("Nouveau Titre"));
    CHECK_NOTHROW(Titre = myManager.getTitre(false));
    CHECK(Titre == "Nouveau Titre");

    std::string Artist;
    CHECK_NOTHROW(Artist = myManager.getInterprete(false));
    std::println("Interprète (depuis getInterprete) : {}",Artist);
    
    CHECK_NOTHROW(myManager.setInterprete("Toto BIDON"));
    CHECK_NOTHROW(Artist = myManager.getInterprete(false));
    CHECK(Artist == "Toto BIDON");

    CHECK_NOTHROW(std::println("Date = {:d}", myManager.getDate(false)));
    CHECK_NOTHROW(myManager.setDate(6666));
    myManager.dump();
    unsigned int Year;
    CHECK_NOTHROW(Year = myManager.getDate(false));
    CHECK(Year == 6666);

    tagManager::btPeriod Periode{};
    CHECK_NOTHROW(Periode = myManager.getPeriod(false));
    std::println("Periode (convertie en int) = {:d}", std::to_underlying(Periode));

    
    CHECK_NOTHROW(myManager.setLangue(tagManager::btLanguage::INT));
    tagManager::btLanguage Langue;
    CHECK_NOTHROW(Langue = myManager.getLangue(false));
    CHECK(Langue == tagManager::btLanguage::INT);

    CHECK(myManager.update() == true);
    
}


TEST_CASE("get / set Extra Tags (Flags)"){
    REQUIRE(std::filesystem::exists(validFileName) == true);
    tagManager  myManager{validFileName};

    bool Flag{false};

    SUBCASE("Movie SoundTrack"){    
        CHECK_NOTHROW(myManager.setMovieSoundTrackFlag(true));
        REQUIRE(Flag == false);
        Flag = myManager.isMovieSoundTrack(false);
        CHECK(Flag == true);

        CHECK_NOTHROW(myManager.setMovieSoundTrackFlag(false));
        REQUIRE(Flag == true);
        Flag = myManager.isMovieSoundTrack(false);
        CHECK(Flag == false);
    }
       
    SUBCASE("TV Show"){    
        CHECK_NOTHROW(myManager.setTvShowFlag(true));
        REQUIRE(Flag == false);
        Flag = myManager.isTvShow(false);
        CHECK(Flag == true);

        CHECK_NOTHROW(myManager.setTvShowFlag(false));
        REQUIRE(Flag == true);
        Flag = myManager.isTvShow(false);
        CHECK(Flag == false);
    }

    SUBCASE("Masterpiece"){    
        CHECK_NOTHROW(myManager.setMasterPieceFlag(true));
        REQUIRE(Flag == false);
        Flag = myManager.isMasterPiece(false);
        CHECK(Flag == true);

        CHECK_NOTHROW(myManager.setMasterPieceFlag(false));
        REQUIRE(Flag == true);
        Flag = myManager.isMasterPiece(false);
        CHECK(Flag == false);
    }

    SUBCASE("Sbig"){    
        CHECK_NOTHROW(myManager.setSbigFlag(true));
        REQUIRE(Flag == false);
        Flag = myManager.isSbig(false);
        CHECK(Flag == true);

        CHECK_NOTHROW(myManager.setSbigFlag(false));
        REQUIRE(Flag == true);
        Flag = myManager.isSbig(false);
        CHECK(Flag == false);
    }

    SUBCASE("Duo"){    
        CHECK_NOTHROW(myManager.setDuetFlag(true));
        REQUIRE(Flag == false);
        Flag = myManager.isDuet(false);
        CHECK(Flag == true);

        CHECK_NOTHROW(myManager.setDuetFlag(false));
        REQUIRE(Flag == true);
        Flag = myManager.isDuet(false);
        CHECK(Flag == false);
    }

    myManager.dump();
    
    bool res = myManager.update();
    CHECK(res == true);
}

TEST_CASE("get / set Extra games tags (EXTRA_TITLE...)"){
    REQUIRE(std::filesystem::exists(validFileName) == true);
    tagManager  myManager{validFileName};

    std::string xtraTitleRef="Back to the future";
    myManager.setExtraTitle(xtraTitleRef);
    std::string xtraTitle{};
    CHECK_NOTHROW(xtraTitle = myManager.getExtraTitle(false));
    CHECK(xtraTitleRef == xtraTitle);

    std::string xtraArtistRef="Etienne DAHO";
    myManager.setExtraArtist(xtraArtistRef);
    std::string xtraArtist{};
    CHECK_NOTHROW(xtraArtist = myManager.getExtraArtist(false));
    CHECK(xtraArtistRef == xtraArtist);

    CHECK_NOTHROW(myManager.setExtraDate(1973));
    unsigned int xtrDate{};
    CHECK_NOTHROW(xtrDate = myManager.getExtraDate(false));
    CHECK(xtrDate == 1973);

    tagManager::btPeriod Periode{};
    CHECK_NOTHROW(Periode = myManager.getExtraPeriod(false));
    std::println("Extra Periode (convertie en int) = {:d}", std::to_underlying(Periode));

    myManager.dump();

    bool res  = myManager.update();
    CHECK(res == true);
}

TEST_CASE("makeFileName"){
    REQUIRE(std::filesystem::exists(validFileName) == true);
    tagManager  myManager{validFileName};
    myManager.dump();
    std::string NewName{};

    SUBCASE("Trad Tags only"){
        CHECK_NOTHROW(NewName = myManager.makeFileName());
        std::println("Nouveau nom de fichier : {}",NewName);
    }

    SUBCASE("Extra tag (movie) only"){
        myManager.setMovieSoundTrackFlag(true);
        myManager.setExtraTitle("Back to the future");
        myManager.setExtraDate(1984);
        CHECK_NOTHROW(NewName = myManager.makeFileName());
        std::println("Nouveau nom de fichier : {}",NewName);
    }
    
}
