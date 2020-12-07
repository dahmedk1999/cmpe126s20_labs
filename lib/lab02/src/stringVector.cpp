#include <iostream>
#include "../inc/stringVector.h"
#include <cstdlib>

namespace lab2
{

    stringVector::stringVector()
    {
        length=0;
        allocated_length=0;
        data = new string[allocated_length];
    }

    stringVector::~stringVector()
    {
            delete [] data;
    }

    unsigned stringVector::size() const
    {
        return length;//how many strings in vector
    }

    unsigned stringVector::capacity() const
    {
        return allocated_length;//how many spaces in vector
    }

    void stringVector::reserve(unsigned new_size)
    {
        if (new_size < 0 || new_size == allocated_length)
            std::cout << "Invalid";
        else if(allocated_length < new_size)
        {
            allocated_length = new_size;
            std::string *tempData = new std::string[new_size];
            for (int i = 0; i < length; i++)
            {
                tempData[i] = data[i];
            }
            delete [] data;
            data = new std::string [new_size];
            for (int i = 0; i < length; i++)
            {
                data[i] = tempData[i];
            }
            delete [] tempData;

        }
        else if(allocated_length > new_size)
        {
            allocated_length = new_size;
            std::string *tempData = new std::string[new_size];
            if(length <= new_size)
            { //if length is less than new_size, we good
                for (int i = 0; i < length; i++)
                {
                    tempData[i] = data[i];
                }
            }
            else if (length > new_size)
            {// truncate if len>s
                for (int i = 0; i < new_size; i++)
                {
                    tempData[i] = data[i];
                }
                length = new_size;
            }

            delete [] data;
            data = new std::string [new_size];
            for (int i = 0; i < length; i++){
                data[i] = tempData[i];
            }
            delete [] tempData;
        }
    }

    bool stringVector::empty() const
    {
        return (size()==0);
        //return (length==0);
    }


    void stringVector::append(std::string new_data) {
        if(allocated_length == 0){
            length = 0;
            allocated_length = 1;
            delete [] data;
            data = new std::string[allocated_length];
            data[length] = new_data;
            length++;

        }else if(length >= allocated_length) {
            allocated_length = 2 * allocated_length;

            std::string *tempData;
            tempData = new std::string[allocated_length];

            for (int j = 0; j < length; j++) {
                tempData[j] = data[j];
            }
            tempData[length] = new_data;
            length++;
            delete[] data;
            data = new std::string[allocated_length];

            for (int j = 0; j < length; j++) {
                data[j] = tempData[j];
            }
            delete [] tempData;
        }else if(length < allocated_length) {
            data[length] = new_data;
            length++;
        }

    }

    void stringVector::swap(unsigned pos1, unsigned pos2)
    {
        if((pos1 > allocated_length) || (pos2 >allocated_length))
            throw "Please enter within the allocated length of the array";
        string temp=data[pos1];
        data[pos1]=data[pos2];
        data[pos2]=temp;

    }


    stringVector &stringVector::operator=(stringVector const &rhs) {
        if(this != &rhs)
        {
            length = rhs.length;
            allocated_length = rhs.allocated_length;
            delete [] data;
            data = new std::string[allocated_length];
            for(int i = 0; i < allocated_length; i++)
                data[i] = rhs.data[i];
        }
        return *this;
    }

    string &stringVector::operator[](unsigned position)
    {
        if (position <= allocated_length && position >= 0 && allocated_length!=0)
            return data[position];
        else
            throw int(1);
    }

    string stringLower(string s)
    {
        for(int i=0;i<s.length();i++)
            s[i]= tolower(s[i]);
        return s;
    }
    void stringVector::sort()
    {
        string temp;
        string tempL;//lowercase
        for(int i=0;i<length;i++)
        {
           for(int j=0;j<length;j++)
           {
               if(stringLower(data[i])<stringLower(data[j]))
               {
                   temp=data[i];
                   data[i]=data[j];
                   data[j]=temp;
               }
           }
        }
    }

}






//        if(!isdigit(new_size))
//        {
//            //cout<<"bad new_size!\n";
//        }
//        if (new_size < allocated_length && new_size >= 0) {
//            //cout << "Truncating data...\n";
//            allocated_length = new_size;
//            length = 0;
//
//            string *temp0;
//            temp0 = new string[allocated_length];//new shortened string array
//
//            for (int i = 0; i < allocated_length; i++)
//                temp0[i] = data[i];//added truncated data to new array
//            delete[]data;
//            data = new string[allocated_length];//remake old array as a shorter, truncated one
//            for (int i = 0; i < allocated_length; i++) {
//                data[i] = temp0[i];
//                length++;
//            }
//            delete[]temp0;
//        }//allocating more space if new_size>allocated_length
//
//        else if (new_size == allocated_length) {
//            //do nothing. wat r u doing
//        }//do nothing if same space is reserved
//
//        else
//        {
//
//        string *temp;
//        temp = new string[new_size];
//        length = 0;//reusing length for new array
//        for (int i = 0; i <allocated_length; i++)//if new_size is 10, reserve 0-9, data could have just 5 originally, write up to original length
//            temp[i] = data[i];
//        delete[]data;
//        data = new string[new_size];//reallocate a new data with new length
//        for (int i = 0; i < allocated_length; i++)
//        {
//            data[i] = temp[i];
//            length++;
//        }
//        delete[]temp;
//        allocated_length = new_size;
//        }
//    }//if new size > allocated length



