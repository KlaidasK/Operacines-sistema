#pragma once

#ifndef _Dll_H_
#define _DLL_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <chrono>
#include <vector>
#include <cmath>
#include <algorithm>


#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllexport)
#endif

using std::cout;
using std::cin;
using std::endl;
using std::wcout;
using std::string;
using std::vector;


extern "C"
DLL_API int mymaks(int, int);

extern "C"
DLL_API void openWindow();

extern "C"
DLL_API void folderCreate(string,string);


extern "C"
DLL_API void deletion();



class Timer { //Laiko matavimas
private:
    using hrClock = std::chrono::high_resolution_clock;
    std::chrono::time_point<hrClock> start;
public:
    Timer() :start{ hrClock::now() } {}
    void reset() {
        start = hrClock::now();
    }
    double elapsed()const {
        std::chrono::duration<double> diffs = hrClock::now() - start;
        return diffs.count();
    }
};

struct Point {
    double x, y;
    Point(double _x, double _y) : x(_x), y(_y) {}
};

double tschirnhausen_cubic(double x, double y) {
    return pow(x, 3) + 3 * pow(x, 2) - pow(y, 2);
}

void write_to_file(const std::string& filename, const Point& point) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << "[" << point.x << ", " << point.y << "]" << std::endl;
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

void calculate_and_write_points(const std::vector<double>& F_values, double x0, double xn, double delta_x) {
    std::vector<std::string> filenames = { "Kubilius/output_file_1.txt",
                                           "Kubilius/Klaidas1/output_file_2.txt",
                                           "Kubilius/Klaidas1/Klaidas1Klaidas1/output_file_3.txt",
                                           "Kubilius/Klaidas1/Klaidas1Klaidas2/output_file_4.txt",
                                           "Kubilius/Klaidas1/Klaidas1Klaidas3/output_file_5.txt",
                                           "Kubilius/Klaidas2/output_file_6.txt",
                                           "Kubilius/Klaidas2/Klaidas2Klaidas1/output_file_7.txt",
                                           "Kubilius/Klaidas2/Klaidas2Klaidas2/output_file_8.txt",
                                           "Kubilius/Klaidas2/Klaidas2Klaidas3/output_file_9.txt",
                                           "Kubilius/Klaidas3/output_file_10.txt",
                                           "Kubilius/Klaidas3/Klaidas3Klaidas1/output_file_11.txt",
                                           "Kubilius/Klaidas3/Klaidas3Klaidas2/output_file_12.txt",
                                           "Kubilius/Klaidas3/Klaidas3Klaidas3/output_file_13.txt",
                                            };
    int file_index = 0;
    double x = x0;

    for (double x = x0; x <= xn; x += delta_x) {
        for (double F : F_values) {
            double y_squared = pow(x, 3) + 3 * pow(x, 2) - F;
            if (y_squared >= 0) { // Check if y^2 is non-negative
                double y = sqrt(y_squared);
                Point point(x, y);
                write_to_file(filenames[file_index], point);
                file_index = (file_index + 1) % 13;
            }
        }
    }

    cout << "Points calculated and written" << endl;
}

bool compare_points(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}

void merge_and_sort_points() {
    std::vector<std::string> filenames = { "Kubilius/output_file_1.txt",
                                       "Kubilius/Klaidas1/output_file_2.txt",
                                       "Kubilius/Klaidas1/Klaidas1Klaidas1/output_file_3.txt",
                                       "Kubilius/Klaidas1/Klaidas1Klaidas2/output_file_4.txt",
                                       "Kubilius/Klaidas1/Klaidas1Klaidas3/output_file_5.txt",
                                       "Kubilius/Klaidas2/output_file_6.txt",
                                       "Kubilius/Klaidas2/Klaidas2Klaidas1/output_file_7.txt",
                                       "Kubilius/Klaidas2/Klaidas2Klaidas2/output_file_8.txt",
                                       "Kubilius/Klaidas2/Klaidas2Klaidas3/output_file_9.txt",
                                       "Kubilius/Klaidas3/output_file_10.txt",
                                       "Kubilius/Klaidas3/Klaidas3Klaidas1/output_file_11.txt",
                                       "Kubilius/Klaidas3/Klaidas3Klaidas2/output_file_12.txt",
                                       "Kubilius/Klaidas3/Klaidas3Klaidas3/output_file_13.txt",
    };


    for (const std::string& filename : filenames) {
        std::ifstream file(filename);
        std::vector<Point> points;
        double x, y;
        while (file >> x >> y) {
            points.push_back(Point(x, y));
        }
        file.close();

        std::sort(points.begin(), points.end(), compare_points);

        std::ofstream merged_file("merged_" + filename);
        for (const Point& point : points) {
            merged_file << point.x << " " << point.y << std::endl;
        }
        merged_file.close();
    }

    // Ištriname tarpinius failus
    for (const std::string& filename : filenames) {
        std::remove(filename.c_str());
    }
}






#endif