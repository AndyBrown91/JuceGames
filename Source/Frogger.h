//
//  Frogger.h
//  JuceGames
//
//  Created by Andy on 27/09/2013.
//
//

#ifndef __JuceGames__Frogger__
#define __JuceGames__Frogger__

#include "../JuceLibraryCode/JuceHeader.h"
#include "GameClass.h"

#define VEHICLESPEED 6

class Vehicle
{
public:    
    Vehicle(Random& random)
    {
        int lane = random.nextInt(4);
        
        if (lane == 0 || lane == 2)
            direction = true;
        else
            direction = false;
        
        int length = (random.nextInt(75) + 30);
        
        position = Rectangle<int> (0-length, (lane*40)+310, length, 25);
        
        if (!direction)
            position.setX(375+length);
    }
    
    ~Vehicle() {}
    
    void timerCallback()
    {
        if (direction)
            position.setX(position.getX() + VEHICLESPEED);
        else
            position.setX(position.getX() - VEHICLESPEED);
    }
    
    Rectangle<int> getPosition() {return position;}
    bool getDirection() { return direction;}
    
private:
    bool direction;
    Rectangle<int> position;
};

#define LOGSPEED 4

class Logs
{
public:
    Logs(Random& _random)
    {
        random = _random;
        
        int lane = random.nextInt(5);
        
        landable = random.nextInt(2);
        landableCounter = 0;

        if (lane == 0 || lane == 2)
            direction = true;
        else
            direction = false;
        
        int length = (random.nextInt(55) + 55);
        
        position = Rectangle<int> (0-length, (lane*40)+55, length, 25);
        
        if (!direction)
            position.setX(375+length);
    }
    
    ~Logs() {}
    
    void timerCallback()
    {
        if (direction)
            position.setX(position.getX() + LOGSPEED);
        else
            position.setX(position.getX() - LOGSPEED);

        landableCounter++;
        
        if (landableCounter > 100 )
        {
            if (random.nextInt(2))
            {
                landable = !landable;
                landableCounter = 0;
            }
        }
        
    }
    
    Rectangle<int> getPosition() {return position;}
    bool getDirection() { return direction;}
    bool getLandable() { //return landable;
        return true;}
    
private:
    Random random;
    bool direction, landable;
    Rectangle<int> position;
    int landableCounter;
};


class FroggerGame : public GameClass
{
public:
    FroggerGame(Component* p, String _name) : GameClass(p, _name)
    {
        mainBox = Rectangle<int>(getWidth()/2, getHeight()-20, 20, 20);
        
        random = Random::getSystemRandom();
        
        safe = true;
    }
    ~FroggerGame() {}
    
    void paint (Graphics &g)
    {
        g.fillAll(Colours::white);
        
        //Water
        g.setColour(Colours::blue);
        Rectangle<int> water = Rectangle<int>(0, 50, getWidth(), 200);
        g.fillRect(water);
        
        safe = false;
        
        for (int i = 0; i < logs.size(); i++)
        {
            if (logs[i]->getPosition().intersects(mainBox) && water.contains(mainBox) && logs[i]->getLandable())
                safe = true;
            else if (! water.contains (mainBox))
                safe = true;
            
            logs[i]->timerCallback();
            
            int position;
            
            if (logs[i]->getDirection())
            {
                position = logs[i]->getPosition().getX();
            }
            else
                position = logs[i]->getPosition().getBottomRight().getX();
            
            if (position > -140 && position < (getWidth()+140))
            {
                if (logs[i]->getLandable())
                    g.setColour(Colours::brown);
                else
                    g.setColour(Colours::aqua);
                
                g.fillRect(logs[i]->getPosition());
            }
            else
                logs.remove(i);
        }
        
        //Frogger
        g.setColour(Colours::green);
        g.fillRect(mainBox);
        
        //Cars
        for (int i = 0; i < cars.size(); i++)
        {
            if (cars[i]->getPosition().intersects(mainBox))
            {
                safe = false;
                //reset();
            }
            
            cars[i]->timerCallback();
            
            int position;
            
            if (cars[i]->getDirection())
            {
                position = cars[i]->getPosition().getX();
            }
            else
                position = cars[i]->getPosition().getBottomRight().getX();
            
            if (position > -140 && position < (getWidth()+140))
            {
                g.setColour(Colours::red);
                g.fillRect(cars[i]->getPosition());
            }
            else
                cars.remove(i);
        }
        
        reset();
    }
    
    void timerCallback()
    {
        if (random.nextInt(100) >= 90)
        {
            //Spawn Vehicle
            cars.insert(-1, new Vehicle(random));
        }

        if (random.nextInt(100) >= 75)
        {
            //Spawn Logs
            logs.insert(-1, new Logs(random));
        }
        
        if (keyDown)
        {
            String direction = currentKey.getTextDescription().fromFirstOccurrenceOf("Cursor ", false, true);

            moveBox(direction, 10);
        }
        
        repaint();
    }
    
    void moveBox(String direction, int amount)
    {
        if (direction == "up")
        {
            if (mainBox.getY() - amount > 0)
                mainBox.setY (mainBox.getY() - amount);
            else
                mainBox.setY (0);
        }
        else if (direction == "left")
        {
            if (mainBox.getX() - amount > 0)
                mainBox.setX (mainBox.getX() - amount);
            else
                mainBox.setX (0);
        }
        else if (direction == "down")
        {
            if (mainBox.getY() + amount < (getHeight()-20))
                mainBox.setY (mainBox.getY() + amount);
            else
                mainBox.setY (getHeight()-20);
        }
        else if (direction == "right")
        {
            if (mainBox.getX() + amount < (getWidth()-20))
                mainBox.setX (mainBox.getX() + amount);
            else
                mainBox.setX (getWidth()-2);
        }
    }
    
    void reset()
    {
        if (!safe)
        {
            mainBox.setX(getWidth()/2);
            mainBox.setY(getHeight()-20);
            
            safe = true;
        }
    }

    
private:
    Rectangle<int> mainBox;
    Random random;

    bool safe;
    
    OwnedArray <Vehicle> cars;
    OwnedArray<Logs> logs;
};

#endif /* defined(__JuceGames__Frogger__) */
