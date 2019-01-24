#ifndef CAPTURE_IMAGE_FROM_CAMERA_HPP
#define CAPTURE_IMAGE_FROM_CAMERA_HPP

#include "event-bus.hpp"

#include <opencv2/highgui.hpp>

#include <thread>
#include <chrono>

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
    float getFrameRate();
private:
	bool keepCapturing;
    float frameRate;
    void updateFrameRate();
	void doCapture();
	void doPropagate();
	std::thread* captureThread;
	std::thread* propagateThread;
    std::chrono::time_point<std::chrono::system_clock> lastFrameSystemClock;
	cv::VideoCapture videoCapture;
	cv::Mat webcam;
	EventBus<EventImageCaptured> eventBus;
};

#endif
