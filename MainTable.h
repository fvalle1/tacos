//
// Created by Filippo Valle on 2019-01-08.
//

#ifndef THESIS_DATA_MINING_MAINTABLE_H
#define THESIS_DATA_MINING_MAINTABLE_H


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <boost/tokenizer.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include "RandomGen.h"
#include "BioParameters.h"

using namespace std;
typedef bool correlated;
typedef bool* matrix;


class MainTable {
public:
    MainTable();

    ~MainTable();

    void read(const char *tableFilename, bool saveAbundancesOccurrences);
    void readBinary();

    void SaveMeansVariances(const char *filename, bool considerZeros = false);
    void SaveBinary(const char *filename = "binaryTable.csv");
    void ExtimateCorrelations(const char *filename = "correlations.dat");

    uint64_t get(uint64_t component, uint64_t realisation) {
        if (component < fNComponents && realisation < fNRealizations)
            return fData[fNRealizations * component + realisation] ? 1 : 0;
        else return 0;
    };

    std::vector<std::string> tokenize(const std::string &);

protected:
    uint64_t fNComponents;
    uint64_t fNRealizations;
    matrix fData;

    void SaveTotalArray(const char *filename, const double *X, uint64_t length);
    void SaveHeapsData(const double *VocabularySize);
    void ExtimateHXY(const char *filename);

    static const std::pair<double, double> fThreshold;

private:
    double GetEntropy(uint64_t l, double *X, uint64_t component = 1000000);
    double SumEntropy(uint64_t l, double *X);

};

#endif //THESIS_DATA_MINING_MAINTABLE_H
