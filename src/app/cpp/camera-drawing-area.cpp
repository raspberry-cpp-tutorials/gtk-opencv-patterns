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

/**
 * Each time we receive a new image, we invalidate the
 * whole Widget rectangle, forcing a complete refresh.
 */
void CameraDrawingArea::receive(EventOrangeDetected e) {
	resize(e.getCapturedImage(), output, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);
    
    // Invalidate the window, but for that we need to be in the GUI thread.
    dispatchInvalidate.emit();
}

void CameraDrawingArea::doInvalidate() {
    auto win = get_window();
    if (win) {
        win->invalidate(false);
    }
}

/**
 * Called every time the widget needs to be redrawn.
 * This happens when the Widget got resized, or obscured by
 * another object, or every now and then.
 */
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

        // Display
        Gdk::Cairo::set_source_pixbuf(cr, pixbuf);
        cr->paint();
    }

    // Don't stop calling me.
    return true;
}

void CameraDrawingArea::on_size_allocate (Gtk::Allocation& allocation) {
    // Call the parent to do whatever needs to be done:
    DrawingArea::on_size_allocate(allocation);

    // Remember the new allocated size for resizing operation:
    width = allocation.get_width();
    height = allocation.get_height();
}

