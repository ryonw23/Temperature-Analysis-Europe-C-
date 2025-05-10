#include "TempCompute.h"
#include "CSVReader.h"
#include <cstddef>
#include <ostream>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
// ** START OF CODE WRITTEN WITHOUT ASSISTANCE **
std::vector<double> TempCompute::openVector;
std::vector<double> TempCompute::highVector;
std::vector<double> TempCompute::lowVector;
std::vector<double> TempCompute::closeVector;

TempCompute::TempCompute(){}

void TempCompute::run(std::vector<double> countryTemp)
{
    getOpen(countryTemp);
    getHigh(countryTemp);
    getLow(countryTemp);
    getClose(countryTemp);
}

std::vector<double> TempCompute::getMean(std::vector<double> countryTemp)
{
    std::vector<double> meanVector;
    meanVector.clear();
    size_t start = 0;  // Start index for the current year
    for (size_t i = 0; i < CSVReader::timestamps.size(); ++i)
    {
        int currentYear = CSVReader::timestamps[i];  // Year for the current row
        int nextYear;
        if (i < CSVReader::timestamps.size())
        {
            nextYear = CSVReader::timestamps[i+1];
        }
        else 
        {
            break;
        }
        // Check if the year changes or if we reach the last row
        if (currentYear != nextYear)
        {
            // Calculate the sum and average for the current year
            double sum = 0;
            for (size_t j = start; j < i+1; ++j)
            {
                sum += countryTemp[j];  // Accumulate temperature values for the current year
            }
            
            double mean = sum / (i - start + 1);  // Average temperature for the year
            meanVector.push_back(mean);
            // Move the start pointer to the next year
            start = i + 1;
        }
    }
    return meanVector;
}

std::vector<double> TempCompute::getOpen(std::vector<double> countryTemp)
{
    TempCompute::openVector.clear();
    std::vector<double> meanVector = getMean(countryTemp);
    // Interpolate first open data with first year data: (high+low)/2
    TempCompute::openVector.push_back((TempCompute::getHigh(countryTemp)[0]+TempCompute::getLow(countryTemp)[0])/2);
    for (size_t i = 0; i < meanVector.size()-1; ++i)
    {
        TempCompute::openVector.push_back(meanVector[i]);
    }
    return TempCompute::openVector;
}

std::vector<double> TempCompute::getHigh(std::vector<double> countryTemp)
{
    TempCompute::highVector.clear();
    size_t start = 0;  // Start index for the current year
    for (size_t i = 0; i < CSVReader::timestamps.size(); ++i)
    {
        int currentYear = CSVReader::timestamps[i];  // Year for the current row
        int nextYear;
        if (i < CSVReader::timestamps.size())
        {
            nextYear = CSVReader::timestamps[i+1];
        }
        else 
        {
            break;
        }
        // Check if the year changes or if we reach the last row
        if (currentYear != nextYear)
        {
            double high = countryTemp[start];
            for (size_t j = start; j < i+1; ++j)
            {
                if(countryTemp[j] > high)
                {
                    high = countryTemp[j];
                }
            }
            TempCompute::highVector.push_back(high);
            // // Move the start pointer to the next year
            start = i + 1;
        }
    }
    return TempCompute::highVector;
}

std::vector<double> TempCompute::getLow(std::vector<double> countryTemp)
{
    TempCompute::lowVector.clear();
    size_t start = 0;  // Start index for the current year
    for (size_t i = 0; i < CSVReader::timestamps.size(); ++i)
    {
        int currentYear = CSVReader::timestamps[i];  // Year for the current row
        int nextYear;
        if (i < CSVReader::timestamps.size())
        {
            nextYear = CSVReader::timestamps[i+1];
        }
        else 
        {
            break;
        }
        // Check if the year changes or if we reach the last row
        if (currentYear != nextYear)
        {
            double low = countryTemp[start];
            for (size_t j = start; j < i+1; ++j)
            {
                if(countryTemp[j] < low)
                {
                    low = countryTemp[j];
                }
            }
            TempCompute::lowVector.push_back(low);
            // // Move the start pointer to the next year
            start = i + 1;
        }
    }
    return TempCompute::lowVector;
}

std::vector<double> TempCompute::getClose(std::vector<double> countryTemp)
{
    TempCompute::closeVector.clear();
    TempCompute::closeVector = getMean(countryTemp);
    return TempCompute::closeVector;
}
// ** END OF CODE WRITTEN WITHOUT ASSISTANCE **