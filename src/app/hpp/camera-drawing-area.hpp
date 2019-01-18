#ifndef CAMERA_DRAWING_AREA_HPP
#define CAMERA_DRAWING_AREA_HPP

#include "movie-maker.hpp"
#include "orange-ball-detector.hpp"

#include <opencv2/highgui.hpp>
#include <gtkmm.h>

#include <thread>

class CameraDrawingArea : public Gtk::DrawingArea {
public:
    CameraDrawingArea();
    virtual ~CameraDrawingArea();

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    void on_size_allocate (Gtk::Allocation& allocation) override;

private:
    void startCapturing();
    void stopCapturing();
    bool keepCapturing;
    void doCapture();
    void doProcess(cv::Mat image);
    Glib::Dispatcher dispatchInvalidate;
    void doInvalidate();
    std::thread* captureThread;
    cv::VideoCapture videoCapture;
    MovieMaker movieMaker;
    OrangeBallDetector orangeBallDetector;
    cv::Mat webcam;
    cv::Mat output;
    int width, height;
};
#endif
