#include "../Core/Entity.h"
#include <iostream>
#include <algorithm> 
#include <cmath>     

namespace Ecosystem {
namespace Core {

// 🏗 CONSTRUCTEUR PRINCIPAL
Entity::Entity(EntityType type, Vector2D pos, std::string entityName)
    : mType(type), position(pos), name(entityName),
      mRandomGenerator(std::random_device{}()) // Initialisation du générateur aléatoire
{
    // INITIALISATION SELON LE TYPE
    switch (mType) {
        case EntityType::HERBIVORE:
            mEnergy = 80.0f;
            mMaxEnergy = 150.0f;
            mMaxAge = 200;
            color = Color::Blue();
            size = 8.0f;
            break;
        case EntityType::CARNIVORE:
            mEnergy = 100.0f;
            mMaxEnergy = 200.0f;
            mMaxAge = 150;
            color = Color::Red();
            size = 12.0f;
            break;
        case EntityType::PLANT:
            mEnergy = 50.0f;
            mMaxEnergy = 100.0f;
            mMaxAge = 300;
            color = Color::Green();
            size = 6.0f;
            break;
    }

    mAge = 0;
    mIsAlive = true;
    mVelocity = GenerateRandomDirection();
    
    // Correction de la ligne coupée
    std::cout << "🌱 Entité créée: " << name << " à (" << position.x << ", " << position.y << ")" << std::endl;
}

// 🏗 CONSTRUCTEUR DE COPIE
Entity::Entity(const Entity& other)
    : mType(other.mType), position(other.position), name(other.name + "_copy"),
      mEnergy(other.mEnergy * 0.7f), // Enfant a moins d'énergie
      mMaxEnergy(other.mMaxEnergy),
      mAge(0), // Nouvelle entité, âge remis à 0
      mMaxAge(other.mMaxAge),
      mIsAlive(true),
      mVelocity(other.mVelocity),
      color(other.color),
      size(other.size * 0.8f), // Enfant plus petit
      mRandomGenerator(std::random_device{}())
{
    // Correction : Le cout doit être DANS les accolades
    std::cout << "👶 Copie d'entité créée: " << name << std::endl;
}

// 🗑 DESTRUCTEUR
Entity::~Entity() {
    // Correction de la ligne coupée
    std::cout << "💀 Entité détruite: " << name << " (Age: " << mAge << ")" << std::endl;
}

// ⚙ MISE À JOUR PRINCIPALE
void Entity::Update(float deltaTime) {
    if (!mIsAlive) return;

    // PROCESSUS DE VIE
    ConsumeEnergy(deltaTime);
    Age(deltaTime);
    Move(deltaTime);
    CheckVitality();
}

// 🏃 MOUVEMENT
void Entity::Move(float deltaTime) {
    if (mType == EntityType::PLANT) return; // Les plantes ne bougent pas

    // Comportement aléatoire occasionnel
    // Correction : Ajout de <float> manquant
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);
    
    if (chance(mRandomGenerator) < 0.02f) {
        mVelocity = GenerateRandomDirection();
    }

    // Application du mouvement
    position = position + mVelocity * deltaTime * 20.0f;

    // Consommation d'énergie due au mouvement
    mEnergy -= mVelocity.Distance(Vector2D(0, 0)) * deltaTime * 0.1f;
}

// 🍽 MANGER
void Entity::Eat(float energy) {
    mEnergy += energy;
    if (mEnergy > mMaxEnergy) {
        mEnergy = mMaxEnergy;
    }
    std::cout << "🍽 " << name << " mange et gagne " << energy << " énergie" << std::endl;
}

// 🔋 CONSOMMATION D'ÉNERGIE
void Entity::ConsumeEnergy(float deltaTime) {
    float baseConsumption = 0.0f;
    switch (mType) {
        case EntityType::HERBIVORE:
            baseConsumption = 1.5f;
            break;
        case EntityType::CARNIVORE:
            baseConsumption = 2.0f;
            break;
        case EntityType::PLANT:
            baseConsumption = -0.5f; // Les plantes génèrent de l'énergie !
            break;
    }
    mEnergy -= baseConsumption * deltaTime;
}

// ⏳ VIEILLISSEMENT
void Entity::Age(float deltaTime) {
    // Correction : static_cast<int>
    mAge += static_cast<int>(deltaTime * 10.0f); // Accéléré pour la simulation
}

// ❤ VÉRIFICATION DE LA SANTÉ
void Entity::CheckVitality() {
    if (mEnergy <= 0.0f || mAge >= mMaxAge) {
        mIsAlive = false;
        std::cout << "💀 " << name << " meurt - ";
        if (mEnergy <= 0) std::cout << "Faim";
        else std::cout << "Vieillesse";
        std::cout << std::endl;
    }
}

// ❤ REPRODUCTION
bool Entity::CanReproduce() const {
    return mIsAlive && mEnergy > mMaxEnergy * 0.8f && mAge > 20;
}

std::unique_ptr<Entity> Entity::Reproduce() {
    if (!CanReproduce()) return nullptr;

    // Chance de reproduction
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);
    if (chance(mRandomGenerator) < 0.3f) {
        mEnergy *= 0.6f; // Coût énergétique de la reproduction
        // Correction : std::make_unique<Entity>
        return std::make_unique<Entity>(*this); // Utilise le constructeur de copie
    }
    return nullptr;
}

// 🎲 GÉNÉRATION DE DIRECTION ALÉATOIRE
Vector2D Entity::GenerateRandomDirection() {
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    return Vector2D(dist(mRandomGenerator), dist(mRandomGenerator));
}

// 🎨 CALCUL DE LA COULEUR BASÉE SUR L'ÉTAT
Color Entity::CalculateColorBasedOnState() const {
    float energyRatio = GetEnergyPercentage();
    Color baseColor = color;

    // Rouge si faible énergie
    if (energyRatio < 0.3f) {
        baseColor.r = 255;
        // Correction : static_cast<uint8_t> car ce sont des entiers 8 bits
        baseColor.g = static_cast<uint8_t>(baseColor.g * energyRatio);
        baseColor.b = static_cast<uint8_t>(baseColor.b * energyRatio);
    }
    return baseColor;
}

// 🖌 RENDU GRAPHIQUE
void Entity::Render(SDL_Renderer* renderer) const {
    if (!mIsAlive) return;

    Color renderColor = CalculateColorBasedOnState();

    // SDL_FRect est utilisé dans SDL3 (Float Rect)
    SDL_FRect rect = {
        position.x - size / 2.0f,
        position.y - size / 2.0f,
        size,
        size
    };

    // Correction des arguments manquants (alpha channel)
    SDL_SetRenderDrawColor(renderer, renderColor.r, renderColor.g, renderColor.b, renderColor.a);
    SDL_RenderFillRect(renderer, &rect);

    // Indicateur d'énergie (barre de vie)
    if (mType != EntityType::PLANT) {
        float energyBarWidth = size * GetEnergyPercentage();
        SDL_FRect energyBar = {
            position.x - size / 2.0f,
            position.y - size / 2.0f - 3.0f,
            energyBarWidth,
            2.0f
        };
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &energyBar);
    }
}


// Ces fonctions étaient dans le .hpp mais pas dans le texte fourni.


Vector2D Entity::SeekFood(const std::vector<Food>& foodSources) const {
    // TODO: Parcourir la liste foodSources, trouver la plus proche et retourner le vecteur direction
    return Vector2D(0, 0); // Pour l'instant, ne fait rien
}

Vector2D Entity::AvoidPredators(const std::vector<Entity>& predators) const {
    // TODO: Détecter les prédateurs proches et fuir
    return Vector2D(0, 0); 
}

Vector2D Entity::StayInBounds(float worldWidth, float worldHeight) const {
    // TODO: Si position.x < 0, renvoyer une force vers la droite, etc.
    return Vector2D(0, 0); 
}

} // namespace Core
} // namespace Ecosystem