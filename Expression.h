#pragma once
enum OperationType {
    Plus,
    Minus,
    Mul,
    Div, 
    LParen,
    RParen
};

class Expr {
    public:
        virtual ~Expr() = default;
        virtual bool IsNumber() const = 0;
        virtual void Print() const = 0;
        virtual float AsNumber() const = 0;
        virtual OperationType AsOperation() const = 0;
};

class NumberExpr: public Expr {
    private:
        float value;
    public:
        NumberExpr(float v): value(v) {};
        float getNumber() const;
        bool IsNumber() const;
        void Print() const;
        float AsNumber() const;
        virtual OperationType AsOperation() const;
};

class OperatorExpr: public Expr {
    private:
        OperationType type; 
    public:
        bool operator<(const OperatorExpr& other) const {
            return type < other.type;
        }
        
        OperatorExpr(OperationType t): type(t) {};
        OperationType getType() const;
        bool IsNumber() const;
        void Print() const;
        float AsNumber() const;
        OperationType AsOperation() const;
};