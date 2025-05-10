#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "CSVReader.h"
#include "TempCompute.h"
#include "TempReadMain.h"
#include "Candlestick.h"
#include "PredictiveModel.h"

TempReadMain::TempReadMain(){}

void TempReadMain::init()
{
    loadTemperature();
    int userInput;
    while(true)
    {
        printMenu();
        userInput = selectedMenuOption();
        executeMenuOption(userInput);
    }
}

void TempReadMain::loadTemperature()
{
    CSVReader::readCSV();
}

void TempReadMain::printMenu()
{
    // 1 Print help
    std::cout << "1: Print help " << std::endl;
    // 2 print yearly temperature data
    std::cout << "2: Print yearly temperature data" << std::endl;
    // 3 Print candlestick plot
    std::cout << "3: Print candlestick plot" << std::endl;
    std::cout << "4: Print predictions" << std::endl;
    std::cout << "Type: 1-4" << std::endl;
}

// ** START OF CODE WRITTEN WITHOUT ASSISTANCE **

void TempReadMain::printHelp()
{
    std::cout << "Help - This app analyses temperature data from 1980 to 2019, including plotting candlestick data." << std::endl;
    std::cout << "=================================" << std::endl;
}

void TempReadMain::printHeader()
{
    std::cout << 
    std::setw(10) << "Year" << 
    std::setw(10) << "Open" <<
    std::setw(10) << "High" <<
    std::setw(10) << "Low" <<
    std::setw(10) << "Close" <<
    std::endl;
}
// ** END OF CODE WRITTEN WITHOUT ASSISTANCE **

void TempReadMain::printYearlyData()
{
    std::cout << "Yearly Data: Pick a country, a start year and an end year from 1980 - 2019" << std::endl;
    std::cout << "=================================" << std::endl;

    std::string countryInput;
    countryInput = selectedCountry();

    std::cout << "You chose: " << std::endl;
    std::cout << "Country: "<< countryInput << std::endl;
    
    executeCountryOption(countryInput);
}

std::string TempReadMain::selectedCountry()
{
    std::string country = "";
    std::string line;
    std::cout << "Select a country: Type the 2 letter country code (e.g. 'AT' for Austria)" << std::endl;
    std::cout << "AT - Austria" << std::endl;
    std::cout << "BE - Belgium" << std::endl;
    std::cout << "BG - Bulgaria" << std::endl;
    std::cout << "CH - Switzerland" << std::endl;
    std::cout << "CZ - Czech Republic" << std::endl;
    std::cout << "DE - Germany" << std::endl;
    std::cout << "DK - Denmark" << std::endl;
    std::cout << "EE - Estonia" << std::endl;
    std::cout << "ES - Spain" << std::endl;
    std::cout << "FI - Finland" << std::endl;
    std::cout << "FR - France" << std::endl;
    std::cout << "GB - Great Britain" << std::endl;
    std::cout << "GR - Greece" << std::endl;
    std::cout << "HR - Croatia" << std::endl;
    std::cout << "HU - Hungary" << std::endl;
    std::cout << "IE - Ireland" << std::endl;
    std::cout << "IT - Italy" << std::endl;
    std::cout << "LT - Lithuania" << std::endl;
    std::cout << "LU - Luxembourg" << std::endl;
    std::cout << "LV - Latvia" << std::endl;
    std::cout << "NL - Netherlands" << std::endl;
    std::cout << "NO - Norway" << std::endl;
    std::cout << "PL - Poland" << std::endl;
    std::cout << "PT - Portugal" << std::endl;
    std::cout << "RO - Romania" << std::endl;
    std::cout << "SE - Sweden" << std::endl;
    std::cout << "SI - Slovenia" << std::endl;
    std::cout << "SK - Slovakia" << std::endl;

    std::getline(std::cin, line);
    try
    {
        country = std::string(line);
    }
    catch(const std::exception& e)
    {

    }
    std::cout << "=================================" << std::endl;

    return country;
}



double TempReadMain::selectedValue()
{
    double value = 0.0;
    std::string line;
    std::getline(std::cin, line);
    try
    {
        value = std::stod(line);
    }
    catch(const std::exception& e)
    {

    }
    std::cout << "=================================" << std::endl;

    return value;
}

// ** START OF CODE WRITTEN WITHOUT ASSISTANCE **

void TempReadMain::printCountryYearlyData(std::vector<double> countryTemp)
{
    int userInput;
    printFilterDataOptions();
    userInput = selectedMenuOption();

    if (userInput < 1 or userInput > 6) // bad input
    {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
        printCountryYearlyData(countryTemp);
        userInput = selectedMenuOption();
    }
    if (userInput == 1) 
    {
        int yearStartInput = 0;
        int yearEndInput = 0;
        std::cout << "Select start year" << std::endl;
        yearStartInput = selectedYear();

        std::cout << "Select end year" << std::endl;
        yearEndInput = selectedYear();

        if(yearStartInput < 1980 or yearStartInput > 2019 or yearEndInput < 1980 or yearEndInput > 2019)
        {
            std::cout << "Years input are out of range" << std::endl;
        }
        else
        {
            Candlestick::clearCandlestick();
            std::vector<int> years = CSVReader::getYears();
            std::vector<double> opens = TempCompute::getOpen(countryTemp);
            std::vector<double> highs = TempCompute::getHigh(countryTemp);
            std::vector<double> lows = TempCompute::getLow(countryTemp);
            std::vector<double> closes = TempCompute::getClose(countryTemp);

            auto startIndex = find(years.begin(),years.end(),yearStartInput);
            int start = startIndex - years.begin();

            auto endIndex = find(years.begin(),years.end(),yearEndInput);
            int end = endIndex - years.begin();

            if (yearStartInput <= yearEndInput)
            {
                for (size_t i = start; i <= end; ++i) 
                {
                    Candlestick stick(years[i], opens[i], highs[i], lows[i], closes[i]);
                    Candlestick::addCandlestick(stick);  
                }
            }
            else if (yearEndInput <= yearStartInput)
            {
                for (size_t i = start; i >= end; --i) 
                {
                    Candlestick stick(years[i], opens[i], highs[i], lows[i], closes[i]);
                    Candlestick::addCandlestick(stick);  
                }
            }

            printHeader();
            for (const auto& entry : Candlestick::getCandlestick())
            {
                std::cout << 
                std::setw(10) << entry.getYear() << 
                std::setw(10) << entry.getOpen() <<
                std::setw(10) << entry.getHigh() <<
                std::setw(10) << entry.getLow() <<
                std::setw(10) << entry.getClose() <<
                std::endl;
            }
            std::cout << "==================================================================" << std::endl;
        }
    }
    if (userInput == 2) 
    {
        double min;
        double max;
        int count;

        std::cout << "Select minimum value" << std::endl;
        min = selectedValue();

        std::cout << "Select maximum value" << std::endl;
        max = selectedValue();

        Candlestick::clearCandlestick();
        std::vector<int> years = CSVReader::getYears();
        std::vector<double> opens = TempCompute::getOpen(countryTemp);
        std::vector<double> highs = TempCompute::getHigh(countryTemp);
        std::vector<double> lows = TempCompute::getLow(countryTemp);
        std::vector<double> closes = TempCompute::getClose(countryTemp);

        for (size_t i = 0; i < years.size(); ++i) 
        {
            if(opens[i] > min and opens[i] < max)
            {
                Candlestick stick(years[i], opens[i], highs[i], lows[i], closes[i]);
                Candlestick::addCandlestick(stick);  
            }
        }
        if(count > 0)
        {
            printHeader();      
            for (const auto& entry : Candlestick::getCandlestick())
            {
                std::cout << 
                std::setw(10) << entry.getYear() << 
                std::setw(10) << entry.getOpen() <<
                std::setw(10) << entry.getHigh() <<
                std::setw(10) << entry.getLow() <<
                std::setw(10) << entry.getClose() <<
                std::endl;
            }
            std::cout << "==================================================================" << std::endl;
        }
        else 
        {
            std::cout << "No data found." << std::endl;
        }
        std::cout << "=================================" << std::endl;
    } 
    if (userInput == 3)
    {
        double min;
        double max;
        int count;

        std::cout << "Select minimum value" << std::endl;
        min = selectedValue();

        std::cout << "Select maximum value" << std::endl;
        max = selectedValue();

        Candlestick::clearCandlestick();
        std::vector<int> years = CSVReader::getYears();
        std::vector<double> opens = TempCompute::getOpen(countryTemp);
        std::vector<double> highs = TempCompute::getHigh(countryTemp);
        std::vector<double> lows = TempCompute::getLow(countryTemp);
        std::vector<double> closes = TempCompute::getClose(countryTemp);

        for (size_t i = 0; i < years.size(); ++i) 
        {
            if(highs[i] > min and highs[i] < max)
            {
                Candlestick stick(years[i], opens[i], highs[i], lows[i], closes[i]);
                Candlestick::addCandlestick(stick);  
            }
        }
        if(count > 0)
        {
            printHeader();      
            for (const auto& entry : Candlestick::getCandlestick())
            {
                std::cout << 
                std::setw(10) << entry.getYear() << 
                std::setw(10) << entry.getOpen() <<
                std::setw(10) << entry.getHigh() <<
                std::setw(10) << entry.getLow() <<
                std::setw(10) << entry.getClose() <<
                std::endl;
            }
            std::cout << "==================================================================" << std::endl;
        }
        else 
        {
            std::cout << "No data found." << std::endl;
        }
        std::cout << "=================================" << std::endl;
    }
    if (userInput == 4) 
    {
        double min;
        double max;
        int count;

        std::cout << "Select minimum value" << std::endl;
        min = selectedValue();

        std::cout << "Select maximum value" << std::endl;
        max = selectedValue();

        Candlestick::clearCandlestick();
        std::vector<int> years = CSVReader::getYears();
        std::vector<double> opens = TempCompute::getOpen(countryTemp);
        std::vector<double> highs = TempCompute::getHigh(countryTemp);
        std::vector<double> lows = TempCompute::getLow(countryTemp);
        std::vector<double> closes = TempCompute::getClose(countryTemp);

        for (size_t i = 0; i < years.size(); ++i) 
        {
            if(lows[i] > min and lows[i] < max)
            {
                Candlestick stick(years[i], opens[i], highs[i], lows[i], closes[i]);
                Candlestick::addCandlestick(stick);  
            }
        }
        if(count > 0)
        {
            printHeader();      
            for (const auto& entry : Candlestick::getCandlestick())
            {
                std::cout << 
                std::setw(10) << entry.getYear() << 
                std::setw(10) << entry.getOpen() <<
                std::setw(10) << entry.getHigh() <<
                std::setw(10) << entry.getLow() <<
                std::setw(10) << entry.getClose() <<
                std::endl;
            }
            std::cout << "==================================================================" << std::endl;
        }
        else 
        {
            std::cout << "No data found." << std::endl;
        }
        std::cout << "=================================" << std::endl;
    }
    if (userInput == 5) 
    {
        double min;
        double max;
        int count = 0;

        std::cout << "Select minimum value" << std::endl;
        min = selectedValue();

        std::cout << "Select maximum value" << std::endl;
        max = selectedValue();

        Candlestick::clearCandlestick();
        std::vector<int> years = CSVReader::getYears();
        std::vector<double> opens = TempCompute::getOpen(countryTemp);
        std::vector<double> highs = TempCompute::getHigh(countryTemp);
        std::vector<double> lows = TempCompute::getLow(countryTemp);
        std::vector<double> closes = TempCompute::getClose(countryTemp);

        for (size_t i = 0; i < years.size(); ++i) 
        {
            if(closes[i] > min and closes[i] < max)
            {
                Candlestick stick(years[i], opens[i], highs[i], lows[i], closes[i]);
                Candlestick::addCandlestick(stick);  
                ++count;
            }
        }
        if(count > 0)
        {
            printHeader();      
            for (const auto& entry : Candlestick::getCandlestick())
            {
                std::cout << 
                std::setw(10) << entry.getYear() << 
                std::setw(10) << entry.getOpen() <<
                std::setw(10) << entry.getHigh() <<
                std::setw(10) << entry.getLow() <<
                std::setw(10) << entry.getClose() <<
                std::endl;
            }
            std::cout << "==================================================================" << std::endl;
        }
        else 
        {
            std::cout << "No data found." << std::endl;
        }
        std::cout << "=================================" << std::endl;
    } 
    if (userInput == 6)
    {
        int userInput;
        printMenu();
        userInput = selectedMenuOption();
        executeMenuOption(userInput);
        return;
    }
}

void TempReadMain::executeCountryOption(std::string selectedCountry)
{
    if (selectedCountry == "AT" || selectedCountry == "at")
    {
        std::cout << "AT - Austria" << std::endl;
        std::vector<double> countryTemp = CSVReader::ATtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "BE" || selectedCountry == "be")
    {
        std::cout << "BE - Belgium" << std::endl;
        std::vector<double> countryTemp = CSVReader::BEtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "BG" || selectedCountry == "bg")
    {
        std::cout << "BG - Bulgaria" << std::endl;
        std::vector<double> countryTemp = CSVReader::BGtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "CH" || selectedCountry == "ch")
    {
        std::cout << "CH - Switzerland" << std::endl;
        std::vector<double> countryTemp = CSVReader::CHtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "CZ" || selectedCountry == "cz")
    {
        std::cout << "CZ - Czech Republic" << std::endl;
        std::vector<double> countryTemp = CSVReader::CZtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "DE" || selectedCountry == "de")
    {
        std::cout << "DE - Germany" << std::endl;
        std::vector<double> countryTemp = CSVReader::DEtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "DK" || selectedCountry == "dk")
    {
        std::cout << "DK - Denmark" << std::endl;
        std::vector<double> countryTemp = CSVReader::DKtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "EE" || selectedCountry == "ee")
    {
        std::cout << "EE - Estonia" << std::endl;
        std::vector<double> countryTemp = CSVReader::EEtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "ES" || selectedCountry == "es")
    {
        std::cout << "ES - Spain" << std::endl;
        std::vector<double> countryTemp = CSVReader::EStemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "FI" || selectedCountry == "fi")
    {
        std::cout << "FI - Finland" << std::endl;
        std::vector<double> countryTemp = CSVReader::FItemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "FR" || selectedCountry == "fr")
    {
        std::cout << "FR - France" << std::endl;
        std::vector<double> countryTemp = CSVReader::FRtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "GB" || selectedCountry == "gb")
    {
        std::cout << "GB - Great Britain" << std::endl;
        std::vector<double> countryTemp = CSVReader::GBtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "GR" || selectedCountry == "gr")
    {
        std::cout << "GR - Greece" << std::endl;
        std::vector<double> countryTemp = CSVReader::GRtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "HR" || selectedCountry == "hr")
    {
        std::cout << "HR - Croatia" << std::endl;
        std::vector<double> countryTemp = CSVReader::HRtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "HU" || selectedCountry == "hu")
    {
        std::cout << "HU - Hungary" << std::endl;
        std::vector<double> countryTemp = CSVReader::HUtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "IE" || selectedCountry == "ie")
    {
        std::cout << "IE - Ireland" << std::endl;
        std::vector<double> countryTemp = CSVReader::IEtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "IT" || selectedCountry == "it")
    {
        std::cout << "IT - Italy" << std::endl;
        std::vector<double> countryTemp = CSVReader::ITtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "LT" || selectedCountry == "lt")
    {
        std::cout << "LT - Lithuania" << std::endl;
        std::vector<double> countryTemp = CSVReader::LTtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "LU" || selectedCountry == "lu")
    {
        std::cout << "LU - Luxembourg" << std::endl;
        std::vector<double> countryTemp = CSVReader::LUtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "LV" || selectedCountry == "lv")
    {
        std::cout << "LV - Latvia" << std::endl;
        std::vector<double> countryTemp = CSVReader::LVtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "NL" || selectedCountry == "nl")
    {
        std::cout << "NL - Netherlands" << std::endl;
        std::vector<double> countryTemp = CSVReader::NLtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "NO" || selectedCountry == "no")
    {
        std::cout << "NO - Norway" << std::endl;
        std::vector<double> countryTemp = CSVReader::NOtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "PL" || selectedCountry == "pl")
    {
        std::cout << "PL - Poland" << std::endl;
        std::vector<double> countryTemp = CSVReader::PLtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "PT" || selectedCountry == "pt")
    {
        std::cout << "PT - Portugal" << std::endl;
        std::vector<double> countryTemp = CSVReader::PTtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "RO" || selectedCountry == "ro")
    {
        std::cout << "RO - Romania" << std::endl;
        std::vector<double> countryTemp = CSVReader::ROtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "SE" || selectedCountry == "se")
    {
        std::cout << "SE - Sweden" << std::endl;
        std::vector<double> countryTemp = CSVReader::SEtemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "SI" || selectedCountry == "si")
    {
        std::cout << "SI - Slovenia" << std::endl;
        std::vector<double> countryTemp = CSVReader::SItemp;
        printCountryYearlyData(countryTemp);
        return;
    }
    if (selectedCountry == "SK" || selectedCountry == "sk")
    {
        std::cout << "SK - Slovakia" << std::endl;
        std::vector<double> countryTemp = CSVReader::SKtemp;
        printCountryYearlyData(countryTemp);
        return;
    }

    std::cout << "Invalid choice. Choose a 2 letter country code" << std::endl;
    std::cout << "=================================" << std::endl;
    printYearlyData();
    return;
}

void TempReadMain::printFilterDataOptions()
{
    std::cout << "1: Filter by Years" << std::endl;
    std::cout << "2: Filter by Open" << std::endl;
    std::cout << "3: Filter by High" << std::endl;
    std::cout << "4: Filter by Low" << std::endl;
    std::cout << "5: Filter by Close" << std::endl;
    std::cout << "6: Exit Yearly Data" << std::endl;
    std::cout << "=================================" << std::endl;
}

// ** END OF CODE WRITTEN WITHOUT ASSISTANCE **


int TempReadMain::selectedYear()
{
    int year;
    std::string line;
    std::getline(std::cin, line);
    try
    {
        year = std::stoi(line);
    }
    catch(const std::exception& e)
    {

    }
    std::cout << "=================================" << std::endl;

    return year;
}

// ** START OF CODE WRITTEN WITHOUT ASSISTANCE **

void TempReadMain::printCandlestickOptions()
{
    std::cout << "Candlestick Plot: Pick a country, a start year and an end year from 1980 - 2019" << std::endl;
    std::cout << "=================================" << std::endl;

    std::string countryInput;
    countryInput = selectedCountry();

    int yearStartInput;     
    std::cout << "Select start year from 1980" << std::endl;
    yearStartInput = selectedYear();

    int yearEndInput;
    std::cout << "Select end year before 2020" << std::endl;
    yearEndInput = selectedYear();

    while(abs(yearStartInput-yearEndInput)>20)
    {
        std::cout << "Year limit exceeded. Start and end years cannot be more than 20 years apart." << std::endl;
        std::cout << "Select start and end year again" << std::endl;
        std::cout << std::endl;
        std::cout << "Select start year from 1980" << std::endl;
        yearStartInput = selectedYear();
        std::cout << "Select end year before 2020" << std::endl;
        yearEndInput = selectedYear();
    }

    std::cout << "You chose: " << std::endl;
    std::cout << "Country: "<< countryInput << std::endl;
    std::cout << "Years: " << yearStartInput << " - " << yearEndInput << std::endl;
    
    executeCandlestickOption(countryInput,yearStartInput,yearEndInput);
}

void TempReadMain::executeCandlestickOption(std::string selectedCountry, int yearStart, int yearEnd)
{
    if (selectedCountry == "AT" || selectedCountry == "at")
    {
        std::cout << "AT - Austria" << std::endl;
        std::vector<double> countryTemp = CSVReader::ATtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "BE" || selectedCountry == "be")
    {
        std::cout << "BE - Belgium" << std::endl;
        std::vector<double> countryTemp = CSVReader::BEtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "BG" || selectedCountry == "bg")
    {
        std::cout << "BG - Bulgaria" << std::endl;
        std::vector<double> countryTemp = CSVReader::BGtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "CH" || selectedCountry == "ch")
    {
        std::cout << "CH - Switzerland" << std::endl;
        std::vector<double> countryTemp = CSVReader::CHtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "CZ" || selectedCountry == "cz")
    {
        std::cout << "CZ - Czech Republic" << std::endl;
        std::vector<double> countryTemp = CSVReader::CZtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "DE" || selectedCountry == "de")
    {
        std::cout << "DE - Germany" << std::endl;
        std::vector<double> countryTemp = CSVReader::DEtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "DK" || selectedCountry == "dk")
    {
        std::cout << "DK - Denmark" << std::endl;
        std::vector<double> countryTemp = CSVReader::DKtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "EE" || selectedCountry == "ee")
    {
        std::cout << "EE - Estonia" << std::endl;
        std::vector<double> countryTemp = CSVReader::EEtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "ES" || selectedCountry == "es")
    {
        std::cout << "ES - Spain" << std::endl;
        std::vector<double> countryTemp = CSVReader::EStemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "FI" || selectedCountry == "fi")
    {
        std::cout << "FI - Finland" << std::endl;
        std::vector<double> countryTemp = CSVReader::FItemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "FR" || selectedCountry == "fr")
    {
        std::cout << "FR - France" << std::endl;
        std::vector<double> countryTemp = CSVReader::FRtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "GB" || selectedCountry == "gb")
    {
        std::cout << "GB - Great Britain" << std::endl;
        std::vector<double> countryTemp = CSVReader::GBtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "GR" || selectedCountry == "gr")
    {
        std::cout << "GR - Greece" << std::endl;
        std::vector<double> countryTemp = CSVReader::GRtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "HR" || selectedCountry == "hr")
    {
        std::cout << "HR - Croatia" << std::endl;
        std::vector<double> countryTemp = CSVReader::HRtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "HU" || selectedCountry == "hu")
    {
        std::cout << "HU - Hungary" << std::endl;
        std::vector<double> countryTemp = CSVReader::HUtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "IE" || selectedCountry == "ie")
    {
        std::cout << "IE - Ireland" << std::endl;
        std::vector<double> countryTemp = CSVReader::IEtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "IT" || selectedCountry == "it")
    {
        std::cout << "IT - Italy" << std::endl;
        std::vector<double> countryTemp = CSVReader::ITtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "LT" || selectedCountry == "lt")
    {
        std::cout << "LT - Lithuania" << std::endl;
        std::vector<double> countryTemp = CSVReader::LTtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "LU" || selectedCountry == "lu")
    {
        std::cout << "LU - Luxembourg" << std::endl;
        std::vector<double> countryTemp = CSVReader::LUtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "LV" || selectedCountry == "lv")
    {
        std::cout << "LV - Latvia" << std::endl;
        std::vector<double> countryTemp = CSVReader::LVtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "NL" || selectedCountry == "nl")
    {
        std::cout << "NL - Netherlands" << std::endl;
        std::vector<double> countryTemp = CSVReader::NLtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "NO" || selectedCountry == "no")
    {
        std::cout << "NO - Norway" << std::endl;
        std::vector<double> countryTemp = CSVReader::NOtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "PL" || selectedCountry == "pl")
    {
        std::cout << "PL - Poland" << std::endl;
        std::vector<double> countryTemp = CSVReader::PLtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "PT" || selectedCountry == "pt")
    {
        std::cout << "PT - Portugal" << std::endl;
        std::vector<double> countryTemp = CSVReader::PTtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "RO" || selectedCountry == "ro")
    {
        std::cout << "RO - Romania" << std::endl;
        std::vector<double> countryTemp = CSVReader::ROtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "SE" || selectedCountry == "se")
    {
        std::cout << "SE - Sweden" << std::endl;
        std::vector<double> countryTemp = CSVReader::SEtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "SI" || selectedCountry == "si")
    {
        std::cout << "SI - Slovenia" << std::endl;
        std::vector<double> countryTemp = CSVReader::SItemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }
    if (selectedCountry == "SK" || selectedCountry == "sk")
    {
        std::cout << "SK - Slovakia" << std::endl;
        std::vector<double> countryTemp = CSVReader::SKtemp;
        printCandlestickPlot(countryTemp,yearStart,yearEnd);
        return;
    }

    std::cout << "Invalid choice. Choose one of the 2 letter country codes and a start year from 1980 - 2019" << std::endl;
    std::cout << "=================================" << std::endl;
    printCandlestickOptions();
    return;
}

void TempReadMain::printCandlestickPlot(std::vector<double> countryTemp, int yearStart, int yearEnd)
{
    Candlestick::clearCandlestick();
    std::vector<int> years = CSVReader::getYears();
    std::vector<double> opens = TempCompute::getOpen(countryTemp);
    std::vector<double> highs = TempCompute::getHigh(countryTemp);
    std::vector<double> lows = TempCompute::getLow(countryTemp);
    std::vector<double> closes = TempCompute::getClose(countryTemp);

    auto startIndex = find(years.begin(),years.end(),yearStart);
    int start = startIndex - years.begin();

    auto endIndex = find(years.begin(),years.end(),yearEnd);
    int end = endIndex - years.begin();

    if (yearStart <= yearEnd)
    {
        for (size_t i = start; i <= end; ++i) 
        {
            Candlestick stick(years[i], opens[i], highs[i], lows[i], closes[i]);
            Candlestick::addCandlestick(stick);  
        }
    }
    else if (yearEnd <= yearStart)
    {
        for (size_t i = start; i >= end; --i) 
        {
            Candlestick stick(years[i], opens[i], highs[i], lows[i], closes[i]);
            Candlestick::addCandlestick(stick);  
        }
    }

    for (int i = 40; i >= -30; --i)
    {
        std::cout << std::setw(4) << i << "|";
        int count = 0;
        for (const auto& entry : Candlestick::getCandlestick())
        {
            int start = count*7;
            int end = (count+1)*7;

            for (int j = start; j <= end; ++j)
            {
                // If open more than close (average temp drops, show negative)
                if(entry.getOpen() > entry.getClose()) 
                {
                    if (i <= round(entry.getHigh()) and i > round(entry.getOpen()) and j == (start+5)) {std::cout << "|";}
                    else if(j >= start+4 and j <= start+6 and i == round(entry.getOpen())) {std::cout << "-";}
                    else if(j >= start+4 and j <= start+6 and i == round(entry.getClose())) {std::cout << "-";}
                    else if(i < round(entry.getOpen()) and i > round(entry.getClose()) and (j==start+4 or j==start+6)) {std::cout << "-";}
                    else if (i >= round(entry.getLow()) and i < round(entry.getClose()) and j == (start+5)) {std::cout << "|";}
                    else {std::cout << " ";}
                }
                // If close more than open (average temp rise, show positive)
                else if(entry.getOpen() < entry.getClose())
                {
                    if (i <= round(entry.getHigh()) and i > round(entry.getClose()) and j == (start+5)) {std::cout << "|";}
                    else if(j >= start+4 and j <= start+6 and i == round(entry.getOpen())) {std::cout << "+";}
                    else if(j >= start+4 and j <= start+6 and i == round(entry.getClose())) {std::cout << "+";}
                    else if(i > round(entry.getOpen()) and i < round(entry.getClose()) and (j==(start+4) or j==(start+6))) {std::cout << "+";}
                    else if (i >= round(entry.getLow()) and i < round(entry.getOpen()) and j == (start+5)) {std::cout << "|";}
                    else {std::cout << " ";}
                }
            }
            ++count;
        }
        std::cout << std::endl;
    }

    std::cout << std::setw(5) << "";
    for (int i = 0; i <= 3*abs(yearStart-yearEnd); ++i)
    {
        std::cout << "▔▔▔";
    }
    std::cout << std::endl;

    std::cout << std::setw(5) << "";
    if(yearStart <= yearEnd)
    {
        for (int i = yearStart; i <= yearEnd; ++i)
        {
            std::cout << std::setw(4) << "" << i ;
        }
    }
    else if(yearEnd <= yearStart)
    {
        for (int i = yearStart; i >= yearEnd; --i)
        {
            std::cout << std::setw(4) << "" << i ;
        }
    }
    
    std::cout << std::endl;
}

void TempReadMain::printPredictiveOptions()
{
    std::cout << "Predictions: Pick a country and an end year after 2019" << std::endl;
    std::cout << "=================================" << std::endl;

    std::string countryInput;
    countryInput = selectedCountry();

    int yearEndInput;
    std::cout << "Select end year after 2019" << std::endl;
    yearEndInput = selectedYear();

    std::cout << "You chose: " << std::endl;
    std::cout << "Country: "<< countryInput << std::endl;
    std::cout << "End Year: " << yearEndInput << std::endl;
    
    executePredictiveOptions(countryInput,yearEndInput);
}

void TempReadMain::executePredictiveOptions(std::string selectedCountry, int yearEnd)
{
    if (selectedCountry == "AT" || selectedCountry == "at")
    {
        std::cout << "AT - Austria" << std::endl;
        std::vector<double> countryTemp = CSVReader::ATtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "BE" || selectedCountry == "be")
    {
        std::cout << "BE - Belgium" << std::endl;
        std::vector<double> countryTemp = CSVReader::BEtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "BG" || selectedCountry == "bg")
    {
        std::cout << "BG - Bulgaria" << std::endl;
        std::vector<double> countryTemp = CSVReader::BGtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "CH" || selectedCountry == "ch")
    {
        std::cout << "CH - Switzerland" << std::endl;
        std::vector<double> countryTemp = CSVReader::CHtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "CZ" || selectedCountry == "cz")
    {
        std::cout << "CZ - Czech Republic" << std::endl;
        std::vector<double> countryTemp = CSVReader::CZtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "DE" || selectedCountry == "de")
    {
        std::cout << "DE - Germany" << std::endl;
        std::vector<double> countryTemp = CSVReader::DEtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "DK" || selectedCountry == "dk")
    {
        std::cout << "DK - Denmark" << std::endl;
        std::vector<double> countryTemp = CSVReader::DKtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "EE" || selectedCountry == "ee")
    {
        std::cout << "EE - Estonia" << std::endl;
        std::vector<double> countryTemp = CSVReader::EEtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "ES" || selectedCountry == "es")
    {
        std::cout << "ES - Spain" << std::endl;
        std::vector<double> countryTemp = CSVReader::EStemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "FI" || selectedCountry == "fi")
    {
        std::cout << "FI - Finland" << std::endl;
        std::vector<double> countryTemp = CSVReader::FItemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "FR" || selectedCountry == "fr")
    {
        std::cout << "FR - France" << std::endl;
        std::vector<double> countryTemp = CSVReader::FRtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "GB" || selectedCountry == "gb")
    {
        std::cout << "GB - Great Britain" << std::endl;
        std::vector<double> countryTemp = CSVReader::GBtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "GR" || selectedCountry == "gr")
    {
        std::cout << "GR - Greece" << std::endl;
        std::vector<double> countryTemp = CSVReader::GRtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "HR" || selectedCountry == "hr")
    {
        std::cout << "HR - Croatia" << std::endl;
        std::vector<double> countryTemp = CSVReader::HRtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "HU" || selectedCountry == "hu")
    {
        std::cout << "HU - Hungary" << std::endl;
        std::vector<double> countryTemp = CSVReader::HUtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "IE" || selectedCountry == "ie")
    {
        std::cout << "IE - Ireland" << std::endl;
        std::vector<double> countryTemp = CSVReader::IEtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "IT" || selectedCountry == "it")
    {
        std::cout << "IT - Italy" << std::endl;
        std::vector<double> countryTemp = CSVReader::ITtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "LT" || selectedCountry == "lt")
    {
        std::cout << "LT - Lithuania" << std::endl;
        std::vector<double> countryTemp = CSVReader::LTtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "LU" || selectedCountry == "lu")
    {
        std::cout << "LU - Luxembourg" << std::endl;
        std::vector<double> countryTemp = CSVReader::LUtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "LV" || selectedCountry == "lv")
    {
        std::cout << "LV - Latvia" << std::endl;
        std::vector<double> countryTemp = CSVReader::LVtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "NL" || selectedCountry == "nl")
    {
        std::cout << "NL - Netherlands" << std::endl;
        std::vector<double> countryTemp = CSVReader::NLtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "NO" || selectedCountry == "no")
    {
        std::cout << "NO - Norway" << std::endl;
        std::vector<double> countryTemp = CSVReader::NOtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "PL" || selectedCountry == "pl")
    {
        std::cout << "PL - Poland" << std::endl;
        std::vector<double> countryTemp = CSVReader::PLtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "PT" || selectedCountry == "pt")
    {
        std::cout << "PT - Portugal" << std::endl;
        std::vector<double> countryTemp = CSVReader::PTtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "RO" || selectedCountry == "ro")
    {
        std::cout << "RO - Romania" << std::endl;
        std::vector<double> countryTemp = CSVReader::ROtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "SE" || selectedCountry == "se")
    {
        std::cout << "SE - Sweden" << std::endl;
        std::vector<double> countryTemp = CSVReader::SEtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "SI" || selectedCountry == "si")
    {
        std::cout << "SI - Slovenia" << std::endl;
        std::vector<double> countryTemp = CSVReader::SItemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }
    if (selectedCountry == "SK" || selectedCountry == "sk")
    {
        std::cout << "SK - Slovakia" << std::endl;
        std::vector<double> countryTemp = CSVReader::SKtemp;
        printPredictions(countryTemp,yearEnd);
        return;
    }

    std::cout << "Invalid choice. Choose one of the 2 letter country codes and an year fter 2019" << std::endl;
    std::cout << "=================================" << std::endl;
    printCandlestickOptions();
    return;
}

void TempReadMain::printPredictions(std::vector<double> countryTemp, int yearEnd)
{
    Candlestick::clearCandlestick();
    std::vector<int> years = CSVReader::getYears();
    std::vector<double> opens = TempCompute::getOpen(countryTemp);
    std::vector<double> highs = TempCompute::getHigh(countryTemp);
    std::vector<double> lows = TempCompute::getLow(countryTemp);
    std::vector<double> closes = TempCompute::getClose(countryTemp);

    int n = yearEnd - 2019;

    std::vector<std::vector<double> > exogHighs(years.size(), std::vector<double>(2));
    for (size_t i = 0; i < years.size(); ++i)
    {
        exogHighs[i][0] = closes[i];
        exogHighs[i][1] = lows[i];
    }

    std::vector<std::vector<double> > exogLows(years.size(), std::vector<double>(2));
    for (size_t i = 0; i < years.size(); ++i)
    {
        exogLows[i][0] = closes[i];
        exogLows[i][1] = highs[i];
    }

    std::vector<std::vector<double> > exogCloses(years.size(), std::vector<double>(3));
    for (size_t i = 0; i < years.size(); ++i)
    {
        exogCloses[i][0] = highs[i];
        exogCloses[i][1] = lows[i];
    }
    
    std::vector<double> predictionHighs = PredictiveModel::arimax(highs,exogHighs, n);
    std::vector<double> predictionLows = PredictiveModel::arimax(lows,exogLows, n);
    std::vector<double> predictionCloses = PredictiveModel::arimax(closes,exogCloses, n);

    for(size_t i = 2020; i<= yearEnd; ++i)
    {
        years.push_back(i);
    }

    opens.push_back(closes.back());
    for(size_t i = 0; i <= n; ++i)
    {
        if(i>0)
        {
            opens.push_back(predictionCloses[i-1]);
        }
        highs.push_back(predictionHighs[i]);
        lows.push_back(predictionLows[i]);
        closes.push_back(predictionCloses[i]);
    }

    for (size_t i = 0; i < years.size(); ++i)
    {
        Candlestick stick(years[i], opens[i], highs[i], lows[i], closes[i]);
        Candlestick::addCandlestick(stick);  
    }
        
    printHeader();      
    for (const auto& entry : Candlestick::getCandlestick())
    {
        std::cout << 
        std::setw(10) << entry.getYear() << 
        std::setw(10) << entry.getOpen() <<
        std::setw(10) << entry.getHigh() <<
        std::setw(10) << entry.getLow() <<
        std::setw(10) << entry.getClose() <<
        std::endl;
    }
    std::cout << "==================================================================" << std::endl;

    std::cout << "Printing candlestick plot for predictions" << std::endl;
    std::cout << "Select a start year" << std::endl;
    int selectedYearStart = selectedYear();
    std::cout << "Select an end year before " << yearEnd+1 << std::endl;
    int selectedYearEnd = selectedYear();
    if(selectedYearEnd - selectedYearStart > 20)
    {
        std::cout << "Start and end years cannot be more than 20 years apart" << std::endl;
        std::cout << "Select a start year" << std::endl;
        selectedYearStart = selectedYear();
        std::cout << "Select an end year before " << yearEnd+1 << std::endl;
        selectedYearEnd = selectedYear();
    }

    printPredictionPlot(years,opens,highs,lows,closes,selectedYearStart,selectedYearEnd);
}

void TempReadMain::printPredictionPlot(std::vector<int> years,std::vector<double> opens,std::vector<double> highs,std::vector<double> lows,std::vector<double> closes, int yearStart, int yearEnd)
{
    Candlestick::clearCandlestick();

    auto startIndex = find(years.begin(),years.end(),yearStart);
    int start = startIndex - years.begin();

    auto endIndex = find(years.begin(),years.end(),yearEnd);
    int end = endIndex - years.begin();

    if (yearStart <= yearEnd)
    {
        for (size_t i = start; i <= end; ++i) 
        {
            Candlestick stick(years[i], opens[i], highs[i], lows[i], closes[i]);
            Candlestick::addCandlestick(stick);  
        }
    }
    else if (yearEnd <= yearStart)
    {
        for (size_t i = start; i >= end; --i) 
        {
            Candlestick stick(years[i], opens[i], highs[i], lows[i], closes[i]);
            Candlestick::addCandlestick(stick);  
        }
    }

    for (int i = 50; i >= -30; --i)
    {
        std::cout << std::setw(4) << i << "|";
        int count = 0;
        for (const auto& entry : Candlestick::getCandlestick())
        {
            int start = count*7;
            int end = (count+1)*7;

            for (int j = start; j <= end; ++j)
            {
                // If open more than close (average temp drops, show negative)
                if(entry.getOpen() > entry.getClose()) 
                {
                    if (i <= round(entry.getHigh()) and i > round(entry.getOpen()) and j == (start+5)) {std::cout << "|";}
                    else if(j >= start+4 and j <= start+6 and i == round(entry.getOpen())) {std::cout << "-";}
                    else if(j >= start+4 and j <= start+6 and i == round(entry.getClose())) {std::cout << "-";}
                    else if(i < round(entry.getOpen()) and i > round(entry.getClose()) and (j==start+4 or j==start+6)) {std::cout << "-";}
                    else if (i >= round(entry.getLow()) and i < round(entry.getClose()) and j == (start+5)) {std::cout << "|";}
                    else {std::cout << " ";}
                }
                // If close more than open (average temp rise, show positive)
                else if(entry.getOpen() < entry.getClose())
                {
                    if (i <= round(entry.getHigh()) and i > round(entry.getClose()) and j == (start+5)) {std::cout << "|";}
                    else if(j >= start+4 and j <= start+6 and i == round(entry.getOpen())) {std::cout << "+";}
                    else if(j >= start+4 and j <= start+6 and i == round(entry.getClose())) {std::cout << "+";}
                    else if(i > round(entry.getOpen()) and i < round(entry.getClose()) and (j==(start+4) or j==(start+6))) {std::cout << "+";}
                    else if (i >= round(entry.getLow()) and i < round(entry.getOpen()) and j == (start+5)) {std::cout << "|";}
                    else {std::cout << " ";}
                }
            }
            ++count;
        }
        std::cout << std::endl;
    }

    std::cout << std::setw(5) << "";
    for (int i = 0; i <= 3*abs(yearStart-yearEnd); ++i)
    {
        std::cout << "▔▔▔";
    }
    std::cout << std::endl;

    std::cout << std::setw(5) << "";
    if(yearStart <= yearEnd)
    {
        for (int i = yearStart; i <= yearEnd; ++i)
        {
            std::cout << std::setw(4) << "" << i ;
        }
    }
    else if(yearEnd <= yearStart)
    {
        for (int i = yearStart; i >= yearEnd; --i)
        {
            std::cout << std::setw(4) << "" << i ;
        }
    }
    
    std::cout << std::endl;
}

// ** END OF CODE WRITTEN WITHOUT ASSISTANCE **


int TempReadMain::selectedMenuOption()
{
    int option = 0;
    std::string line;
    std::getline(std::cin, line);
    try
    {
        option = std::stoi(line);
    }
    catch(const std::exception& e)
    {

    }
    std::cout << "=================================" << std::endl;
    std::cout << "You chose: " << option << std::endl;
    return option;
}

void TempReadMain::executeMenuOption(int selectedOption)
{
    if (selectedOption < 0 or selectedOption > 4) // bad input
    {
        std::cout << "Invalid choice. Choose 1-3" << std::endl;
    }
    if (selectedOption == 1) 
    {
        printHelp();
    }
    if (selectedOption == 2) 
    {
        printYearlyData();
    } 
    if (selectedOption == 3)
    {
        printCandlestickOptions();
    }
    if (selectedOption == 4)
    {
        printPredictiveOptions();
    }
}