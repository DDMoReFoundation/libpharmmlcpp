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

#include "ParameterModel.h"
#include <visitors/AstAnalyzer.h>
#include <AST/AstBuilder.h>
#include <iostream>

namespace pharmmlcpp
{
    ParameterModel::ParameterModel(PharmMLReader &reader, xml::Node node) {
        this->parse(reader, node);
    }

    void ParameterModel::parse(PharmMLReader &reader, xml::Node node) {
        this->Block::parse(node);
        std::vector<xml::Node> param_nodes = reader.getElements(node, "./mdef:Parameter");
        for (xml::Node n : param_nodes) {
            Parameter *param = new Parameter(reader, n);
            this->parameters.push_back(param);
        }

        std::vector<xml::Node> pop_nodes = reader.getElements(node, "./mdef:PopulationParameter");
        for (xml::Node n : pop_nodes) {
            pharmmlcpp::PopulationParameter *pop = new PopulationParameter(reader, n);
            this->populationParameters.push_back(pop);
        }

        std::vector<xml::Node> ind_nodes = reader.getElements(node, "./mdef:IndividualParameter");
        for (xml::Node n : ind_nodes) {
            pharmmlcpp::IndividualParameter *ind = new IndividualParameter(reader, n);
            this->individualParameters.push_back(ind);
        }

        std::vector<xml::Node> rand_nodes = reader.getElements(node, "./mdef:RandomVariable");
        for (xml::Node n : rand_nodes) {
            pharmmlcpp::RandomVariable *ind = new RandomVariable(reader, n);
            this->randomVariables.push_back(ind);
        }

        std::vector<xml::Node> corr_nodes = reader.getElements(node, "./mdef:Correlation");
        for (xml::Node n : corr_nodes) {
            pharmmlcpp::Correlation *ind = new Correlation(reader, n);
            this->correlations.push_back(ind);
        }
    }

    void ParameterModel::setupRefererSymbRefs(SymbolGathering &gathering) {
        // Only Correlation in ParameterModel are Referer's (and not Symbol's)
        for (pharmmlcpp::Correlation *corr : this->getCorrelations()) {
            corr->setupSymbRefs(gathering, this->getBlkId());
        }
    }

    void ParameterModel::gatherSymbols(SymbolGathering &gatherer) {
        gatherer.newBlock(this);
        for (Parameter *parameter : this->parameters) {
            gatherer.addSymbol(parameter);
        }
        for (PopulationParameter *parameter : this->populationParameters) {
            gatherer.addSymbol(parameter);
        }
        for (IndividualParameter *parameter : this->individualParameters) {
            gatherer.addSymbol(parameter);
        }
        for (RandomVariable *rv : this->randomVariables) {
            gatherer.addSymbol(rv);
        }
    }

    std::vector<Parameter *> ParameterModel::getParameters() {
        return this->parameters;
    }

    std::vector<PopulationParameter *> ParameterModel::getPopulationParameters() {
        return this->populationParameters;
    }

    std::vector<IndividualParameter *> ParameterModel::getIndividualParameters() {
        return this->individualParameters;
    }

    std::vector<RandomVariable *> ParameterModel::getRandomVariables() {
        return this->randomVariables;
    }

    std::vector<Correlation *> ParameterModel::getCorrelations() {
        return this->correlations;
    }

    // Return the the initial covariance between var1 and var2 given a vector of parameterEstimations
    // FIXME: How to now which correlations are applicable? Can correlations from other ParameterModel apply?
    AstNode *ParameterModel::initialCovariance(RandomVariable *var1, RandomVariable *var2, std::vector<ParameterEstimation *> parameterEstimations) {
        for (Correlation *correlation : this->correlations) {
            if (correlation->isPairwise()) {
                Symbol *symbol_1 = correlation->getPairwiseSymbRefs()[0]->getSymbol();
                Symbol *symbol_2 = correlation->getPairwiseSymbRefs()[1]->getSymbol();
                // Is this the correlation we are searching for?
                if ((symbol_1 == var1 && symbol_2 == var2) || (symbol_2 == var1 && symbol_1 == var2)) {
                    std::shared_ptr<AstNode> assignment = correlation->getPairwiseAssignment();
                    AstAnalyzer analyzer;
                    assignment->accept(&analyzer);
                    if (analyzer.getPureScalar() && correlation->getPairwiseType() == "Covariance") {
                        // A scalar covariance
                        return analyzer.getPureScalar();
                    } else if (analyzer.getPureScalar() && correlation->getPairwiseType() == "CorrelationCoefficient") {
                        // A scalar correlation coefficient
                        // cov(X,Y) = cor(X,Y) * stdev(X) * stdev(Y)
                        // Have method initialStdev on a RandomVariable with parameterEstimations as argument
                        std::vector<AstNode *> multiplicands;
                        multiplicands.push_back(analyzer.getPureScalar());
                        multiplicands.push_back(var1->initialStdev(parameterEstimations));
                        multiplicands.push_back(var2->initialStdev(parameterEstimations));
                        AstNode *cov = AstBuilder::multiplyMany(multiplicands);
                        return cov;
                    } else if (analyzer.getPureSymbRef() && correlation->getPairwiseType() == "Covariance") {
                        Symbol *symbol = analyzer.getPureSymbRef()->getSymbol();
                        // FIXME: Better way of parameterEstimations lookup
                        for (ParameterEstimation *pe : parameterEstimations) {
                            if (pe->getSymbRef()->getSymbol() == symbol) {
                                return pe->getInitValue().get();        // FIXME: Ownership?
                            }
                        }
                        return new ScalarInt(0);    // FIXME: What to do when we cannot find initial value
                    } else if (analyzer.getPureSymbRef() && correlation->getPairwiseType() == "CorrelationCoefficient") {
                        Symbol *symbol = analyzer.getPureSymbRef()->getSymbol();
                        for (ParameterEstimation *pe : parameterEstimations) {
                            if (pe->getSymbRef()->getSymbol() == symbol) {
                                std::vector<AstNode *> multiplicands;
                                multiplicands.push_back(pe->getInitValue().get());
                                multiplicands.push_back(var1->initialStdev(parameterEstimations));
                                multiplicands.push_back(var2->initialStdev(parameterEstimations));
                                return AstBuilder::multiplyMany(multiplicands);
                            }
                        }
                        return new ScalarInt(0);    // FIXME: What to do when we cannot find initial value
                    }
                }
            } else {
                // TODO
                return nullptr;
            }
        }
        return new ScalarInt(0);        // No covariance 
    }
}
