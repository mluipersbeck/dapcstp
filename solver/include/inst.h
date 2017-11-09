/**
 * \file   inst.h
 * \brief  problem instance class
 *
 * \author Martin Luipersbeck 
 * \date   2015-05-03
 */

#ifndef INST_H_
#define INST_H_

#include <vector>
#include <set>

#include "def.h"
#include "ds.h"

using namespace std;

class Inst {
public:

	Inst();
	Inst(const Inst& inst);
	~Inst();

	vector<vector<int>> din, dout;
	vector<int> tail, head;
	vector<int> opposite;
	 // position of arc in adjacency lists
	vector<int> pin, pout;

	// information on variable fixing
	vector<flag_t> f0, f1, fe0;

	// data used for algorithm, changed by fixing
	vector<weight_t> c, p;
	vector<flag_t> T;
	vector<vector<int>> bmna, bmaa;

	weight_t offset;
	int n, m, t, r;
	bool isInt = false;
	bool isAsym = false;
	bool isMWCS = false;
	Inst* inst1 = nullptr;
	weight_t bigM = -1;

	void resizeNodes(int _m);
	void resizeEdges(int _m);

	void removeNode(int i);

	void newArc(int i, int j, int ij, int ji, weight_t w);
	void delArc(int ij);

	void moveHead(int ij, int k);
	void moveTail(int ij, int k);

	void merge(int ij, int i, int j);
	void contractArc(int ji);

	void     increaseRevenue(int i, weight_t val);
	weight_t decreaseRevenue(int i);

	InstSizeData countInstSize();

	weight_t nonreachableRevenue(int start);

	void printArcSet(vector<int>& s);
	void printNodeSet(set<int>& s);

	bool hasCheaperIncomingArc(int i, int ij);
	bool singleAdjacency(int i);
	bool doubleAdjacency(int i, int& j, int& k, int& ki, int& ij, int& ji, int& ik);

	vector<flag_t> AP(vector<flag_t>& ap, vector<int>& lastap);
	void processNode(int i, int j, vector<flag_t>& visited, vector<int>& parent, vector<int>& disc, vector<int>& low, vector<flag_t>& ap, int& time, vector<vector<int>>& certs);
	void APsearch(int i, vector<flag_t>& ap, vector<vector<int>>& certs);
	void findAllSubtrees(vector<flag_t>& ap, vector<int>& lastap, vector<vector<int>>& certs);

	// update backmapping for reduction tests
	void updatebmNTD1(int ji);
	void updatebmNTD2triangle(int ik, int ij, int jk);
	void updatebmNTD2(int ij, int jk);
	void updatebmMerge(int ij, bool bidirect = false);

	void convertMWCS2PCSTP();
	weight_t convertPCSTPBound2MWCS(weight_t bound);
	Inst createRootedBigMCopy();
	void setBigM(weight_t M);
	int countReachableFixed(int r);

	Transformation* transformation = nullptr;
};

#endif // INST_H_
