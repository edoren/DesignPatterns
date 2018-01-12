// Builder
//  The Builder Creational Pattern is used to separate the construction of a
//  complex object from its representation so that the same construction process
//  can create different objects representations.

// Problem
//  We want to construct a complex object, however we do not want to have a
//  complex constructor member or one that would need many arguments.
// Solution
//  Define an intermediate object whose member functions define the desired
//  object part by part before the object is available to the client. Builder
//  Pattern lets us defer the construction of the object until all the options
//  for creation have been specified.

#include <iostream>
#include <memory>
#include <string>

// "Product"
class Pizza {
public:
    void SetDoug(const std::string& dough) {
        m_dough = dough;
    }
    void SetSauce(const std::string& sauce) {
        m_sauce = sauce;
    }
    void SetTopping(const std::string& topping) {
        m_topping = topping;
    }
    void open() const {
        std::cout << "Pizza with " << m_dough << " dough, " << m_sauce
                  << " sauce and " << m_topping << " topping. Mmm."
                  << std::endl;
    }

private:
    std::string m_dough;
    std::string m_sauce;
    std::string m_topping;
};

// "Abstract Builder"
class PizzaBuilder {
public:
    virtual ~PizzaBuilder() {}
    Pizza* GetPizza() {
        return m_pizza.get();
    }
    void CreateNewPizzaProduct() {
        m_pizza = std::make_unique<Pizza>();
    }
    virtual void BuildDough() = 0;
    virtual void BuildSauce() = 0;
    virtual void BuildTopping() = 0;

protected:
    std::unique_ptr<Pizza> m_pizza;
};

//----------------------------------------------------------------

class HawaiianPizzaBuilder : public PizzaBuilder {
public:
    virtual ~HawaiianPizzaBuilder() {}
    virtual void BuildDough() {
        m_pizza->SetDoug("cross");
    }
    virtual void BuildSauce() {
        m_pizza->SetSauce("mild");
    }
    virtual void BuildTopping() {
        m_pizza->SetTopping("ham+pineapple");
    }
};
class SpicyPizzaBuilder : public PizzaBuilder {
public:
    virtual ~SpicyPizzaBuilder() {}
    virtual void BuildDough() {
        m_pizza->SetDoug("pan baked");
    }
    virtual void BuildSauce() {
        m_pizza->SetSauce("hot");
    }
    virtual void BuildTopping() {
        m_pizza->SetTopping("pepperoni+salami");
    }
};

//----------------------------------------------------------------

class Cook {
public:
    void OpenPizza() {
        m_pizzaBuilder->GetPizza()->open();
    }
    void MakePizza(PizzaBuilder* pb) {
        m_pizzaBuilder = pb;
        m_pizzaBuilder->CreateNewPizzaProduct();
        m_pizzaBuilder->BuildDough();
        m_pizzaBuilder->BuildSauce();
        m_pizzaBuilder->BuildTopping();
    }

private:
    PizzaBuilder* m_pizzaBuilder;
};

int main() {
    Cook cook;
    HawaiianPizzaBuilder hawaiianPizzaBuilder;
    SpicyPizzaBuilder spicyPizzaBuilder;

    cook.MakePizza(&hawaiianPizzaBuilder);
    cook.OpenPizza();

    cook.MakePizza(&spicyPizzaBuilder);
    cook.OpenPizza();
}
