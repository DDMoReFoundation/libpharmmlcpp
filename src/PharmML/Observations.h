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

#ifndef PHARMML_OBSERVATIONS_H_
#define PHARMML_OBSERVATIONS_H_

#include <xml/xml.h>
#include <PharmML/PharmMLContext.h>
#include <AST/AstNode.h>
#include <symbols/Variable.h>
#include <AST/symbols.h>
#include <PharmML/ColumnMapping.h>
#include <PharmML/Dataset.h>
#include <objects/Object.h>
#include <PharmML/PharmMLSection.h>
#include <visitors/ObjectVisitor.h>
//~ #include "ExternalDataset.h" // Check comments in this file

namespace pharmmlcpp
{
    class Observation : public Object, public PharmMLSection
    {
        public:
            Observation(PharmMLContext *context, xml::Node node);
            void parse(xml::Node node);
            void gatherObjectRefs(std::unordered_map<std::string, Object *> &oidMap);
            ObjectRef* getOidRef();
            AstNode *getNumber();
            AstNode *getTimes();
            std::vector<AstNode *> getTimesAsVector();
            std::vector<pharmmlcpp::SymbRef *> getContinuousVariables();
            std::vector<pharmmlcpp::SymbRef *> getDiscreteVariables();
            void accept(PharmMLVisitor *visitor);
            void accept(ObjectVisitor *visitor);

        private:
            pharmmlcpp::PharmMLContext *context;
            ObjectRef *oidRef = nullptr;
            AstNode *number = nullptr;
            AstNode *times = nullptr;
            std::vector<pharmmlcpp::SymbRef *> continuousVariables;
            std::vector<pharmmlcpp::SymbRef *> discreteVariables;
    };

    // IndividualObservations class
    class IndividualObservations : public Object, public PharmMLSection
    {
        public:
            IndividualObservations(pharmmlcpp::PharmMLContext *context, xml::Node node);
            void parse(xml::Node node);
            void gatherObjectRefs(std::unordered_map<std::string, Object *> &oidMap) {};
            xml::Node xml();
            std::vector<pharmmlcpp::ColumnMapping *> getColumnMappings();
            Dataset *getDataset();
            void accept(PharmMLVisitor *visitor);
            void accept(ObjectVisitor *visitor);

        private:
            pharmmlcpp::PharmMLContext *context;
            std::vector<pharmmlcpp::ColumnMapping *> columnMappings;
            Dataset *dataset;
    };

    // ObservationCombination class
    class ObservationCombination
    {
        public:
            ObservationCombination(PharmMLContext *context, xml::Node node);
            void parse(xml::Node node);
            std::string getOid();
            std::vector<std::string> getOidRefs();
            AstNode *getRelative();
            void accept(PharmMLVisitor *visitor);

        private:
            pharmmlcpp::PharmMLContext *context;
            std::string oid;
            std::vector<std::string> oidRefs;
            AstNode *relative = nullptr;
    };

    // Observations class (contains objects of classes above)
    class Observations
    {
        public:
            Observations(PharmMLContext *context, xml::Node node);
            void parse(xml::Node node);
            xml::Node xml();
            std::vector<Variable *> getDesignParameters();
            std::vector<Observation *> getObservations(); // Or getSimulationObservations()?
            std::vector<IndividualObservations *> getIndividualObservations(); // Or getDatasetObservations()?
            std::vector<ObservationCombination *> getObservationCombinations();
            void accept(PharmMLVisitor *visitor);

        private:
            pharmmlcpp::PharmMLContext *context;
            std::vector<Variable *> designParameters;
            std::vector<Observation *> simulationObservations;
            std::vector<IndividualObservations *> datasetObservations;
            // TODO: Implement support for LookupTable according to schema
            std::vector<ObservationCombination *> observationCombinations;
    };
}

#endif
