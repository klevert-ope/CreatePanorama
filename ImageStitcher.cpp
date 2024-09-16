#include "ImageStitcher.h"
#include <opencv2/stitching.hpp>
#include <iostream>

using namespace cv;

ImageStitcher::ImageStitcher() = default;

std::vector<cv::Mat> ImageStitcher::loadImages(const std::vector<std::string>& imagePaths) {
    std::vector<cv::Mat> images;
    for (const auto& path : imagePaths) {
        cv::Mat image = cv::imread(path);
        if (image.empty()) {
            std::cerr << "Error: Could not open or find the image at " << path << std::endl;
        } else {
            images.push_back(image);
        }
    }
    return images;
}

bool ImageStitcher::stitchImages(const std::vector<std::string>& imagePaths, const std::string& outputPath) {
    std::vector<cv::Mat> images = loadImages(imagePaths);

    if (images.size() < 2) {
        std::cerr << "Error: Need at least two images to create a panorama" << std::endl;
        return false;
    }

    cv::Mat panorama;
    cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
    cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);

    // Perform the stitching process
    cv::Stitcher::Status status = stitcher->stitch(images, panorama);

    if (status != cv::Stitcher::OK) {
        std::cerr << "Error during stitching: " << status << std::endl;
        return false;
    }

    // Write the result to the specified output path
    if (!cv::imwrite(outputPath, panorama)) {
        std::cerr << "Error: Could not write the image to " << outputPath << std::endl;
        return false;
    }

    std::cout << "Panorama saved successfully at " << outputPath << std::endl;
    return true;
}
