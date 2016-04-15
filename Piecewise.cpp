#include "Piecewise.h"

namespace PharmML
{
    Piece::Piece() {
        
    }

    void Piece::setExpression(AstNode *expression) {
        this->expression = expression;
    }

    void Piece::setCondition(AstNode *condition) {
        this->condition = condition;   
    }
    
    void Piece::setOtherwise() {
        otherwise = true;
    }

    AstNode *Piece::getExpression() {
        return this->expression;
    }

    AstNode *Piece::getCondition() {
        return this->condition;
    }
    
    bool Piece::isOtherwise() {
        return otherwise;
    }

    void Piece::accept(AbstractVisitor *visitor) {
        visitor->visit(this);
    }

    Piecewise::Piecewise() {

    }

    void Piecewise::addPiece(Piece *piece) {
        this->pieces.push_back(piece);
    }

    std::vector<Piece *> Piecewise::getPieces() {
        return this->pieces;
    }

    void Piecewise::accept(AbstractVisitor *visitor) {
        visitor->visit(this);
    }
}
