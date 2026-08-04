/// @file
/// @brief tiny portable GUI (SDL-based, no host OS integration)
#pragma once

#include <SDL2/SDL.h>
#include <assert.h>

/// @defgroup gui gui
/// @brief tiny portable GUI (SDL-based, no host OS integration)
/// @{

extern SDL_Window *window;
extern SDL_Renderer *renderer;

/// true color
struct RGB {
    uint8_t r;  ///< red
    uint8_t g;  ///< greeb
    uint8_t b;  ///< blue
} __attribute__((packed));

/// true color with alpha channel
struct RGBA {
    uint8_t r;  ///< red
    uint8_t g;  ///< greeb
    uint8_t b;  ///< blue
    uint8_t a;  ///< alpha
} __attribute__((packed));

class GUI {
   public:
    static void init(int argc, char *argv[]);  ///< start GUi system
    static void fini();   ///< stop GUI system (before @ref halt)
    static uint16_t W;    ///< screen width (cell phone emulation)
    static uint16_t H;    ///< screen height (cell phone emulation)
    static void clear();  ///< clear main window
    static RGB bg;        ///< defult background color
};
/// @}
