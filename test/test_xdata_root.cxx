#include "WireCellXdataRoot/Writer.h"
#include "WireCellXdataRoot/CloneHelper.h"
#include "WireCellXdataRoot/Wire.h"
#include "WireCellXdataRoot/Cell.h"
#include "WireCellXdataRoot/RunInfo.h"

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

    geom.ident=1;
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
    ri.geomid = geom.ident;
    xwriter.runinfo.fill();

    // writer closes as it leaves scope and destructs>
}

// void test_read(const std::string& filename)
// {

//     XdataFile in;
//     cerr << "Reading back " << filename << endl;
//     in.read(filename);

//     assert(in.runinfo().detector != "");
//     assert(in.runinfo().ident == 42);
//     assert(in.geom().wires.size() == 300);

//     auto &geom = in.geom();
//     auto &img = in.image();

//     Lookup lu(geom, img);

//     int nblobs = img.num_blobs();
//     cerr << nblobs << " blobs:\n";
//     for (int iblob=0; iblob<nblobs; ++iblob) {
// 	auto blob = img.get_blob(iblob);
// 	cerr << "\tblob id:" << blob->ident << " @ " << blob->slice
// 	     << " [";
// 	string comma = "";
// 	for (auto v : blob->values) {
// 	    cerr << comma << v;
// 	    comma = ", ";
// 	}
// 	cerr << "] " << blob->cellind.size() << " cells:\n";
// 	for (auto cell : lu(blob)) {
// 	    cerr <<"\t\tcell id:" << cell->ident << " A=" << cell->area
// 		 << " @ "
// 		 << cell->center.x << " "
// 		 << cell->center.y << " "
// 		 << cell->center.z << " wires:\n";
// 	    for (auto wire : lu(cell)) {
// 	    	cerr << "\t\t\twire id: " << wire->wireid
// 	    	     << " plane=" << (int) wire->plane
// 	    	     << " chan=" << wire->chanid
// 	    	     << " vol=" << wire->volid << "\n";
// 	    }
// 	}
//     }


// }

int main()
{

    const string filename = "test_xdata.root";
    test_write(filename);
//    test_read(filename);

    return 0;
}
