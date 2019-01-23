#include "camera-drawing-area.hpp"
#include "system-helper.hpp"

#include <opencv2/imgproc.hpp>

CameraDrawingArea::CameraDrawingArea():
dispatchInvalidate() {
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

        // Initializes a pixbuf sharing the same data as the mat:
        pixbuf = Gdk::Pixbuf::create_from_data(
                (guint8*)output.data,
                Gdk::COLORSPACE_RGB,
                false,
                8,
                output.cols,
                output.rows,
                (int) output.step);

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
    if (pixbuf) {
        Gdk::Cairo::set_source_pixbuf(cr, pixbuf);
        cr->paint();
    }

    return true;
}

void CameraDrawingArea::on_size_allocate (Gtk::Allocation& allocation) {
    DrawingArea::on_size_allocate(allocation);

    width = allocation.get_width();
    height = allocation.get_height();
}

