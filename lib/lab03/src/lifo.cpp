#include "lifo.h"

namespace lab3
{
    lifo::lifo()
    {
        index = 0;
        lifo_storage.reserve(100);
    }

    lifo::lifo(std::string input_string) {
        index=0;
        lifo_storage.reserve(100);
        lifo_storage[0] = input_string;
        index++;
    }

    lifo::lifo(const lifo &original)
    {
        index = original.index;
        lifo_storage.operator=(original.lifo_storage);
    }

    lifo::~lifo()
    {
        index = -1;
    }

    lifo &lifo::operator=(const lifo &right)
    {
        if(&right==this)
            return*this;
        index = right.index;
        lifo_storage.operator=(right.lifo_storage);
        return *this;
    }

    bool lifo::is_empty() {
        return index == 0;
    }

    int lifo::size() {
        return index;
    }

    std::string lifo::top()
    {
        if(index > 0){
            return lifo_storage[index-1];
        }
    }

    void lifo::push(std::string input)
    {
        if(index <= 99) {
            lifo_storage[index] = input;
            index++;
        }
    }

    void lifo::pop() {
        if (index > 0)
        {
            index--;
        }
    }
}


//last in first out, stack
/*
namespace lab33{
    lifo::lifo()
    {
        lifo_storage.reserve(100);
        index=0;//empty, size=0
        lifo_storage[0]="\0";
    }

    lifo::lifo(std::string input_string)
    {
        lifo_storage.reserve(100);
        index=0;
        lifo_storage[index]=(input_string);//not empty
        index++;
    }

    lifo::lifo(const lifo &original)
    {
        index=original.index;
        lifo_storage.operator=(original.lifo_storage);
    }

    lifo::~lifo() {
    index=0;
    }

    lifo &lifo::operator=(const lifo &right) {
        //return <#initializer#>;
        if(&right==this)
            return *this;
        lifo newlifo;
        newlifo.lifo_storage=right.lifo_storage;
        newlifo.index=right.index;

        index = newlifo.index;
        lifo_storage = newlifo.lifo_storage;
        return *this;
    }

    bool lifo::is_empty()
    {
        return index == 0 || lifo_storage[0] == "\0";
    }

    int lifo::size()
    {
        if(lifo_storage[0]=="\0")
            return 0;
        else
            return index;
    }

    std::string lifo::top(){
        //return std::__cxx11::string();

        if (lifo_storage[0]!="\0" && (index>=0 && index<=99))
            return lifo_storage[index];
    }

    void lifo::push(std::string input)
    {//empty array
        if(index==0 && lifo_storage[0]=="\0")
        {
            lifo_storage[index]=input;
            index++;
            //index is 0 still, pushes new value into empty array
        }
//        else if(index==0)
//        {//0th element exists in array, not empty
//            index++;
//            lifo_storage[index]=input;//index 1 assigned
//        }
        else if(index>=0 && index<99 )//cant push when full(99)
        {
            lifo_storage[index]=input;
            index++;
        }
        else
        {
            //throw "debug push";
            //cant push over 99 or <-1
        }
    }


    void lifo::pop() {

        if(index==0)
        {
            lifo_storage[0]="\0";
            //cant pop empty stac
            //please push
        }
        else if(lifo_storage[0]!="\0" && index>=0 && index<=99)//cant pop when index is 0 AND stack is empty
        {
            //lets say index is 1, it gets nulled, then decremented to 0, above else if block is used next call
            //  lifo_storage[index] = "\0";
            lifo_storage[index]="\0";
            index--;//cant use stringvector size and capacity since there is no way to reduce length/size
        }
    }
}
*/