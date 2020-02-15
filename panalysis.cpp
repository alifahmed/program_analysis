// Author: Alif Ahmed (alifahmed@virginia.edu)

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "BPatch.h"
#include "BPatch_function.h"
#include "BPatch_basicBlock.h"
#include "BPatch_flowGraph.h"
#include "BPatch_Set.h"

using namespace std;

int main(int argc, char** argv){
	BPatch bpatch;
	if(argc != 2){
		cerr << "Usage: panalysis <path_to_binary>" << endl;
		return -1;
	}

	BPatch_binaryEdit* bin = bpatch.openBinary(argv[1]);

	if(bin == nullptr){
		cerr << "Cannot open binary file: " << argv[1] << endl;
	}

	BPatch_image* img = bin->getImage();

	std::vector<BPatch_function *> funcs;
	img->getProcedures(funcs);

	size_t num_bb = 0;
	size_t num_iedge = 0;
	size_t num_oedge = 0;

	for(auto fit = funcs.begin(); fit != funcs.end(); fit++){
		BPatch_flowGraph* fg = (*fit)->getCFG();
		BPatch_Set<BPatch_basicBlock*> bbs;
		fg->getAllBasicBlocks(bbs);
		for(BPatch_basicBlock* bb : bbs){
			num_bb++;

			vector<BPatch_edge*> edges;
			bb->getIncomingEdges(edges);
			for(auto ed : edges){
				if((ed->getType() == CondJumpTaken) || (ed->getType() == CondJumpNottaken)){
					num_iedge++;
				}
			}

			edges.clear();
			bb->getOutgoingEdges(edges);
			for(auto ed : edges){
				if((ed->getType() == CondJumpTaken) || (ed->getType() == CondJumpNottaken)){
					num_oedge++;
				}
			}
		}
	}

	cout << "Number of basic blocks: " << num_bb << endl;
	cout << "Number of incoming edges: " << num_iedge << endl;
	cout << "Number of outgoing edges: " << num_oedge << endl;

	return 0;
}
