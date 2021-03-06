/* libpharmmlcpp - Library to handle PharmML
 * Copyright (C) 2016 Rikard Nordgren and Gunnar Yngman
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * his library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include <vector>
#include <iostream>

#include "VariabilityModel.h"

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <symbols/SymbolGathering.h>

namespace pharmmlcpp
{
    VariabilityModel::VariabilityModel(PharmMLReader &reader, xml::Node node) {
        this->Block::parse(node);
        this->parse(reader, node);
    }

    void VariabilityModel::parse(PharmMLReader &reader, xml::Node node) {
        // Get type and name
        this->type = node.getAttribute("type").getValue();
        xml::Node name_node = reader.getSingleElement(node, "./ct:Name");
        if (name_node.exists()) {
            this->name = reader.getSingleElement(node, "./ct:Name").getText();
        }

        // Get variability levels
        std::vector<xml::Node> var_level_nodes = reader.getElements(node, "./mdef:Level");
        for (xml::Node var_level_node : var_level_nodes) {
            VariabilityLevel *var_level = new VariabilityLevel(reader, var_level_node);
            this->variabilityLevels.push_back(var_level);
        }
    }

    std::string VariabilityModel::getName() {
        return this->name;
    }

    bool VariabilityModel::onResidualError() {
        return (this->type == "residualError");
    }

    bool VariabilityModel::onParameter() {
        return (this->type == "parameterVariability");
    }

    std::vector<pharmmlcpp::VariabilityLevel *> VariabilityModel::getVariabilityLevels() {
        return this->variabilityLevels;
    }
            
    void VariabilityModel::gatherSymbols(SymbolGathering &gathering) {
        gathering.newBlock(this);
        for (VariabilityLevel *varlev : this->variabilityLevels) {
            gathering.addSymbol(varlev);
        }
    }
}
