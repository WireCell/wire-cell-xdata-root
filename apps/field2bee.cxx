// convert xdata "field" points to json format for Bee display
// ./build/field2bee xdata-root-file bee-json-file reco-name
// reco-name must be one of [truth, rec_simple, rec_charge_blob]

#include "WireCellXdataRoot/Reader.h"
#include "WireCellXdataRoot/CloneHelper.h"

#include "TString.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;
using namespace WireCellXdataRoot;

void print_vector(ostream& out, vector<float>& v, TString desc, bool end=false)
{
    int N = v.size();

    out << '"' << desc << '"' << ":[";
    for (int i=0; i<N; i++) {
        out << v[i];
        if (i!=N-1) {
            out << ",";
        }
    }
    out << "]";
    if (!end) out << ",";
    out << endl;
}

void dump_runinfo(ofstream& jsonFile, Reader& xreader)
{
    jsonFile << fixed << setprecision(0);
    while (xreader.runinfo_reader.Next()) {
        RunInfo& r = *xreader.runinfo;
        jsonFile << '"' << "runNo" << '"' << ":" << '"' << (r.ident>>32) << '"' << "," << endl;
        jsonFile << '"' << "subRunNo" << '"' << ":" << '"' << (0xffffffff&r.ident) << '"' << "," << endl;
    }

    while (xreader.trigger_reader.Next()) {
        Trigger& t = *xreader.trigger;
        jsonFile << '"' << "eventNo" << '"' << ":" << '"' << t.ident << '"' << "," << endl;
    }

    while (xreader.geom_reader.Next()) {
        Geom& g = *xreader.geom;
        jsonFile << '"' << "geom" << '"' << ":" << '"' << g.description << '"' << endl;
    }
}

void dump_3dpoints(ofstream& jsonFile, Reader& xreader, TString name)
{
    // Field: 1 true charge deposition
    // Field: 2 no charge image
    // Field: 3 charge image
    map<string, int> nameMap;
    nameMap["truth"] = 1;
    nameMap["rec_simple"] = 2;
    nameMap["rec_charge_blob"] = 3;

    vector<float> vx, vy, vz, vq;

    while (xreader.field_reader.Next()) {
        Field& f = *xreader.field;
        if (f.ident == nameMap[name.Data()]) {
            CloneHelper<FieldPoint> fieldca(*f.points);
            // cerr << "retreving: Field: " << f.ident << " (" << f.name << ") trig=" << f.trigid << " geom=" << f.geomid
            //     << " #points=" << fieldca.size() << endl;
            int nPoints = fieldca.size();
            for (int i=0; i<nPoints; i++) {
                FieldPoint *fp = fieldca.get(i);
                vx.push_back(fp->point.x);
                vy.push_back(fp->point.y);
                vz.push_back(fp->point.z);
                if (fp->values.size()>0) {
                    vq.push_back(fp->values.at(0));  // q
                }
            }
            break;
        }
    }

    jsonFile << fixed << setprecision(1);
    print_vector(jsonFile, vx, "x");
    print_vector(jsonFile, vy, "y");
    print_vector(jsonFile, vz, "z");

    if (vq.size()>0) {
        jsonFile << fixed << setprecision(0);
        print_vector(jsonFile, vq, "q");
    }

    jsonFile << '"' << "type" << '"' << ":" << '"' << name << '"' << "," << endl;
}

int main(int argc, char* argv[])
{
    TString rootFileName = argv[1];
    TString jsonFileName = argv[2];
    TString name = argv[3];

    ofstream jsonFile(jsonFileName);

    Reader xreader(rootFileName.Data());

    jsonFile << "{" << endl;

    dump_3dpoints(jsonFile, xreader, name);
    dump_runinfo(jsonFile, xreader);

    jsonFile << "}" << endl;

}
