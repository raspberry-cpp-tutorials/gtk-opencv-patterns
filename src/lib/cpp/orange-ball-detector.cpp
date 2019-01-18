#include "orange-ball-detector.hpp"

#include <opencv2/imgproc.hpp>

void OrangeBallDetector::detect(cv::Mat image) {
    // Make the image of a reasonable size:
    double width = image.size().width;
    double scale = 600 / width;
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
        
        // Draw the circle:
        if (radius > 20) {
            cv::circle(resizedImage, ballPosition, radius, cv::Scalar(0, 255, 0), 3);
        }
        showIfDebug(resizedImage);
    }
}

void OrangeBallDetector::setDebug(bool d) {
    debug = d;
}

void OrangeBallDetector::showIfDebug(cv::Mat m) {
    if (debug) {
        imshow("orange-ball-detector", m);
        cv::waitKey(0);
    }
}

cv::Point2f OrangeBallDetector::getBallPosition() {
    return ballPosition;
}

float OrangeBallDetector::getRadius() {
    return radius;
}

cv::Mat OrangeBallDetector::getImage() {
    return resizedImage;
}
