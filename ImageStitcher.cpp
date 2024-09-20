#include "ImageStitcher.h"
#include <opencv2/stitching.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <filesystem>


// ANSI escape codes for colors
constexpr const char* RESET  = "\033[0m";
constexpr const char* RED    = "\033[31m";
constexpr const char* GREEN  = "\033[32m";
constexpr const char* YELLOW = "\033[33m";
constexpr const char* BLUE   = "\033[34m";
constexpr const char* CYAN   = "\033[36m";

ImageStitcher::ImageStitcher() = default;

bool ImageStitcher::stitchImages(const std::vector<std::string>& imagePaths, const std::string& outputPath) {
    std::vector<cv::Mat> images;

    // Load each image
    for (const auto& path : imagePaths) {
        cv::Mat img = cv::imread(path);
        if (img.empty()) {
            std::cerr << RED << "Error: Could not load image at path: " << path << RESET << std::endl;
            return false;
        }
        std::cout << "Loaded image: " << path << " with dimensions: " << img.cols << "x" << img.rows << std::endl;
        images.push_back(img);
    }

    // Create a stitcher instance
    cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
    cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);

    // Stitch the images together
    cv::Mat pano;

    // Handle different status codes from the stitcher using init-statement
    if (cv::Stitcher::Status status = stitcher->stitch(images, pano); status != cv::Stitcher::OK) {
        std::cerr << RED << "Error during stitching: " << status << RESET << std::endl;
        switch (status) {
            case cv::Stitcher::ERR_NEED_MORE_IMGS:
                std::cerr << RED << "Error: Not enough valid overlapping regions between the images to stitch." << RESET << std::endl;
                break;
            case cv::Stitcher::ERR_HOMOGRAPHY_EST_FAIL:
                std::cerr << RED << "Error: Homography estimation failed. The images may not overlap enough or have too few common features." << RESET << std::endl;
                break;
            case cv::Stitcher::ERR_CAMERA_PARAMS_ADJUST_FAIL:
                std::cerr << RED << "Error: Camera parameters could not be adjusted successfully." << RESET << std::endl;
                break;
            default:
                std::cerr << RED << "Error: Unknown stitching error." << RESET << std::endl;
                break;
        }
        return false;
    }

    // Check if the output directory exists and is writable
    if (std::filesystem::path outputDir = std::filesystem::path(outputPath).parent_path();
            !std::filesystem::exists(outputDir) || !std::filesystem::is_directory(outputDir)) {
        std::cerr << RED << "Error: Output directory does not exist or is not a directory." << RESET << std::endl;
        return false;
    }

    // Save the panorama image
    if (!cv::imwrite(outputPath, pano)) {
        std::cerr << RED << "Error: Failed to save panorama to: " << outputPath << RESET << std::endl;
        return false;
    }

    return true;
}
