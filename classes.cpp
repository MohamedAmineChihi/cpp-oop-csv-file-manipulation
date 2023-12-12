#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <typeinfo>

class OriginDest
{
public:
    // Class Constructors
    OriginDest()
    {
        this->origin = origin;
        this->destination = destination;
    }
    OriginDest(std::string origin, std::string destination)
    {
        this->origin = origin;
        this->destination = destination;
    }
    OriginDest(std::string origin, std::string destination, std::set<float> fares)
    {
        this->origin = origin;
        this->destination = destination;
        this->fares = fares;
    }

public:
    // public attributes
    std::string origin;
    std::string destination;

private:
    // private attributes
    std::set<float> fares;

public:
    // fare getter and setter methods
    std::set<float> getFares()
    {
        return fares;
    }

    void setFares(std::set<float> &f)
    {
        this->fares = f;
    }
    // fare calculation methods
    float minFares()
    {
        if (!fares.empty())
        {
            return *(fares.begin());
        }
        return -1;
    }

    float maxFares()
    {
        if (!fares.empty())
        {
            return *(fares.rbegin());
        }
        return -1;
    }

    float avgFares()
    {
        long sum = 0;
        std::set<float>::iterator itr;
        for (itr = fares.begin(); itr != fares.end(); itr++)
        {
            sum += *itr;
        }
        return float(sum) / float(fares.size());
    }
    // exporting data method
    void exportOriginDestLine(std::string filename)
    {
        // create file to write OriginDest data
        std::ofstream file(filename, std::ios::app);
        if (file.is_open())
        {
            // add attributes and baseline fares to the file
            file << origin << "," << destination << "," << minFares() << "," << maxFares() << "," << avgFares() << std::endl;
        }
        file.close();
    }
};

class FlightNbr
{
public:
    // Class Constructors
    FlightNbr(std::string number, OriginDest &od)
    {
        this->number = number;
        this->od = od;
    }

public:
    // Class attributes
    std::string number;
    OriginDest od;
};