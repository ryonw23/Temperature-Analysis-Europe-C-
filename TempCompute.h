#pragma once

#include <vector>
// ** START OF CODE WRITTEN WITHOUT ASSISTANCE **
class TempCompute
{
    public:
        TempCompute();
        static void run(std::vector<double> countryTemp);
        static std::vector<double> openVector;
        static std::vector<double> highVector;
        static std::vector<double> lowVector;
        static std::vector<double> closeVector;
        static std::vector<double> getMean(std::vector<double> countryTemp);
        static std::vector<double> getOpen(std::vector<double> countryTemp);
        static std::vector<double> getHigh(std::vector<double> countryTemp);
        static std::vector<double> getLow(std::vector<double> countryTemp);
        static std::vector<double> getClose(std::vector<double> countryTemp);
};
// ** END OF CODE WRITTEN WITHOUT ASSISTANCE **