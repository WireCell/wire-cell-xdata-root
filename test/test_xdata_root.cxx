#include "WireCellXdataRoot/XdataFile.h"
#include "WireCellXdataRoot/Lookup.h"

#include <string>
#include <iostream>
#include <cassert>
#include <map>

using namespace std;
using namespace WireCellXdataRoot;

void test_write(const std::string& filename)
{
    XdataFile out;
	
    RunInfo& ri = out.runinfo();
    ri.detector = "bogusdet";
    ri.ident = 42;

    Geom& geom = out.geom();
    for (int plane = 1; plane <=3; ++plane) {
	for (int ind = 0; ind<100; ++ind) {
	    Wire* wire = new Wire;
	    wire->chanid = wire->wireid = plane*1000+ind+1;
	    wire->volid=1;
	    wire->plane=plane;
	    wire->offset=ind;
	    wire->segment=0;
	    //wire->point1 = ...;
	    //wire->point2 = ...;
	    geom.wires.push_back(wire);
	}
    }
    cerr << "Number of wires: " << geom.wires.size() << endl;

    Image& img = out.image();
    int blobind = -1;
    Blob* allcells = img.new_blob(blobind);
    allcells->ident = 42;
    allcells->slice = 99;
    /// fill up some bogus cells
    map<int,int> cell_id2ind;
    for (int uind = 0; uind<10; ++uind) {
	for (int vind = 0; vind<10; ++vind) {
	    for (int wind = 0; wind<10; ++wind) {
		//img.cells.push_back(new Cell(uind*10000 + vind*100 + wind,uind,vind,wind));
		int ident = uind*10000 + vind*100 + wind;
		int ind = -1;
		Cell* cell = img.new_cell(ind);
		cell->ident = ident;
		cell->uind = uind;
		cell->vind = vind;
		cell->wind = wind;
		cell_id2ind[ident] = ind;
		allcells->cellind.push_back(ind);
	    }
	}
    }

    cerr << "Writing " << filename << endl;
    out.write(filename);
    assert(out.geom().wires.size() == 300);
}

void test_read(const std::string& filename)
{

    XdataFile in;
    cerr << "Reading back " << filename << endl;
    in.read(filename);

    assert(in.runinfo().detector != "");
    assert(in.runinfo().ident == 42);
    assert(in.geom().wires.size() == 300);

    auto &geom = in.geom();
    auto &img = in.image();

    Lookup lu(geom, img);

    int nblobs = img.num_blobs();
    cerr << nblobs << " blobs:\n";
    for (int iblob=0; iblob<nblobs; ++iblob) {
	auto blob = img.get_blob(iblob);
	cerr << "\tblob id:" << blob->ident << " @ " << blob->slice
	     << " [";
	string comma = "";
	for (auto v : blob->values) {
	    cerr << comma << v;
	    comma = ", ";
	}
	cerr << "] " << blob->cellind.size() << " cells:\n";
	for (auto cell : lu(blob)) {
	    cerr <<"\t\tcell id:" << cell->ident << " A=" << cell->area
		 << " @ "
		 << cell->center.x << " "
		 << cell->center.y << " "
		 << cell->center.z << " wires:\n";
	    for (auto wire : lu(cell)) {
	    	cerr << "\t\t\twire id: " << wire->wireid
	    	     << " plane=" << (int) wire->plane
	    	     << " chan=" << wire->chanid
	    	     << " vol=" << wire->volid << "\n";
	    }
	}
    }


}
int main()
{

    const string filename = "test_xdata.root";
    test_write(filename);
    test_read(filename);

    return 0;
}
