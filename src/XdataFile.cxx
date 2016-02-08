#include "WireCellXdataRoot/XdataFile.h"

#include "TFile.h"
#include "TTree.h"

#include <iostream>
#include <cassert>

using namespace std;
using namespace WireCellXdataRoot;

XdataFile::XdataFile(const std::string& treename)
    : m_treename(treename)
    , m_image(new Image)
    , m_runinfo(new RunInfo)
    , m_geom(new Geom)
{
}

XdataFile::~XdataFile()
{
    delete m_geom; m_geom = 0;
    delete m_runinfo; m_runinfo = 0;
    delete m_image; m_image = 0;
}

RunInfo& XdataFile::runinfo() { return *m_runinfo; }
Geom& XdataFile::geom() { return *m_geom; }
Image& XdataFile::image() { return *m_image; }

size_t XdataFile::read(const std::string& url)
{
    TFile* tfile = TFile::Open(url.c_str(), "READ");
    TTree* tree = dynamic_cast<TTree*>(tfile->Get(m_treename.c_str()));
    if (!tree) {
	string msg = "Unable to get '" + m_treename + "' tree from " + url;
	throw runtime_error(msg.c_str());
    }

    int what = tree->SetBranchAddress("runinfo", &m_runinfo);
    if (what < 0) {
	string msg = "Unable to set branch 'runinfo' in '" + m_treename + "' tree from " + url;
	throw runtime_error(msg.c_str());
    }

    what = tree->SetBranchAddress("geom", &m_geom);
    if (what < 0) {
	string msg = "Unable to set branch 'geom' in '" + m_treename + "' tree from " + url;
	throw runtime_error(msg.c_str());
    }

    what = tree->SetBranchAddress("image", &m_image);
    if (what < 0) {
	string msg = "Unable to set branch 'image' in '" + m_treename + "' tree from " + url;
	throw runtime_error(msg.c_str());
    }

    int nentries = tree->GetEntries();
    //cerr << "Reading " << nentries << " from: " << url << "\n";
    assert(nentries > 0);
    size_t ret = tree->GetEntry(0);

    tfile->Close();
    delete tfile;
    return ret;
}


size_t XdataFile::write(const std::string& filename) {
    TFile* tfile = TFile::Open(filename.c_str(), "RECREATE");
    tfile->cd();

    TTree* tree = new TTree(m_treename.c_str(),
			    "Wire Cell Exchange Data Imaging");

    tree->Branch("runinfo", &m_runinfo);
    tree->Branch("geom", &m_geom);
    tree->Branch("image", &m_image);

    size_t ret = tree->Fill();

    tree->Write("", TObject::kOverwrite);
    //tree->Write();    

    tfile->Close();
    delete tfile;
    return ret;
}

