#include "main-window.hpp"
#include "orange-ball-detector.hpp"
#include "capture-image-from-camera.hpp"
#include "event-bus.hpp"
int main (int argc, char *argv[]) {
	
	CaptureImageFromCamera captureImageFromCamera;
	OrangeBallDetector orangeBallDetector;
	EventBus<EventImageCaptured> eventImageBus;
	eventImageBus.subscribe(&orangeBallDetector);
	
	auto app = Gtk::Application::create(argc, argv, "ch.agl-developpement.cpp-tutorial.raspberry-cpp-gtk-opencv");
	MainWindow mainWindow(300, 300);
	return app->run(mainWindow);	
}
