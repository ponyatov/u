#include "gui.hpp"

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

void GUI::init(int, char *[]) {  //
    assert(!SDL_Init(SDL_INIT_VIDEO));
    assert(!SDL_CreateWindowAndRenderer(GUI::W, GUI::H, SDL_WINDOW_HIDDEN,
                                        &window, &renderer));
}

void GUI::fini() {  //
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

uint16_t GUI::W = 240;
uint16_t GUI::H = 320;

RGB GUI::bg = {0x22, 0x22, 0x22};

void GUI::clear() {
    SDL_SetRenderDrawColor(renderer, GUI::bg.r, GUI::bg.g, GUI::bg.b, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
