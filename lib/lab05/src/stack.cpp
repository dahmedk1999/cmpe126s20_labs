#include "stack.h"
namespace lab5{
    stack::stack() {
        //storage_structure;
    }

    stack::stack(std::string &data) {
        storage_structure.append(data);
    }

    stack::stack(const stack &original) {
//        this->storage_structure=original.storage_structure;
        for (unsigned i = 0; i < original.storage_structure.listSize(); i++)
        {
            this->storage_structure.append(original.storage_structure.get_value_at(i));
        }
    }

    stack::~stack() {
        //use linked list destructor
    }

    stack &stack::operator=(const stack &RHS) {
        //return <#initializer#>;
        if(this==&RHS)
            return *this;
        storage_structure.operator=(RHS.storage_structure);
        return *this;
    }

    bool stack::isEmpty() const {
        return storage_structure.isEmpty();
    }

    unsigned stack::stackSize() const {
        return storage_structure.listSize();
    }

    std::string stack::top() const {
        //return std::__cxx11::string();
        return storage_structure.get_value_at(0);
    }

    void stack::push(const std::string &data) {
        storage_structure.insert(data);//add to head by default
    }

    void stack::pop() {
        storage_structure.remove();//remove from head by default
    }

    std::ostream& operator<<(std::ostream &stream, stack &RHS) {
        stack copystack=RHS;
        std::string copystring=copystack.top();
        for(int i=0;i<RHS.stackSize();i++)
        {
            stream<<copystring;
            copystack.pop();
            copystring=copystack.top();
        }
        return stream;
    }

    std::istream& operator>>(std::istream &stream, stack &RHS) {
        std::string pass;
        stream >> pass;
        RHS.push(pass);
        return stream;
    }
}