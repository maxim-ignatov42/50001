#include <cctype>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>
#include "Polygon.h"
#include "Reader.h"
#include "functions.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "ERROR: Filename not provided" << std::endl;
        return 1;
    }

    std::ifstream inFile(argv[1]);
    if (!inFile.is_open()) {
        std::cout << "ERROR: Failed to open file" << std::endl;
        return 1;
    }

    std::vector<Polygon> polygons;
    polygonReader(inFile, polygons);
    inFile.close();
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream cmdStream(line);
        std::string cmd;
        if (!(cmdStream >> cmd)) {
            std::cout << "<INVALID COMMAND>" << std::endl;
            continue;
        }

        std::cout << std::setprecision(1) << std::fixed;

        try {
            if (cmd == "RMECHO") {
                Polygon target;
                if (!(cmdStream >> target)) {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    continue;
                }
                size_t removed = rmecho(polygons, target);
                std::cout << removed << std::endl;
            }

            else if (cmd == "SAME") {
                Polygon target;
                if (!(cmdStream >> target)) {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    continue;
                }
                size_t count = same(polygons, target);
                std::cout << count << std::endl;
            }

            else if (cmd == "AREA") {
                if (!(cmdStream >> cmd)) {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    continue;
                }
                if (cmd == "EVEN") {
                    std::cout << area(polygons, true) << std::endl;
                }
                else if (cmd == "ODD") {
                    std::cout << area(polygons, false) << std::endl;
                }
                else if (cmd == "MEAN") {
                    std::cout << areaMean(polygons) << std::endl;
                }
                else if (std::all_of(cmd.begin(), cmd.end(),
                    [](unsigned char symbol) { return std::isdigit(symbol); })) {
                    std::cout << areaNVertexes(polygons, std::stoull(cmd)) << std::endl;
                }
                else {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                }
            }

            else if (cmd == "MIN") {
                if (!(cmdStream >> cmd)) {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    continue;
                }
                if (cmd == "AREA") {
                    std::cout << minArea(polygons) << std::endl;
                }
                else if (cmd == "VERTEXES") {
                    std::cout << minVertexes(polygons) << std::endl;
                }
                else {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                }
            }

            else if (cmd == "MAX") {
                if (!(cmdStream >> cmd)) {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    continue;
                }
                if (cmd == "AREA") {
                    std::cout << maxArea(polygons) << std::endl;
                }
                else if (cmd == "VERTEXES") {
                    std::cout << maxVertexes(polygons) << std::endl;
                }
                else {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                }
            }

            else if (cmd == "COUNT") {
                if (!(cmdStream >> cmd)) {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    continue;
                }
                if (cmd == "EVEN") {
                    std::cout << countEven(polygons) << std::endl;
                }
                else if (cmd == "ODD") {
                    std::cout << countOdd(polygons) << std::endl;
                }
                else if (std::all_of(cmd.begin(), cmd.end(),
                    [](unsigned char symbol) { return std::isdigit(symbol); })) {
                    std::cout << countNVertexes(polygons, std::stoull(cmd)) << std::endl;
                }
                else {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                }
            }

            else {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
        catch (const std::exception&) {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }
    return 0;
}
