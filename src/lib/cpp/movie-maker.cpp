#include "movie-maker.hpp"

using namespace std;
using namespace cv;

MovieMaker::MovieMaker(string filename, double fps):
videoWriter(),
isMovieStarted(false),
filename(filename),
fps(fps) {
    // Nothing to do.
}

MovieMaker::~MovieMaker() {
    endMovie();
}

void MovieMaker::receive(EventImageCaptured e) {
    addPhotogram(e.getCapturedImage());
}

void MovieMaker::addPhotogram(Mat photogram) {
    if (!photogram.empty()) {
        if (!isMovieStarted) {
            startMovie(photogram);
            isMovieStarted = true;
        }
        videoWriter.write(photogram);
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
