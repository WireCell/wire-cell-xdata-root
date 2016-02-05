#include "WireCellXdataRoot/XdataFile.h"

#include "TFile.h"
#include "TTree.h"

#include <iostream>

using namespace std;
using namespace WireCellXdataRoot;

XdataFile::XdataFile(const std::string& url,
		     const std::string& mode)
    : m_tfile(0)
    , m_frame(0)
    , m_ri(0)
    , m_ws(0)
{
    if (mode[0] == 'r') {
	//...
    }
    else {
	m_tfile = TFile::Open(url.c_str(), "RECREATE");
    }
}

XdataFile::~XdataFile()
{
    m_tfile->Write("image");
    m_tfile->Close();
    delete m_tfile;
    m_tfile = nullptr;
}

std::size_t XdataFile::write(const RunInfo& ri)
{
    TTree* tree = dynamic_cast<TTree*>(m_tfile->Get("run"));
    if (!tree) {
	tree = new TTree("run", "Wire Cell Exchange Data RunInfo");
	//tree->SetDirectory(m_tfile); // needed if multiple files open?
	tree->Branch("info", &m_ri);
    }
    (*m_ri) = ri;
    auto siz = tree->Fill();
    //tree->Write("", TObject::kOverwrite);
    return siz;
}

std::size_t XdataFile::write(const WireSet& ws)
{
    TTree* tree = dynamic_cast<TTree*>(m_tfile->Get("geom"));
    if (!tree) {
	tree = new TTree("geom", "Wire Cell Exchange Data Geometry");
	//tree->SetDirectory(m_tfile); // needed if multiple files open?
	tree->Branch("wireset", &m_ws);
    }
    (*m_ws) = ws;
    auto siz = tree->Fill();
    //tree->Write("", TObject::kOverwrite);
    return siz;
}

std::size_t XdataFile::append(const Frame& frame)
{
    TTree* tree = dynamic_cast<TTree*>(m_tfile->Get("image"));
    if (!tree) {
	tree = new TTree("image", "Wire Cell Exchange Data Imaging");
	//tree->SetDirectory(m_tfile); // needed if multiple files open?
	tree->Branch("frame", &m_frame);
    }
    auto entry = tree->GetEntries();
    (*m_frame) = frame;
    tree->Fill();
    return entry;
}
