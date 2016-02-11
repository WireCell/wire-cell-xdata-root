#include "WireCellXdataRoot/Writer.h"
#include "WireCellXdataRoot/Reader.h"
#include "WireCellXdataRoot/CloneHelper.h"
#include "WireCellXdataRoot/WireDB.h"

#include <string>
#include <iostream>
#include <cassert>
#include <map>

using namespace std;
using namespace WireCellXdataRoot;

void test_write(const std::string& filename)
{
    Writer xwriter(filename.c_str());
	
    Geom& geom = xwriter.geom.obj();
    CloneHelper<Wire> wireca(*geom.wires);
    CloneHelper<Cell> cellca(*geom.cells);

    geom.ident=42;
    geom.description = "bogus detector from test_xdata_root";

    std::vector<Wire*> uvw_wires[3];
    int uvw_nwires[3] = {200,100,100};

    for (int iplane = 0; iplane < 3; ++iplane) {
	for (int ind = 0; ind<uvw_nwires[iplane]; ++ind) {
	    Wire* wire = wireca.make();
	    wire->chanid = wire->ident = (iplane+1)*1000+ind+1; // make up some convention
	    wire->apaid=1;
	    wire->plane=iplane;
	    wire->offset=ind;
	    wire->segment=0;
	    //wire->point1 = ...;
	    //wire->point2 = ...;

	    // cache by plane
	    uvw_wires[iplane].push_back(wire);
	}
    }
    cerr << "Number of wires: " << wireca.size() << endl;

    map<int,int> cell_id2ind;
    for (auto uwire : uvw_wires[0]) {
	for (auto vwire : uvw_wires[1]) {
	    for (auto wwire : uvw_wires[2]) {
		Cell* cell = cellca.make();
		cell->set(uwire->ident, vwire->ident, wwire->ident);
		// cell->area=...;
		// cell->center=...;
	    }
	}
    }
    cerr << "Number of cells: " << cellca.size() << endl;

    xwriter.geom.fill();

    RunInfo& ri = xwriter.runinfo.obj();
    ri.ident = 42;
    xwriter.runinfo.fill();

    // writer closes as it leaves scope and destructs>
}

void test_read(const std::string& url)
{
    // TFile* file = TFile::Open(url.c_str());
    // assert(file);
    // TTree* tree = dynamic_cast<TTree*>(file->Get("geom"));
    // assert(tree);
    // Geom* geom = new Geom;
    // tree->SetBranchAddress("geom",&geom);
    // tree->GetEntry(0);
    // assert(geom->ident=42);
    

    Reader xreader(url);
    cerr << "Reading back " << url << endl;

    while (xreader.runinfo_reader.Next()) {
	RunInfo& ri = *xreader.runinfo;
	cerr << "Run: " << ri.ident << endl;
    }
    WireDB wdb;
    while (xreader.geom_reader.Next()) {
	Geom& g = *xreader.geom;
	assert (g.ident == 42);
	CloneHelper<Wire> wireca(*g.wires);
	CloneHelper<Cell> cellca(*g.cells);
	cerr << "Geom: " << g.ident << " " << g.description
	     << " #wires=" << wireca.size() << " #cells=" << cellca.size()
	     << endl;
	for (int ind=0; ind < wireca.size(); ++ind) {
	    wdb(wireca.get(ind));
	}
    }
    const Wire* wire1001 = wdb.by_chan(1001);
    assert(wire1001->chanid == 1001);
    assert(wire1001 = wdb.by_id(1001)); // test bogus chan convention used above
    assert(wire1001->ident == 1001);
    

    while (xreader.trigger_reader.Next()) {
	Trigger& t = *xreader.trigger;
	cerr << "Trigger: " << t.ident << " type=" << t.type << " run=" << t.runid
	     << " @ " << t.second << "s and " << t.nanosecond << "ns" <<endl;
    }
    while (xreader.frame_reader.Next()) {
	Frame& f = *xreader.frame;
	CloneHelper<Deco> decoca(*f.decos);
	cerr << "Frame: " << f.ident << " trig=" << f.trigid << " geom=" << f.geomid
	     << " #decos=" << decoca.size() << endl;
    }
    while (xreader.image_reader.Next()) {
	Image& img = *xreader.image;
	CloneHelper<Blob> blobca(*img.blobs);
	cerr << "Image: " << img.ident << " frame=" << img.frameid
	     << " #blobs=" << blobca.size() << endl;;
    }
    while (xreader.field_reader.Next()) {
	Field& f = *xreader.field;
	CloneHelper<FieldPoint> fieldca(*f.points);
	cerr << "Field: " << f.ident << " " << f.name << " trig=" << f.trigid << " geom=" << f.geomid
	     << " #points=" << fieldca.size() << endl;
    }
    

}

int main()
{

    const string filename = "test_xdata.root";
    test_write(filename);
    test_read(filename);

    return 0;
}
