#ifndef ORANGE_BALL_DETECTOR_HPP
#define ORANGE_BALL_DETECTOR_HPP

#include <opencv2/highgui.hpp>

class OrangeBallDetector {
public:
    virtual ~OrangeBallDetector() = default;
    void detect(cv::Mat image);
    cv::Point2f getBallPosition();
    float getRadius();
    void setDebug(bool d);
    cv::Mat getImage();

private:
    cv::Mat resizedImage;
    cv::Mat blurImage;
    cv::Mat hsvImage;
    cv::Mat rangeImage;
    cv::Mat erodedImage;
    cv::Mat dilatedImage;

    cv::Point2f ballPosition;
    float radius;
    
    void showIfDebug(cv::Mat m);
    bool debug = false;
};

#endif
