#pragma once

#include <string>
#include <SDL3/SDL.h>

/**
 * @class Framework
 * @brief Classe gérant l'affichage, les entrées et le rendu des sprites du jeu.
 */
class Framework {
public:
    /**
     * @brief Lance l'affichage plein écran dans la résolution courante.
     * @param fps Taux de rafraîchissement (images par seconde).
     * @param shipSize Taille d'affichage du vaisseau, en pixels.
     * @param missileSize Taille d'affichage du missile, en pixels.
     */
    Framework(int fps, int shipSize, int missileSize);

    /**
     * @brief Lance l'affichage dans la résolution choisie.
     * @param width Largeur de la fenêtre.
     * @param height Hauteur de la fenêtre.
     * @param fps Taux de rafraîchissement (images par seconde).
     * @param shipSize Taille d'affichage du vaisseau, en pixels.
     * @param missileSize Taille d'affichage du missile, en pixels.
     */
    Framework(int width, int height, int fps, int shipSize, int missileSize);

    ~Framework();

    int getScreenWidth() const;
    int getScreenHeight() const;

    static int getInput();

    void update();

    void drawShip(const int x, const int y, const float angle, const float shieldLevel, const bool warning) const;
    void drawAsteroid(const int x, const int y, const int size) const;
    void drawMissile(const int x, const int y) const;

    void drawAimLine(int x, int y, float angleDeg, int screenW, int screenH) const;
    void drawHUD(float shieldLevel, int score) const;
    void drawEndScreen(bool victory) const;

private:
    SDL_Window*   window;
    SDL_Renderer* renderer;

    int    width;
    int    height;
    Uint32 ticksForNextFrame;
    Uint32 lastTimeScreenUpdate = 0;

    SDL_Texture* textureShip;
    SDL_Texture* textureShipWarning;
    SDL_Texture* textureAsteroid;
    SDL_Texture* textureMissile;
    SDL_Texture* textureShield;

    int shipSize;
    int missileSize;

    void init(int width, int height, int fps, int shipSize, int missileSize);
    void drawSprite(SDL_Texture* texture, const int x, const int y, const int w, const int h, const float angle) const;
    void drawSpriteAlpha(SDL_Texture* texture, const int x, const int y, const int w, const int h, const float angle, const float alpha) const;
    SDL_Texture* getTexture(const std::string& imgName) const;
};
