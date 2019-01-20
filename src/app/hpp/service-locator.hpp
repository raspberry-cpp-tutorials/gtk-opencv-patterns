#ifndef SERVICE_LOCATOR_HPP
#define SERVICE_LOCATOR_HPP

#include "movie-maker.hpp"
#include "capture-image-from-camera.hpp"
#include "orange-ball-detector.hpp"

class ServiceLocator {
public:
    ServiceLocator();
    virtual ~ServiceLocator();
    void startUp();
    static ServiceLocator * obtainInstance();
    MovieMaker * locateMovieMaker();
    CaptureImageFromCamera * locateCaptureImageFromCamera();
    OrangeBallDetector * locateOrangeBallDetector();
    
private:
    static ServiceLocator * serviceLocator;
    static MovieMaker * movieMaker;
    static CaptureImageFromCamera * captureImageFromCamera;
    static OrangeBallDetector * orangeBallDetector;
}

#endif
