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

#include "FunctionCall.h"

namespace PharmML
{
    void FunctionCall::accept(AstNodeVisitor *visitor) {
        visitor->visit(this);
    }

    void FunctionCall::setFunction(SymbRef *node) {
        this->function = node;
    }

    SymbRef *FunctionCall::getFunction() {
        return this->function;
    }

    void FunctionCall::addFunctionArgument(FunctionArgument *farg) {
        this->functionArguments.push_back(farg);
    }

    void FunctionCall::gatherSymbRefs(std::unordered_map<std::string, Symbol *> &symbolMap) {
        PharmML::Symbol *found_symbol = this->addSymbRef(this->function, symbolMap);
        this->addReference(found_symbol);
        for (FunctionArgument *arg : this->functionArguments) {
            arg->gatherSymbRefs(symbolMap);
            std::unordered_set<PharmML::Symbol *> found_symbols = this->symbRefsFromAst(arg, symbolMap);
            this->addReferences(found_symbols);
        }
    }

    std::vector<FunctionArgument *> FunctionCall::getFunctionArguments() {
        return this->functionArguments;
    }

    void FunctionArgument::setSymbId(std::string symbId) {
        this->symbId = symbId;
    }

    std::string FunctionArgument::getSymbId() {
        return this->symbId;
    }

    void FunctionArgument::setArgument(AstNode *node) {
        this->argument = node;
    }

    AstNode *FunctionArgument::getArgument() {
        return this->argument;
    }

    void FunctionArgument::gatherSymbRefs(std::unordered_map<std::string, Symbol *> &symbolMap) {
        std::unordered_set<PharmML::Symbol *> found_symbols = this->symbRefsFromAst(this->argument, symbolMap);
        this->addReferences(found_symbols);
    }

    void FunctionArgument::accept(AstNodeVisitor *visitor) {
        visitor->visit(this);
    }
}
