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

#ifndef PHARMML_DERIVATIVEVARIABLE_H_
#define PHARMML_DERIVATIVEVARIABLE_H_

#include <PharmML/PharmMLContext.h>
#include <symbols/Variable.h>
#include <visitors/PharmMLVisitor.h>

namespace PharmML
{
    class DerivativeVariable : public CommonVariable
    {
        AstNode *independent_variable;
        AstNode *initial_value;
        AstNode *initial_time;

        public:
        DerivativeVariable(PharmMLContext *context, xml::Node node) : CommonVariable(context, node) { is_derivative = true; this->parse(node); };
        AstNode *getIndependentVariable();
        AstNode *getInitialValue();
        AstNode *getInitialTime();
        void parse(xml::Node node);
        void gatherSymbRefs(std::unordered_map<std::string, Symbol *> symbolMap);
        void accept(PharmMLVisitor *visitor); 
        void accept(SymbolVisitor *visitor); 
    };
}

#endif
