#include <string>
#include "../inc/recursion.h"
#include <exception>
namespace lab7 {
    recursion::recursion()
    {
        //empty
    }

    recursion::~recursion()
    {
        //empty
    }

    int recursion::fibonacci(int N)
    {
        //exception if less than 0
        //return Nth number of fib
        //first 2 numbers are special cases
        if(N==0)return 0;
        else if(N==1)return 1;
        else if(N>1)
        {
            return fibonacci(N-1)+fibonacci(N-2);
        }
        else{throw std::exception();}
    }

    int recursion::climb_stairs(int n)
    {
        if(n<1)
            throw std::exception();
        if(n==1)
            return n;
        else
        {
            return fibonacci(n)+fibonacci(n-1);
        }
    }

    int recursion::pow(int base, int n)
    {
        if(n<0)
            throw std::exception();
        if(n==0)
            return 1;
        else
        {
            return base*pow(base,n-1);
        }
    }

    // hint: first check the first and last characters, then recurse with what's left inside
    bool recursion::valid_parenthesis(std::string input)
    {
        //each ( needs an )
        //even number of ()s
        int l=input.length();
        if(input=="")
            return true;
        else if(l%2==0)
        {
            if(input.front()=='(' && input.back()==')')
                return valid_parenthesis(input.substr(1,l-2));
        }
        return false;
    }
//        //2 base cases
//        //""
//        //)
//        if(input[0]=='\0')return true;
//        if(input[0]==')')return false;
//
//        int z,count=0,l=input.length();
//        for(z=1;z<input.length();z++)
//        {
//            if(input[z]==')')
//                count++;//found match so move to next
//            if(input[z]=='(')
//            {
//                if(count==0)break;
//                count--;
//            }
//
//
//        }
//        std::string snipp;
//        std::string snip=input;
//        snip.erase(0,1);
//        if(z==l)return false;//reached end of string and found none
//        if(z==1) return (valid_parenthesis(snip));
//        else{
//            snipp=input;
//            snipp.erase(0);
//            return (valid_parenthesis(snipp));
//        }



    // hint: this is very similar to what you've done with linked lists previously, just using recursion.
    bool recursion::are_nodes_ok(const node* head)
    {
        //if head exists, then true
        //move to next node, return self
        auto temp=head;
        if(temp->ok)
        {
            if(temp->next)
                return are_nodes_ok(temp->next);
            //temp=temp->next;//next node, recursion starts from here
            return temp->ok;
        }
        else return false;

    }
//        auto temp=head;
//        if(temp)
//            return true;
//        else if(temp->next) {
//            temp=temp->next;
//            return are_nodes_ok(temp);
//        }
//        else return true;




}