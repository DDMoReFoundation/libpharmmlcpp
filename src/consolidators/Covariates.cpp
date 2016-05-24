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

#include <consolidators/Covariates.h>

namespace CPharmML
{
    // Construct with PharmML::Covariate as base
    Covariate::Covariate(PharmML::Covariate *covariate) {
        this->covariate = covariate;

        this->name = covariate->getSymbId();
        this->derived = covariate->isTransformed();
        this->continuous = covariate->isContinuous();
        this->type = covariate->getType();
        this->distribution = covariate->getDistribution();
        this->definition = covariate->getAssignment();
    }

    // Add PharmML objects for consolidation (in this order)
    void Covariate::addColumnMapping(PharmML::ColumnMapping *columnMapping) {
        this->columnMapping = columnMapping;

        this->columnId = columnMapping->getColumnIdRef();
    }

    void Covariate::addColumnDefinition(PharmML::ColumnDefinition *covariateColumnDef) {
        this->columnDef = covariateColumnDef;
    }

    // Get attributes
    PharmML::Covariate *Covariate::getCovariate() {
        return this->covariate;
    }

    PharmML::ColumnMapping *Covariate::getColumnMapping() {
        return this->columnMapping;
    }

    PharmML::ColumnDefinition *Covariate::getColumnDefinition() {
        return this->columnDef;
    }

    std::string Covariate::getName() {
        return this->name;
    }

    bool Covariate::isDerived() {
        return this->derived;
    }

    bool Covariate::isContinuous() {
        return this->continuous;
    }

    std::string Covariate::getType() {
        return this->type;
    }

    PharmML::Distribution *Covariate::getDistribution() {
        return this->distribution;
    }

    PharmML::AstNode *Covariate::getDefinition() {
        return this->definition;
    }

    std::string Covariate::getColumnId() {
        return this->columnId;
    }
}
