#include <iostream>
#include "Intervention.h"
#include "PharmMLContext.h"
#include "AstNodeFactory.h"
#include "AstNode.h"
#include "symbols.h"

namespace PharmML
{
    // TODO: Maybe move this somewhere? Variable.cpp (this is a reference, however)?
    // TODO: Maybe the name can be changed to something more general if needed
    SteadyStateParameter::SteadyStateParameter(PharmMLContext *context, xml::Node node) {
        this->context = context;
        this->parse(node);
    }

    void SteadyStateParameter::parse(xml::Node node) {
        xml::Node symbol = this->context->getSingleElement(node, ".//ct:SymbRef");
        symbRef = new SymbRef(symbol);
        
        xml::Node assign = this->context->getSingleElement(node, ".//ct:Assign");
        if (assign.exists()) {
            xml::Node tree = assign.getChild();
            this->assignment = this->context->factory.create(tree);
        }
    }
        
    AstNode *SteadyStateParameter::getAssignment() {
        return this->assignment;
    }

    AstNode *SteadyStateParameter::getSymbRef() {
        return this->symbRef;
    }

    std::string SteadyStateParameter::accept(AbstractVisitor *visitor) {
        return visitor->visit(this);
    }
    
    // TODO: Move elsewhere (Dataset.h when implemented)
    // TODO: Subclass for MapType? Subclass for SymbRef (see usage in Administration)?
    TargetMapping::TargetMapping(PharmMLContext *context, std::string type, xml::Node node) {
        this->context = context;
        this->type = type;
        this->blkIdRef = node.getAttribute("blkIdRef").getValue();
        xml::Node map = this->context->getSingleElement(node, ".//ds:Map");
        // Not sure type differentiates attribute used in MapType (only empirical observation)
        if (type == "parameter") {
            // Not seen example of but in schema
        } else if (type == "derivativeVaribel") {
            this->ref = map.getAttribute("modelSymbol").getValue();
        } else if (type == "variable") {
            // Not seen example of but in schema
        } else if (type == "admType") {
            this->ref = map.getAttribute("admNumber").getValue();
        }
        // Not sure when used in MapType
        //~ this->ref = map.getAttribute("dataSymbol").getValue();
    }
    
    std::string TargetMapping::getType() {
        return this->type;
    }
    
    std::string TargetMapping::getBlkIdRef() {
        return this->blkIdRef;
    }
    std::string TargetMapping::getRef() {
        return this->ref;
    }
    
    std::string TargetMapping::accept(AbstractVisitor *visitor) {
        return visitor->visit(this);
    }
    
    Administration::Administration(PharmMLContext *context, xml::Node node) {
        this->context = context;
        this->parse(node);
    }
    
    void Administration::parse(xml::Node node) {
        this->oid = node.getAttribute("oid").getValue();
        xml::Node dose = node.getChild();
        this->type = dose.getName();
        
        // Get dose amount
        xml::Node amount = this->context->getSingleElement(dose, ".//design:DoseAmount");
        xml::Node assign = this->context->getSingleElement(dose, ".//design:DoseAmount/ct:Assign");
        xml::Node tree = assign.getChild();
        this->amount = this->context->factory.create(tree);
        
        // Get dose target ('target' should probably be of parent class of SymbRef/TargetMapping).
        std::string targetType = amount.getAttribute("inputTarget").getValue();
        xml::Node symbref = this->context->getSingleElement(dose, ".//design:DoseAmount/ct:SymbRef");
        xml::Node mapping = this->context->getSingleElement(dose, ".//design:DoseAmount/design:TargetMapping");
        if (symbref.exists()) {
            this->target = new SymbRef(symbref);
        } else if (mapping.exists()) {
            this->target = new TargetMapping(this->context, targetType, mapping);
        }
        
        // Get dose times/steady state
        xml::Node times = this->context->getSingleElement(dose, ".//design:DosingTimes");
        xml::Node steady = this->context->getSingleElement(dose, ".//design:SteadyState");
        if (times.exists()) {
            xml::Node assign = this->context->getSingleElement(times, ".//ct:Assign");
            xml::Node tree = assign.getChild();
            this->times = this->context->factory.create(tree);
        } else if (steady.exists()) {
            this->steady = new SteadyStateParameter(this->context, steady);
        }
        
        // Get duration/rate for infusion type
        if (this->type == "Infusion") {
            xml::Node duration = this->context->getSingleElement(dose, ".//design:duration");
            xml::Node rate = this->context->getSingleElement(dose, ".//design:rate");
            if (duration.exists()) {
                // TODO: Support <Duration>
                this->duration = nullptr;
            } else if (rate.exists()) {
                // TODO: Support <Rate>
                this->rate = nullptr;
            }
        }
    }
    
    std::string Administration::getOid() {
        return this->oid;
    }
    
    std::string Administration::getType() {
        return this->type;
    }
    
    AstNode *Administration::getTarget() {
        return this->target;
    }
    
    AstNode *Administration::getTimes() {
        return this->times;
    }
    
    AstNode *Administration::getSteady() {
        return this->steady;
    }
    
    AstNode *Administration::getDuration() {
        return this->duration;
    }
    
    AstNode *Administration::getRate() {
        return this->rate;
    }
    
    std::string Administration::accept(AbstractVisitor *visitor) {
        return visitor->visit(this);
    }
    
    Intervention::Intervention(PharmMLContext *context, xml::Node node) {
        this->context = context;
        this->parse(node);
    }
    
    void Intervention::parse(xml::Node node) {
        std::vector<xml::Node> array = this->context->getElements(node, ".//design:Administration");
        for (xml::Node n : array) {
            PharmML::Administration *adm = new PharmML::Administration(this->context, n);
            this->Administrations.push_back(adm);
        }
    }
    
    std::vector <Administration *> Intervention::getAdministrations() {
        return Administrations;
    }
}