#include "movie-maker.hpp"

using namespace std;
using namespace cv;

MovieMaker::MovieMaker(string filename, double fps):
videoWriter(),
isMovieStarted(false),
recording(true),
filename(filename),
fps(fps) {
    // Nothing to do.
}

MovieMaker::~MovieMaker() {
    endMovie();
}

bool MovieMaker::isRecording() {
    return recording;
}

void MovieMaker::toggleRecording() {
    recording = !recording;
}

void MovieMaker::receive(EventImageCaptured e) {
    addPhotogram(e.getCapturedImage());
}

void MovieMaker::addPhotogram(Mat photogram) {
    if (recording) {
        if (photogram.size().width > 0) {
            if (!isMovieStarted) {
                startMovie(photogram);
                isMovieStarted = true;
            }
            videoWriter.write(photogram);
        }
    }
}

void MovieMaker::endMovie() {
    videoWriter.release();
    isMovieStarted = false;
}

void MovieMaker::startMovie(cv::Mat firstPhotogram) {
    int fourcc = VideoWriter::fourcc('M', 'J', 'P', 'G');
    bool isColor = (firstPhotogram.type() == CV_8UC3);
    videoWriter.open(filename, fourcc, fps, firstPhotogram.size(), isColor);
}
