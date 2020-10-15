#include "WPA/Andersen.h"

namespace SVF
{
    class Andersen_PTA : public AndersenBase{
        public:
        /// Constructor
        Andersen_PTA(PAG* _pag, PTATY type = Andersen_WPA, bool alias_check = true)
        :  AndersenBase(_pag, type, alias_check){

        }

        /// Destructor
        virtual ~Andersen_PTA(){

        }

        /// Andersen analysis
        virtual void analyze();

        inline NodeID sccRepNode(NodeID id) const
        {
            return consCG->sccRepNode(id);
        }

        /// Operation of points-to set
        virtual inline const PointsTo& getPts(NodeID id)
        {
            return getPTDataTy()->getPts(sccRepNode(id));
        }

        virtual inline bool unionPts(NodeID id, const PointsTo& target)
        {
            id = sccRepNode(id);
            return getPTDataTy()->unionPts(id, target);
        }

        protected:

        /// Handle propagated points-to set.
        inline void updatePropaPts(NodeID dstId, NodeID srcId)
        {
            NodeID srcRep = sccRepNode(srcId);
            NodeID dstRep = sccRepNode(dstId);
            getDiffPTDataTy()->updatePropaPtsMap(srcRep, dstRep);
        }

        /// Add copy edge on constraint graph
        virtual inline bool addCopyEdge(NodeID src, NodeID dst)
        {
            if (consCG->addCopyCGEdge(src, dst))
            {
                updatePropaPts(src, dst);
                return true;
            }
            return false;
        }

        // virtual void initWorklist() {}

        void processAllAddr();

        void processAddr(const AddrCGEdge* addr);

        bool processStore(NodeID node, const ConstraintEdge* store);
        
        bool processLoad(NodeID node, const ConstraintEdge* load);

        bool processCopy(NodeID node, const ConstraintEdge* edge);

        bool processGepPts(const PointsTo& pts, const GepCGEdge* edge);

        bool processGep(NodeID node, const GepCGEdge* edge);

        void handleCopyGep(ConstraintNode* node);

        void handleLoadStore(ConstraintNode *node);

        /// match types for Gep Edges
        virtual bool matchType(NodeID, NodeID, const NormalGepCGEdge*)
        {
            return true;
        }

        /// add type for newly created GepObjNode
        virtual void addTypeForGepObjNode(NodeID, const NormalGepCGEdge*)
        {
            return;
        }

    };
}