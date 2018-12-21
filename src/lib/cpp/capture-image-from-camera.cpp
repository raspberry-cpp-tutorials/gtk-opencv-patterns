#include "capture-image-from-camera.hpp"

CaptureImageFromCamera::CaptureImageFromCamera():
captureThread(nullptr),
videoCapture(0) {
	startCapturing();
}

CaptureImageFromCamera::~CaptureImageFromCamera() {
	stopCapturing();
}

void CaptureImageFromCamera::startCapturing() {
	if (!captureThread) {
		keepCapturing = true;
		captureThread = new std::thread([this] {
			doCapture();
		});
	}
}

void CaptureImageFromCamera::stopCapturing() {
	if (captureThread) {
		keepCapturing = false;
		captureThread->join();
		free(captureThread);
		captureThread = nullptr;
	}
}

void CaptureImageFromCamera::doCapture() {
	while (keepCapturing) {
		videoCapture.grab();
		videoCapture.grab();
		videoCapture.grab();
		videoCapture.read(webcam);
		eventBus.propagate(EventImageCaptured(webcam));
	}
}

EventImageCaptured::EventImageCaptured(cv::Mat i):
capturedImage(i){
}

cv::Mat EventImageCaptured::getCapturedImage() {
	return capturedImage;
}
