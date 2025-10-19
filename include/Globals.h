#pragma once

constexpr int MAXMAINMENU = 3;
const int SOUND_NUM = 8;

enum Songs {
    START,
    GAMEPLAY,
    REMOVE,
    DUCK,
    REMOVEDUCK,
    SELECTLEVEL,
    GAMEWIN ,
    Cranky
};

enum class TextureID {
    Background,
    ButtonPlay,
    ButtonHelp,
    Exit,
    Crocodile,
    SpiritSheet,
    Level1,
    Dirt,
    EmptyDuck,
    LessThanHalfDuck,
    MoreThanHalfDuck,
    FullyDuck,
    DissapperDuck,
    SPRITEVIDEO,
    ButtonPause,
    ButtonRestart,
    SelectLevel,
    VideoSprite,
    FULLDUCK,
    Win,
    Light,
    Super,
    GoodJob,
    Excellent,
    NEXT,
    Level2,
    Level3

};

enum class DuckState {
    FULLDUCK

};
enum CollisionCategory {
    CATEGORY_BLUEBALL = 0x0001,
    CATEGORY_DUCK = 0x0002,
    CATEGORY_BROWNBALL = 0x0004,
    CATEGORY_STONE = 0x0008,
    CATEGORY_OTHER = 0x0010,
    CATEGORY_PINKBALL = 0x0020,
    CATEGORY_TAP = 0x0015,
    CATEGORY_SOIL = 0x0040    

};



