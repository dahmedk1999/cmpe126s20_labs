#include "fifo.h"
//first in first out, queue
namespace lab3{
    fifo::fifo()
    {
    front_index=0;back_index=0;
    fifo_storage.reserve(100);
    }

    fifo::fifo(std::string input_string)
    {
        fifo_storage.reserve(100);
        front_index=0;back_index=1;
        fifo_storage[front_index%100]=input_string;//index 0
    }

    fifo::fifo(const fifo &original)
    {
     //   Remember:
     //   Test t1, t2;
     //   t2 = t1;  Calls assignment operator
     //   Test t3 = t1; Calls copy constructor
//
       // fifo_storage.reserve(100);
        fifo_storage.operator=(original.fifo_storage);
        front_index=original.front_index;
        back_index=original.back_index;
       // queuesize=original.queuesize;
    }

    fifo::~fifo()
    {
        //~stringVector();called
    }

    fifo &fifo::operator=(const fifo &right)
   {
        //return <#initializer#>;
        if(&right==this)
            return *this;
        else
        {
        fifo_storage = right.fifo_storage;//calls the stringvector's hard copy assignment operator
        front_index = right.front_index;
        back_index = right.back_index;
       // queuesize = right.queuesize;
        return *this;
        }
   }


    int fifo::size()
    {
        //return fifo_storage.size();
        //if((back_index%100 - front_index%100) >=0 && (back_index%100 - front_index%100)<=99)
            return (back_index-front_index);
        //  return back_index-front_index;
    }

    bool fifo::is_empty()
    {
        return !(size());
    }
    std::string fifo::top()
    {
        if(!is_empty())
            return fifo_storage[front_index%100];
    }

    void fifo::enqueue(std::string input)
    {
        if(size()<=99)
        {
        fifo_storage[back_index%100]=input;
        back_index++;
        }
        else if((back_index+1 % 100 != front_index % 100) && (size() != 99) )//if size counter isnt 99, theres space.
        {
            fifo_storage[back_index%100]=(input);
            back_index++;
        }
    }
    //front[0][1][2][3][4][5]back
    //  <-dequeue, 0 freed ,front is 1, enqueued a new one to 0, back++%6 is 0
    void fifo::dequeue()
    {
        if((fifo_storage[front_index%100]=="\0" || fifo_storage[back_index%100]=="\0") && size()==0)
        {//front_index==back_index
            //throw "Cannot dequeue empty queue.";
        }
        else
        {
            fifo_storage[front_index%100]="\0";
            front_index++;
            //queuesize--;
        }
    }
}