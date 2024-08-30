#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define THRESHOLD 0.2

cv::Mat readCSVtoMat(const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Could not open the file - '" << filename << "'" << std::endl;
        return cv::Mat();
    }

    std::vector<std::vector<float>> data;
    std::string line;

    // Reading each line of the CSV file
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string value;
        std::vector<float> row;

        // Splitting the line by comma and converting to float
        while (getline(ss, value, ',')) {
            row.push_back(std::stof(value));
        }

        data.push_back(row);
    }

    file.close();

    // Determining the size of the matrix
    int rows = data.size();
    int cols = data[0].size();
    
    // Creating the cv::Mat object
    cv::Mat mat(rows, cols, CV_32F);

    // Filling the cv::Mat object with the data
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat.at<float>(i, j) = data[i][j];
        }
    }

    return mat;
}

void isVehicleInsideLane(const std::string& lane_csv, const std::string& mask_csv, int image_height, int image_width) {
    // Read lane and mask data
    cv::Mat lane = readCSVtoMat(lane_csv);
    cv::Mat mask = readCSVtoMat(mask_csv);

    // Create an empty image
    cv::Mat image = cv::Mat::zeros(image_height, image_width, CV_8U);

    // Combine lane and mask into image
    image.setTo(255, lane > THRESHOLD);
    image.setTo(255, mask > THRESHOLD);
    
    // Save the resulting image
    cv::imwrite("output.png", image);

    int n1 = cv::countNonZero(lane == 255);
    int n2 = cv::countNonZero(mask > THRESHOLD);
    int n3 = cv::countNonZero(image == 255);

    std::cout << "n1: " << n1 << std::endl;
    std::cout << "n2: " << n2 << std::endl;
    std::cout << "n3: " << n3 << std::endl;

    if (n3 < n1 + n2)
    {
        std::cout << "Inside lane" << std::endl;
    }
    else
    {
        std::cout << "Outside lane" << std::endl;
    }
}

bool isVehicleInSideLane(cv::Mat lane, cv::Mat mask) {
    return true;
}