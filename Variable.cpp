#include "Variable.h"
#include <iostream>

namespace PharmML
{
    CommonVariable::CommonVariable(PharmMLContext *context, xml::Node node) {
        this->context = context;
        this->parse(node);
    }

    void CommonVariable::parse(xml::Node node) {
        this->symbId = node.getAttribute("symbId").getValue();
        xml::Node assign = this->context->getSingleElement(node, ".//ct:Assign");
        if (assign.exists()) {
            xml::Node tree = assign.getChild();
            this->assignment = this->context->factory.create(tree, &this->deps);
        }
    }
        
    AstNode *CommonVariable::getAssignment() {
        return this->assignment;
    }

    std::string CommonVariable::getSymbId() {
        return this->symbId;
    }

    Dependencies& CommonVariable::getDependencies() {
        return this->deps;
    }

    std::string Variable::accept(AbstractVisitor *visitor) {
        return visitor->visit(this);
    }
}
