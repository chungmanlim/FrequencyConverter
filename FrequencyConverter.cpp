#include <iostream>
#include <string>

std::pair<float, float> freqConverter(float f0, float f1) {
    float JND_M = 0.25;
    float JND_U = 0.73;

    float f0_U = f0;
    float f1_U = f0 + (f1 - f0) * (JND_U / JND_M);

    if (f0 < 0 || f1 < 0) {
        std::cout << "Check frequency ranges" << std::endl;
        return std::make_pair(-1, -1); 
    }
    else if (f1 < f0) {
        std::cout << "The second frequency should be higher than the first frequency." << std::endl;
        return std::make_pair(-1, -1); 
    }
    else {
        return std::make_pair(f0_U, f1_U);
    }
}

int main() {
    float freq0_U = 0;
    float freq1_U = 0;

    while (true) {
        std::cout << " " << std::endl;
        std::cout << "[Frequency range of mechanical vibrations]" << std::endl;

        std::cout << "Enter lower frequency (Hz): ";
        std::string line_1;
        std::getline(std::cin, line_1);

        std::cout << "Enter higher frequency (Hz): ";
        std::string line_2;
        std::getline(std::cin, line_2);

        if (line_1.empty() || line_2.empty())
            break;

        float freq0 = std::stof(line_1);
        float freq1 = std::stof(line_2);


        std::pair<float, float> convertedFreqs = freqConverter(freq0, freq1);
        if (convertedFreqs.first != -1 && convertedFreqs.second != -1) {
            freq0_U = convertedFreqs.first;
            freq1_U = convertedFreqs.second;

            std::cout << " " << std::endl;
            std::cout << "[Converted AM frequency range]" << std::endl;
            std::cout << "Lower AM frequency: " << freq0_U << " Hz " << std::endl;
            std::cout << "Higher AM frequency: " << freq1_U << " Hz " << std::endl;
            std::cout << " " << std::endl;
            std::cout << "Hit ENTER to quit...";
            std::cout << " " << std::endl;
        }
    }

}
