#include "Sounds.h"

Sounds::~Sounds() {}

Sounds& Sounds::getInstance() {
    static Sounds instance;
    return instance;
}

/* loadds the sounds into the buffer array*/
Sounds::Sounds() {
    for (int i = 0; i < SOUND_NUM; i++) {
        m_buffers[i].loadFromFile(m_soundNames[i]);
    }

    /* matches each sound with it's own buffer*/
    for (int i = 0; i < SOUND_NUM; i++) {
        m_sounds[i].setBuffer(m_buffers[i]);
    }
}

void Sounds::playSound(Songs SongNum) {

    if (SongNum == GAMEPLAY) {
    m_sounds[SongNum].setLoop(true); // Set the music to loop
    }
    m_sounds[SongNum].play();
}

void Sounds::pauseSound(Songs SongNum) {
    if (SongNum == GAMEPLAY){
    m_sounds[SongNum].setLoop(false); // Disable looping when paused
    }
    m_sounds[SongNum].pause();
}



bool Sounds::isSoundPaused(Songs songNum) 
{
    return m_sounds[songNum].getStatus() == sf::SoundSource::Paused;
}
