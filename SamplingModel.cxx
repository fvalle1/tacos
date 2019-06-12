//
// Created by Filippo Valle on 2019-01-16.
//

#include "SamplingModel.h"

void SamplingModel::GenerateNullData(int maxStatistic) {
    cout << "Generating null model averaging over "<<maxStatistic << endl;
    fstream occ("A.dat", ios_base::in);
    fstream voc("vocabulary_size.dat", std::ios::in);

    if(occ.is_open()&&voc.is_open()) {
        double o;
        std::vector<uint64_t> probabilities;
        probabilities.reserve(fNComponents);
        uint64_t actualComponents = 0;
        while(occ>>o){
            probabilities.push_back(static_cast<uint64_t>(o));
            actualComponents++;
        }
        occ.close();
        fNComponents = actualComponents;
        cout<<"loaded occurences.."<<endl;

        // Make a random number engine
        auto rng = RandomGen::Instance();

        // Choose a random multinomial
        boost::random::discrete_distribution<uint64_t> distr(probabilities);

        probabilities.clear(); //a copy is stored in boost::ranodm::dicrete_distribution
        delete[] fData; //just to free some RAM I'll reallocate in the future

        auto nullData = new uint64_t[fNRealizations*fNComponents];
        for(uint64_t i = 0; i < fNComponents*fNRealizations; i++) nullData[i]=0;

        double M;
        uint64_t effectivelyLoadedRealization = 0;
        auto counts = new uint64_t[fNComponents];
        for(uint64_t i = 0; i < fNComponents; i++) counts[i]=0;

        cout<<"generating data.."<<endl;
        //for realization
        while (voc >> M) {
            for(int statistics = 0; statistics < maxStatistic; statistics++)
                for(uint64_t word = 0; word < M; word++) counts[distr(rng)]++;
            printf("\r%llu/%llu",effectivelyLoadedRealization,fNRealizations);

            for(uint64_t component = 0; component < fNComponents; component++) {
                nullData[fNRealizations * component + effectivelyLoadedRealization] = static_cast<uint64_t>(counts[component]/maxStatistic);
            }

            for(uint64_t i = 0; i < fNComponents; i++) counts[i]=0;
            effectivelyLoadedRealization++;
        }
        delete[] counts;
        voc.close();

        cout<<endl<<"saving file.."<<endl;
        fstream file("nullTable.csv", std::ios::out);
        file<<endl; //mime header line
        for(uint64_t component = 0; component < fNComponents; component++) {
            file<<","; //mime index column
            printf("\r%llu/%llu", component+1, fNComponents);
            for (uint64_t realization = 0; realization < fNRealizations; realization++) {
                file << nullData[fNRealizations * component + realization];
                if(realization < effectivelyLoadedRealization - 1) file << ",";
                else break;
            }
            file<<"\n";
        }

        delete[] nullData;

        file.close();

        cout << endl;

        fData = new correlated[fNRealizations*fNComponents];
    }else{
        cerr<<"Error reading files"<<endl;
    }
}

void SamplingModel::GenerateNullBinary() const {
    cout << "Generating null model binary" << endl;
    fstream occ("O.dat", ios_base::in);

    if (!occ.is_open()) {
        cerr << "File not found" << endl;
    } else {

        double o;
        uint64_t idata = 0;

        // Make a random number engine
        auto rng = RandomGen::Instance();

        // Choose a random mean between 0 and 1
        boost::random::uniform_01<double> uniform_dist;

        while (occ >> o) {
            for (int realization = 0; realization < fNRealizations; ++realization) {
                if (idata % 100000 == 0) printf("\r%llu/%llu", idata, fNRealizations * fNComponents);
                bool point = uniform_dist(rng) < o;
                fData[idata++] = point;
            }
        }

        occ.close();
        cout << endl;
    }
}
