
#ifndef CMPE126S20_LABS_STRINGVECTOR_H
#define CMPE126S20_LABS_STRINGVECTOR_H
#include <iostream>
#include <string>
using std::string;
using std::cout;
namespace lab2 {
    class stringVector {
    private:
        string *data;
        unsigned length;
        unsigned allocated_length;

    public:
        stringVector();
        virtual ~stringVector();
        unsigned size()const;
        unsigned capacity()const;
        void reserve(unsigned new_size);
        bool empty()const;
        void append(string new_data);
        void swap(unsigned pos1, unsigned pos2);
        stringVector &operator=(stringVector const &rhs);
        string &operator[](unsigned position);
        void sort();
    };
}

#endif //CMPE126S20_LABS_STRINGVECTOR_H
