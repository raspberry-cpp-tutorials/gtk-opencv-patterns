#ifndef CAPTURE_IMAGE_FROM_CAMERA_HPP
#define CAPTURE_IMAGE_FROM_CAMERA_HPP

#include "event-bus.hpp"
#include "rate-meter.hpp"

#include <opencv2/highgui.hpp>

#include <thread>

class EventImageCaptured {
public:
	EventImageCaptured(cv::Mat i);
	virtual ~EventImageCaptured() = default;
	cv::Mat getCapturedImage();
private:
	cv::Mat capturedImage;
};

class CaptureImageFromCamera {
public:
	CaptureImageFromCamera();
	virtual ~CaptureImageFromCamera();
	void startCapturing();
	void stopCapturing();
    double getFrameRate();
    double getCaptureRate();
private:
	bool keepCapturing;
	void doCapture();
	void doPropagate();
    std::thread * captureThread;
    std::thread * propagateThread;
    RateMeter frameRate, captureRate;
	cv::VideoCapture videoCapture;
	cv::Mat webcam;
	EventBus<EventImageCaptured> eventBus;
};

#endif
