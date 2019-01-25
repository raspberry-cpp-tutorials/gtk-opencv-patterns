#include "capture-image-from-camera.hpp"

CaptureImageFromCamera::CaptureImageFromCamera():
captureThread(nullptr),
propagateThread(nullptr),
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
    if (propagateThread) {
        propagateThread->join();
        free(propagateThread);
        propagateThread = nullptr;
    }
}

void CaptureImageFromCamera::doCapture() {
    do {
        videoCapture.grab();
        frameRate.updateRate();

        videoCapture.grab();
        frameRate.updateRate();

        videoCapture.grab();
        frameRate.updateRate();

        videoCapture.read(webcam);
        frameRate.updateRate();
        captureRate.updateRate();

        if (!webcam.empty()) {
            doPropagate();
        }
    } while (keepCapturing);
}

double CaptureImageFromCamera::getFrameRate() {
    return frameRate.getRate();
}

double CaptureImageFromCamera::getCaptureRate() {
    return captureRate.getRate();
}

void CaptureImageFromCamera::doPropagate() {
    if (propagateThread) {
        propagateThread->join();
    }
    propagateThread = new std::thread([this] {
        eventBus.propagate(EventImageCaptured(webcam));
    });
}

EventImageCaptured::EventImageCaptured(cv::Mat i):
capturedImage(i){
}

cv::Mat EventImageCaptured::getCapturedImage() {
    return capturedImage;
}
