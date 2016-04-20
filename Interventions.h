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

#ifndef PHARMML_INTERVENTIONS_H_
#define PHARMML_INTERVENTIONS_H_

#include "xml.h"
#include "PharmMLContext.h"
#include "AstNode.h"
#include "symbols.h"

namespace PharmML
{
    // TODO: Maybe move this somewhere?
    class SteadyStateParameter : public AstNode
    {
        AstNode *assignment = nullptr;
        SymbRef *symbRef = nullptr;

        protected:
        PharmML::PharmMLContext *context;

        public:
        SteadyStateParameter(PharmMLContext *context, xml::Node node);
        void parse(xml::Node node);
        AstNode *getAssignment();
        AstNode *getSymbRef();
        void accept(AbstractVisitor *visitor);
    };
    
    // TODO: Move elsewhere (Dataset.h when implemented)
    // TODO: Subclass for MapType? Subclass for SymbRef? Container? It's a bit
    // weird to piggyback on AstNode instead of dedicated reference class
    // and it would need to be resolved
    class TargetMapping : public AstNode
    {
        PharmML::PharmMLContext *context;
        std::string type;
        std::string blkIdRef;
        std::string ref;
        
        public:
        TargetMapping(PharmMLContext *context, std::string type, xml::Node node);
        std::string getType();
        std::string getBlkIdRef();
        std::string getRef();
        void accept(AbstractVisitor *visitor);
    };
    
    
    class Administration
    {
        PharmML::PharmMLContext *context;
        std::string oid;
        std::string type;
        AstNode *amount = nullptr;
        AstNode *target = nullptr; // Should probably be parent class of TargetMapping
        AstNode *times = nullptr;
        AstNode *steady = nullptr;
        AstNode *duration = nullptr;
        AstNode *rate = nullptr;
        
        public:
        Administration(PharmMLContext *context, xml::Node node);
        void parse(xml::Node node);
        std::string getOid();
        std::string getType();
        AstNode *getTarget();
        AstNode *getTimes();
        AstNode *getSteady();
        AstNode *getDuration();
        AstNode *getRate();
        void accept(AbstractVisitor *visitor);
    };
    
    class Interventions
    {
        PharmML::PharmMLContext *context;
        std::vector<PharmML::Administration *> Administrations;

        public:
        Interventions(PharmMLContext *context, xml::Node node);
        void parse(xml::Node node);
        std::vector<Administration *> getAdministrations();
        void accept(AbstractVisitor *visitor);
    };
}

#endif
