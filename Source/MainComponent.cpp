/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    selectedGame = 1;
    
    setWantsKeyboardFocus(true);
    addKeyListener(this);
    
    games.insert(-1, new FroggerGame(this, "Frogger"));
    games.insert(-1, new TowerGame(this, "Tower"));
    
    addAndMakeVisible(&combo);
    
    for (int i = 0; i < games.size(); i++)
    {
        combo.addItem(games[i]->getName(), i+1);
        addChildComponent(games[i]);
    }
    
    games[selectedGame]->setVisible(true);
    
    combo.setSelectedItemIndex(selectedGame);
    combo.addListener(this);
    
    startTimer(50);
    
    setSize (500, 650);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{

}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
    combo.setBounds(0, 0, 100, 20);
    
    games[selectedGame]->setBounds(50, 50, 400, 575);
    
}

void MainContentComponent::timerCallback()
{
    games[selectedGame]->timerCallback();
}

void MainContentComponent::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    games[selectedGame]->reset();

    games[selectedGame]->setVisible(false);

    selectedGame = combo.getSelectedItemIndex();
    
    games[combo.getSelectedItemIndex()]->setVisible(true);

    resized();

}

bool MainContentComponent::keyPressed (const KeyPress &key, Component *originatingComponent)
{
    games[selectedGame]->keyPressed(key, originatingComponent);
    return true;
}

bool MainContentComponent::keyStateChanged (bool isKeyDown, Component *originatingComponent)
{
    games[selectedGame]->keyStateChanged(isKeyDown, originatingComponent);
    return true;
}