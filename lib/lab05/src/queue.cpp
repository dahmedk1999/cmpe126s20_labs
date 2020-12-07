#include "queue.h"
namespace lab5{
    queue::queue() {
        //storage_structure;
    }

    queue::queue(std::string &data) {
        storage_structure.insert(data);
    }

    queue::queue(const queue &original) {
        for (unsigned i = 0; i < original.storage_structure.listSize(); i++)
        {
            this->storage_structure.append(original.storage_structure.get_value_at(i));
        }
    }

    queue::~queue() {
        //use linked list
    }

    queue &queue::operator=(const queue &RHS) {
        //return <#initializer#>;
        if(this==&RHS)
            return *this;
        storage_structure.operator=(RHS.storage_structure);
        return *this;
    }

    bool queue::isEmpty() const {
        return storage_structure.isEmpty();
    }

    unsigned queue::queueSize() const {
        return storage_structure.listSize();
    }

    std::string queue::top() const {
        //return std::__cxx11::string();
        return storage_structure.get_value_at(0);//front of the line
    }

    void queue::enqueue(const std::string &data) {
        storage_structure.append(data);//add to the end of the line
    }

    void queue::dequeue() {
        storage_structure.remove();//remove from the front of the line
    }

    std::ostream& operator<<(std::ostream &stream, queue &RHS) {
        queue copyQ=RHS;
        std::string copystring=copyQ.top();
        for(int i=0;i<copyQ.queueSize();i++) {
            stream<<copystring;
            copyQ.dequeue();
            copystring=copyQ.top();
        }
        return stream;
    }

    std::istream& operator>>(std::istream &stream, queue &RHS) {
        std::string istring;
        stream>>istring;
        RHS.enqueue(istring);
        return stream;
    }
}