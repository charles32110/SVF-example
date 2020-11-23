//
// Created by guanqin on 23/11/20.
//

#ifndef SVF_EX_REASONING_SEQ_H
#define SVF_EX_REASONING_SEQ_H
#endif //SVF_EX_REASONING_SEQ_H
#include "SVF-FE/LLVMUtil.h"
#include "SVF-FE/PAGBuilder.h"
#include "Graphs/SVFG.h"
#include "z3++.h"
#include <iostream>
#include <vector>

using namespace z3;
using namespace SVF;
using namespace std;
class RSeq
{
public:

    static RSeq &getInstance()
    {
        static RSeq s;
        return s;
    };
//    void demorgan();
//    void traversPAG(PAG* pag);
//    void PAGNode_case(PAGNode::GNodeK k);
//    void traversICFG(ICFG* icfg);
    vector<vector< ICFGNode*>> findSrcToSnkPath(ICFG *icfg, ICFGNode src, ICFGNode dst);
    void pathtrack(vector<vector< ICFGNode *>> &paths, vector< ICFGNode *> &seq,
                   set< ICFGNode *> &visited, ICFGNode *src, ICFGNode *snk);
    void expr_seq(vector<ICFGNode *>path);


private:
    RSeq(){};


};


