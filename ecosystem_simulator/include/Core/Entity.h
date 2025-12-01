#pragma once
#include "Structs.h"
#include <SDL3/SDL.h>
#include <memory> // Pour std::unique_ptr
#include <random> // Pour std::mt19937
#include <vector> // Pour std::vector

namespace Ecosystem
{
    namespace Core
    {

        // ÉNUMÉRATION DES TYPES D'ENTITÉS
        enum class EntityType
        {
            HERBIVORE,
            CARNIVORE,
            PLANT
        };

        class Entity
        {
        private:
            // DONNÉES PRIVÉES - État interne protégé
            // Le "m" devant signifie "member" (convention du cours)
            float mEnergy;
            float mMaxEnergy;
            int mAge;
            int mMaxAge;
            bool mIsAlive;
            Vector2D mVelocity;
            EntityType mType;

            // Générateur aléatoire
            // "mutable" permet de modifier cette variable même dans une fonction const
            mutable std::mt19937 mRandomGenerator;

        public:
            // DONNÉES PUBLIQUES - Accès direct sécurisé
            // On laisse la position publique pour faciliter l'accès par le moteur graphique
            Vector2D position;
            Color color;
            float size;
            std::string name;

            // CONSTRUCTEURS
            Entity(EntityType type, Vector2D pos, std::string entityName = "Unnamed");
            Entity(const Entity &other); // Constructeur de copie

            // DESTRUCTEUR
            ~Entity();

            // MÉTHODES PUBLIQUES
            void Update(float deltaTime);
            void Move(float deltaTime);
            void Eat(float energy);
            bool CanReproduce() const;

            // Retourne un pointeur unique vers le "bébé" (gestion mémoire automatique)
            std::unique_ptr<Entity> Reproduce();

            void ApplyForce(Vector2D force);

            // GETTERS - Accès contrôlé aux données privées
            float GetEnergy() const { return mEnergy; }
            float GetEnergyPercentage() const { return mEnergy / mMaxEnergy; }
            int GetAge() const { return mAge; }
            bool IsAlive() const { return mIsAlive; }
            EntityType GetType() const { return mType; }
            Vector2D GetVelocity() const { return mVelocity; }

            // MÉTHODES DE COMPORTEMENT (L'Intelligence Artificielle)
            // Notez les < > que j'ai rajoutés ci-dessous :
            Vector2D SeekFood(const std::vector<Food> &foodSources) const;
            Vector2D AvoidPredators(const std::vector<Entity> &predators) const; // C'était incomplet
            Vector2D StayInBounds(float worldWidth, float worldHeight) const;

            // MÉTHODE DE RENDU
            void Render(SDL_Renderer *renderer) const;

        private:
            // MÉTHODES PRIVÉES - Logique interne
            void ConsumeEnergy(float deltaTime);
            void Age(float deltaTime);
            void CheckVitality();
            Vector2D GenerateRandomDirection();
            Color CalculateColorBasedOnState() const;
        };

    } // namespace Core
} // namespace Ecosystem