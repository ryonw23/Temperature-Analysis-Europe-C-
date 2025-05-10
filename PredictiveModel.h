#pragma once

#include <vector>
// ** START OF CODE WRITTEN WITHOUT ASSISTANCE **
class PredictiveModel
{
    public:
        PredictiveModel();
        static std::vector<double> arimax(std::vector<double>& data, std::vector<std::vector<double> >& exog, int forecast);
    private:
        static double autocorrelation(std::vector<double>& data, int lag);
        static double movingAverage(std::vector<double>& residuals, int lag);

        static std::vector<double> difference(std::vector<double>& data);
        static double mean(std::vector<double>& data);
};
// ** END OF CODE WRITTEN WITHOUT ASSISTANCE **