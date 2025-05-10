#include "PredictiveModel.h"
#include <cstddef>
#include <stdexcept>
#include <exception>
#include <ostream>
#include <iostream>
#include <vector>

PredictiveModel::PredictiveModel(){};

double PredictiveModel::mean(std::vector<double>& data)
{
	if (data.empty())
	{
        throw std::invalid_argument("Dataset is empty");
	}
	double sum = 0;
	for (const auto& entry : data)
	{
        sum += entry;
	}
	return sum / data.size();
}

std::vector<double> PredictiveModel::difference(std::vector<double>& data)
{
	std::vector<double> differencedData;
	for (size_t i = 1; i < data.size(); ++i)
	{
        differencedData.push_back(data[i]-data[i-1]);
	}
	return differencedData;
}

double PredictiveModel::autocorrelation(std::vector<double>& data, int lag)
{
	// implement using the autocorrelation formula with data and input lag
	int n = data.size();
	// prevent lag from being greater than or equal to dataset size
	if (lag >= n)
	{
        throw std::invalid_argument("Lag cannot be greater than dataset size");
	};

	double meanVal = mean(data);
	double numerator = 0;
	double denominator = 0;

	for (size_t i = 0; i < n - lag; ++i)
	{
    	// numerator is equal to the sum of the products of the difference between data and mean with the difference between the lag data and mean
    	numerator += (data[i] - meanVal) * (data[i+lag] - meanVal);
	};

	for (size_t i = 0; i < n; ++i)
	{
    	// denominator is equal to the sum of the square of the difference between data and mean
    	denominator += (data[i] - meanVal) * (data[i] - meanVal);
	};

	return numerator / denominator;
}

double PredictiveModel::movingAverage(std::vector<double>& residuals, int lag)
{
	double meanVal = mean(residuals);
	double numerator = 0;
	double denominator = 0;

	for (size_t i = 0; i < residuals.size()-lag; ++i)
	{
    	numerator += residuals[i] * residuals[i+lag];
	}
	for (size_t i = 0; i < residuals.size(); ++i)
	{
    	denominator += residuals[i] * residuals[i];
	}
	return numerator / denominator;
}

std::vector<double> PredictiveModel::arimax(std::vector<double>& data, std::vector<std::vector<double> >& exog, int forecast)
{
	if (data.size() < 2) 
    {
        throw std::invalid_argument("Insufficient data for ARIMAX model");
	}

	// Differencing to make the data stationary
	std::vector<double> diffData = difference(data);

	// Calculate AR(5) coefficient
	double ar5 = autocorrelation(diffData, 5);

	// Calculate residuals (data - AR part)
	std::vector<double> residuals;
	for (size_t i = 5; i < diffData.size(); ++i) 
    {
    	residuals.push_back(diffData[i] - ar5 * diffData[i - 5]);
	}

	// Calculate MA(5) coefficient (Moving Average)
	double ma5 = movingAverage(residuals,5);

	// Forecast with Exogenous variables
	std::vector<double> forecasts;
	double lastValue = data[data.size()-5]; // Use last original value
	double lastResidual = residuals[residuals.size()-5];
    
	for (int i = 0; i < forecast; ++i) 
    {
    	// Exogenous variable is used for the prediction
        double exogEffect = 0;
        for (size_t j = 0; j < exog[i].size(); ++j) 
        {
        	exogEffect += 0.01 * exog[i][j];  	   	
        }

    	// Forecasting using ARIMAX formula AR + MA + Exogenous Variables
    	double forecastVal = lastValue + ar5 * (lastValue - mean(data)) + ma5 * lastResidual + exogEffect;
        forecasts.push_back(forecastVal);

    	// Update last values
        lastResidual = forecastVal - lastValue;
        lastValue = forecastVal;
	}

	return forecasts;
}
