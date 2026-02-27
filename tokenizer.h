#include<string>
#include<vector>
#include<memory>

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
};

class NumberExpr: public Expr {
    private:
        float value;
    public:
        NumberExpr(float v): value(v) {};
        float getNumber() const;
};

class OperatorExpr: public Expr {
    private:
        OperationType type; 
    public:
        OperatorExpr(OperationType t): type(t) {};
        OperationType getType() const;
};

class Parser {
    private:
        std::vector<std::unique_ptr<Expr>> tokens;
    public:
        std::vector<std::unique_ptr<Expr>> parse(std::string);  
};