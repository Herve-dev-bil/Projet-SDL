#pragma once
#include "Structs.h"
#include <SDL3/SDL.h>
#include <memory>
#include <random>
#include <vector>
#include <string>

namespace Ecosystem {
namespace Core {

// ÉNUMÉRATION DES TYPES D'ENTITÉS
enum class EntityType {
    HERBIVORE,
    CARNIVORE,
    PLANT
};

class Entity {
private:
    // DONNÉES PRIVÉES (Encapsulation)
    float mEnergy;
    float mMaxEnergy;
    int mAge;
    int mMaxAge;
    bool mIsAlive;
    Vector2D mVelocity;
    EntityType mType;
    
    // Générateur aléatoire
    mutable std::mt19937 mRandomGenerator;

public:
    // DONNÉES PUBLIQUES
    Vector2D position;
    Color color;
    float size;
    std::string name;

    // CONSTRUCTEURS & DESTRUCTEUR
    Entity(EntityType type, Vector2D pos, std::string entityName = "Unnamed");
    Entity(const Entity& other); // Constructeur de copie
    ~Entity();

    // MÉTHODES PUBLIQUES
    void Update(float deltaTime);
    void Move(float deltaTime);
    void Eat(float energy);
    bool CanReproduce() const;
    std::unique_ptr<Entity> Reproduce();
    
    // GETTERS
    float GetEnergy() const { return mEnergy; }
    float GetEnergyPercentage() const { return mEnergy / mMaxEnergy; }
    int GetAge() const { return mAge; }
    bool IsAlive() const { return mIsAlive; }
    EntityType GetType() const { return mType; }

    // MÉTHODE DE RENDU
    void Render(SDL_Renderer* renderer) const;

private:
    // MÉTHODES PRIVÉES (Logique interne)
    void ConsumeEnergy(float deltaTime);
    void Age(float deltaTime);
    void CheckVitality();
    Vector2D GenerateRandomDirection();
    Color CalculateColorBasedOnState() const;
};

} // namespace Core
} // namespace Ecosystem