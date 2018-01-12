// Abstract Factory
//  A utility class that creates an instance of several families of
//  classes. It can also return a factory for a certain group.

//  The Factory Design Pattern is useful in a situation that requires the
//  creation of many different types of objects, all derived from a common base
//  type. The Factory Method defines a method for creating the objects, which
//  subclasses can then override to specify the derived type that will be
//  created. Thus, at run time, the Factory Method can be passed a description
//  of a desired object (e.g., a string read from user input) and return a base
//  class pointer to a new instance of that object. The pattern works best when
//  a well-designed interface is used for the base class, so there is no need to
//  cast the returned object.

// Problem
//  We want to decide at run time what object is to be created based on some
//  configuration or application parameter. When we write the code, we do not
//  know what class should be instantiated.
// Solution
//  Define an interface for creating an object, but let subclasses decide which
//  class to instantiate. Factory Method lets a class defer instantiation to
//  subclasses.

#include <iostream>
#include <memory>
#include <stdexcept>

/* Abstract Base Class */
class Pizza {
public:
    virtual float GetPrice() = 0;
    virtual ~Pizza() {}
};

//----------------------------------------------------------------

class ChickenAndMushroomPizza : public Pizza {
public:
    virtual float GetPrice() {
        return 10.f;
    }
    virtual ~ChickenAndMushroomPizza() {}
};

class HawaiianPizza : public Pizza {
public:
    virtual float GetPrice() {
        return 8.f;
    }
    virtual ~HawaiianPizza() {}
};

class NapolitanPizza : public Pizza {
public:
    virtual float GetPrice() {
        return 9.f;
    }
    virtual ~NapolitanPizza() {}
};

//----------------------------------------------------------------

enum class PizzaType { ChickenAndMushroom, Hawaiian, Napolitan };

class PizzaFactory {
public:
    static std::unique_ptr<Pizza> CreatePizza(PizzaType type) {
        switch (type) {
            case PizzaType::ChickenAndMushroom:
                return std::make_unique<ChickenAndMushroomPizza>();
            case PizzaType::Hawaiian:
                return std::make_unique<HawaiianPizza>();
            case PizzaType::Napolitan:
                return std::make_unique<NapolitanPizza>();
        }
        throw "invalid pizza type.";
    }
};

int main(void) {
    std::unique_ptr<Pizza> pizza1, pizza2, pizza3;
    pizza1 = PizzaFactory::CreatePizza(PizzaType::ChickenAndMushroom);
    pizza2 = PizzaFactory::CreatePizza(PizzaType::Hawaiian);
    pizza3 = PizzaFactory::CreatePizza(PizzaType::Napolitan);

    std::cout << "The price of ChickenAndMushroom is " << pizza1->GetPrice()
              << " USD." << std::endl;
    std::cout << "The price of Hawaiian is " << pizza2->GetPrice() << " USD."
              << std::endl;
    std::cout << "The price of Napolitan is " << pizza3->GetPrice() << " USD."
              << std::endl;

    return 0;
}
