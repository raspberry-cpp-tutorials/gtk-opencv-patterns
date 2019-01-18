#ifndef MOVIE_MAKER_HPP
#define MOVIE_MAKER_HPP

#include <opencv2/videoio.hpp>

class MovieMaker {
public:
    MovieMaker(std::string fileName, double fps);
    virtual ~MovieMaker();
    void endMovie();
    void addPhotogram(cv::Mat photogram);
private:
    cv::VideoWriter videoWriter;
    bool isMovieStarted;
    std::string filename;
    double fps;
    
    void startMovie(cv::Mat firstPhotogram);
};

#endif
