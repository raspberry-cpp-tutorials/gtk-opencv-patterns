#include "service-locator.hpp"

#include "system-helper.hpp"

ServiceLocator * ServiceLocator::serviceLocator = nullptr;

MovieMaker * ServiceLocator::movieMaker = nullptr;

CaptureImageFromCamera * ServiceLocator::captureImageFromCamera = nullptr;

OrangeBallDetector * ServiceLocator::orangeBallDetector = nullptr;

void ServiceLocator::startUp() {
    serviceLocator = new ServiceLocator();
}

ServiceLocator::ServiceLocator() {
    CaptureImageFromCamera captureImageFromCamera;
    OrangeBallDetector orangeBallDetector;
    MovieMaker movieMaker(obtainPathToDesktopFolder().append("/live.avi"), 20.0);

    EventBus<EventImageCaptured> eventImageBus;
    eventImageBus.subscribe(&orangeBallDetector);
    eventImageBus.subscribe(&movieMaker);
}

ServiceLocator::~ServiceLocator() {

}

MovieMaker * ServiceLocator::locateMovieMaker() {
    if (!movieMaker) {
        movieMaker = buildMovieMaker();
    }
    return movieMaker;
}
MovieMaker * ServiceLocator::buildMovieMaker() {
}
CaptureImageFromCamera * ServiceLocator::locateCaptureImageFromCamera() {
    if (!captureImageFromCamera) {
        captureImageFromCamera = buildCaptureImageFromCamera();
    }
    return captureImageFromCamera;
}

OrangeBallDetector * ServiceLocator::locateOrangeBallDetector() {
    if (!orangeBallDetector) {
        orangeBallDetector = buildOrangeBallDetector();
    }
    return orangeBallDetector;
}
