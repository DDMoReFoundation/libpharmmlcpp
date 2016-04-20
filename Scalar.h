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

#ifndef PHARMML_SCALAR_H_
#define PHARMML_SCALAR_H_

#include "AstNode.h"
#include "xml.h"

namespace PharmML
{
    class Scalar : public AstNode
    {

    };

    class ScalarInt : public Scalar
    {
        private:
            int value;

        public:
            ScalarInt(int value);
            ScalarInt(std::string s);
            ScalarInt(xml::Node xml_node);
            std::string toString();
            virtual void accept(AbstractVisitor *visitor);
    };

    class ScalarReal : public Scalar
    {
        private:
            double value;

        public:
            ScalarReal(double value);
            ScalarReal(std::string s);
            ScalarReal(xml::Node xml_node);
            std::string toString();
            virtual void accept(AbstractVisitor *visitor);
    };
}

#endif
