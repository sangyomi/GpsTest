#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

std::pair<double, double> GPSabsorption(std::ifstream& ser) {
    std::string data;
    std::getline(ser, data);
    std::istringstream iss(data);
    std::string datName = "GNGLL";
    std::pair<double, double> gps_data = { 0.0, 0.0 };

    if (data.substr(1, 5) == datName) {
        std::string ignored;
        double data2, data3;
        std::getline(iss, ignored, ',');
        iss >> data2;
        std::getline(iss, ignored, ',');
        std::getline(iss, ignored, ',');
        iss >> data3;
        gps_data = { data2, data3 };
    }
    return gps_data;
}

int main() {
    std::ifstream ser("/dev/ttyUSB1");
    ser.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    while (true) {
        int GPS_S = 0;
        while (GPS_S == 0) {
            std::pair<double, double> gps_data = GPSabsorption(ser);
            if (gps_data.first != 0.0 || gps_data.second != 0.0) {
                std::cout << "gps on" << std::endl;
                double x = gps_data.first * 0.01;
                double y = gps_data.second * 0.01;
                std::cout << x << std::endl;
                std::cout << y << std::endl;
                GPS_S = 1;
            } else {
                GPS_S = 0;
            }
        }
    }

    return 0;
}

