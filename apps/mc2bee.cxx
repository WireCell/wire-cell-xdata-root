// For now xdata don't have a dedicated class to save particle truth.
// WireCell makes a temporary "TMC" tree that has all particle truth info
// This script convert it to a json format for Bee display
// ./build/mc2bee xdata-root-file bee-json-file

#include <vector>
#include <map>
#include <iomanip>
#include <iostream>
#include <fstream>

#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TDatabasePDG.h"
#include "TNamed.h"
#include "TLorentzVector.h"

using namespace std;

class MCReader {
public:
    TFile *rootFile;
    ofstream jsonFile;

    enum LIMITS {
        MAX_TRACKS = 30000,
    };

    int mc_Ntrack;  // number of tracks in MC
    int mc_id[MAX_TRACKS];  // track id; size == mc_Ntrack
    int mc_pdg[MAX_TRACKS];  // track particle pdg; size == mc_Ntrack
    int mc_process[MAX_TRACKS];  // track generation process code; size == mc_Ntrack
    int mc_mother[MAX_TRACKS];  // mother id of this track; size == mc_Ntrack
    float mc_startXYZT[MAX_TRACKS][4];  // start position of this track; size == mc_Ntrack
    float mc_endXYZT[MAX_TRACKS][4];  // end position of this track; size == mc_Ntrack
    float mc_startMomentum[MAX_TRACKS][4];  // start momentum of this track; size == mc_Ntrack
    float mc_endMomentum[MAX_TRACKS][4];  // end momentum of this track; size == mc_Ntrack
    vector<vector<int> > *mc_daughters;  // daughters id of this track; vector

    // ----- derived ---
    map<int, int> trackIndex;
    vector<vector<int> > trackParents;
    vector<vector<int> > trackChildren;
    vector<vector<int> > trackSiblings;
    TDatabasePDG *dbPDG;

    //-------------------------------------
    MCReader();
    MCReader(const char* filename, const char* jsonFileName="mc.json");
    virtual ~MCReader();

    void DumpMC();

    void print_vector(ostream& out, vector<double>& v, TString desc, bool end=false);

    bool IsPrimary(int i) { return mc_mother[i] == 0 ; }
    void ProcessTracks();
    double KE(float* momentum);  // KE
    TString PDGName(int pdg);
    double thresh_KE;
    bool KeepMC(int i);

    bool DumpMCJSON(int id, ostream& out);
    void DumpMCJSON(ostream& out = cout);
};

//----------------------------------------------------------------
MCReader::MCReader(){}

//----------------------------------------------------------------
MCReader::MCReader(const char* filename, const char* jsonFileName)
{
    dbPDG = new TDatabasePDG();
    mc_daughters = new vector<vector<int> >;  // daughters id of this track; vector
    thresh_KE = 1; // MeV

    rootFile = new TFile(filename);

    jsonFile.open(jsonFileName);
}

//----------------------------------------------------------------
MCReader::~MCReader()
{
    jsonFile.close();

    delete mc_daughters;

    rootFile->Close();
    delete rootFile;
}

//----------------------------------------------------------------
void MCReader::DumpMC()
{
    TTree *t = (TTree*)rootFile->Get("TMC");

    if (t) {
        t->SetBranchAddress("mc_Ntrack"       , &mc_Ntrack);
        t->SetBranchAddress("mc_id"           , &mc_id);
        t->SetBranchAddress("mc_pdg"          , &mc_pdg);
        t->SetBranchAddress("mc_process"      , &mc_process);
        t->SetBranchAddress("mc_mother"       , &mc_mother);
        t->SetBranchAddress("mc_daughters"    , &mc_daughters);
        t->SetBranchAddress("mc_startXYZT"    , &mc_startXYZT);
        t->SetBranchAddress("mc_endXYZT"      , &mc_endXYZT);
        t->SetBranchAddress("mc_startMomentum", &mc_startMomentum);
        t->SetBranchAddress("mc_endMomentum"  , &mc_endMomentum);

        t->GetEntry(0);
        ProcessTracks();
        DumpMCJSON(jsonFile);
    }
}

//----------------------------------------------------------------
void MCReader::ProcessTracks()
{
    // map track id to track index in the array
    for (int i=0; i<mc_Ntrack; i++) {
        trackIndex[mc_id[i]] = i;
    }

    // in trackParents, trackChildren, trackSiblings vectors, store track index (not track id)
    for (int i=0; i<mc_Ntrack; i++) {
        // currently, parent size == 1;
        // for primary particle, parent id = 0;
        vector<int> parents;
        if ( !IsPrimary(i) ) {
            parents.push_back(trackIndex[mc_mother[i]]);
        }
        trackParents.push_back(parents); // primary track will have 0 parents

        vector<int> children;
        int nChildren = (*mc_daughters).at(i).size();
        for (int j=0; j<nChildren; j++) {
            children.push_back(trackIndex[(*mc_daughters).at(i).at(j)]);
        }
        trackChildren.push_back(children);

    }

    // siblings
    for (int i=0; i<mc_Ntrack; i++) {
        vector<int> siblings;
        if ( IsPrimary(i) ) {
            for (int j=0; j<mc_Ntrack; j++) {
                if( IsPrimary(j) ) {
                    siblings.push_back(j);
                }
            }
        }
        else {
            // siblings are simply children of the mother
            int mother = trackIndex[mc_mother[i]];
            int nSiblings = trackChildren.at(mother).size();
            for (int j=0; j<nSiblings; j++) {
                siblings.push_back(trackChildren.at(mother).at(j));
            }
        }
        trackSiblings.push_back(siblings);
    }

}

//----------------------------------------------------------------
bool MCReader::DumpMCJSON(int id, ostream& out)
{
    int i = trackIndex[id];
    if (!KeepMC(i)) return false;

    int e = KE(mc_startMomentum[i])*1000;

    int nDaughter = (*mc_daughters).at(i).size();
    vector<int> saved_daughters;
    for (int j=0; j<nDaughter; j++) {
        int daughter_id = (*mc_daughters).at(i).at(j);
        // int e_daughter = KE(mc_startMomentum[ trackIndex[daughter_id] ])*1000;
        // if (e_daughter >= thresh_KE) {
        if ( KeepMC(trackIndex[daughter_id]) ) {
            saved_daughters.push_back(daughter_id);
        }
    }

    out << fixed << setprecision(1);
    out << "{";

    out << "\"id\":" << id << ",";
    out << "\"text\":" << "\"" << PDGName(mc_pdg[i]) << "  " << e << " MeV\",";
    out << "\"data\":{";
    out << "\"start\":[" << mc_startXYZT[i][0] << ", " <<  mc_startXYZT[i][1] << ", " << mc_startXYZT[i][2] << "],";
    out << "\"end\":[" << mc_endXYZT[i][0] << ", " <<  mc_endXYZT[i][1] << ", " << mc_endXYZT[i][2] << "]";
    out << "},";
    out << "\"children\":[";
    int nSavedDaughter = saved_daughters.size();
    if (nSavedDaughter == 0) {
        out << "],";
        out << "\"icon\":" << "\"jstree-file\"";
        out << "}";
        return true;
    }
    else {
        for (int j=0; j<nSavedDaughter; j++) {
            DumpMCJSON(saved_daughters.at(j), out);
            if (j!=nSavedDaughter-1) {
                out << ",";
            }
        }
        out << "]";
        out << "}";
        return true;
    }
}

//----------------------------------------------------------------
void MCReader::DumpMCJSON(ostream& out)
{
    out << "[";
    vector<int> primaries;
    for (int i=0; i<mc_Ntrack; i++) {
        if (IsPrimary(i)) {
            // int e = KE(mc_startMomentum[i])*1000;
            // if (e<thresh_KE) continue;
            if (KeepMC(i)) {
                primaries.push_back(i);
            }
        }
    }
    int size = primaries.size();
    // cout << size << endl;
    for (int i=0; i<size; i++) {
        if (DumpMCJSON(mc_id[primaries[i]], out) && i!=size-1) {
            out << ", ";
        }
    }

    out << "]\n";
}

//----------------------------------------------------------------
bool MCReader::KeepMC(int i)
{
    double e = KE(mc_startMomentum[i])*1000;
    double thresh_KE_em = 5.; // MeV
    double thresh_KE_np = 10; // MeV
    if (mc_pdg[i]==22 || mc_pdg[i]==11 || mc_pdg[i]==-11) {
        if (e>=thresh_KE_em) return true;
        else return false;
    }
    else if (mc_pdg[i]==2112 || mc_pdg[i]==2212 || mc_pdg[i]>1e9) {
        if (e>=thresh_KE_np) return true;
        else return false;
    }
    return true;
}

//----------------------------------------------------------------
double MCReader::KE(float* momentum)
{
    TLorentzVector particle(momentum);
    return particle.E()-particle.M();
}

//----------------------------------------------------------------
TString MCReader::PDGName(int pdg)
{
    TParticlePDG *p = dbPDG->GetParticle(pdg);
    if (p == 0) {
        if (pdg>1e9) {
            int z = (pdg - 1e9) / 10000;
            int a = (pdg - 1e9 - z*1e4) / 10;
            TString name;
            if (z == 18) name = "Ar";
            else if (z == 17) name = "Cl";
            else if (z == 19) name = "Ca";
            else if (z == 16) name = "S";
            else if (z == 15) name = "P";
            else if (z == 14) name = "Si";
            else if (z == 1) name = "H";
            else if (z == 2) name = "He";
            else name = "Unknown";
            return Form("%s-%i", name.Data(), a);
        }
        else {
            return Form("%s-%i", "PDG", pdg);;
        }
    }
    else {
        return p->GetName();
    }
}

int main(int argc, char* argv[])
{
    // gInterpreter->EnableAutoLoading();

    TString rootFileName = argv[1];
    TString jsonFileName = argv[2];

    // cout << rootFileName <<  ", " << jsonFileName << endl;

    MCReader r(rootFileName, jsonFileName);
    r.DumpMC();

}