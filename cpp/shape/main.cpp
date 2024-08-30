#include "main.h"

std::vector<cv::Point> readCSVtoPoints(const std::string& file_path) {
    std::ifstream file(file_path);
    std::string line, cell;
    std::vector<cv::Point> points;

    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::vector<int> coordinates;
        while (std::getline(lineStream, cell, ',')) {
            coordinates.push_back(std::stoi(cell));
        }
        if (coordinates.size() == 2) {
            points.emplace_back(coordinates[0], coordinates[1]);
        }
    }

    return points;
}

int main() {
    std::string lane_csv = "../../../assets/lane/inside/lane.csv";
    std::string mask_csv = "../../../assets/lane/inside/mask.csv";
    
    int image_height = 600;
    int image_width = 800;
    
    isVehicleInsideLane(lane_csv, mask_csv, image_height, image_width);

    return 0;
}
