

#include <string>
#include "calculator.h"
using std::stoi;
namespace lab4 {
    void calculator::parse_to_infix(std::string &input_expression)
    {
        lab1::expressionstream expstream(input_expression);


       // while(expstream.next_token_is_int() || expstream.next_token_is_op() || expstream.next_token_is_paren_close() ||expstream.next_token_is_paren_open())
       while(expstream.get_current_token()!="\0")
       {
        infix_expression.enqueue(expstream.get_current_token());
        expstream.get_next_token();
       }
    }


    void calculator::convert_to_postfix(lab3::fifo infix_expression) {
        lab3::lifo opStore;    //stack to hold operators

        while (infix_expression.size() != 0) {
            if ((infix_expression.top() == "*" || infix_expression.top() == "/" || infix_expression.top() == "-" || infix_expression.top() == "+") || infix_expression.top() == "(")
            {
                while ((opStore.size()!= 0 &&(
                (opStore.top() == "*" && infix_expression.top() == "/") ||
                        (opStore.top() == "*" && infix_expression.top() == "+") ||
                        (opStore.top() == "*" && infix_expression.top() == "-") ||
                        (opStore.top() == "*" && infix_expression.top() == "*") ||

                        (opStore.top() == "/" && infix_expression.top() == "-") ||
                        (opStore.top() == "/" && infix_expression.top() == "/") ||
                        (opStore.top() == "/" && infix_expression.top() == "+") ||

                        (opStore.top() == "+" && infix_expression.top() == "+") ||
                        (opStore.top() == "+" && infix_expression.top() == "-") ||

                        (opStore.top() == "-" && infix_expression.top() == "-")||
                        ((opStore.top() == "-" && infix_expression.top() == "+")
                      && infix_expression.top() != "(")))) {
                    postfix_expression.enqueue(opStore.top());
                    opStore.pop();
                }//compare each op precedence combination
                opStore.push(infix_expression.top());

            } else if (infix_expression.top() == ")")
            {
                while (opStore.top() != "(")
                {
                    postfix_expression.enqueue(opStore.top());
                    opStore.pop();
                }
                opStore.pop();
            }
            else
            {
                postfix_expression.enqueue(infix_expression.top());
            }
            infix_expression.dequeue();//1 dequeue per while loop, make sure to not double up
        }

        while (opStore.size() != 0 && opStore.top()!="\0")
        {
            postfix_expression.enqueue(opStore.top());
            opStore.pop();
        }
    }


    calculator::calculator()
    {
        //empty constructor
    }

    calculator::calculator(std::string &input_expression)
    {
        parse_to_infix(input_expression);
        convert_to_postfix(infix_expression);
    }

    std::istream &operator>>(std::istream &stream, calculator &RHS) {
        string infix,append;
        while(stream >> append)
            infix=infix+append;
        RHS.parse_to_infix(infix);
        RHS.convert_to_postfix(RHS.infix_expression);

        return stream;

    }

    int lab4::calculator::calculate() {
        //iterate through postfix expression
        //push every number to a stack until you meet an operator
        //when operator reached, pop 2 numbers out of stack and apply the operator to them
        //push result back to stack
        int result=0;
        string num1;//left num
        string num2;//right num
        string eval;

        lab3::lifo calcStack;


        if(postfix_expression.is_empty())
        {}//throw 5;//either postfix was not converted or is empty

        while(postfix_expression.size() != 0) {
            //std::cout << "\nCalculation: " << postfix_expression.top();
            if(!postfix_expression.top().empty() && postfix_expression.top().find_first_not_of("0123456789") == std::string::npos)
            {
                calcStack.push(postfix_expression.top());
            }
            if((postfix_expression.top()=="*")){
                // postfix_expression.dequeue();//dequeue operator, perform operation
                num1=calcStack.top();
                calcStack.pop();
                num2=calcStack.top();
                calcStack.pop();

                result = std::stoi(num2)*std::stoi(num1);
                eval = std::to_string(result);
                calcStack.push(eval);

            }
            else if((postfix_expression.top()=="/"))
            {
                //postfix_expression.dequeue();//dequeue operator, perform operation
                num1=calcStack.top();
                calcStack.pop();
                num2=calcStack.top();
                calcStack.pop();

                result = std::stoi(num2)/std::stoi(num1);
                eval = std::to_string(result);
                calcStack.push(eval);
            }
            if((postfix_expression.top()=="+"))//just to be safe, put +,- after */ if
            {
                num1=calcStack.top();
                calcStack.pop();
                num2=calcStack.top();
                calcStack.pop();
                result = std::stoi(num2)+std::stoi(num1);
                eval = std::to_string(result);
                calcStack.push(eval);
            }
            if((postfix_expression.top()=="-"))
            {
                num1=calcStack.top();
                calcStack.pop();
                num2=calcStack.top();
                calcStack.pop();
                result = std::stoi(num2)-std::stoi(num1);
                eval = std::to_string(result);
                calcStack.push(eval);
            }
            postfix_expression.dequeue();
        }
        result = std::stoi(calcStack.top());
        return result;
    }


    std::ostream &operator<<(std::ostream &stream, calculator &RHS)
    {
        stream << "Infix: ";
        //for (int i=0;i<=RHS.infix_expression.size();i++)
        while(!RHS.infix_expression.is_empty())
        {
            stream << RHS.infix_expression.top();RHS.infix_expression.dequeue();
            if(RHS.infix_expression.size()>0)
                stream<<",";//removes the ending comma
        }
        stream << "\nPostfix: ";
        //for (int i=0;i<=RHS.postfix_expression.size();i++)
        while(!RHS.postfix_expression.is_empty())
        {
            stream << RHS.postfix_expression.top();RHS.postfix_expression.dequeue();
            if(RHS.postfix_expression.size()>0)
                stream<< ",";
        }

        return stream;
    }



    // AUXILIARY FUNCTIONS
    bool is_number(std::string input_string);

    bool is_operator(std::string input_string);

    int get_number(std::string input_string);

    std::string get_operator(std::string input_string);

    int operator_priority(std::string operator_in);
}

//  if(infix_expression.size()<3) //if less than 3, disregard the expression. An expression at minimum needs 1 operator and 2 operands.
//  {
//while(infix_expression.top()!="\0")
//    infix_expression.dequeue();
// }


//    void calculator::convert_to_postfix(lab3::fifo infix_expression)
//        {
//
//            string token;
//            lab3::lifo opStore;
//            while(!(infix_expression.is_empty()))//while there are things to read in the infix expression
//            {
//                token = infix_expression.top();
//
//                if (token >= "0" && token <= "9") {
//                    postfix_expression.enqueue(token);
//                }
//                if (token == "*" || token == "/" || token == "-" || token == "+") {
//                    if (opStore.top() >= token && opStore.top() != "("){
//                        postfix_expression.enqueue(opStore.top());opStore.pop();}
//                    else
//                        opStore.push(token);
//                }
//                if (token == "(")
//                    opStore.push(token);
//                if (token == ")")
//                    while (opStore.top() != "(") {
//                        postfix_expression.enqueue(opStore.top());
//                        opStore.pop();
//                    }
//                if (opStore.top() == "(")
//                    opStore.pop();
//                infix_expression.dequeue();
//            }
//        if(infix_expression.is_empty())
//            while(!opStore.is_empty())//while STACK isnt empty, pop all the operators after the infix is empty
//            {
//                postfix_expression.enqueue(opStore.top());
//                opStore.pop();
//            }
//    }