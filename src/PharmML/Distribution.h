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

#ifndef PHARMML_DISTRIBUTION_H_
#define PHARMML_DISTRIBUTION_H_

#include <PharmML/PharmMLContext.h>
#include <PharmML/DistributionParameter.h>
#include <AST/Scalar.h>
#include <AST/symbols.h>
#include <visitors/PharmMLVisitor.h>
#include <PharmML/Dependencies.h>

namespace PharmML
{
    class Distribution
    {
        PharmMLContext *context;
        std::string name;
        std::vector<PharmML::DistributionParameter *> parameters;
        Dependencies deps;

        public:
        Distribution(PharmMLContext *context, xml::Node node);
        void parse(xml::Node node);
        std::string getName();
        std::vector<PharmML::DistributionParameter *> getDistributionParameters();
        Dependencies &getDependencies();
        void accept(PharmML::PharmMLVisitor *visitor);
    };
}

#endif