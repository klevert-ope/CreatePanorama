#include "ImageStitcher.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>

// ANSI escape codes for colors
constexpr const char* RESET  = "\033[0m";
constexpr const char* RED    = "\033[31m";
constexpr const char* GREEN  = "\033[32m";
constexpr const char* YELLOW = "\033[33m";
constexpr const char* BLUE   = "\033[34m";
constexpr const char* CYAN   = "\033[36m";
constexpr const char* MAGENTA = "\033[35m";
constexpr const char* BOLD = "\033[1m";

// Function prototypes
void printWelcomeMessage();
std::string getOutputFilePath();
std::vector<std::string> getImagePaths();
void printInstructions();
bool confirmExecution();
void clearInputBuffer();

int main() {
    printWelcomeMessage();
    printInstructions();

    // Get output file path
    std::string outputPath = getOutputFilePath();

    // Get the list of image paths from the user
    std::vector<std::string> imagePaths = getImagePaths();

    // Confirm if user wants to proceed with the stitching
    if (!confirmExecution()) {
        std::cout << YELLOW << "Operation canceled by the user." << RESET << std::endl;
        return 0;
    }

    // Perform image stitching
    if (!ImageStitcher::stitchImages(imagePaths, outputPath)) {
        std::cerr << RED << "Failed to create the panorama." << RESET << std::endl;
        return -1;
    }

    std::cout << GREEN << "Panorama created successfully!" << RESET << std::endl;
    return 0;
}

// Function to print welcome message
void printWelcomeMessage() {
    std::cout << MAGENTA << "---------------------------------------" << RESET << std::endl;
    std::cout << BLUE << BOLD << "     Image Stitcher - Panorama Maker   " << RESET << std::endl;
    std::cout << MAGENTA << "---------------------------------------" << RESET << std::endl;
    std::cout << BLUE << "Welcome to the Image Stitcher tool!" << RESET << std::endl;
    std::cout << BLUE << "You can combine multiple images into a single panorama." << RESET << std::endl;
    std::cout << std::endl;
}

// Function to get the output file path
std::string getOutputFilePath() {
    std::string outputPath;
    while (true) {
        std::cout << BLUE << "Please enter the output file path for the panorama (e.g., output.jpg): ";
        std::getline(std::cin, outputPath);

        if (!outputPath.empty()) {
            return outputPath;
        }

        std::cerr << RED << "Error: Output file path cannot be empty." << RESET << std::endl;
    }
}

// Function to get image paths from the user
std::vector<std::string> getImagePaths() {
    std::vector<std::string> imagePaths;
    std::string imagePath;
    int imageCount = 0;

    while (true) {
        std::cout << BLUE << "How many images do you want to stitch together? ";
        std::cin >> imageCount;

        // Validate the input
        if (imageCount >= 2) {
            break;
        }

        std::cerr << RED << "Error: You must provide at least two images to create a panorama." << RESET << std::endl;
    }

    clearInputBuffer(); // Clear the buffer after numeric input

    // Collect image paths
    for (int i = 0; i < imageCount; ++i) {
        while (true) {
            std::cout << BLUE << "Enter the path for image " << (i + 1) << ": ";
            std::getline(std::cin, imagePath);

            if (!imagePath.empty()) {
                imagePaths.push_back(imagePath);
                break;
            }

            std::cerr << RED << "Error: Image path cannot be empty." << RESET << std::endl;
        }
    }

    return imagePaths;
}

// Function to print further instructions
void printInstructions() {
    std::cout << "\n" << CYAN << "Instructions:" << RESET << std::endl;
    std::cout << "1. Enter the output file path for the panorama." << std::endl;
    std::cout << "2. Enter the number of images you wish to stitch together." << std::endl;
    std::cout << "3. Provide the file paths of all the images in sequence." << std::endl;
    std::cout << "4. The program will output the panorama image at the specified location." << std::endl;
    std::cout << MAGENTA << "-----------------------------------------------" << RESET << std::endl;
}

// Function to confirm execution from the user
bool confirmExecution() {
    char response;
    std::cout << "\n" << YELLOW << "Are you sure you want to proceed with the image stitching? (y/n): " << RESET;
    std::cin >> response;

    return (response == 'y' || response == 'Y');
}

// Function to clear input buffer after numeric input
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
