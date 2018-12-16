#ifndef CAMERA_DRAWING_AREA_H
#define CAMERA_DRAWING_AREA_H

#include <opencv2/highgui.hpp>
#include <gtkmm.h>
#include "movie-maker.hpp"
#include "orange-ball-detector.hpp"

class CameraDrawingArea :
public Gtk::DrawingArea {
public:
    CameraDrawingArea();
    virtual ~CameraDrawingArea();
    
protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	void on_size_allocate (Gtk::Allocation& allocation) override;
	
	bool everyNowAndThen();

private:
	sigc::connection everyNowAndThenConnection;
	cv::VideoCapture videoCapture;
	MovieMaker movieMaker;
	OrangeBallDetector orangeBallDetector;
	cv::Mat webcam;
	cv::Mat output;
	int width, height;
};
#endif
