#include "fancy_calculator.h"
#include "stack.h"
#include "queue.h"
#include <cmath>

namespace lab5{
    void calculator::parse_to_infix(std::string &input_expression) {
            lab1::expressionstream expstream(input_expression);
            while(expstream.get_current_token()!="\0")
            {
                infix_expression.enqueue(expstream.get_current_token());
                expstream.get_next_token();
            }
    }

    void calculator::convert_to_postfix(lab5::queue infix_expression) {
        lab5::stack opStore;    //stack to hold operators

        while (infix_expression.queueSize() != 0) {
            if ((
                infix_expression.top() == "^" ||
                infix_expression.top() == "*" ||
                infix_expression.top() == "%" ||
                infix_expression.top() == "/" ||
                infix_expression.top() == "-" ||
                infix_expression.top() == "+")||

                infix_expression.top() == "("){
                while ((opStore.stackSize() != 0 &&(
                               (opStore.top() == "^" && infix_expression.top() == "%") ||
                               (opStore.top() == "^" && infix_expression.top() == "/") ||
                               (opStore.top() == "^" && infix_expression.top() == "+") ||
                               (opStore.top() == "^" && infix_expression.top() == "-") ||
                               (opStore.top() == "^" && infix_expression.top() == "^") ||
                               (opStore.top() == "^" && infix_expression.top() == "*") ||

                               (opStore.top() == "*" && infix_expression.top() == "%") ||
                               (opStore.top() == "*" && infix_expression.top() == "/") ||
                               (opStore.top() == "*" && infix_expression.top() == "+") ||
                               (opStore.top() == "*" && infix_expression.top() == "-") ||
                               (opStore.top() == "*" && infix_expression.top() == "*") ||

                               (opStore.top() == "/" && infix_expression.top() == "%") ||
                               (opStore.top() == "/" && infix_expression.top() == "-") ||
                               (opStore.top() == "/" && infix_expression.top() == "/") ||
                               (opStore.top() == "/" && infix_expression.top() == "+") ||

                               (opStore.top() == "%" && infix_expression.top() == "%") ||
                               (opStore.top() == "%" && infix_expression.top() == "-") ||
                               (opStore.top() == "%" && infix_expression.top() == "+") ||

                               (opStore.top() == "+" && infix_expression.top() == "+") ||
                               (opStore.top() == "+" && infix_expression.top() == "-") ||

                               (opStore.top() == "-" && infix_expression.top() == "-") ||
                               (opStore.top() == "-" && infix_expression.top() == "+"))
                       && infix_expression.top() != "("))
                {
                    postfix_expression.enqueue(opStore.top());
                    opStore.pop();
                }//compare each op precedence combination and enq them into the postfix
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

        while (opStore.stackSize() != 0 && opStore.top() != "\0") {
            postfix_expression.enqueue(opStore.top());
            opStore.pop();
        }
    }

    calculator::calculator() {
//        infix_expression;
//        postfix_expression;
    }

    calculator::calculator(std::string &input_expression) {
        parse_to_infix(input_expression);
        convert_to_postfix(infix_expression);
    }

    std::istream &operator>>(std::istream &stream, calculator &RHS) {
        std::string infix;std::string append;
        while(stream >> append)
            infix=infix+append;
        RHS.parse_to_infix(infix);
        RHS.convert_to_postfix(RHS.infix_expression);

        return stream;
    }

    int calculator::calculate() {
        int result=0;
        std::string num1;//left num
        std::string num2;//right num
        std::string eval;

        lab5::stack calcStack;


        if(postfix_expression.isEmpty())
        {}//throw 5;//either postfix was not converted or is empty

        while(postfix_expression.queueSize() != 0)
        {
            if(!postfix_expression.top().empty() && postfix_expression.top().find_first_not_of("0123456789") == std::string::npos)
            {
                calcStack.push(postfix_expression.top());
            }

            if((postfix_expression.top()=="^")) {
                //caret, x ^ n, x is base, n is exp
                num1 = calcStack.top();
                calcStack.pop();
                num2 = calcStack.top();
                calcStack.pop();

                result =pow(std::stoi(num2),std::stoi(num1));
                eval = std::to_string(result);
                calcStack.push(eval);
            }

            else if((postfix_expression.top()=="*"))
            {
                // postfix_expression.dequeue();//dequeue operator, perform operation
                num1=calcStack.top();
                calcStack.pop();
                num2=calcStack.top();
                calcStack.pop();

                result = (std::stoi(num2))*(std::stoi(num1));
                eval = std::to_string(result);
                calcStack.push(eval);
            }

            else if((postfix_expression.top()=="%"))
            {
                num1=calcStack.top();
                calcStack.pop();
                num2=calcStack.top();
                calcStack.pop();

                result = (std::stoi(num2))%(std::stoi(num1));
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

                result = (std::stoi(num2))/(std::stoi(num1));
                eval = std::to_string(result);
                calcStack.push(eval);
            }
            else if((postfix_expression.top()=="+"))//just to be safe, put +,- after */ if
            {
                num1=calcStack.top();
                calcStack.pop();
                num2=calcStack.top();
                calcStack.pop();

                result = (std::stoi(num2))+(std::stoi(num1));
                eval = std::to_string(result);
                calcStack.push(eval);
            }
            else if((postfix_expression.top()=="-"))
            {
                num1=calcStack.top();
                calcStack.pop();
                num2=calcStack.top();
                calcStack.pop();

                result = (std::stoi(num2))-(std::stoi(num1));
                eval = std::to_string(result);
                calcStack.push(eval);
            }
            postfix_expression.dequeue();
        }
        return std::stoi(calcStack.top());;
    }

    std::ostream &operator<<(std::ostream &stream, calculator &RHS) {
        stream << "Infix: ";
        //for (int i=0;i<=RHS.infix_expression.size();i++)
        while (!RHS.infix_expression.isEmpty()) {
            stream << RHS.infix_expression.top();
            RHS.infix_expression.dequeue();
            if (RHS.infix_expression.queueSize() > 0)
                stream << ",";//removes the ending comma
        }
        stream << "\nPostfix: ";
        //for (int i=0;i<=RHS.postfix_expression.size();i++)
        while (!RHS.postfix_expression.isEmpty()) {
            stream << RHS.postfix_expression.top();
            RHS.postfix_expression.dequeue();
            if (RHS.postfix_expression.queueSize() > 0)
                stream << ",";
        }
    }


    // AUXILIARY FUNCTIONS
    bool is_number(std::string input_string);

    bool is_operator(std::string input_string);

    int get_number(std::string input_string);

    std::string get_operator(std::string input_string);

    int operator_priority(std::string operator_in);

}

