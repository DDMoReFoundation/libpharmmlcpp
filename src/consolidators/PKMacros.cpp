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

#include "PKMacros.h"

namespace CPharmML
{
    // Construct with PKMacro's as base
    PKMacros::PKMacros(std::vector<PharmML::PKMacro *> pk_macros) {
        this->pk_macros.reserve(pk_macros.size());
        this->pk_macros.insert(this->pk_macros.begin(), pk_macros.begin(), pk_macros.end());
    }
    
    // Validate the internals
    void PKMacros::validate(const std::shared_ptr<PharmML::Logger> &logger) {
        for (PharmML::PKMacro *macro : this->pk_macros) {
            std::string name = macro->getName();
            for (PharmML::MacroValue value : macro->getValues()) {
                if (value.first == "") {
                    logger->warning("PK macro '" + name + "' has a value without attribute type", macro);
                }
            }
        }
    }
    
    // Get PharmML objects used to consolidate
    std::vector<PharmML::PKMacro *> PKMacros::getMacros() {
        return this->pk_macros;
    }
    
    PharmML::PKMacro *PKMacros::getCompartment(int cmt_num) {
        
    }
    
    // Get attributes
    
}
