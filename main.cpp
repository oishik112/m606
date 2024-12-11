#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

// Data structure to store carbon footprint data
struct CarbonData
{
    std::string country;
    int year;
    double co2_emissions;
    double population;
    double co2_per_capita;
};

// Function to read data from a CSV file
std::vector<CarbonData> readData(const std::string &filename)
{
    std::vector<CarbonData> data;
    std::ifstream file(filename);
    std::string line;

    if (file.is_open())
    {
        // Skip header
        std::getline(file, line);

        while (std::getline(file, line))
        {
            CarbonData entry;
            std::stringstream ss(line);
            std::string temp;

            std::getline(ss, entry.country, ',');
            std::getline(ss, temp, ',');
            entry.year = std::stoi(temp);
            std::getline(ss, temp, ',');
            entry.co2_emissions = std::stod(temp);
            std::getline(ss, temp, ',');
            entry.population = std::stod(temp);
            entry.co2_per_capita = entry.co2_emissions / entry.population;

            data.push_back(entry);
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file." << std::endl;
    }
    return data;
}

// Function to display suggestions for reducing carbon footprint
void displaySuggestions()
{
    std::cout << "\nSuggestions for Reducing Carbon Footprint:\n";
    std::cout << "1. Reduce energy consumption by using energy-efficient appliances.\n";
    std::cout << "2. Shift to renewable energy sources like solar and wind.\n";
    std::cout << "3. Minimize travel-related emissions by using public transport or carpooling.\n";
    std::cout << "4. Plant trees and support reforestation initiatives.\n";
    std::cout << "5. Reduce, Reuse, and Recycle materials to lower waste.\n";
}

// Function to generate a summary report
void generateReport(const std::vector<CarbonData> &data, const std::string &country)
{
    std::ofstream report("Carbon_Footprint_Report.txt");
    if (!report.is_open())
    {
        std::cerr << "Error: Unable to create report file." << std::endl;
        return;
    }

    report << "Carbon Footprint Report for " << country << "\n\n";
    report << std::setw(10) << "Year" << std::setw(20) << "CO2 Emissions (t)"
           << std::setw(20) << "Population" << std::setw(20) << "CO2/Capita (t)" << "\n";

    for (const auto &entry : data)
    {
        if (entry.country == country)
        {
            report << std::setw(10) << entry.year << std::setw(20) << entry.co2_emissions
                   << std::setw(20) << entry.population << std::setw(20) << entry.co2_per_capita << "\n";
        }
    }

    report.close();
    std::cout << "Report generated: Carbon_Footprint_Report.txt\n";
}

int main()
{
    std::string filename = "carbon_data.csv"; // Placeholder for actual dataset file
    std::vector<CarbonData> data = readData(filename);

    if (data.empty())
    {
        std::cerr << "Error: No data loaded. Exiting program." << std::endl;
        return 1;
    }

    std::cout << "Welcome to the Carbon Footprint Monitoring Tool!\n";
    std::string country;
    std::cout << "Enter the country you want to analyze: ";
    std::getline(std::cin, country);

    auto it = std::find_if(data.begin(), data.end(), [&country](const CarbonData &entry)
                           { return entry.country == country; });

    if (it != data.end())
    {
        generateReport(data, country);
        displaySuggestions();
    }
    else
    {
        std::cerr << "Error: Country not found in dataset." << std::endl;
    }

    return 0;
}
