#include "MainTable.h"
#include "SamplingModel.h"
#include "GraphGenerator.h"
#include "LabelsReshuffler.h"
#include <boost/timer/timer.hpp>
#include <omp.h>


int main(int argc, const char** argv) // minimal test driver
{
    omp_set_nested(1);
    printf("Running Tool for Analysis of COmponent Systems\n");
#pragma omp parallel
    if(omp_get_thread_num()==0) printf("threads: %d\n", omp_get_num_threads());

    #TelegramWatch watch("thesis");
    boost::timer::auto_cpu_timer();
    
    MainTable* TCGA;
    GraphGenerator* G;

    if(argc < 2){
        cerr<<"Please write some options"<<endl;
        cout<<"0 ---> read mainTable.csv"<<endl;
        cout<<"1 ---> read and extimate correlation mainTable.csv"<<endl;
        cout<<"2 ---> extimate means and variances"<<endl;
        cout<<"3 ---> Do the sampling"<<endl;
        cout<<"4 ---> read nullTable.csv"<<endl;
        cout<<"5 ---> nullTable.csv read and extimate correlation"<<endl;
        cout<<"6 ---> nullTable.csv extimate means and variances"<<endl;
        cout<<"7 ---> read and make bipartite graph"<<endl;
        cout<<"8 ---> shuffle"<<endl;
    }else {
        switch (std::atoi(argv[1])) {
            case 0:
                TCGA = new MainTable();
                TCGA->read("mainTable.csv", true);
                TCGA->~MainTable();
                break;
            case 1:
                TCGA = new MainTable();
                TCGA->read("mainTable.csv", true);
                TCGA->ExtimateCorrelations();
                TCGA->~MainTable();
                break;
            case 2:
                TCGA = new MainTable();
                TCGA->SaveMeansVariances("mainTable.csv", true);
                TCGA->~MainTable();
                break;
            case 3:
                TCGA = new SamplingModel();
                ((SamplingModel *) (TCGA))->GenerateNullData(1);
                TCGA->~MainTable();
                break;
            case 4:
                TCGA = new MainTable();
                TCGA->read("nullTable.csv", true);
                TCGA->~MainTable();
                break;
            case 5:
                TCGA = new MainTable();
                TCGA->read("nullTable.csv", true);
                TCGA->ExtimateCorrelations("correlations_null.dat");
                TCGA->~MainTable();
            case 6:
                TCGA = new MainTable();
                TCGA->SaveMeansVariances("nullTable.csv", true);
                TCGA->~MainTable();
                break;
            case 7:
                G = new GraphGenerator(20000, 1.1 ,true, true);
                G->MakeGraph();
                delete G;
                break;
            case 8:
                LabelsReshuffler::Shuffle();
                break;
            default:
                std::cerr << "missing arguments" << std::endl;
                break;
        }

    }

    return 0;
}
