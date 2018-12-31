#ifndef CAPTURE_IMAGE_FROM_CAMERA_HPP
#define CAPTURE_IMAGE_FROM_CAMERA_HPP

#include "event-bus.hpp"

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
private:
	bool keepCapturing;
	void doCapture();
	std::thread* captureThread;
	cv::VideoCapture videoCapture;
	cv::Mat webcam;
	EventBus<EventImageCaptured> eventBus;
};

#endif
