#include "service-locator.hpp"

#include "system-helper.hpp"

void ServiceLocator::startUp() {
    getInstance();
}

ServiceLocator * ServiceLocator::getInstance() {
    static ServiceLocator serviceLocator;
    return &serviceLocator;
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

MovieMaker * ServiceLocator::getMovieMaker() {
    return & getInstance()->movieMaker;
}

CaptureImageFromCamera * ServiceLocator::getCaptureImageFromCamera() {
    return & getInstance()->captureImageFromCamera;
}

OrangeBallDetector * ServiceLocator::getOrangeBallDetector() {
    return & getInstance()->orangeBallDetector;
}
