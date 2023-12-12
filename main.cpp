#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include "classes.cpp"

std::vector<OriginDest> read_csv(std::string filename)
{
    std::vector<OriginDest> od_objects;
    std::set<float> fares;
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        getline(file, line);
        while (getline(file, line))
        {
            std::stringstream ss(line);
            std::string origin, destination, f;
            std::getline(ss, origin, ';');
            std::getline(ss, destination, ';');
            od_objects.push_back(OriginDest(origin, destination));
            std::getline(ss, f, '\n');
            fares.insert(std::stof(f));
        }
        file.close();
    }
    std::vector<OriginDest>::iterator itr;
    for (itr = od_objects.begin(); itr != od_objects.end(); itr++)
    {
        itr->setFares(fares);
    }
    return od_objects;
};

// export OriginDest function
void exportOriginDestAll(std::vector<OriginDest> od_objects, std::string filename)
{
    //  create an iterator to go through OriginDest elements
    //  and call exportOriginDestLine for each element
    std::vector<OriginDest>::iterator itr;
    for (itr = od_objects.begin(); itr != od_objects.end(); itr++)
    {
        itr->exportOriginDestLine(filename);
    }
}
// export FlightNbr data function
void exportFlightOriginDestLine(FlightNbr fn, std::string filename)
{
    // create file to write FlightNbr data
    std::ofstream file(filename, std::ios::app);
    if (file.is_open())
    {
        // add flight number
        file << fn.number << ",";
    }
    file.close();
    // call ObjectDest export method
    fn.od.exportOriginDestLine(filename);
}

// instanciate our objects and test our methods and functions
int main()
{
    // instanciate a new OriginDest object
    std::vector<OriginDest> od_test;
    // read the dataset and ingest it into the OriginDest Object
    od_test = read_csv("OrigineDestinationTarif.csv");
    // export some random rows from our dataset
    od_test[0].exportOriginDestLine("test.csv");
    od_test[16].exportOriginDestLine("test.csv");
    // export the modified dataset with the extra columns
    exportOriginDestAll(od_test, "test_all.csv");
    // instanciate a new FlightNbr
    FlightNbr fn = FlightNbr("515", od_test[0]);
    // export the row created from the FlightNbr object
    exportFlightOriginDestLine(fn, "test_flight.csv");
}