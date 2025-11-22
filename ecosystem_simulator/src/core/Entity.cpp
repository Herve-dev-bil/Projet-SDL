#include "Core/Entity.h"
#include <cmath>
#include <iostream>

namespace Ecosystem {
namespace Core {

// CONSTRUCTEUR PRINCIPAL
Entity::Entity(EntityType type, Vector2D pos, std::string entityName)
    : mType(type), position(pos), name(entityName), 
      mRandomGenerator(std::random_device{}()) 
{
    // Initialisation selon le type
    switch (mType) {
        case EntityType::HERBIVORE:
            mEnergy = 80.0f; mMaxEnergy = 150.0f; mMaxAge = 200;
            color = Color::Blue(); size = 8.0f;
            break;
        case EntityType::CARNIVORE:
            mEnergy = 100.0f; mMaxEnergy = 200.0f; mMaxAge = 150;
            color = Color::Red(); size = 12.0f;
            break;
        case EntityType::PLANT:
            mEnergy = 50.0f; mMaxEnergy = 100.0f; mMaxAge = 300;
            color = Color::Green(); size = 6.0f;
            break;
    }
    mAge = 0;
    mIsAlive = true;
    mVelocity = GenerateRandomDirection();
}

// CONSTRUCTEUR DE COPIE (Pour la reproduction)
Entity::Entity(const Entity& other)
    : mType(other.mType), position(other.position), name(other.name + "_copy"),
      mEnergy(other.mEnergy * 0.7f), // L'enfant part avec moins d'énergie
      mMaxEnergy(other.mMaxEnergy),
      mAge(0), // Age remis à 0
      mMaxAge(other.mMaxAge),
      mIsAlive(true),
      mVelocity(other.mVelocity),
      color(other.color),
      size(other.size * 0.8f),
      mRandomGenerator(std::random_device{}())
{
}

// DESTRUCTEUR
Entity::~Entity() {
    // std::cout << "Entité détruite: " << name << std::endl;
}

// MISE A JOUR
void Entity::Update(float deltaTime) {
    if (!mIsAlive) return;
    ConsumeEnergy(deltaTime);
    Age(deltaTime);
    Move(deltaTime);
    CheckVitality();
}

void Entity::Move(float deltaTime) {
    if (mType == EntityType::PLANT) return; // Les plantes ne bougent pas

    // Changement de direction aléatoire
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);
    if (chance(mRandomGenerator) < 0.02f) {
        mVelocity = GenerateRandomDirection();
    }

    position = position + (mVelocity * deltaTime * 20.0f);
    
    // Coût énergétique du mouvement
    mEnergy -= 0.5f * deltaTime;
}

void Entity::Eat(float energy) {
    mEnergy += energy;
    if (mEnergy > mMaxEnergy) mEnergy = mMaxEnergy;
}

void Entity::ConsumeEnergy(float deltaTime) {
    float baseConsumption = 0.5f;
    if (mType == EntityType::PLANT) baseConsumption = -0.5f; // Photosynthèse
    mEnergy -= baseConsumption * deltaTime;
}

void Entity::Age(float deltaTime) {
    // On simule le vieillissement
    if(deltaTime > 0) mAge++; 
}

void Entity::CheckVitality() {
    if (mEnergy <= 0.0f || mAge >= mMaxAge) {
        mIsAlive = false;
    }
}

bool Entity::CanReproduce() const {
    return mIsAlive && mEnergy > (mMaxEnergy * 0.8f) && mAge > 20;
}

std::unique_ptr<Entity> Entity::Reproduce() {
    if (!CanReproduce()) return nullptr;

    std::uniform_real_distribution<float> chance(0.0f, 1.0f);
    if (chance(mRandomGenerator) < 0.05f) { // 5% de chance par frame si conditions réunies
        mEnergy *= 0.6f; // Coût de reproduction
        return std::make_unique<Entity>(*this);
    }
    return nullptr;
}

Vector2D Entity::GenerateRandomDirection() {
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    return Vector2D(dist(mRandomGenerator), dist(mRandomGenerator));
}

Color Entity::CalculateColorBasedOnState() const {
    Color baseColor = color;
    if (GetEnergyPercentage() < 0.3f) {
        // Devient plus pâle si faible énergie
        baseColor.a = 150;
    }
    return baseColor;
}

void Entity::Render(SDL_Renderer* renderer) const {
    if (!mIsAlive) return;
    Color c = CalculateColorBasedOnState();
    
    // SDL3 utilise des float pour les rects
    SDL_FRect rect = { position.x, position.y, size, size };
    
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(renderer, &rect);
}

} // namespace Core
} // namespace Ecosystem