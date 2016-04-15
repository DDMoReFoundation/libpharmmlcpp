#include "Arms.h"

namespace PharmML
{
    // InterventionSequence class
    InterventionSequence::InterventionSequence(PharmML::PharmMLContext *context, xml::Node node) {
        this->context = context;
        this->parse(node);
    }
    
    void InterventionSequence::parse(xml::Node node) {
        // Get intervention references
        xml::Node interventionList = this->context->getSingleElement(node, "./design:InterventionList");
        std::vector<xml::Node> interventionRefs = this->context->getElements(interventionList, "./design:InterventionRef");
        for (xml::Node ref : interventionRefs) {
            this->oidRefs.push_back(ref.getAttribute("oidRef").getValue());
        }
        
        // Get start value
        xml::Node assign = this->context->getSingleElement(node, "./design:Start/ct:Assign");
        if (assign.exists()) {
            this->start = this->context->factory.create(assign.getChild());
        }
    }
    
    std::vector<std::string> InterventionSequence::getOidRefs() {
        return this->oidRefs;
    }
    
    AstNode *InterventionSequence::getStart() {
        return this->start;
    }
    
    std::string InterventionSequence::accept(AbstractVisitor *visitor) {
        return visitor->visit(this);
    }
    
    // ObservationSequence class
    ObservationSequence::ObservationSequence(PharmML::PharmMLContext *context, xml::Node node) {
        this->context = context;
        this->parse(node);
    }
    
    void ObservationSequence::parse(xml::Node node) {
        // Get observation references
        xml::Node observationList = this->context->getSingleElement(node, "./design:ObservationList");
        std::vector<xml::Node> observationRefs = this->context->getElements(observationList, "./design:ObservationRef");
        for (xml::Node ref : observationRefs) {
            this->oidRefs.push_back(ref.getAttribute("oidRef").getValue());
        }
        
        // Get start value
        xml::Node assign = this->context->getSingleElement(node, "./design:Start/ct:Assign");
        if (assign.exists()) {
            this->start = this->context->factory.create(assign.getChild());
        }
    }
    
    std::vector<std::string> ObservationSequence::getOidRefs() {
        return this->oidRefs;
    }
    
    AstNode *ObservationSequence::getStart() {
        return this->start;
    }
    
    std::string ObservationSequence::accept(AbstractVisitor *visitor) {
        return visitor->visit(this);
    }
    
    // Arm class
    Arm::Arm(PharmMLContext *context, xml::Node node) {
        this->context = context;
        this->parse(node);
    }
    
    void Arm::parse(xml::Node node) {
        this->oid = node.getAttribute("oid").getValue();
        
        // Get arm (oid) reference
        xml::Node armRef = this->context->getSingleElement(node, "./design:ArmRef");
        if (armRef.exists()) {
            this->oidRef = armRef.getAttribute("oidRef").getValue();
        }
        
        // Get arm size
        xml::Node assign = this->context->getSingleElement(node, "./design:ArmSize/ct:Assign");
        if (assign.exists()) {
            this->armSize = this->context->factory.create(assign.getChild());
        }
        
        // Get number of samples
        assign = this->context->getSingleElement(node, "./design:NumberSamples/ct:Assign");
        if (assign.exists()) {
            this->numSamples = this->context->factory.create(assign.getChild());
        }
        
        // Get number of times
        assign = this->context->getSingleElement(node, "./design:NumberTimes/ct:Assign");
        if (assign.exists()) {
            this->numTimes = this->context->factory.create(assign.getChild());
        }
        
        // Get same times
        assign = this->context->getSingleElement(node, "./design:SameTimes/ct:Assign");
        if (assign.exists()) {
            this->sameTimes = this->context->factory.create(assign.getChild());
        }
        
        // Get intervention sequences
        std::vector<xml::Node> sequence = this->context->getElements(node, "./design:InterventionSequence");
        for (xml::Node node : sequence) {
            InterventionSequence *sequence = new InterventionSequence(this->context, node);
            this->interventionSequences.push_back(sequence);
        }
        
        // Get observation sequences
        sequence = this->context->getElements(node, "./design:ObservationSequence");
        for (xml::Node node : sequence) {
            ObservationSequence *sequence = new ObservationSequence(this->context, node);
            this->observationSequences.push_back(sequence);
        }
        
        // Get occasion sequences
        sequence = this->context->getElements(node, "./design:OccasionSequence");
        //~ for (xml::Node node : sequence) {
            //~ OccasionSequence *sequence = new OccasionSequence(this->context, node);
            //~ this->occasionSequences.push_back(sequence);
        //~ }
    }
    
    std::string Arm::getOid(){
        return this->oid;
    }
    
    std::string Arm::getOidRef(){
        return this->oidRef;
    }

    AstNode *Arm::getArmSize(){
        return this->armSize;
    }

    AstNode *Arm::getNumSamples(){
        return this->numSamples;
    }

    AstNode *Arm::getNumTimes(){
        return this->numTimes;
    }

    AstNode *Arm::getSameTimes(){
        return this->sameTimes;
    }
    
    std::vector<InterventionSequence *> Arm::getInterventionSequences(){
        return this->interventionSequences;
    }
    
    std::string Arm::accept(AbstractVisitor *visitor) {
        return visitor->visit(this);
    }
    
    // Arms class
    Arms::Arms(PharmMLContext *context, xml::Node node) {
        this->context = context;
        this->parse(node);
    }
    
    void Arms::parse(xml::Node node) {
        // Get arm size
        xml::Node assign = this->context->getSingleElement(node, "./design:ArmSize/ct:Assign");
        if (assign.exists()) {
            this->armSize = this->context->factory.create(assign.getChild());
        }
        
        // Get cost function
        assign = this->context->getSingleElement(node, "./design:CostFunction/ct:Assign");
        if (assign.exists()) {
            this->costFunction = this->context->factory.create(assign.getChild());
        }
        
        // Get number of arms
        assign = this->context->getSingleElement(node, "./design:NumberArms/ct:Assign");
        if (assign.exists()) {
            this->numArms = this->context->factory.create(assign.getChild());
        }
        
        // Get number of samples
        assign = this->context->getSingleElement(node, "./design:NumberSamples/ct:Assign");
        if (assign.exists()) {
            this->numSamples = this->context->factory.create(assign.getChild());
        }
        
        // Get number of times
        assign = this->context->getSingleElement(node, "./design:NumberTimes/ct:Assign");
        if (assign.exists()) {
            this->numTimes = this->context->factory.create(assign.getChild());
        }
        
        // Get same times
        assign = this->context->getSingleElement(node, "./design:SameTimes/ct:Assign");
        if (assign.exists()) {
            this->sameTimes = this->context->factory.create(assign.getChild());
        }
        
        // Get total cost
        assign = this->context->getSingleElement(node, "./design:TotalCost/ct:Assign");
        if (assign.exists()) {
            this->totalCost = this->context->factory.create(assign.getChild());
        }
        
        // Get total size
        assign = this->context->getSingleElement(node, "./design:TotalSize/ct:Assign");
        if (assign.exists()) {
            this->totalSize = this->context->factory.create(assign.getChild());
        }
        
        // Get the arm definitions themselves
        std::vector<xml::Node> arms = this->context->getElements(node, "./design:Arm");
        for (xml::Node node : arms) {
            Arm *arm = new Arm(this->context, node);
            this->arms.push_back(arm);
        }
    }
    
    AstNode *Arms::getArmSize() {
        return this->armSize;
    }
    
    AstNode *Arms::getCostFunction() {
        return this->costFunction;
    }
    
    AstNode *Arms::getNumArms() {
        return this->numArms;
    }
    
    AstNode *Arms::getNumSamples() {
        return this->numSamples;
    }
    
    AstNode *Arms::getNumTimes() {
        return this->numTimes;
    }
    
    AstNode *Arms::getSameTimes() {
        return this->sameTimes;
    }
    
    AstNode *Arms::getTotalCost() {
        return this->totalCost;
    }
    
    AstNode *Arms::getTotalSize() {
        return this->totalSize;
    }
    
    std::vector <Arm *> Arms::getArms() {
        return this->arms;
    }
    
    std::string Arms::accept(AbstractVisitor *visitor) {
        return visitor->visit(this);
    }
}
