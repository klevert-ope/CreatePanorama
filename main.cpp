#include "ImageStitcher.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>

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
        std::cout << "Operation canceled by the user." << std::endl;
        return 0;
    }

    // Perform image stitching
    if (!ImageStitcher::stitchImages(imagePaths, outputPath)) {
        std::cerr << "Failed to create the panorama." << std::endl;
        return -1;
    }

    std::cout << "Panorama created successfully!" << std::endl;
    return 0;
}

// Function to print welcome message
void printWelcomeMessage() {
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "     Image Stitcher - Panorama Maker   " << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Welcome to the Image Stitcher tool!" << std::endl;
    std::cout << "You can combine multiple images into a single panorama." << std::endl;
    std::cout << std::endl;
}

// Function to get the output file path
std::string getOutputFilePath() {
    std::string outputPath;
    while (true) {
        std::cout << "Please enter the output file path for the panorama (e.g., output.jpg): ";
        std::getline(std::cin, outputPath);

        if (!outputPath.empty()) {
            return outputPath;
        }

        std::cerr << "Error: Output file path cannot be empty." << std::endl;
    }
}

// Function to get image paths from the user
std::vector<std::string> getImagePaths() {
    std::vector<std::string> imagePaths;
    std::string imagePath;
    int imageCount = 0;

    while (true) {
        std::cout << "How many images do you want to stitch together? ";
        std::cin >> imageCount;

        // Validate the input
        if (imageCount >= 2) {
            break;
        }

        std::cerr << "Error: You must provide at least two images to create a panorama." << std::endl;
    }

    clearInputBuffer(); // Clear the buffer after numeric input

    // Collect image paths
    for (int i = 0; i < imageCount; ++i) {
        while (true) {
            std::cout << "Enter the path for image " << (i + 1) << ": ";
            std::getline(std::cin, imagePath);

            if (!imagePath.empty()) {
                imagePaths.push_back(imagePath);
                break;
            }

            std::cerr << "Error: Image path cannot be empty." << std::endl;
        }
    }

    return imagePaths;
}

// Function to print further instructions
void printInstructions() {
    std::cout << "\nInstructions:" << std::endl;
    std::cout << "1. Enter the output file path for the panorama." << std::endl;
    std::cout << "2. Enter the number of images you wish to stitch together." << std::endl;
    std::cout << "3. Provide the file paths of all the images in sequence." << std::endl;
    std::cout << "4. The program will output the panorama image at the specified location." << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
}

// Function to confirm execution from the user
bool confirmExecution() {
    char response;
    std::cout << "\nAre you sure you want to proceed with the image stitching? (y/n): ";
    std::cin >> response;

    return (response == 'y' || response == 'Y');
}

// Function to clear input buffer after numeric input
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
