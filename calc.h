#include<map>
#include<memory>

class Operation{
    public:
        virtual float change_value(float left, float right) const = 0;
        virtual ~Operation() = default;
};

class Add: public Operation{
    public:
        float change_value(float left, float right) const override;
};

class Sub: public Operation{
    public:
        float change_value(float left, float right) const override;
};


class Mul: public Operation{
    public:
        float change_value(float left, float right) const override;
};

class Div: public Operation{
    public:
        float change_value(float left, float right) const override;
};

class Pow: public Operation{
    public:
        float change_value(float left, float right) const override;
};



class Calculator{
    private:
        float start_value;
        std::map<std::string, std::unique_ptr<Operation>> registry;
    
    public:
        Calculator() : start_value(0.0) {};
        Calculator(float number) : start_value(number) {};
        template <class T>
        Calculator& Calculator::RegisterOperation(std::string name) noexcept {
            registry.emplace(std::move(name), std::make_unique<T>());
            return *this;
        }
        const std::unique_ptr<Operation>& GetOperationByName(std::string name) const;
};