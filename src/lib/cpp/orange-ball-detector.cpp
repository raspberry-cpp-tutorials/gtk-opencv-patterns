#include "orange-ball-detector.hpp"

#include <opencv2/imgproc.hpp>

#define ORANGE_BALL_DETECTOR_IMAGE_WIDTH 600

void OrangeBallDetector::receive(EventImageCaptured e) {
    detect(e.getCapturedImage());
}

void OrangeBallDetector::detect(cv::Mat image) {
    if (image.empty()) {
        return;
    }
    radius = 0;
    ballPosition.x = 0;
    ballPosition.y = 0;

    // Make the image of a reasonable size:
    double width = image.size().width;
    double scale = ORANGE_BALL_DETECTOR_IMAGE_WIDTH / width;
    resize(image, resizedImage, cv::Size(), scale, scale, cv::INTER_LINEAR);
    showIfDebug(resizedImage);

    GaussianBlur(resizedImage, blurImage, cv::Size(11, 11), 0);
    showIfDebug(blurImage);

    cvtColor(blurImage, hsvImage, cv::COLOR_BGR2HSV );
    showIfDebug(hsvImage);


    // Detect the color orange: (Hue, Sat, Val)
    auto lowOrange =  cv::Scalar(  7, 170, 120);
    auto highOrange = cv::Scalar( 18, 255, 255);
    inRange(hsvImage, lowOrange, highOrange, rangeImage);

    // Smooth it out:
    erode(rangeImage, erodedImage, 2);
    dilate(erodedImage, dilatedImage, 2);
    showIfDebug(dilatedImage);

    // Detect contours:
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours( dilatedImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );

    // If any contour:
    if (!contours.empty()) {

        // Find the biggest contour:
        double maxArea = -1;
        std::vector<cv::Point> maxContour;
        for (auto contour : contours) {
            double area = cv::contourArea(contour);
            if (area > maxArea) {
                maxArea = area;
                maxContour = contour;
            }
        }

        // Assuming that biggest contour is a circle,
        // determine its center and size:
        cv::minEnclosingCircle(maxContour, ballPosition, radius);
        showIfDebug(resizedImage);
    }
    eventBus.propagate(EventOrangeDetected(
            resizedImage,
            ballPosition / ORANGE_BALL_DETECTOR_IMAGE_WIDTH,
            radius / ORANGE_BALL_DETECTOR_IMAGE_WIDTH));
}

void OrangeBallDetector::setDebug(bool d) {
    debug = d;
}

void OrangeBallDetector::showIfDebug(cv::Mat m) {
    if (debug) {
        if (radius > 20) {
            cv::circle(m, ballPosition, radius, cv::Scalar(0, 255, 0), 3);
        }
        imshow("orange-ball-detector", m);
        cv::waitKey(0);
    }
}

cv::Mat OrangeBallDetector::getCapturedImage() {
    return resizedImage;
}

cv::Point2f OrangeBallDetector::getBallPosition() {
    return ballPosition;
}

float OrangeBallDetector::getRadius() {
    return radius;
}

EventOrangeDetected::EventOrangeDetected():
EventOrangeDetected(cv::Mat(), cv::Point2f(), 0) {
    // Nothing to do.
}

EventOrangeDetected::EventOrangeDetected(cv::Mat i):
EventOrangeDetected(i, cv::Point2f(), 0) {
    // Nothing to do.
}

EventOrangeDetected::EventOrangeDetected(cv::Mat i, cv::Point2f bp, float r):
capturedImage(i),
ballPosition(bp),
radius(r) {
    // Nothing to do
}

cv::Mat EventOrangeDetected::getCapturedImage() {
    return capturedImage;
}

cv::Point2f EventOrangeDetected::getBallPosition() {
    return ballPosition;
}

float EventOrangeDetected::getRadius() {
    return radius;
}

bool EventOrangeDetected::hasDetectedSomething() {
    return radius > 10 / ORANGE_BALL_DETECTOR_IMAGE_WIDTH;
}
