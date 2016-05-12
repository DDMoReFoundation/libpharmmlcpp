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

#ifndef PHARMML_SYMBREFFINDER_H_
#define PHARMML_SYMBREFFINDER_H_

#include <string>
#include <visitors/AstNodeVisitor.h>
#include <AST/symbols.h>

namespace PharmML
{
    class SymbRefFinder : public AstNodeVisitor
    {
        private:
            std::unordered_set<SymbRef *> symbRefs;

        public:
            std::unordered_set<SymbRef *> getSymbRefs();

            virtual void visit(SymbRef *node);
    };
}

#endif