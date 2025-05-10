#include "CSVReader.h"
#include "Candlestick.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

CSVReader::CSVReader(){};

std::vector<int> CSVReader::timestamps;
std::vector<int> CSVReader::yearsList;
std::vector<double> CSVReader::ATtemp;
std::vector<double> CSVReader::BEtemp;
std::vector<double> CSVReader::BGtemp;
std::vector<double> CSVReader::CHtemp;
std::vector<double> CSVReader::CZtemp;
std::vector<double> CSVReader::DEtemp;
std::vector<double> CSVReader::DKtemp;
std::vector<double> CSVReader::EEtemp;
std::vector<double> CSVReader::EStemp;
std::vector<double> CSVReader::FItemp;
std::vector<double> CSVReader::FRtemp;
std::vector<double> CSVReader::GBtemp;
std::vector<double> CSVReader::GRtemp;
std::vector<double> CSVReader::HRtemp;
std::vector<double> CSVReader::HUtemp;
std::vector<double> CSVReader::IEtemp;
std::vector<double> CSVReader::ITtemp;
std::vector<double> CSVReader::LTtemp;
std::vector<double> CSVReader::LUtemp;
std::vector<double> CSVReader::LVtemp;
std::vector<double> CSVReader::NLtemp;
std::vector<double> CSVReader::NOtemp;
std::vector<double> CSVReader::PLtemp;
std::vector<double> CSVReader::PTtemp;
std::vector<double> CSVReader::ROtemp;
std::vector<double> CSVReader::SEtemp;
std::vector<double> CSVReader::SItemp;
std::vector<double> CSVReader::SKtemp;

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char sep)
{
    std::vector<std::string> tokens;
    signed int start,end;
    std::string token;

    start = csvLine.find_first_not_of(sep, 0);
    do 
    {
        end = csvLine.find_first_of(sep, start);
        if (start == csvLine.length() || start == end) 
        {
            break;
        }
        if (end >= 0) 
        {
            token = csvLine.substr(start,end - start);
        }
        else 
        {
            token = csvLine.substr(start,csvLine.length() - start);
        }
        tokens.push_back(token);
        start = end + 1;
    }
    while (end > 0);
    return tokens;
}

void CSVReader::readCSV()
{
    std::ifstream csvFile{"weather_data_EU_1980-2019_temp_only.csv"};
    std::string line;
    std::vector<std::string> tokens;

    if (csvFile.is_open()) 
    {
        std::cout << "Reading file. Please hold." << std::endl;
        while (getline(csvFile,line))
        {
            // std::cout << "Read line: " << line << std::endl;
            tokens = tokenise(line,',');
            if(tokens.size() != 29)
            {
                // std::cout << "Bad line" << std::endl;
                throw std::exception{};
            }
            try
            {
                std::string timestamp = tokens[0];
                CSVReader::timestamps.push_back(std::stoi(timestamp.substr(0,4)));
                CSVReader::ATtemp.push_back(std::stod(tokens[1]));
                CSVReader::BEtemp.push_back(std::stod(tokens[2]));
                CSVReader::BGtemp.push_back(std::stod(tokens[3]));
                CSVReader::CHtemp.push_back(std::stod(tokens[4]));
                CSVReader::CZtemp.push_back(std::stod(tokens[5]));
                CSVReader::DEtemp.push_back(std::stod(tokens[6]));
                CSVReader::DKtemp.push_back(std::stod(tokens[7]));
                CSVReader::EEtemp.push_back(std::stod(tokens[8]));
                CSVReader::EStemp.push_back(std::stod(tokens[9]));
                CSVReader::FItemp.push_back(std::stod(tokens[10]));
                CSVReader::FRtemp.push_back(std::stod(tokens[11]));
                CSVReader::GBtemp.push_back(std::stod(tokens[12]));
                CSVReader::GRtemp.push_back(std::stod(tokens[13]));
                CSVReader::HRtemp.push_back(std::stod(tokens[14]));
                CSVReader::HUtemp.push_back(std::stod(tokens[15]));
                CSVReader::IEtemp.push_back(std::stod(tokens[16]));
                CSVReader::ITtemp.push_back(std::stod(tokens[17]));
                CSVReader::LTtemp.push_back(std::stod(tokens[18]));
                CSVReader::LUtemp.push_back(std::stod(tokens[19]));
                CSVReader::LVtemp.push_back(std::stod(tokens[20]));
                CSVReader::NLtemp.push_back(std::stod(tokens[21]));
                CSVReader::NOtemp.push_back(std::stod(tokens[22]));
                CSVReader::PLtemp.push_back(std::stod(tokens[23]));
                CSVReader::PTtemp.push_back(std::stod(tokens[24]));
                CSVReader::ROtemp.push_back(std::stod(tokens[25]));
                CSVReader::SEtemp.push_back(std::stod(tokens[26]));
                CSVReader::SItemp.push_back(std::stod(tokens[27]));
                CSVReader::SKtemp.push_back(std::stod(tokens[28]));
            }
            catch (std::exception &e)
            {
            }
        }
        csvFile.close();
    }
    else 
    {
        std::cout << "File is not open" << std::endl;
    }
}
// ** START OF CODE WRITTEN WITHOUT ASSISTANCE **
const std::vector<int>& CSVReader::getYears()
{
    CSVReader::yearsList.clear();
    CSVReader::yearsList.push_back(CSVReader::timestamps[0]);
    for (size_t i = 1; i < CSVReader::timestamps.size(); ++i)
    {
        int currentYear = CSVReader::timestamps[i];
        if(currentYear != CSVReader::yearsList.back())
        {
            CSVReader::yearsList.push_back(CSVReader::timestamps[i]);
        }
    }
    return CSVReader::yearsList;
}
// ** END OF CODE WRITTEN WITHOUT ASSISTANCE **