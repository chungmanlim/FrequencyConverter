/**
 * This example uses a StreamingEmitter to project a ControlPoint moving
 * in a circle, 20cm above the centre of the array. The radius of the
 * circle can be changed during playback.
 */

#include <cmath>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <algorithm>


#include "ultraleap/haptics/streaming.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323
#endif

using namespace Ultraleap::Haptics;

//It's important to use double to prevent precision issues with long run times
using Seconds = std::chrono::duration<double>;

// Structure for passing data to the callback function
struct CircleData
{
    double radius;
    double control_point_speed;
    float control_point_intensity;
    double frequency_1;
    double frequency_2;
    double envelope_frequency;
    double duration;
    LocalTimePoint start_time;
};




/**
 * Callback function to calculate the position of the circle at each time point
 *
 * This uses the control_point_speed and the elapsed time to calculate an
 * angle around the circle.
 *
 * This uses the EmissionCallback signature.
 */
void circle_callback(const StreamingEmitter& emitter,
    OutputInterval& interval,
    const LocalTimePoint& submission_deadline,
    void* circle_data_ptr)
{
    auto circle_data = static_cast<CircleData*>(circle_data_ptr);
    double angular_frequency = circle_data->control_point_speed / circle_data->radius;

    for (auto& sample : interval) {
        Seconds t = sample - circle_data->start_time;
        double angle = t.count() * angular_frequency;

        Vector3 p;
        p.x = static_cast<float>(std::cos(angle) * circle_data->radius);
        p.y = static_cast<float>(std::sin(angle) * circle_data->radius);
        p.z = 0.2f;


        // Calculate the elapsed time in seconds
        double elapsed_seconds = t.count();
        double current_intensity = 0.5 * std::sin(2.0 * M_PI * circle_data->frequency_1 * elapsed_seconds) + 0.5 * std::sin(2.0 * M_PI * circle_data->frequency_2 * elapsed_seconds);
        if (circle_data->frequency_1 == 0 || circle_data->frequency_2 == 0) {
            current_intensity = 1;
        }
        
        double EV = 1;
        if (circle_data->envelope_frequency == 0) {
            EV = 1;
        }
        else {
            EV = std::sin(2.0 * M_PI * circle_data->envelope_frequency * elapsed_seconds);
        }

        double Intensity = circle_data->control_point_intensity;
        
        // Duration
        if (elapsed_seconds >= circle_data->duration) {
            Intensity = 0;
        }

        sample.controlPoint(0).setPosition(p);
        sample.controlPoint(0).setIntensity(Intensity * current_intensity * EV);
    }
}

int main()
{
    // Create a Library object and connect it to a running service
    Library lib;
    auto connect_result = lib.connect();
    if (!connect_result) {
        std::cout << "Library failed to connect: " << connect_result.error().message() << std::endl;
        return 1;
    }

    // Create a streaming emitter and add a device to it
    StreamingEmitter emitter{ lib };
    auto device_result = lib.findDevice(DeviceFeatures::StreamingHaptics);
    if (!device_result) {
        std::cout << "Failed to find device: " << device_result.error().message() << std::endl;
        return 1;
    }

    auto add_result = emitter.addDevice(device_result.value());
    if (!add_result) {
        std::cout << "Failed to add device: " << add_result.error().message() << std::endl;
        return 1;
    }

    //Set the ControlPoint count on the emitter to be 1
    auto set_count_result = emitter.setControlPointCount(1, AdjustRate::All);
    if (!set_count_result) {
        std::cout << "Failed to set ControlPoint count: " << set_count_result.error().message() << std::endl;
        return 1;
    }

    CircleData circle_data{ 0.02, 12, 1.0, 200, 200, 0, 2, LocalTimeClock::now() };

    auto set_cb_result = emitter.setEmissionCallback(&circle_callback, &circle_data);
    if (!set_cb_result) {
        std::cout << "Failed to set callback on emitter: " << set_cb_result.error().message() << std::endl;
        return 1;
    }

    auto start_result = emitter.start();
    if (!start_result) {
        std::cout << "Failed to start emitter: " << start_result.error().message() << std::endl;
        return 1;
    }

    // Wait for enter key to be pressed.

    std::cout << "[Initial Setting]" << std::endl;
    std::cout << "Duration (s): " << circle_data.duration << std::endl;
    std::cout << "Amplitude (0 - 1): " << circle_data.control_point_intensity << std::endl;
    std::cout << "Radius (mm): " << circle_data.radius * 1000.0f << std::endl;
    std::cout << "Amplitude-modulated frequency_1 (Hz): " << circle_data.frequency_1 << std::endl;
    std::cout << "Amplitude-modulated frequency_2 (Hz): " << circle_data.frequency_2 << std::endl;
    std::cout << "Envelope frequency (Hz): " << circle_data.envelope_frequency << std::endl;
    std::cout << " " << std::endl;

    std::cout << "Hit ENTER to quit..." << std::endl << std::endl;

    while (true) {
        std::cout << " " << std::endl;
        std::cout << "[Start]" << std::endl;

        std::cout << "Enter Duration (s): ";
        std::string line_5;
        std::getline(std::cin, line_5);

        std::cout << "Enter Amplitude (0-1): ";
        std::string line_3;
        std::getline(std::cin, line_3);

        std::cout << "Enter radius (mm): ";
        std::string line_1;
        std::getline(std::cin, line_1);

        std::cout << "Enter Amplitude-modulated frequency_1 (Hz): ";
        std::string line_2;
        std::getline(std::cin, line_2);

        std::cout << "Enter Amplitude-modulated frequency_2 (Hz): ";
        std::string line_7;
        std::getline(std::cin, line_7);

        std::cout << "Enter Envelope frequency (Hz): ";
        std::string line_4;
        std::getline(std::cin, line_4);
        

        if (line_1.empty() || line_2.empty() || line_3.empty() || line_4.empty())
            break;
        

        try {
            float mm = std::stof(line_1);
            float hz_1 = std::stof(line_2);
            float intensity = std::stof(line_3);
            float envelope = std::stof(line_4);
            float sec = std::stof(line_5);
            float hz_2 = std::stof(line_7);

            circle_data.control_point_intensity = intensity;
            circle_data.radius = mm / 1000.0f;
            circle_data.frequency_1 = hz_1;
            circle_data.frequency_2 = hz_2;
            circle_data.envelope_frequency = envelope;
            circle_data.duration = sec;

            circle_data.start_time = LocalTimeClock::now();

        }
        catch (std::invalid_argument e) {
            std::cout << "Unable to parse as number: " << line_1 << std::endl;
        }


    }

    // Stop the callback
    auto stop_result = emitter.stop();
    if (!stop_result) {
        std::cout << "Failed to stop callback: " << stop_result.error().message() << std::endl;
        return 1;
    }

    return 0;
}