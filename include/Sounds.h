#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <Globals.h>




class Sounds {
public:
    Sounds();
    ~Sounds();
    static Sounds& getInstance();
    void playSound(Songs SongNum);
    void pauseSound(Songs SongNum);
    bool isSoundPaused(Songs songNum);
   


private:
    std::string m_soundNames[SOUND_NUM] = { "MenuMusic.mp3" , "levelmusic.mp3" , "remove.mp3" , "Duck.mp3" , "Duck1.mp3" ,
        "selectlevel.mp3" , "gamewin.ogg" ,"gamewin.ogg" };
    sf::SoundBuffer m_buffers[SOUND_NUM];
    sf::Sound m_sounds[SOUND_NUM];
};
