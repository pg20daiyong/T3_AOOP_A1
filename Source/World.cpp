#include "World.h"
#include "EngineInterface.h"
#include "ActorFactoryImpl.h"
#include "ActorPoolImpl.h"
#include "ActorImpl.h"
#include "Ship.h"
#include "EventSystem.h"
#include "Callbacks.h"
#include "TransformComponent.h"
#include "SquareRenderingComponent.h"
#include "SquareWithinSquareRenderingComponent.h"

World* World::sWorld = nullptr;

void ShootCallback(const IEventArgs& shootEvt);
void CollisionCallback(const IEventArgs& collisionEvt);

World* World::GetInstance()
{
    if (sWorld == nullptr)
    {
        sWorld = new World();
    }
    return sWorld;
}

World::~World()
{

}

void World::Initialize()
{
    mPlayerLives = 3;
    mPlayerScore = 0;
    mPlayedTime = 0.0f;

    SetupShip();
    SetupBulletPool();
    SetupAsteroidManager();
    SetupCallbacks();
}

void World::Update(float deltaTime)
{
    if (mGameState == GameState::Playing)
    {
        mPlayedTime += deltaTime;

        mAsteroidMgr.Update(deltaTime);

        for (Actor* actor : mActors)
        {
            if (actor->IsActive())
            {
                actor->Update(deltaTime);
            }
        }

        for (Actor* actor : mActors)
        {
            auto* collider = actor->GetComponent<ColliderComponent>(ComponentType::Collider);
            if (actor->IsActive() && collider != nullptr)
            {
                collider->Update(deltaTime);
            }
        }
        //Rendering Path

        for (Actor* actor : mActors)
        {
            // Get SquareRendering 
            // If that null?

            //Get SquareWithinRendering
            // If that
            auto* squareRendering = actor->GetComponent<SquareRenderingComponent>(ComponentType::SquareRendering);
            auto* squareWithinSquareRendering = actor->GetComponent<SquareWithinSquareRenderingComponent>(ComponentType::SquareWithinSquareRendering);
            if (actor->IsActive())
            {
                if (squareRendering != nullptr)
                {
                    squareRendering->Render();
                }
                else if (squareWithinSquareRendering != nullptr)
                {
                    squareWithinSquareRendering->Render();
                }
            }   
        }
    }  
}
void World::PostUpdate()
{
    if (mGameState == GameState::Playing)
    {
        for (Actor* actor : mActors)
        {
            auto* collider = actor->GetComponent<ColliderComponent>(ComponentType::Collider);
            if (actor->IsActive() && collider != nullptr)
            {
                collider->PostUpdate();
            }
        }
    }
}

void World::HurtPlayer(int damage)
{
    mPlayerLives -= damage;

    if (mPlayerLives <= 0)
    {
        mGameState = GameState::GameOver;
    }
    else
    {
        Ship* ship = static_cast<Ship*>(mActors[mShipID]);
        ship->PlayHurt();
    }
}

void World::AddActor(Actor* actor)
{
    mActors.push_back(actor);
}

void World::SetupShip()
{
    auto ship = ACTORFAC->CreateActor<Ship>();
    mShipID = ship->GetID();
    ship->Initialize();
}

void World::SetupBulletPool()
{
    mBulletPoolSize = 10;
    mBulletPool = new ActorPool<Bullet>();
    mBulletPool->InitializePool(mBulletPoolSize);
}

void World::SetupAsteroidManager()
{
    // lambda 
    auto generator = [this]() -> exVector2
    {
        auto shipTransform = mActors[mShipID]->GetComponent<TransformComponent>(ComponentType::Transform);
        exVector2 target = exVector2((rand() % 150) - 75, 0);
        target.x += shipTransform->GetPosition().x;
        target.y += shipTransform->GetPosition().y;
        return target;
    };

    mAsteroidMgr.Initialize(20, 2.0f, generator);
}

void World::SetupCallbacks()
{
    EVTSYS->StartListening(EventTypes::Shoot, &ShootCallback);
    EVTSYS->StartListening(EventTypes::Collision, &CollisionCallback);
}