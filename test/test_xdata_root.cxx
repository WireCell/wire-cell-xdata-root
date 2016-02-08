#include "WireCellXdataRoot/XdataFile.h"

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
    ri.ident = 0;

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
    /// fill up some bogus cells
    map<int,int> cell_id2ind;
    for (int uind = 0; uind<100; ++uind) {
	for (int vind = 0; vind<100; ++vind) {
	    for (int wind = 0; wind<100; ++wind) {
		//img.cells.push_back(new Cell(uind*10000 + vind*100 + wind,uind,vind,wind));
		int ident = uind*10000 + vind*100 + wind;
		int ind = -1;
		Cell* cell = img.new_cell(ind);
		cell->ident = ident;
		cell->uind = uind;
		cell->vind = vind;
		cell->wind = wind;
		cell_id2ind[ident] = ind;
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
    assert(in.geom().wires.size() == 300);

}
int main()
{

    const string filename = "test_xdata.root";
    test_write(filename);
    test_read(filename);

    return 0;
}
