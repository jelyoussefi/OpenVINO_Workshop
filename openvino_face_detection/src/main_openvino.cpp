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

using namespace InferenceEngine;

std::string model = "C:\\Intel\\computer_vision_sdk\\deployment_tools\\intel_models\\face-detection-adas-0001\\FP32\\face-detection-adas-0001";
std::string device = "CPU";
float threshold = 0.5;

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
        cv::Mat next_frame;

        // Try to get a frame from the camera
        if (!cap.read(curr_frame)) {
            throw std::logic_error("Failed to get frame from the camera!");
        }

        // -----------------------------------------------------------------------------------------------------

        // --------------------------- Load Plugin for inference engine -------------------------------------
        std::cout << "Loading plugin" << std::endl;
        InferencePlugin plugin = PluginDispatcher({""}).getPluginByDevice(device);
        printPluginVersion(plugin, std::cout);

        /** Loading default extensions **/
        if (device.find("CPU") != std::string::npos) {
            plugin.AddExtension(std::make_shared<Extensions::Cpu::CpuExtensions>());
        }

        // -----------------------------------------------------------------------------------------------------

        // ---------------------------------- Read IR (.xml and .bin files) ------------------------------------
        std::cout << "Loading network files..." << std::endl;

        /** Read network model and weights**/
        CNNNetReader netReader;
        netReader.ReadNetwork(model + ".xml");
        netReader.ReadWeights(model + ".bin");        

        // -----------------------------------------------------------------------------------------------------

        // --------------------------- Configure input & output blobs---------------------------------------------

        InputsDataMap inputInfo(netReader.getNetwork().getInputsInfo());
        auto inputName = inputInfo.begin()->first;
        InputInfo::Ptr& input = inputInfo.begin()->second;
        input->setPrecision(Precision::U8);
        input->getInputData()->setLayout(Layout::NCHW);

        OutputsDataMap outputInfo(netReader.getNetwork().getOutputsInfo());
        auto outputName = outputInfo.begin()->first;
        DataPtr& output = outputInfo.begin()->second;
        const SizeVector outputDims = output->getTensorDesc().getDims();
        const int numDetections = outputDims[2];
        const int objectSize = outputDims[3];
        output->setPrecision(Precision::FP32);
        output->setLayout(Layout::NCHW);

        // -----------------------------------------------------------------------------------------------------

        // --------------------------- Loading model to the plugin ------------------------------------------
        std::cout << "Loading model to the plugin" << std::endl;
        ExecutableNetwork network = plugin.LoadNetwork(netReader.getNetwork(), {});
        // -----------------------------------------------------------------------------------------------------

        // --------------------------- Create infer requests -------------------------------------------------
        InferRequest::Ptr infer_request = network.CreateInferRequestPtr();
        InferRequest::Ptr infer_request_next = network.CreateInferRequestPtr();
        // -----------------------------------------------------------------------------------------------------

        //----------------------- Timer Variables -------------------------------
        typedef std::chrono::duration<double, std::ratio<1, 1000>> ms;
        auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        //-------------------------------------------------------------

        /* Resize and copy data from the first camera frame to the current input blob */
        Blob::Ptr input_blob = infer_request->GetBlob(inputName);
        matU8ToBlob<uint8_t>(curr_frame, input_blob);

        // Execute the first infer request
        infer_request->StartAsync();

        std::cout << "Start inference " << std::endl;

        // ----------------------------------- Main Loop ---------------------------------------------
        while (true) {
            /* Prepare next input blob */
            if (!cap.read(next_frame)) { // Grab next frame from camera
                throw std::logic_error("Failed to get frame from camera!");
            }

            /* Resize and copy the next camera frame to the next input blob */
            Blob::Ptr input_blob_next = infer_request_next->GetBlob(inputName);
            matU8ToBlob<uint8_t>(next_frame, input_blob_next);

            /* Execute the next infer request while waiting for the current one to complete */            
            infer_request_next->StartAsync();

            /* Wait for current infer request to complete */
            infer_request->Wait(IInferRequest::WaitMode::RESULT_READY);

            //---------------------------------------- Calculate performance metrics -----------------------------------------------------
            endTime = std::chrono::high_resolution_clock::now();
            ms timer = std::chrono::duration_cast<ms>(endTime - startTime);
            startTime = endTime;

            std::ostringstream out;
            out << std::fixed << std::setprecision(2) << 1000.f / timer.count() << " fps";
            cv::putText(curr_frame, out.str(), cv::Point2f(0, 20), cv::FONT_HERSHEY_TRIPLEX, 0.6, cv::Scalar(0, 0, 255));
            //-----------------------------------------------------------------------------------------------------------------------------

            /* Process output blob */
            const float *detections = infer_request->GetBlob(outputName)->buffer().as<PrecisionTrait<Precision::FP32>::value_type*>();
            for (int i = 0; i < numDetections; i++) {
                float confidence = detections[i * objectSize + 2];
                float xmin = detections[i * objectSize + 3] * width;
                float ymin = detections[i * objectSize + 4] * height;
                float xmax = detections[i * objectSize + 5] * width;
                float ymax = detections[i * objectSize + 6] * height;

                if (confidence > threshold) {
                    std::ostringstream conf;
                    conf << std::fixed << std::setprecision(3) << confidence;
                    cv::putText(curr_frame,
                                conf.str(),
                                cv::Point2f(xmin, ymin - 5), cv::FONT_HERSHEY_COMPLEX_SMALL, 1,
                                cv::Scalar(0, 0, 255));
                    cv::rectangle(curr_frame, cv::Point2f(xmin, ymin), cv::Point2f(xmax, ymax), cv::Scalar(0, 0, 255));
                }
            }

            // Display results in output window
            cv::imshow("Face Detector", curr_frame);

            // Swap the next and current requests for the next iteration
            curr_frame = next_frame;
            next_frame = cv::Mat();
            infer_request.swap(infer_request_next);
            
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