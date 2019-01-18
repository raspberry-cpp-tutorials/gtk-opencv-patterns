#ifndef ORANGE_BALL_DETECTOR_HPP
#define ORANGE_BALL_DETECTOR_HPP

#include <opencv2/highgui.hpp>
#include "event-bus.hpp"
#include "capture-image-from-camera.hpp"

class EventOrangeDetected {
    friend class OrangeBallDetector;
public:
    EventOrangeDetected();
    cv::Mat getCapturedImage();
    cv::Point2f getBallPosition();
    float getRadius();
    bool hasDetectedSomething();
private:
    EventOrangeDetected(cv::Mat i);
    EventOrangeDetected(cv::Mat i, cv::Point2f bp, float r);
    cv::Mat capturedImage;
    cv::Point2f ballPosition;
    float radius;
};

class OrangeBallDetector :
public Subscriptor<EventImageCaptured> {
public:
    void receive(EventImageCaptured e);
    void detect(cv::Mat image);
    virtual ~OrangeBallDetector() = default;
    void setDebug(bool d);
    cv::Mat getCapturedImage();
    cv::Point2f getBallPosition();
    float getRadius();
    
private:
    cv::Mat resizedImage;
    cv::Mat blurImage;
    cv::Mat hsvImage;
    cv::Mat rangeImage;
    cv::Mat erodedImage;
    cv::Mat dilatedImage;

    EventBus<EventOrangeDetected> eventBus;

    cv::Point2f ballPosition;
    float radius;
    
    void showIfDebug(cv::Mat m);
    bool debug = false;
};

#endif
