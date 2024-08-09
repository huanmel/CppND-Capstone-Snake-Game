#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

// Game interface class
class GameInterface {
public:
    // Method to save the game (pure virtual function)
    virtual void Save(std::string filename) = 0;
    virtual void Load(std::string filename) = 0;
};

#endif