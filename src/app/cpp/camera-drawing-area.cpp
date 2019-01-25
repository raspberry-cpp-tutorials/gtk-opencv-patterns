#define _USE_MATH_DEFINES

#include "camera-drawing-area.hpp"

#include "service-locator.hpp"
#include "system-helper.hpp"

#include <opencv2/imgproc.hpp>

#include <math.h>

CameraDrawingArea::CameraDrawingArea():
dispatchInvalidate(),
movieMaker(ServiceLocator::getMovieMaker()),
captureImageFromCamera(ServiceLocator::getCaptureImageFromCamera()){

    fontDescription.set_family("Monospace");
    fontDescription.set_weight(Pango::WEIGHT_BOLD);
    fontDescription.set_size(10 * Pango::SCALE);

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
        // Resize captured image without changing its aspect:
        cv::Mat capturedImage = e.getCapturedImage();
        double capturedImageWidth = capturedImage.size().width;
        double scale = width / capturedImageWidth;
        resize(capturedImage, output, cv::Size(), scale, scale, cv::INTER_LINEAR);

        // Initialize a pixbuf based on the same data as the image:
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

    if (movieMaker->isRecording()) {
        displayRec(cr);
    }

    displayCaptureRate(cr, captureImageFromCamera->getCaptureRate());
    displayFrameRate(cr, captureImageFromCamera->getFrameRate());

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

void CameraDrawingArea::displayCaptureRate(const Cairo::RefPtr<Cairo::Context> &cr, double captureRate) {

    char text[30];
    sprintf(text, "CR %.1f fps", captureRate);

    auto layout = create_pango_layout(text);
    layout->set_font_description(fontDescription);

    int textWidth, textHeight;
    layout->get_pixel_size(textWidth, textHeight);

    cr->move_to(0, height - textHeight);

    cr->set_source_rgb(1.0, 1.0, 1.0);
    layout->show_in_cairo_context(cr);
}

void CameraDrawingArea::displayFrameRate(const Cairo::RefPtr<Cairo::Context> &cr, double frameRate) {

    char text[30];
    sprintf(text, "FR %.1f fps", frameRate);

    auto layout = create_pango_layout(text);
    layout->set_font_description(fontDescription);

    int textWidth, textHeight;
    layout->get_pixel_size(textWidth, textHeight);

    cr->move_to(width - textWidth, height - textHeight);

    cr->set_source_rgb(1.0, 1.0, 1.0);
    layout->show_in_cairo_context(cr);
}

void CameraDrawingArea::on_size_allocate (Gtk::Allocation& allocation) {
    DrawingArea::on_size_allocate(allocation);

    width = allocation.get_width();
    height = allocation.get_height();
}
