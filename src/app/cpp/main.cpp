#include "main-window.hpp"

#include "capture-image-from-camera.hpp"
#include "event-bus.hpp"
#include "movie-maker.hpp"
#include "orange-ball-detector.hpp"
#include "system-helper.hpp"

int main (int argc, char *argv[]) {

	CaptureImageFromCamera captureImageFromCamera;
	OrangeBallDetector orangeBallDetector;
	MovieMaker movieMaker(obtainPathToDesktopFolder().append("/live.avi"), 20.0);

	EventBus<EventImageCaptured> eventImageBus;
	eventImageBus.subscribe(&orangeBallDetector);
	eventImageBus.subscribe(&movieMaker);

	auto app = Gtk::Application::create(argc, argv, "ch.agl-developpement.cpp-tutorial.raspberry-cpp-gtk-opencv");
	MainWindow mainWindow(300, 300);
	return app->run(mainWindow);	
}
