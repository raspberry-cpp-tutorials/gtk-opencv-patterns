#ifndef MOVIE_MAKER_HPP
#define MOVIE_MAKER_HPP

#include "capture-image-from-camera.hpp"
#include "event-bus.hpp"

#include <opencv2/videoio.hpp>

class MovieMaker: public Subscriptor<EventImageCaptured> {
public:
	MovieMaker(std::string fileName, double fps);
	virtual ~MovieMaker();
	void endMovie();
	void addPhotogram(cv::Mat photogram);
	void receive(EventImageCaptured e);
private:
	cv::VideoWriter videoWriter;
	bool isMovieStarted;
	std::string filename;
	double fps;
	
	void startMovie(cv::Mat firstPhotogram);
};

#endif
