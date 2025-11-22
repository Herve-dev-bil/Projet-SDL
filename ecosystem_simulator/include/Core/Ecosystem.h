#pragma once
#include "Entity.h"
#include "Structs.h"
#include <vector>    //  pour std::vector
#include <memory>    //  pour std::unique_ptr
#include <random>    // Pour std::mt19937
#include <SDL3/SDL.h> // pour SDL_Renderer*

namespace Ecosystem {
namespace Core {

class Ecosystem {
private:
    // ÉTAT INTERNE
    // C'est ici que l'on stocke tous les animaux.
    // On utilise unique_ptr pour que l'écosystème soit le "propriétaire" de la mémoire.
    std::vector<std::unique_ptr<Entity>> mEntities;
    
    // Les sources de nourriture (objets simples, pas de pointeurs nécessaires)
    std::vector<Food> mFoodSources;
    
    float mWorldWidth;
    float mWorldHeight;
    int mMaxEntities;
    int mDayCycle;

    // Générateur aléatoire
    std::mt19937 mRandomGenerator;

public:
    // STATISTIQUES (Structure publique pour pouvoir être lue de l'extérieur)
    struct Statistics {
        int totalHerbivores;
        int totalCarnivores;
        int totalPlants;
        int totalFood;
        int deathsToday;
        int birthsToday;
    } mStats;

    // CONSTRUCTEUR/DESTRUCTEUR
    Ecosystem(float width, float height, int maxEntities = 500);
    ~Ecosystem();

    // MÉTHODES PUBLIQUES
    // J'ai rétabli la parenthèse fermante qui manquait dans votre texte
    void Initialize(int initialHerbivores, int initialCarnivores, int initialPlants);
    
    void Update(float deltaTime);
    void SpawnFood(int count);
    void RemoveDeadEntities();
    void HandleReproduction();
    void HandleEating();

    // GETTERS
    int GetEntityCount() const { return mEntities.size(); }
    int GetFoodCount() const { return mFoodSources.size(); }
    Statistics GetStatistics() const { return mStats; }
    float GetWorldWidth() const { return mWorldWidth; }
    float GetWorldHeight() const { return mWorldHeight; }

    // MÉTHODES DE GESTION
    void AddEntity(std::unique_ptr<Entity> entity);
    void AddFood(Vector2D position, float energy = 25.0f);

    // RENDU
    void Render(SDL_Renderer* renderer) const;

private:
    // MÉTHODES PRIVÉES
    void UpdateStatistics();
    void SpawnRandomEntity(EntityType type);
    Vector2D GetRandomPosition() const;
    void HandlePlantGrowth(float deltaTime);
};

} // namespace Core
} // namespace Ecosystem