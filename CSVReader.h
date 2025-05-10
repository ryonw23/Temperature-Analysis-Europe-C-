#pragma once

#include <string>
#include <vector>

class CSVReader
{
    public:
        CSVReader();
        static void readCSV();
        static const std::vector<int>& getYears();
        static std::vector<int> timestamps;
        static std::vector<int> yearsList;
        static std::vector<double> ATtemp;
        static std::vector<double> BEtemp;
        static std::vector<double> BGtemp;
        static std::vector<double> CHtemp;
        static std::vector<double> CZtemp;
        static std::vector<double> DEtemp;
        static std::vector<double> DKtemp;
        static std::vector<double> EEtemp;
        static std::vector<double> EStemp;
        static std::vector<double> FItemp;
        static std::vector<double> FRtemp;
        static std::vector<double> GBtemp;
        static std::vector<double> GRtemp;
        static std::vector<double> HRtemp;
        static std::vector<double> HUtemp;
        static std::vector<double> IEtemp;
        static std::vector<double> ITtemp;
        static std::vector<double> LTtemp;
        static std::vector<double> LUtemp;
        static std::vector<double> LVtemp;
        static std::vector<double> NLtemp;
        static std::vector<double> NOtemp;
        static std::vector<double> PLtemp;
        static std::vector<double> PTtemp;
        static std::vector<double> ROtemp;
        static std::vector<double> SEtemp;
        static std::vector<double> SItemp;
        static std::vector<double> SKtemp;
        static std::vector<std::string> tokenise(std::string csvLine, char sep);
};