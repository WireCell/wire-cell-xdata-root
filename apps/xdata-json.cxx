/** example dumper of xdata root into xdata json.
 *
 * The schema of the ROOT file is preserved.
 *
 * Run example:
 *
 * $ ./build/xdata-json ../xdata.root ../xdata.json
 * Read Xdata in 0.861631s
 * Jsonify in 18.9272s
 * 
 * Size comparison (kByte):
 * ```
 *  209352547 Feb  8 15:09 ../xdata.json
 *    6873222 Feb  8 14:35 ../xdata.root
 *   11709205 Feb  8 15:09 ../xdata.json.gz
 * ```
 */


#include "WireCellXdataRoot/XdataFile.h"

// JSONCPP
#include <json/json.h>

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

Json::Value Jpoint(WireCellXdataRoot::Point& xp)
{
    Json::Value jp;
    jp["x"] = xp.x;
    jp["y"] = xp.y;
    jp["z"] = xp.z;
    return jp;
}
template<typename Type>
Json::Value Jvalues(const std::vector<Type>& xvalues)
{
    Json::Value jvalues;
    for (auto v : xvalues) {
	jvalues.append(v);
    }
    return jvalues;
}
template<>
Json::Value Jvalues(const std::vector<size_t>& xvalues)
{
    Json::Value jvalues;
    for (auto v : xvalues) {
	jvalues.append((Json::UInt64)v);
    }
    return jvalues;
}


using namespace std;
using namespace WireCellXdataRoot;



int main(int argc, char* argv[])
{
    if (argc < 3) {
	cerr << "usage: xdata-json xdata.root xdata.json" << endl;
    }

    const std::string json_filename = argv[2];
    ofstream outstr(json_filename.c_str());

    const std::string xdata_filename = argv[1];

    std::chrono::duration<double> in_duration;
    std::chrono::duration<double> out_duration;

    chrono::time_point<std::chrono::system_clock> clock1, clock2, clock3;

    clock1 = chrono::system_clock::now();
    XdataFile xdata;
    xdata.read(xdata_filename.c_str());
    clock2 = chrono::system_clock::now();
    in_duration = clock2-clock1;
    cerr << "Read Xdata in " << in_duration.count() << "s\n";

    clock1 = chrono::system_clock::now();

    Json::Value jdata;

    // Dump RunInfo
    RunInfo& xri = xdata.runinfo();
    Json::Value jri;
    jri["detector"] = xri.detector;
    jri["ident"] = (Json::UInt64)xri.ident;
    jdata["runinfo"] = jri;

    
    // Dump Geom
    Geom& xgeom = xdata.geom();
    Json::Value jwires;
    int iwire = -1;
    for (auto xwire : xgeom.wires) {
	++iwire;
	Json::Value jwire;
    
	jwire["wireid"] = xwire->wireid;
	jwire["chanid"] = xwire->chanid;
	jwire["volid"] = xwire->volid;
	jwire["plane"] = xwire->plane;
	jwire["face"] = xwire->face;
	jwire["offset"] = xwire->offset;
	jwire["segment"] = xwire->segment;
	jwire["point1"] = Jpoint(xwire->point1);
	jwire["point2"] = Jpoint(xwire->point2);

	jwires[iwire] = jwire;
    }
    Json::Value jgeom;
    jgeom["wires"] = jwires;
    jdata["geom"] = jgeom;

    // Dump Image
    Image& ximg = xdata.image();
    Json::Value jimg;
    jimg["ident"] = (Json::UInt64)ximg.ident;
    jimg["second"] = (Json::UInt64)ximg.second;
    jimg["nanosecond"] = ximg.nanosecond;
    jimg["toffset"] = ximg.toffset;
    jimg["slicespan"] = ximg.slicespan;
    
    Json::Value jdecos;
    int ndecos = ximg.num_decos();
    for (int ind=0; ind<ndecos; ++ind) {
	auto xdeco = ximg.get_deco(ind);
	Json::Value jdeco;
	jdeco["wireind"] = xdeco->wireind;
	jdeco["slice"] = xdeco->slice;
	jdeco["values"] = Jvalues(xdeco->values);
	jdecos.append(jdeco);
    }
    jimg["decos"] = jdecos;


    Json::Value jcells;
    int ncells = ximg.num_cells();
    for (int ind=0; ind<ncells; ++ind) {
	auto xcell = ximg.get_cell(ind);
	Json::Value jcell;
	jcell["ident"] = xcell->ident;
	jcell["uind"] = xcell->uind;
	jcell["vind"] = xcell->vind;
	jcell["wind"] = xcell->wind;
	jcell["area"] = xcell->area;
	jcell["center"] = Jpoint(xcell->center);
	jcells.append(jcell);
    }
    jimg["cells"] = jcells;


    Json::Value jblobs;
    int nblobs = ximg.num_blobs();
    for (int ind=0; ind<nblobs; ++ind) {
	auto xblob = ximg.get_blob(ind);
	Json::Value jblob;
	jblob["ident"] = xblob->ident;
	jblob["slice"] = xblob->slice;
	jblob["cellind"] = Jvalues<size_t>(xblob->cellind);
	jblob["values"] = Jvalues(xblob->values);
	jblobs.append(jblob);
    }
    jimg["blobs"] = jblobs;

    Json::Value jfields;
    int nfields = ximg.num_fields();
    for (int ind=0; ind<nfields; ++ind) {
	auto xfield = ximg.get_field(ind);
	Json::Value jfield;
	jfield["name"] = xfield->name;

	Json::Value jfps;
	for (auto xfp : xfield->points) {
	    Json::Value jfp;
	    jfp["point"] = Jpoint(xfp.point);
	    jfp["values"] = Jvalues(xfp.values);
	    jfps.append(jfp);
	}
	jfield["points"] = jfps;
	jfields.append(jfield);
    }
    jimg["fields"] = jfields;    
    jdata["image"] = jimg;

    outstr << jdata;
    outstr.close();

    clock2 = chrono::system_clock::now();
    out_duration = clock2-clock1;
    cerr << "Jsonify in " << out_duration.count() << "s\n";
    return 0;
}
