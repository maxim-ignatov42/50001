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
        std::cerr << "ERROR: Filename not provided" << std::endl;
        return 1;
    }

    std::ifstream inFile(argv[1]);
    if (!inFile.is_open()) {
        std::cerr << "ERROR: Failed to open file" << std::endl;
        return 1;
    }

    std::vector<Polygon> polygons;
    polygonReader(inFile, polygons);
    inFile.close();
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream cmdStream(line);
        std::string cmd;
        cmdStream >> cmd;

        try {
            if (cmd == "RMECHO") {
                Polygon target;
                if (!(cmdStream >> target)) {
                    std::cerr << "<INVALID COMMAND>" << std::endl;
                }
                size_t removed = rmecho(polygons, target);
                std::cout << removed << std::endl;
            }

            else if (cmd == "SAME") {
                Polygon target;
                if (!(cmdStream >> target)) {
                    std::cerr << "<INVALID COMMAND>" << std::endl;
                }
                size_t count = same(polygons, target);
                std::cout << count << std::endl;
            }

            else if (cmd == "AREA") {
                if (!(cmdStream >> cmd)) {
                    std::cerr << "<INVALID COMMAND>" << std::endl;
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
                else if (std::all_of(cmd.begin(), cmd.end(), std::isdigit)) {
                    std::cout << area(polygons, std::stoull(cmd)) << std::endl;
                }
                else {
                    std::cerr << "<INVALID COMMAND>" << std::endl;
                }
            }

            else if (cmd == "MIN") {
                if (!(cmdStream >> cmd)) {
                    std::cerr << "<INVALID COMMAND>" << std::endl;
                }
                if (cmd == "AREA") {
                    std::cout << minArea(polygons) << std::endl;
                }
                else if (cmd == "VERTEXES") {
                    std::cout << minVertexes(polygons) << std::endl;
                }
                else {
                    std::cerr << "<INVALID COMMAND>" << std::endl;
                }
            }

            else if (cmd == "MAX") {
                if (!(cmdStream >> cmd)) {
                    std::cerr << "<INVALID COMMAND>" << std::endl;
                }
                if (cmd == "AREA") {
                    std::cout << maxArea(polygons) << std::endl;
                }
                else if (cmd == "VERTEXES") {
                    std::cout << maxVertexes(polygons) << std::endl;
                }
                else {
                    std::cerr << "<INVALID COMMAND>" << std::endl;
                }
            }

            else if (cmd == "AREA") {
                if (!(cmdStream >> cmd)) {
                    std::cerr << "<INVALID COMMAND>" << std::endl;
                }
                if (cmd == "EVEN") {
                    std::cout << countEven(polygons) << std::endl;
                }
                else if (cmd == "ODD") {
                    std::cout << countOdd(polygons) << std::endl;
                }
                else if (std::all_of(cmd.begin(), cmd.end(), std::isdigit)) {
                    std::cout << countNVertexes(polygons, std::stoull(cmd)) << std::endl;
                }
                else {
                    std::cerr << "<INVALID COMMAND>" << std::endl;
                }
            }

            else {
                std::cerr << "<INVALID COMMAND>" << std::endl;
            }
        }
        catch (const std::exception&) {
            std::cerr << "<INVALID COMMAND>" << std::endl;
        }
    }
    return 0;
}
