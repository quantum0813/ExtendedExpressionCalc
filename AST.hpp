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

/*#ifndef AST_HPP
#define AST_HPP

#include <iostream>
//#include <deque>
#include "Type.hpp"

using namespace std;

// Have to forward declare all this shit
class Expression;
class IntExpression;
class BoolExpression;
class OrderingEqualityBase;
class OrderingEqualityExpression;
class IntValue;
class BoolValue;
class UnaryIntExpression;
class UnaryBoolExpression;
class NegationExpression;
class PositiveExpression;
class NotExpression;
class BinaryIntExpression;
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
        virtual void visit(IntExpression *) = 0;
        virtual void visit(BoolExpression *) = 0;
        virtual void visit(OrderingEqualityBase *) = 0;
        virtual void visit(OrderingEqualityExpression *) = 0;
        virtual void visit(IntValue *) = 0;
        virtual void visit(BoolValue *) = 0;
        virtual void visit(UnaryIntExpression *) = 0;
        virtual void visit(UnaryBoolExpression *) = 0;
        virtual void visit(NegationExpression *) = 0;
        virtual void visit(PositiveExpression *) = 0;
        virtual void visit(NotExpression *) = 0;
        virtual void visit(BinaryIntExpression *) = 0;
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
};

class IntExpression : public Expression, VisitableNode {
    public:
        void accept(Visitor * v) { }
        virtual int evaluate() const = 0;
};

class BoolExpression : public Expression, VisitableNode {
    public:
        void accept(Visitor * v) {}
        virtual bool evaluate() const = 0;
};

class OrderingEqualityBase : public Expression, VisitableNode {
    public:
        void accept(Visitor * v) {};
        virtual bool evaluate() const = 0;
};

class OrderingEqualityExpression : public OrderingEqualityBase, VisitableNode {
    public:
        OrderingEqualityExpression(IntExpression * l, IntExpression * r) : mLeft(l), mRight(r) {}
        IntExpression * getLeft() const {
            return mLeft;
        }
        IntExpression * getRight() const {
            return mRight;
        }

    protected:
        IntExpression * mLeft;
        IntExpression * mRight;
};

class IntValue : public IntExpression, VisitableNode {
    public:
        IntValue(int val) : mValue(val) {}
        void accept(Visitor * v) {
            v->visit(this);
        }
        int evaluate() const {
            return mValue;
        }
    private:
        int mValue;
};

class BoolValue : public BoolExpression, VisitableNode {
    public:
        BoolValue(bool val) : mValue(val) {}
        void accept(Visitor * v) {
            v->visit(this);
        }
        bool evaluate() const {
            return mValue;
        }
    private:
        bool mValue;
};

class UnaryIntExpression : public IntExpression, VisitableNode {
    public:
        UnaryIntExpression(IntExpression * expr) : mExpr(expr) {}
        IntExpression * getExpression() const {
            return mExpr;
        }
        void accept(Visitor * v) {}
    protected:
        IntExpression * mExpr;
};

class UnaryBoolExpression : public BoolExpression, VisitableNode {
    public:
        UnaryBoolExpression(BoolExpression * expr) : mExpr(expr) {}
        BoolExpression * getExpression() const {
            return mExpr;
        }
        void accept(Visitor * v) {}
    protected:
        BoolExpression * mExpr;
};

class NegationExpression : public UnaryIntExpression, VisitableNode {
    public:
        NegationExpression(IntExpression * val) : UnaryIntExpression(val) {}
        int evaluate() const {
            return -mExpr->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class PositiveExpression : public UnaryIntExpression, VisitableNode {
    public:
        PositiveExpression(IntExpression * val) : UnaryIntExpression(val) {}
        int evaluate() const {
            return +mExpr->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class NotExpression : public UnaryBoolExpression, VisitableNode {
    public:
        NotExpression(BoolExpression * val) : UnaryBoolExpression(val) {}
        bool evaluate() const {
            return !mExpr->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class BinaryIntExpression : public IntExpression, VisitableNode {
    public:
        BinaryIntExpression(IntExpression * l, IntExpression * r) : mLeft(l), mRight(r) {}
        IntExpression * getLeft() const {
            return mLeft;
        }
        IntExpression * getRight() const {
            return mRight;
        }
        void accept(Visitor * v) {}

    protected:
        IntExpression * mLeft;
        IntExpression * mRight;
};

class BinaryBoolExpression : public BoolExpression, VisitableNode {
    public:
        BinaryBoolExpression(BoolExpression * l, BoolExpression * r) : mLeft(l), mRight(r) {}
        BoolExpression * getLeft() const {
            return mLeft;
        }
        BoolExpression * getRight() const {
            return mRight;
        }
        void accept(Visitor * v) {}
    protected:
        BoolExpression * mLeft;
        BoolExpression * mRight;
};

class AdditionExpression : public BinaryIntExpression, VisitableNode {
    public:
        AdditionExpression(IntExpression * l, IntExpression * r) : BinaryIntExpression(l, r) { }
        int evaluate() const {
            return mLeft->evaluate() + mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class SubtractionExpression : public BinaryIntExpression, VisitableNode {
    public:
        SubtractionExpression(IntExpression * l, IntExpression * r) : BinaryIntExpression(l, r) { }
        int evaluate() const {
            return mLeft->evaluate() - mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class MultiplicationExpression : public BinaryIntExpression, VisitableNode {
    public:
        MultiplicationExpression(IntExpression * l, IntExpression * r) : BinaryIntExpression(l, r) { }
        int evaluate() const {
            return mLeft->evaluate() * mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class DivisionExpression : public BinaryIntExpression, VisitableNode {
    public:
        DivisionExpression(IntExpression * l, IntExpression * r) : BinaryIntExpression(l, r) { }
        int evaluate() const {
            return mLeft->evaluate() / mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class ModExpression : public BinaryIntExpression, VisitableNode {
    public:
        ModExpression(IntExpression * l, IntExpression * r) : BinaryIntExpression(l, r) { }
        int evaluate() const {
            return mLeft->evaluate() % mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class LogicalOrExpression : public BinaryBoolExpression, VisitableNode {
    public:
        LogicalOrExpression(BoolExpression * l, BoolExpression * r) : BinaryBoolExpression(l, r) {}
        bool evaluate() const {
            return mLeft->evaluate() || mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class LogicalAndExpression : public BinaryBoolExpression, VisitableNode {
    public:
        LogicalAndExpression(BoolExpression * l, BoolExpression * r) : BinaryBoolExpression(l, r) {}
        bool evaluate() const {
            return mLeft->evaluate() && mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class EqualExpression : public OrderingEqualityExpression, VisitableNode {
    public:
        EqualExpression(IntExpression * l, IntExpression * r) : OrderingEqualityExpression(l, r) {}
        bool evaluate() const {
            return mLeft->evaluate() == mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class NotEqualExpression : public OrderingEqualityExpression, VisitableNode {
    public:
        NotEqualExpression(IntExpression * l, IntExpression * r) : OrderingEqualityExpression(l, r) {}
        bool evaluate() const {
            return mLeft->evaluate() != mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class GreaterThanExpression : public OrderingEqualityExpression, VisitableNode {
    public:
        GreaterThanExpression(IntExpression * l, IntExpression * r) : OrderingEqualityExpression(l, r) {}
        bool evaluate() const {
            return mLeft->evaluate() > mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class LessThanExpression : public OrderingEqualityExpression, VisitableNode {
    public:
        LessThanExpression(IntExpression * l, IntExpression * r) : OrderingEqualityExpression(l, r) {}
        bool evaluate() const {
            return mLeft->evaluate() < mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class GreaterThanEqualExpression : public OrderingEqualityExpression, VisitableNode {
    public:
        GreaterThanEqualExpression(IntExpression * l, IntExpression * r) : OrderingEqualityExpression(l, r) {}
        bool evaluate() const {
            return mLeft->evaluate() >= mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class LessThanEqualExpression : public OrderingEqualityExpression, VisitableNode {
    public:
        LessThanEqualExpression(IntExpression * l, IntExpression * r) : OrderingEqualityExpression(l, r) {}
        bool evaluate() const {
            return mLeft->evaluate() <= mRight->evaluate();
        }
        void accept(Visitor * v) {
            v->visit(this);
        }
};

class EvaluateVisitor : public Visitor {
    void visit(Expression * val) {}
    void visit(IntExpression * val) {}
    void visit(BoolExpression * val) {}
    void visit(UnaryIntExpression * val) {}
    void visit(UnaryBoolExpression * val) {}
    void visit(OrderingEqualityBase * val) {}
    void visit(BinaryIntExpression * val) {}
    void visit(OrderingEqualityExpression * val) {}

    void visit(IntValue * val) {
        std::cout << val->evaluate() << std::endl;
    }
    void visit(BoolValue * val) {
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

#endif*/


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