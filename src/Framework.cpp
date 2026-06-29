#include "Framework.h"
#include <iostream>
#include <cmath>
#include <algorithm>

const std::string pathSep =
#ifdef _WIN32
        "\\";
#else
        "/";
#endif

Framework::Framework(int fps, int shipSize, int missileSize)
{
    init(-1, -1, fps, shipSize, missileSize);
}

Framework::Framework(int width, int height, int fps, int shipSize, int missileSize)
{
    init(width, height, fps, shipSize, missileSize);
}

Framework::~Framework()
{
    SDL_Quit();
}

int Framework::getScreenWidth() const { return width; }
int Framework::getScreenHeight() const { return height; }

int Framework::getInput()
{
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
            return SDL_EVENT_QUIT;
        if (e.type == SDL_EVENT_KEY_DOWN)
            return static_cast<int>(e.key.key);
    }
    return 0;
}

void Framework::update()
{
    int nbTicksWait{0};
    Uint32 now = SDL_GetTicks();
    while (now - lastTimeScreenUpdate < ticksForNextFrame)
    {
        SDL_Delay(1);
        nbTicksWait++;
        now = SDL_GetTicks();
    }

    if (lastTimeScreenUpdate != 0u && nbTicksWait == 0)
        std::cout << "Warning, FPS too high, lagged for " << now - lastTimeScreenUpdate << " ms" << std::endl;

    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    lastTimeScreenUpdate = SDL_GetTicks();
}

void Framework::drawShip(const int x, const int y, const float angle, const float shieldLevel, const bool warning) const
{
    const int shieldSize = shipSize * 1.3;

    if (warning)
        drawSprite(textureShipWarning, x, y, shipSize, shipSize, angle);
    else
        drawSprite(textureShip, x, y, shipSize, shipSize, angle);

    if (shieldLevel > 0.0)
        drawSpriteAlpha(textureShield, x, y, shieldSize, shieldSize, 0.0, shieldLevel);
}

void Framework::drawAsteroid(const int x, const int y, const int size) const
{
    drawSprite(textureAsteroid, x, y, size, size, 0);
}

void Framework::drawMissile(const int x, const int y) const
{
    drawSprite(textureMissile, x, y, missileSize, missileSize, 0.0);
}

void Framework::drawAimLine(int shipX, int shipY, float angleDeg, int screenW, int screenH) const
{
    double radians = angleDeg * M_PI / 180.0;
    double dx = sin(radians);
    double dy = -cos(radians);

    double startX = shipX + 25.0 * dx;
    double startY = shipY + 25.0 * dy;

    double t = 1e9;
    if (dx > 0.001)       t = std::min(t, (screenW - startX) / dx);
    else if (dx < -0.001) t = std::min(t, -startX / dx);
    if (dy > 0.001)       t = std::min(t, (screenH - startY) / dy);
    else if (dy < -0.001) t = std::min(t, -startY / dy);

    double endX = startX + t * dx;
    double endY = startY + t * dy;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 100, 220, 255, 140);

    double pos = 0.0;
    bool drawing = true;
    double total = sqrt((endX - startX) * (endX - startX) + (endY - startY) * (endY - startY));

    while (pos < total) {
        double segEnd = std::min(pos + (drawing ? 12.0 : 8.0), total);
        if (drawing) {
            SDL_RenderLine(renderer,
                static_cast<float>(startX + dx * pos),
                static_cast<float>(startY + dy * pos),
                static_cast<float>(startX + dx * segEnd),
                static_cast<float>(startY + dy * segEnd));
        }
        pos = segEnd;
        drawing = !drawing;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

void Framework::drawHUD(float shieldLevel, int score) const
{
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_FRect bg = {10.0f, 10.0f, 150.0f, 14.0f};
    SDL_RenderFillRect(renderer, &bg);

    Uint8 r = static_cast<Uint8>(255 * (1.0f - shieldLevel));
    Uint8 g = static_cast<Uint8>(255 * shieldLevel);
    SDL_SetRenderDrawColor(renderer, r, g, 0, 255);
    SDL_FRect fill = {10.0f, 10.0f, 150.0f * shieldLevel, 14.0f};
    SDL_RenderFillRect(renderer, &fill);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, 10.0f, 30.0f, ("Score: " + std::to_string(score)).c_str());
}

void Framework::drawEndScreen(bool victory) const
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
    SDL_FRect overlay = {0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height)};
    SDL_RenderFillRect(renderer, &overlay);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    const float scale = 5.0f;
    SDL_SetRenderScale(renderer, scale, scale);

    std::string msg = victory ? "VICTOIRE !" : "GAME OVER";
    float scaledW = width / scale;
    float scaledH = height / scale;
    float textW = static_cast<float>(msg.size()) * 8.0f;

    if (victory)
        SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 80, 80, 255);

    SDL_RenderDebugText(renderer, (scaledW - textW) / 2.0f, (scaledH - 8.0f) / 2.0f, msg.c_str());
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

void Framework::init(int width, int height, int fps, int shipSize, int missileSize)
{
    srand(time(nullptr));

    if (!SDL_Init(0))
    {
        printf("Framework -> SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
    {
        std::cerr << SDL_GetError();
        SDL_Quit();
        exit(1);
    }

    if (width == -1 && height == -1)
    {
        const SDL_DisplayMode *dm = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
        if (dm == nullptr)
        {
            std::cerr << SDL_GetError();
            SDL_Quit();
            exit(1);
        }
        width = dm->w;
        height = dm->h;
    }

    window = SDL_CreateWindow("EFREIroid", width, height, SDL_WINDOW_OPENGL);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError();
        SDL_Quit();
        exit(1);
    }

    if (width == -1 && height == -1)
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError();
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    SDL_SetRenderVSync(renderer, 1);

    textureShip        = getTexture("spaceship.bmp");
    textureShipWarning = getTexture("redSpaceship.bmp");
    textureShield      = getTexture("shield.bmp");
    textureAsteroid    = getTexture("asteroid.bmp");
    textureMissile     = getTexture("missile.bmp");

    ticksForNextFrame = 1000 / fps;
    this->width       = width;
    this->height      = height;
    this->shipSize    = shipSize;
    this->missileSize = missileSize;
}

void Framework::drawSprite(SDL_Texture* texture, const int x, const int y, const int w, const int h, const float angle) const
{
    drawSpriteAlpha(texture, x, y, w, h, angle, 1.0);
}

void Framework::drawSpriteAlpha(SDL_Texture* texture, const int x, const int y, const int w, const int h, const float angle, const float alpha) const
{
    if (alpha < 1.0)
    {
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(texture, static_cast<Uint8>(255 * alpha));
    }
    SDL_FRect dest{
        static_cast<float>(x - (w / 2)), static_cast<float>(y - (h / 2)),
        static_cast<float>(w), static_cast<float>(h)
    };
    SDL_RenderTextureRotated(renderer, texture, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
}

SDL_Texture* Framework::getTexture(const std::string& imgName) const
{
    std::string imgPath = "resources" + pathSep + "images" + pathSep + imgName;
    SDL_Surface* sprite = SDL_LoadBMP(imgPath.c_str());
    if (!sprite)
    {
        std::cerr << "SDL_LoadBMP failed: " << SDL_GetError();
        exit(1);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, sprite);
    if (!texture)
    {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError();
        exit(1);
    }

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    return texture;
}
