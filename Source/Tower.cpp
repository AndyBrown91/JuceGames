//
//  Tower.cpp
//  JuceGames
//
//  Created by Andy on 29/09/2013.
//
//

#include "Tower.h"

TowerGame::TowerGame(Component* p, String _name) : GameClass(p, _name), world(b2Vec2(0.0f, -10.0f))
{
    // Define the gravity vector.
    //b2Vec2 gravity(0.0f, -10.0f);
    // Construct a world object, which will hold and simulate the rigid bodies.
    //b2World world(gravity);
    
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    
    // Define the ground box shape.
    b2PolygonShape groundBox;
    
    // The extents are the half-widths of the box.
    groundBox.SetAsBox(5.0f, 10.0f);
    
    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);
    
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);
    
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(10.0f, 10.0f);
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    
    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;
    
    // Override the default friction.
    fixtureDef.friction = 0.3f;
    
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);
}

TowerGame::~TowerGame()
{
    
}

void TowerGame::paint(Graphics &g)
{
    g.fillAll(Colours::white);
    
    Box2DRenderer box2d;
    
    box2d.render(g, world, 0, 0, getWidth(), getHeight(), Rectangle<float>(0,0,getWidth()*8, getHeight()*8));
}

void TowerGame::timerCallback()
{
    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    
    world.Step(timeStep, velocityIterations, positionIterations);
    
    while (world.GetBodyList()->GetNext() != nullptr) {
        b2Body* body = world.GetBodyList()->GetNext();
        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();
        
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    }

}

void TowerGame::reset()
{}

bool TowerGame::keyPressed(const KeyPress &key, Component *originatingComponent)
{}

bool TowerGame::keyStateChanged (bool isKeyDown, Component *originatingComponent)
{}