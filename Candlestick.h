#pragma once

#include <string>   
#include <vector>
// ** START OF CODE WRITTEN WITHOUT ASSISTANCE **
class Candlestick{
    public:
        Candlestick();
        Candlestick(int _year, double _open, double _high, double _low, double _close);
        int getYear() const;
        double getOpen() const;
        double getHigh() const;
        double getLow() const;
        double getClose() const;
        static void addCandlestick(const Candlestick& stick);
        static std::vector<Candlestick> getCandlestick();
        static std::vector<Candlestick> clearCandlestick();
    private:
        int year;
        double open;
        double high;
        double low;
        double close;
        static std::vector<Candlestick> candlestickData;
};
// ** END OF CODE WRITTEN WITHOUT ASSISTANCE **