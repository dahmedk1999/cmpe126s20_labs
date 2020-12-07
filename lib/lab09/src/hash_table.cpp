#include "../inc/hash_table.h"
#include <iostream>
namespace lab9 {
    // Implemented for you.
    unsigned hash_table::hash_1(std::string to_hash) {
        // DJB2 Hashing Algorithm
        unsigned int hash = 5381;
        for(char c: to_hash){
            hash = ((hash << 5) + hash) + c;
        }
        return hash;
    }

    // Implemented for you.
    unsigned hash_table::hash_2(std::string to_hash) {//
        // BKDR Hashing Algorithm
        unsigned int seed = 131;
        unsigned int hash = 0;
        for(char c: to_hash){
            hash = (hash * seed) + c;
        }
        return hash;
    }

    void hash_table::expand()
    {
        int nextprime =0;//for loop search
        //const int PRIMES[16] = {31, 67, 137, 277, 557, 1117, 2237, 4481, 8963, 17929, 35863, 71741, 143483, 286999, 574003, 1148029};
        int oldmax=max_size;
        for(int i=0;i<=15;i++)
        {
            nextprime=PRIMES[i];
            if(max_size<nextprime)
            {
                max_size=nextprime;
                break;
            }
        }

        current_size=0;
        auto *new_array= new key_value[nextprime];//declare increased size array
        for(int i=0;i<oldmax;i++)//go up to previous max size
        {
            new_array[i].key=hash_table_array[i].key;
            new_array[i].value=hash_table_array[i].value;
            current_size++;
        }

        delete[]hash_table_array;

        hash_table_array = new key_value[max_size];
        current_size=0;

        for(int i=0;i<oldmax; i++){
            if(new_array[i].key!="") insert(new_array[i].key,new_array[i].value);
        }

    }


    hash_table::hash_table(char type) {
        /*
         * Define the probing technique
         * 'l': Linear probing
         *          hash_1() + attempt
         * 'q': Quadratic probing
         *          hash_1() + attempt^2
         * 'd': Double Probing
         *          hash_1() + attempt * hash_2()
         *
         * Create a hash table with an initial size of 100
         */
        probing = (type == 'l' || type == 'q' ||type == 'd') ? type : '\0';
        current_size = 0;
        max_size = (probing =='\0')? 0 : 100;
        hash_table_array = new key_value[max_size];

    }

    hash_table::~hash_table()
    {
        if(this)
            delete[]hash_table_array;
        max_size = 0;
        current_size = 0;
    }


    bool hash_table::insert(std::string key, int value) {
        if (current_size>= 0.7*max_size) expand();
        if(in_table(key)) return false;
        // Insert a key according to the defined probing technique
        // If you run into an issue where you get an infinite collision loop,
        //   figure out a way to get out of the loop.


        unsigned indx= hash_1(key) % max_size;
        unsigned attempt=1,begin=indx;
        key_value to_insert = {key, value};

        while ( !hash_table_array[indx].key.empty() )
        {
            if(hash_table_array[indx].key == key) return false;   //need this to check duplicated key
            if(probing=='l')
                indx++;
            else if(probing=='q')
                indx = (indx + attempt * attempt);
            else if(probing=='d')
                indx = (indx + attempt * hash_2(key));
            indx%=max_size;
            attempt++;
            if(indx==begin)
                if(max_size < PRIMES[(*(&PRIMES+1) - PRIMES) - 1]) //learned this blackmagic from Hoang
                {
                    expand();
                    indx=hash_1(key)%max_size;
                }
                else return false;
        }

        hash_table_array[indx].key=key;
        hash_table_array[indx].value=value;
        current_size++;
        return true;

    }


    bool hash_table::in_table(std::string key){
        // Checks to see if that key is in the table.
        // Use the specified probing technique
        // Keep collisions in mind
        unsigned hash = hash_1(key) % max_size;
        unsigned attempt = 1,begin = hash;
        if(current_size<0)
            throw std::exception();
        while(hash_table_array[hash].key!="")
        {
            if(hash_table_array[hash].key == key) return true;
            if(probing=='l')hash++;
            if(probing=='q')hash = (hash + attempt * attempt);
            if(probing=='d')hash = (hash + attempt * hash_2(key));
            attempt++;
            hash %= max_size;
            if(hash==begin) return false;//end infinite loop
        }
        return false;
    }


    int hash_table::get(std::string key)
    {
        // Get the int value from the node that has key
        // Use the specified probing technique
        unsigned  idx = hash_1(key) % max_size;
        unsigned attempt = 1, begin = idx;
        if(current_size<=0) { throw std::exception(); }
        else
        {
            while(hash_table_array[idx].key !="")
            {
                if(hash_table_array[idx].key == key)
                    return hash_table_array[idx].value;
                if(probing == 'l') { idx++;}
                if(probing == 'q') { idx = (idx + attempt * attempt);}
                if(probing == 'd') { idx = (idx + attempt * hash_2(key));}
                attempt ++;
                idx %= max_size;
                if (idx == begin) return 0;
            }
        }
        return 0;
    }


    void hash_table::update(std::string key, int value){
        // Update a key in the hash table.
        // Keep collisions in mind
        // Use the specified probing technique
        unsigned hash = hash_1(key) % max_size;
        unsigned attempt = 1, begin = hash;
        if(current_size <= 0) throw std::exception();
        while(hash_table_array[hash].key != "")
        {
            if(hash_table_array[hash].key == key)
                hash_table_array[hash].value = value;
            if(probing == 'l') hash ++;
            if(probing == 'q') hash = (hash + attempt * attempt);
            if(probing == 'd') hash = (hash + attempt * hash_2(key));
            attempt ++;
            hash %= max_size;
            if (hash == begin)
                return;
        }

    }

    void hash_table::remove(std::string key)
    {
        // Remove an item from the hash table. Keep collisions in mind
        // Use the specified probing technique
        // If the item isn't in the table, do nothing.
        unsigned hash = hash_1(key) % max_size;
        unsigned attempt = 1, begin = hash;
        if(current_size <= 0) throw std::exception();
        while(!hash_table_array[hash].key.empty())
        {
            if( hash_table_array[hash].key == key )
            {
                hash_table_array[hash].key = "0";//empty the key
                hash_table_array[hash].value = 0;//0
                current_size--;
                return;
            }
            if(probing == 'l') hash ++;
            if(probing == 'q') hash = (hash + attempt * attempt);
            if(probing == 'd') hash = (hash + attempt * hash_2(key));
            attempt ++;
            hash %= max_size;
            if(hash == begin)  return  ;
        }
    }

    std::string hash_table::to_string(){
        // Run through the entire array and create a string following this format. The {} brackets aren't part of the return
        // [{array location}]{key_value.key}:{key_value.int}
        std::string toreturn;
        std::cout<<"Output String:\n";
        for(int i = 0 ; i< current_size; i++)
        {
            if (hash_table_array[i].key != "")
            {
                unsigned index=hash_1(hash_table_array[i].key)%max_size;
                toreturn +="[";toreturn+=std::to_string(index);toreturn+="]";toreturn+=":";toreturn+=hash_table_array[i].key;toreturn+=":";toreturn+=
                std::to_string(hash_table_array[i].value);toreturn+="\n";
                std::cout <<"["<<index<< "]" << hash_table_array[i].key << ":" << hash_table_array[i].value << "\n";
            }
        }
        std::cout<<"End of Output String:\n";
        return toreturn;
    }
}
