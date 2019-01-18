#include "camera-drawing-area.hpp"
#include "system-helper.hpp"

#include <opencv2/imgproc.hpp>

CameraDrawingArea::CameraDrawingArea():
    dispatchInvalidate(),
    captureThread(nullptr),
    videoCapture(0),
    movieMaker(obtainPathToDesktopFolder().append("/live.avi"), 20.0) {
        startCapturing();
        dispatchInvalidate.
            connect(sigc::mem_fun(*this, 
                        &CameraDrawingArea::doInvalidate));
    }

CameraDrawingArea::~CameraDrawingArea() {
    stopCapturing();
}

void CameraDrawingArea::startCapturing() {
    if (!captureThread) {
        keepCapturing = true;
        captureThread = new std::thread([this] { doCapture(); });
    }
}

void CameraDrawingArea::stopCapturing() {
    keepCapturing = false;
    captureThread->join();
    free(captureThread);
    captureThread = nullptr;
}

void CameraDrawingArea::doCapture() {
    std::thread* processThread(nullptr);
    do {
        videoCapture.grab();
        videoCapture.grab();
        videoCapture.grab();
        videoCapture.read(webcam);
        if (processThread) {
            processThread->join();
        }
        processThread = new std::thread([this] { 
                doProcess(webcam); 
                });
    } while (keepCapturing);

    processThread->join();
}

void CameraDrawingArea::doProcess(cv::Mat image) {
    if (image.size().width > 0) {

        // Stream it in video:
        movieMaker.addPhotogram(image);

        // Detect the ball:
        orangeBallDetector.detect(image);

        // Resize it to the allocated size of the Widget.
        resize(orangeBallDetector.getImage(), output, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);

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

        // Display
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

