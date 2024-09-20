#ifndef CREATEPANORAMA_IMAGESTITCHER_H
#define CREATEPANORAMA_IMAGESTITCHER_H

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

class ImageStitcher {
public:
    // Constructor
    ImageStitcher();

    // Method to stitch images together into a panorama
    static bool stitchImages(const std::vector<std::string>& imagePaths, const std::string& outputPath);
};

#endif //CREATEPANORAMA_IMAGESTITCHER_H