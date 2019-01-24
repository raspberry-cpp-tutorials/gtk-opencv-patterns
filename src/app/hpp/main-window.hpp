#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "camera-drawing-area.hpp"

#include <gtkmm.h>

class MainWindow : public Gtk::Window {
public:
    MainWindow(int width, int height);
    virtual ~MainWindow() = default;

protected:
    bool on_key_press_event(GdkEventKey* event) override;

private:
    bool probablyInFullScreen;
    CameraDrawingArea cameraDrawingArea;
    MovieMaker * movieMaker;
};

#endif
