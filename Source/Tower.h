//
//  Tower.h
//  JuceGames
//
//  Created by Andy on 29/09/2013.
//
//

#ifndef __JuceGames__Tower__
#define __JuceGames__Tower__

#include "../JuceLibraryCode/JuceHeader.h"
#include "GameClass.h"


class TowerGame : public GameClass
{
public:
    TowerGame (Component* p, String _name);
    ~TowerGame();
    
    void paint (Graphics& g);
    
    void timerCallback();
    void reset();
    
    bool keyPressed (const KeyPress &key, Component *originatingComponent);
    
    bool keyStateChanged (bool isKeyDown, Component *originatingComponent);
    
private:
    b2World world;
};

#endif /* defined(__JuceGames__Tower__) */
