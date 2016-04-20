#include "ExternalDataset.h"

namespace PharmML
{
    ExternalDataset::ExternalDataset(PharmML::PharmMLContext *context, xml::Node node) {
        this->context = context;
        this->parse(node);
    }

    void ExternalDataset::parse(xml::Node node) {
        this->oid = node.getAttribute("oid").getValue();
        std::vector<xml::Node> array = this->context->getElements(node, ".//design:ColumnMapping");
        for (xml::Node n : array) {
            PharmML::ColumnMapping *col = new PharmML::ColumnMapping(this->context, n);
            this->ColumnMappings.push_back(col);
        }
    }
    
    std::string ExternalDataset::getOid() {
        return this->oid;
    }

    std::vector<PharmML::ColumnMapping *> ExternalDataset::getColumnMappings() {
        return this->ColumnMappings;
    }
}
