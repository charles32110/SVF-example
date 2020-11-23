//
// Created by guanqin on 23/11/20.
//
#include "Reasoning_seq.h"

using namespace SVF;
using namespace SVFUtil;
using namespace llvm;
using namespace std;
using namespace z3;


vector<vector<ICFGNode*>> RSeq::findSrcToSnkPath(ICFG *icfg, ICFGNode src, ICFGNode dst)
{
    vector<vector<ICFGNode*>> paths;
    set<ICFGNode *> visited;
    //store for node sequence
    vector<ICFGNode *> seq;
    pathtrack(paths, seq, visited, &src, &dst);
    return paths;
}

void RSeq::pathtrack(vector<vector<ICFGNode *>> &paths, vector< ICFGNode *> &seq,
                     set< ICFGNode *> &visited, ICFGNode *src, ICFGNode *snk) {
    visited.insert(src);
    seq.push_back(src);
    if (src->getId()==snk->getId())
    {
        //store one reached seq
        paths.push_back(seq);
    }
    for ( auto it = src->OutEdgeBegin(); it != src->OutEdgeEnd(); it ++) {
        ICFGNode *cur = (*it)->getDstNode();
        if (visited.find(cur) == visited.end()) {
            pathtrack(paths, seq, visited, cur, snk);
        }
    }
    visited.erase(src);
    seq.pop_back();
}

void RSeq::expr_seq(vector<ICFGNode *> path)
{
    for( unsigned int i = 0; i < path.size();i++)
    {
        ICFGNode* iNode = path[i];
        if (IntraBlockNode* bNode = SVFUtil::dyn_cast<IntraBlockNode>(iNode))
        {
            SVFUtil::outs() << *bNode<< "\n";
            for(ICFGNode::VFGNodeList::const_iterator v = bNode->getVFGNodes().begin(); v != iNode->getVFGNodes().end(); ++v)
            {
                //Todo: gives the node repeatedly should figure out reasons
                SVFUtil::outs() << (*v)->toString()<< "\n";
            }
//            PAG::PAGEdgeList&  edges = PAG::getPAG()->getInstPTAPAGEdgeList(bNode);
//            for (PAG::PAGEdgeList::iterator it = edges.begin(), eit = edges.end(); it != eit; ++it) {
//                const PAGEdge *edge = *it;
//                PAGNode *srcPN = edge->getSrcNode();
//                PAGNode *dstPN = edge->getDstNode();
//                SVFUtil::outs() << "\t src : " << *srcPN  << "\t dst : " << *dstPN << "\n";
//            }
        }
    }
}