/**
 * Copyright 2015 Eric Vestfals
 * esv5@zips.uakron.edu
 *
 * AST.hpp
 *
 * This class lays out the classes that make up the grammar for the calculator
 * language. Every class inherits from the base class "Expression". Number
 * inherits Expression directly while the rest of the class inherit from
 * "BinaryExpr" which in turn inherits from Expression.
 */

#ifndef AST_HPP
#define AST_HPP

#include <iostream>
//#include <deque>
#include "Type.hpp"

using namespace std;

// Have to forward declare all this shit
class Expression;
class Value;
class UnaryExpression;
class BinaryExpression;
class NegationExpression;
class PositiveExpression;
class NotExpression;
class BinaryExpression;
class AdditionExpression;
class SubtractionExpression;
class MultiplicationExpression;
class DivisionExpression;
class ModExpression;
class LogicalOrExpression;
class LogicalAndExpression;
class EqualExpression;
class NotEqualExpression;
class GreaterThanExpression;
class LessThanExpression;
class GreaterThanEqualExpression;
class LessThanEqualExpression;

class Visitor {
    public:
        virtual void visit(Expression *) = 0;
        virtual void visit(Value *) = 0;
        virtual void visit(UnaryExpression *) = 0;
        virtual void visit(BinaryExpression *) = 0;
        virtual void visit(NegationExpression *) = 0;
        virtual void visit(PositiveExpression *) = 0;
        virtual void visit(NotExpression *) = 0;
        virtual void visit(AdditionExpression *) = 0;
        virtual void visit(SubtractionExpression *) = 0;
        virtual void visit(MultiplicationExpression *) = 0;
        virtual void visit(DivisionExpression *) = 0;
        virtual void visit(ModExpression *) = 0;
        virtual void visit(LogicalOrExpression *) = 0;
        virtual void visit(LogicalAndExpression *) = 0;
        virtual void visit(EqualExpression *) = 0;
        virtual void visit(NotEqualExpression *) = 0;
        virtual void visit(GreaterThanExpression *) = 0;
        virtual void visit(LessThanExpression *) = 0;
        virtual void visit(GreaterThanEqualExpression *) = 0;
        virtual void visit(LessThanEqualExpression *) = 0;
};

class VisitableNode {
    virtual void accept(Visitor *) = 0;
};

class Expression : public VisitableNode {
    public:
        void accept(Visitor * v) {}
        virtual int evaluate() const = 0;
};


class Value : public Expression, VisitableNode {
    public:
        Value(int val) : mValue(val) {}
        Value(bool val) : mValue(val ? 1 : 0) {}
        void accept(Visitor * v) {
            v->visit(this);
        }
        int evaluate() const {
            return mValue;
        }

    private:
        int mValue;
};

class UnaryExpression : public Expression, VisitableNode {
    public:
        UnaryExpression(Expression * l) : mExpr(l) {}
        Expression * getExpression() const {
            return mExpr;
        }
        void accept(Visitor * v) {}
    protected:
        Expression * mExpr;
};

class BinaryExpression : public Expression, VisitableNode {
    public:
        BinaryExpression(Expression * l, Expression * r) : mLeft(l), mRight(r) {}
        Expression * getLeft() const {
            return mLeft;
        }
        Expression * getRight() const {
            return mRight;
        }
        void accept(Visitor * v) {}
    protected:
        Expression * mLeft;
        Expression * mRight;
};

class NegationExpression : public UnaryExpression, VisitableNode {
    public:
        NegationExpression(Expression * val) : UnaryExpression(val) {}
        int evaluate() const {
            return -mExpr->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class PositiveExpression : public UnaryExpression, VisitableNode {
    public:
        PositiveExpression(Expression * val) : UnaryExpression(val) {}
        int evaluate() const {
            return +mExpr->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class NotExpression : public UnaryExpression, VisitableNode {
    public:
        NotExpression(Expression * val) : UnaryExpression(val) {}
        int evaluate() const {
            bool val = (mExpr->evaluate() != 0);
            return !val;
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class AdditionExpression : public BinaryExpression, VisitableNode {
    public:
        AdditionExpression(Expression * l, Expression * r) : BinaryExpression(l, r) { }
        int evaluate() const {
            return mLeft->evaluate() + mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class SubtractionExpression : public BinaryExpression, VisitableNode {
    public:
        SubtractionExpression(Expression * l, Expression * r) : BinaryExpression(l, r) { }
        int evaluate() const {
            return mLeft->evaluate() - mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class MultiplicationExpression : public BinaryExpression, VisitableNode {
    public:
        MultiplicationExpression(Expression * l, Expression * r) : BinaryExpression(l, r) { }
        int evaluate() const {
            return mLeft->evaluate() * mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class DivisionExpression : public BinaryExpression, VisitableNode {
    public:
        DivisionExpression(Expression * l, Expression * r) : BinaryExpression(l, r) { }
        int evaluate() const {
            return mLeft->evaluate() / mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class ModExpression : public BinaryExpression, VisitableNode {
    public:
        ModExpression(Expression * l, Expression * r) : BinaryExpression(l, r) { }
        int evaluate() const {
            return mLeft->evaluate() % mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class LogicalOrExpression : public BinaryExpression, VisitableNode {
    public:
        LogicalOrExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
        int evaluate() const {
            bool lhs = (mLeft->evaluate() != 0);
            bool rhs = (mRight->evaluate() != 0);
            return lhs || rhs;
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class LogicalAndExpression : public BinaryExpression, VisitableNode {
    public:
        LogicalAndExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
        int evaluate() const {
            bool lhs = (mLeft->evaluate() != 0);
            bool rhs = (mRight->evaluate() != 0);
            return lhs && rhs;
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class EqualExpression : public BinaryExpression, VisitableNode {
    public:
        EqualExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
        int evaluate() const {
            return mLeft->evaluate() == mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class NotEqualExpression : public BinaryExpression, VisitableNode {
    public:
        NotEqualExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
        int evaluate() const {
            return mLeft->evaluate() != mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class GreaterThanExpression : public BinaryExpression, VisitableNode {
    public:
        GreaterThanExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
        int evaluate() const {
            return mLeft->evaluate() > mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class LessThanExpression : public BinaryExpression, VisitableNode {
    public:
        LessThanExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
        int evaluate() const {
            return mLeft->evaluate() < mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class GreaterThanEqualExpression : public BinaryExpression, VisitableNode {
    public:
        GreaterThanEqualExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
        int evaluate() const {
            return mLeft->evaluate() >= mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class LessThanEqualExpression : public BinaryExpression, VisitableNode {
    public:
        LessThanEqualExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
        int evaluate() const {
            return mLeft->evaluate() <= mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class EvaluateVisitor : public Visitor {
    void visit(Expression * val) {}
    void visit(UnaryExpression * val) {}
    void visit(BinaryExpression * val) {}

    void visit(Value * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void visit(NegationExpression * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void visit(PositiveExpression * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void visit(AdditionExpression * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void visit(SubtractionExpression * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void visit(MultiplicationExpression * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void visit(DivisionExpression * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void visit(ModExpression * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void visit(LogicalOrExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void visit(LogicalAndExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void visit(EqualExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void visit(NotEqualExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void visit(GreaterThanExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void visit(LessThanExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void visit(GreaterThanEqualExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void visit(LessThanEqualExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void visit(NotExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
};

#endif