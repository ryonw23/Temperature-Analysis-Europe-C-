#pragma once

#include <string>
#include <vector>
// ** START OF CODE WRITTEN WITHOUT ASSISTANCE **
class TempReadMain
{
    public:
        TempReadMain();
        void init();
    private:
        void loadTemperature();

        void printMenu();
        void printHelp();
        void printHeader();

        std::string selectedCountry();
        void printYearlyData();
        void printCountryYearlyData(std::vector<double> countryTemp);
        void executeCountryOption(std::string selectedCountry);

        double selectedValue();
        void printFilterDataOptions();

        int selectedYear();
        void printCandlestickOptions();
        void executeCandlestickOption(std::string selectedCountry,int yearStart, int yearEnd);
        void printCandlestickPlot(std::vector<double> countryTemp,int yearStart, int yearEnd);

        void printPredictiveOptions();
        void executePredictiveOptions(std::string selectedCountry, int yearEnd);
        void printPredictions(std::vector<double> countryTemp, int yearEnd);
        void printPredictionPlot(std::vector<int> years,std::vector<double> opens,std::vector<double> highs,std::vector<double> lows,std::vector<double> closes, int yearStart, int yearEnd);

        int selectedMenuOption();
        void executeMenuOption(int selectedOption);
};
// ** END OF CODE WRITTEN WITHOUT ASSISTANCE **