#ifndef WIRECELLXDATAROOT_WRITER
#define WIRECELLXDATAROOT_WRITER

#include "WireCellXdataRoot/Geom.h"
#include "WireCellXdataRoot/RunInfo.h"
#include "WireCellXdataRoot/Trigger.h"
#include "WireCellXdataRoot/Field.h"
#include "WireCellXdataRoot/Frame.h"
#include "WireCellXdataRoot/Image.h"

#include "TFile.h"
#include "TTree.h"

namespace WireCellXdataRoot {

    template<class Type>
    class TreeHelper {
	TTree* m_tree;
	Type* m_obj;
    public:
	TreeHelper()
	    : m_tree(0)
	    , m_obj(new Type) {
	}
	void init(const std::string& tree, const std::string& branch) {
	    std::string title = "Wire Cell Exchange Data " + tree;
	    m_tree = new TTree(tree.c_str(), tree.c_str());
	    m_tree->Branch(branch.c_str(), &m_obj);
	}
	~TreeHelper() {
	    // delete m_obj;
	}

	Type& obj() { return *m_obj; }
	
	size_t fill() {
	    m_tree->Fill(); 
	}

	size_t write() {
	    //m_tree->Write();    
	    return m_tree->Write("", TObject::kOverwrite);
	}

    };


    class Writer {

	TFile* m_tfile;

    public:

	/// Give caller direct access
	TreeHelper<Geom> geom;
	TreeHelper<RunInfo> runinfo;
	TreeHelper<Trigger> trigger;
	TreeHelper<Field> field;
	TreeHelper<Frame> frame;
	TreeHelper<Image> image;

	Writer(const std::string& filename)
	    : m_tfile(TFile::Open(filename.c_str(), "RECREATE")) {
	    geom.init("geom","geom");
	    runinfo.init("runinfo","runinfo");
	    trigger.init("trig","trig");
	    field.init("field","field");
	    frame.init("frame","frame");
	    image.init("image","image");
	}
	void close() {
	    if (!m_tfile) {
		return;
	    }
	    geom.write();
	    runinfo.write();
	    trigger.write();
	    field.write();
	    frame.write();
	    image.write();

	    m_tfile->Close();
	    delete m_tfile; m_tfile = nullptr;
	}

	~Writer() {
	    close();
	}

    };

}

#endif
