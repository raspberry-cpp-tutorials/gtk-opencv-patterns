#include "camera-drawing-area.hpp"

#include "service-locator.hpp"
#include "system-helper.hpp"

#include <opencv2/imgproc.hpp>

CameraDrawingArea::CameraDrawingArea():
dispatchInvalidate(),
movieMaker(ServiceLocator::getMovieMaker()){
    dispatchInvalidate.
        connect(sigc::mem_fun(*this, 
                    &CameraDrawingArea::doInvalidate));
    eventBus.subscribe(this);
}

CameraDrawingArea::~CameraDrawingArea() {
	eventBus.unsubscribe(this);
}

void CameraDrawingArea::receive(EventOrangeDetected e) {
	if (width > 0 && height > 0) {
		resize(e.getCapturedImage(), output, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);
		
		// Invalidate the window, but for that we need to be in the GUI thread.
		dispatchInvalidate.emit();
	}
}

void CameraDrawingArea::doInvalidate() {
    auto win = get_window();
    if (win) {
        win->invalidate(false);
    }
}

bool CameraDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    if (output.size().width > 0) {
        // Initializes a pixbuf sharing the same data as the mat:
        Glib::RefPtr<Gdk::Pixbuf> pixbuf =
            Gdk::Pixbuf::create_from_data((guint8*)output.data,
                    Gdk::COLORSPACE_RGB,
                    false,
                    8,
                    output.cols,
                    output.rows,
                    (int) output.step);
        // Show it all
        Gdk::Cairo::set_source_pixbuf(cr, pixbuf);
        cr->paint();

        // When recording, displays a red circle
        if (movieMaker->isRecording()) {
            displayRec(cr);
        }
    }

    return true;
}

void CameraDrawingArea::displayRec(const Cairo::RefPtr<Cairo::Context>& cr) {
    double radius = 7;
    double x = width / 2;
    double y = height - radius;
    cr->set_source_rgb(1.0, 0.1, 0.1);
    cr->arc(x, y, radius, 0, 2 * M_PI);
    cr->fill();
    cr->stroke();
}

void CameraDrawingArea::on_size_allocate (Gtk::Allocation& allocation) {
    DrawingArea::on_size_allocate(allocation);

    width = allocation.get_width();
    height = allocation.get_height();
}


