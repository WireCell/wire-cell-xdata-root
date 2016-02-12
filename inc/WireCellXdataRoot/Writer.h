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
    class TreeWriter {
	TTree* m_tree;
	Type* m_obj;
    public:
	TreeWriter()
	    : m_tree(0)
	    , m_obj(new Type) {
	}
	void init(const std::string& tree, const std::string& branch) {
	    std::string title = "Wire Cell Exchange Data " + tree;
	    m_tree = new TTree(tree.c_str(), tree.c_str());
	    m_tree->Branch(branch.c_str(), &m_obj);
	}
	~TreeWriter() {
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


    /**  A simple helper to write Xdata ROOT files.
     *
     *  Use the provided TreeHelper objects to set data on their
     *  .obj() and then call the helper's .fill().  When done, call
     *  the Writer's .close() or just delete the Writer.
     */
    class Writer {

	TFile* m_tfile;
	bool m_owner;

    public:

	/// Give caller direct access
	TreeWriter<Geom> geom;
	TreeWriter<RunInfo> runinfo;
	TreeWriter<Trigger> trigger;
	TreeWriter<Field> field;
	TreeWriter<Frame> frame;
	TreeWriter<Image> image;
	TTree *TMC;

	Writer(TFile* tfile) 
	    : m_tfile(tfile)
	    , m_owner(false)
	{
	    geom.init("geom","geom");
	    runinfo.init("runinfo","runinfo");
	    trigger.init("trig","trig");
	    field.init("field","field");
	    frame.init("frame","frame");
	    image.init("image","image");
	}
	Writer(const std::string& filename)
	    : m_tfile(TFile::Open(filename.c_str(), "RECREATE"))
	    , m_owner(true)
	{
	    geom.init("geom","geom");
	    runinfo.init("runinfo","runinfo");
	    trigger.init("trig","trig");
	    field.init("field","field");
	    frame.init("frame","frame");
	    image.init("image","image");
	    TMC = 0;
	}
	void set_tree_mc(TTree* tree){
	  TMC = tree;
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
	    if (TMC!=0){
	      TMC->CloneTree()->Write();
	    }

	    if (m_owner) {
		m_tfile->Close();
		delete m_tfile;
		m_tfile = nullptr;
	    }
	}

	~Writer() {
	    close();
	}

    };

}

#endif
