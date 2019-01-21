#ifndef SERVICE_LOCATOR_HPP
#define SERVICE_LOCATOR_HPP

#include "movie-maker.hpp"
#include "capture-image-from-camera.hpp"
#include "orange-ball-detector.hpp"

class ServiceLocator {
public:
    virtual ~ServiceLocator();

    static void startUp();
    static ServiceLocator * getInstance();
    static MovieMaker * getMovieMaker();
    static CaptureImageFromCamera * getCaptureImageFromCamera();
    static OrangeBallDetector * getOrangeBallDetector();

    // Don't copy a singleton.
    ServiceLocator(const ServiceLocator &) = delete;
    // Don't copy a singleton.
    ServiceLocator& operator= (const ServiceLocator &) = delete;

private:
    MovieMaker movieMaker;
    CaptureImageFromCamera captureImageFromCamera;
    OrangeBallDetector orangeBallDetector;
    EventBus<EventImageCaptured> eventImageBus;
    
    // Don't instantiate a singleton.
    ServiceLocator();
};

#endif
