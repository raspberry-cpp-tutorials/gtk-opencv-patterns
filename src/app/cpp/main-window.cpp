#include "main-window.hpp"

#include "service-locator.hpp"

#include <iostream>

MainWindow::MainWindow(int width, int height):
probablyInFullScreen(false),
movieMaker(ServiceLocator::getMovieMaker()){
    // Configure this window:
    this->set_default_size(width, height);

    // Make the second label visible:
    cameraDrawingArea.show();

    // Add the box in this window:
    add(cameraDrawingArea);

    // Activate Key-Press events
    add_events(Gdk::KEY_PRESS_MASK);
}

bool MainWindow::on_key_press_event(GdkEventKey* event) {
    switch (event->keyval) {
        // Ctrl + C: Ends the application:
        case GDK_KEY_C:
        case GDK_KEY_c:
            if ((event->state & GDK_CONTROL_MASK) == GDK_CONTROL_MASK) {
                get_application()->quit();
            }
            return true;
            
        // [P] Toggles the record pause:
        case GDK_KEY_P:
        case GDK_KEY_p:
            movieMaker->toggleRecording();
            return true;
            
        // [F] toggles full screen mode:
        case GDK_KEY_F:
        case GDK_KEY_f:
            if (probablyInFullScreen) {
                unfullscreen();
                probablyInFullScreen = false;
            } else {
                fullscreen();
                probablyInFullScreen = true;
            }
            return true;

        // [esc] exits full screen mode:
        case GDK_KEY_Escape:
            unfullscreen();
            probablyInFullScreen = false;
            return true;
    }

    return false;
}
