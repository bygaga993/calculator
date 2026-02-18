#include<vector>
#include<memory>

class Operation{
    public:
        virtual float change_value(float&) const = 0;
        virtual ~Operation() {};
};

class Add: public Operation{
    private:
        float number;
    public:
        Add(float n): number(n) {};
        float change_value(float&) const override;
};

class Sub: public Operation{
    private:
        float number;
    public:
        Sub(float n): number(n) {};
        float change_value(float&) const override;
};


class Mul: public Operation{
    private:
        float number;
    public:
        Mul(float n): number(n) {};
        float change_value(float&) const override;
};

class Div: public Operation{
    private:
        float number;
    public:
        Div(float n): number(n) {};
        float change_value(float&) const override;
};

class Pow: public Operation{
    private:
        float number;
    public:
        Pow(float n): number(n) {};
        float change_value(float&) const override;
};

class SquareRoot: public Operation{
    public:
        float change_value(float&) const override;
};

class Square: public Operation{
    public:
        float change_value(float&) const override;
};


class Calculator{
    private:
        float start_value;
        std::vector<std::unique_ptr<Operation>> operations;
    
    public:
        Calculator() : start_value(0.0) {};
        Calculator(float number) : start_value(number) {};
        void add_operation(std::unique_ptr<Operation>);
        float return_result();
};