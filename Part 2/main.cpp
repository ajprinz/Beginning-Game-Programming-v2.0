// Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>


// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


// Global Variables (not common practice)
// The window we'll be rendering to
SDL_Window* window = NULL;

// The surface contained by the window
SDL_Surface* screenSurface = NULL;

// The image we'll show on the surface
SDL_Surface* image = NULL;


// Starts SDL and creates the window
bool init() {

    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {

        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

    } else {

        //  Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        if (window == NULL) {

            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

        } else {
            // Get window surface
            screenSurface = SDL_GetWindowSurface(window);

        }
    }

    return success;

}


// Loads media such as images
bool loadMedia() {

    // Initialization flag
    bool success = true;

    // Load the image (.bmp has native support)
    image = SDL_LoadBMP("ps5.bmp");

    // Show error message if image doesn't load
    if (image == NULL) {

        printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
        success = false;

    }

    return success;

}


// Shut down SDL and free media memory
void close() {

    // Free the surface memory and reset the global variable
    SDL_FreeSurface(image);
    image = NULL;

    // Destroy the window and reset the global variable
    SDL_DestroyWindow(window);
    window = NULL;

    // Quit SDL subsystems
    SDL_Quit();

}



// main requires arguments so SDL is cross platform
int main(int argc, char* args[]) {

    // Create SDL window and check for errors
    if ( !init() ) {

        printf("Failed to initialize!\n");

    } else {

        // Load media and check for errors
        if ( !loadMedia() ) {

            printf("Failed to load media!\n");

        } else {

            // Apply the image
            SDL_BlitSurface(image, NULL, screenSurface, NULL);

            // Update the surface
            SDL_UpdateWindowSurface(window);

            // Wait two seconds to show the window
            SDL_Delay(2000);

        }

    }

    // Free memory resources and close SDL
    close();

    return 0;

}