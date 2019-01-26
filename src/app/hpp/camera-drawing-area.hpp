#ifndef CAMERA_DRAWING_AREA_HPP
#define CAMERA_DRAWING_AREA_HPP

#include "capture-image-from-camera.hpp"
#include "movie-maker.hpp"
#include "orange-ball-detector.hpp"

#include <opencv2/highgui.hpp>
#include <gtkmm.h>

class CameraDrawingArea :
public Gtk::DrawingArea,
public Subscriptor<EventOrangeDetected> {
public:
    CameraDrawingArea();
    virtual ~CameraDrawingArea();
    void receive(EventOrangeDetected e) override;
    
protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    void on_size_allocate (Gtk::Allocation& allocation) override;

private:
    Glib::Dispatcher dispatchInvalidate;
    void doInvalidate();
	cv::Mat output;
	int width, height;
	EventBus<EventOrangeDetected> eventBus;
    MovieMaker * movieMaker;
    CaptureImageFromCamera * captureImageFromCamera;
    std::mutex pixbufMutex;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf;
    Pango::FontDescription fontDescription;
    void displayRec(const Cairo::RefPtr<Cairo::Context>& cr);
    void displayCaptureRate(const Cairo::RefPtr<Cairo::Context>& cr, double captureRate);
    void displayFrameRate(const Cairo::RefPtr<Cairo::Context>& cr, double captureRate);
};
#endif
