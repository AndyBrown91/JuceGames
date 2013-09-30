//
//  GameClass.h
//  JuceGames
//
//  Created by Andy on 27/09/2013.
//
//

#ifndef JuceGames_GameClass_h
#define JuceGames_GameClass_h

#include "../JuceLibraryCode/JuceHeader.h"
//#include "MainComponent.h"

class GameClass : public Component
{
public:
    GameClass (Component* p, String _name)
    {
        setName(_name);
        
        parent = p;
        
        setSize(400, 575);
        //Set speed
        //MainContentComponent* comp = static_cast<MainContentComponent*>(p);
        
    }
    
    ~GameClass()
    {
        
    }
    
    virtual void timerCallback()=0;
    virtual void reset()=0;
    
    bool keyPressed (const KeyPress &key, Component *originatingComponent)
    {
        if (key.isCurrentlyDown())
            currentKey = key;
        
        return true;
    }
    
    bool keyStateChanged (bool isKeyDown, Component *originatingComponent)
    {
        keyDown = isKeyDown;
        return true;
    }


    bool keyDown;
    KeyPress currentKey;
    
private:
    Component* parent;
};

#endif
