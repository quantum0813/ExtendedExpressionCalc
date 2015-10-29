#ifndef EXTENDEDCALC_TYPE_HPP
#define EXTENDEDCALC_TYPE_HPP

class Type {
    public:
        virtual ~Type() {}; };

class BoolType : public Type {
    public:
        BoolType() {};
};

class IntType : public Type {
    public:
        IntType() {};
};

static BoolType * getBoolType() {
    static BoolType bt;
    return &bt;
}

static IntType * getIntType() {
    static IntType it;
    return &it;
}

#endif //EXTENDEDCALC_TYPE_HPP