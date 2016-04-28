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

#ifndef PHARMML_MODEL_H_
#define PHARMML_MODEL_H_

#ifndef PHARMML_PHARMMLCONTEXT_H_
#include "PharmMLContext.h"
#endif

#include "IndependentVariable.h"
#include "FunctionDefinition.h"
#include "ModelDefinition.h"
#include "TrialDesign.h"
#include "xml.h"

namespace PharmML
{
    class Model
    {
        PharmMLContext *context;
        PharmML::IndependentVariable *IndependentVariable;
        std::vector<PharmML::FunctionDefinition *> FunctionDefinitions; 
        PharmML::ModelDefinition *ModelDefinition;
        PharmML::TrialDesign *TrialDesign;

        private:
        void parse(xml::Node node);

        public:
        Model(const char *filename);
        ~Model();
        void write(const char *filename);
        PharmML::IndependentVariable *getIndependentVariable();
        std::vector<PharmML::FunctionDefinition *> getFunctionDefinitions();
        PharmML::ModelDefinition *getModelDefinition();
        PharmML::TrialDesign *getTrialDesign();
    };
}

#endif
