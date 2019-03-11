// Copyright (C) 2018 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//
#include <functional>
#include <iostream>
#include <fstream>
#include <random>
#include <memory>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <inference_engine.hpp>
#include <ocv_common.hpp>
#include <ext_list.hpp>

int main(int argc, char *argv[]) {
    try {
        // -------------------------- Load Camera Stream ------------------------------------
        std::cout << "Starting camera..." << std::endl;
        cv::VideoCapture cap;
        if (!cap.open(0)) {
            throw std::logic_error("Cannot open camera!");
        }

        // Store camera stream parameters
        const size_t width  = (size_t) cap.get(cv::CAP_PROP_FRAME_WIDTH);
        const size_t height = (size_t) cap.get(cv::CAP_PROP_FRAME_HEIGHT);

        // Store frames grabbed from the camera
        cv::Mat curr_frame;

        // Try to get a frame from the camera
        if (!cap.read(curr_frame)) {
            throw std::logic_error("Failed to get frame from the camera!");
        }

        // -----------------------------------------------------------------------------------------------------

        //----------------------- Timer Variables -------------------------------
        typedef std::chrono::duration<double, std::ratio<1, 1000>> ms;
        auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        //-------------------------------------------------------------

        // ----------------------------------------------------- Main Loop ---------------------------------------------------------
        while (true) {
            //---------------------------------------- Calculate performance metrics -----------------------------------------------
            endTime = std::chrono::high_resolution_clock::now();
            ms timer = std::chrono::duration_cast<ms>(endTime - startTime);
            startTime = endTime;

            std::ostringstream out;
            out << std::fixed << std::setprecision(2) << 1000.f / timer.count() << " fps";
            cv::putText(curr_frame, out.str(), cv::Point2f(0, 20), cv::FONT_HERSHEY_TRIPLEX, 0.6, cv::Scalar(0, 0, 255));
            //----------------------------------------------------------------------------------------------------------------------

            // Display results in output window
            cv::imshow("Face Detector", curr_frame);

            // Grab next frame from the camera
            if (!cap.read(curr_frame)) {
                throw std::logic_error("Failed to get frame from camera!");
            }
            
            // ESC to exit
            const int key = cv::waitKey(1);
            if (27 == key)  // Esc
                break;
        }
    }
    catch (const std::exception& error) {
        std::cerr << "[ ERROR ] " << error.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "[ ERROR ] Unknown/internal exception happened." << std::endl;
        return 1;
    }

    return 0;
}