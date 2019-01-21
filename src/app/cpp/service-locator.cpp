#include "service-locator.hpp"

#include "system-helper.hpp"

ServiceLocator * ServiceLocator::serviceLocator = nullptr;

void ServiceLocator::startUp() {
    serviceLocator = new ServiceLocator();
}

ServiceLocator * ServiceLocator::obtainInstance() {
    if (!serviceLocator) {
        startUp();
    }
    return serviceLocator;
}

ServiceLocator::ServiceLocator():
movieMaker(obtainPathToDesktopFolder().append("/live.avi"), 20.0),
captureImageFromCamera(),
orangeBallDetector(),
eventImageBus() {
    eventImageBus.subscribe(&orangeBallDetector);
    eventImageBus.subscribe(&movieMaker);
}

ServiceLocator::~ServiceLocator() {
    eventImageBus.unsubscribe(&orangeBallDetector);
    eventImageBus.unsubscribe(&movieMaker);
}

MovieMaker * ServiceLocator::locateMovieMaker() {
    return &movieMaker;
}

CaptureImageFromCamera * ServiceLocator::locateCaptureImageFromCamera() {
    return &captureImageFromCamera;
}

OrangeBallDetector * ServiceLocator::locateOrangeBallDetector() {
    return &orangeBallDetector;
}
