/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Frogger.h"
#include "Tower.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
                               public Timer,
                               public ComboBoxListener,
                               public KeyListener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&);
    void resized();

    void timerCallback();
    void comboBoxChanged (ComboBox *comboBoxThatHasChanged);
    
    bool keyPressed (const KeyPress &key, Component *originatingComponent);
    bool keyStateChanged (bool isKeyDown, Component *originatingComponent);
    
    void setSpeed (int milliseconds) { stopTimer(); startTimer(milliseconds);}
    
private:
    OwnedArray<GameClass> games;
    
    ComboBox combo;
    int selectedGame;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
