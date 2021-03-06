//
// Created by Filippo Valle on 2019-02-28.
//

#ifndef THESIS_DATA_MINING_GRAPHGENERATOR_H
#define THESIS_DATA_MINING_GRAPHGENERATOR_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/range/adaptor/map.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "BioParameters.h"

using namespace std;
using boost::property_tree::ptree;
typedef float checkable;
typedef pair<string, int64_t> TitleId;
typedef pair<int64_t, checkable> IdCheckable;
typedef pair<uint64_t,pair<string,string>> Weight_WordTitle;
typedef map<string, int64_t> title_index;
typedef vector<Weight_WordTitle> edge_index;
typedef map<string, IdCheckable> dictionary;

class GraphGenerator {
public:
    GraphGenerator(uint64_t maxStorableDocs = 1000,  float maxOccurrence = 0.5, bool weighted = true, bool countPropertyNode = true);
    void MakeGraph();

private:
    void TreeToFile(fstream &graphxmlfile, title_index &titles, dictionary &words, edge_index &edges);
    void VectorsToFile(fstream &graphxmlfile, title_index &titles, dictionary &words, edge_index &edges);

    void addKeyAttrs(ptree &graphml) const;
    void addWordNode(ptree &graph, string name, uint64_t id) const;
    void addDocumentNode(ptree &graph, string title, uint64_t id) const;
    void addEdge(ptree &graph, uint64_t idSource, uint64_t idTarget, uint64_t weight) const;
    std::vector<std::string> tokenize(const std::string &);


    bool fCounts;
    bool fWeighted;
    float fMaxOccurrence;
    uint64_t fMaxStorableDocs;
};


#endif //THESIS_DATA_MINING_GRAPHGENERATOR_H
