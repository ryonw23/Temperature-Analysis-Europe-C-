#include "Candlestick.h"
#include <string>
#include <vector>
// ** START OF CODE WRITTEN WITHOUT ASSISTANCE **
Candlestick::Candlestick(){}
Candlestick::Candlestick(int _year, double _open, double _high, double _low, double _close)
: year(_year), open(_open), high(_high), low(_low), close(_close){};

int Candlestick::getYear() const { return year;};
double Candlestick::getOpen() const { return open;};
double Candlestick::getHigh() const { return high;};
double Candlestick::getLow() const { return low;};
double Candlestick::getClose() const { return close;};

std::vector<Candlestick> Candlestick::candlestickData;

void Candlestick::addCandlestick(const Candlestick& stick) {candlestickData.push_back(stick);};
std::vector<Candlestick> Candlestick::clearCandlestick() {candlestickData.clear();return candlestickData;};
std::vector<Candlestick> Candlestick::getCandlestick() {return candlestickData;};
// ** END OF CODE WRITTEN WITHOUT ASSISTANCE **