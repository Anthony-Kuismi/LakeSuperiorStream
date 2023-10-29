#include <memory> // We're using a unique ptr

// the imGUI graphical user interface code
// has been encapsulated into a class to make it a little
// more organized.
#include "StreamGUI.h"

int main(int, char**)
{
    // Create a new graphical user interface - the constructor will take
    // care of setting up the windows and other calls to make it work
    // with the operating system and windowing environment.
    std::unique_ptr<GUI> gui = std::make_unique<GUI>();

    gui->setBackgroundColor( 1.0f, 0.9f, 0.0f );

    // Once the GUI is initialized, functionality is turned over to the GUI
    // to handle key presses and other user interface work.
    gui->mainLoop();

    exit(EXIT_SUCCESS);
}
