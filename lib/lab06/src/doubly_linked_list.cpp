#include "../inc/doubly_linked_list.h"

namespace lab6
{
    doubly_linked_list::doubly_linked_list()
    {
        head= nullptr;//head.prev should never have any value, must always become the new head.
        tail= nullptr;
    }

    doubly_linked_list::doubly_linked_list(int input)
    {
        head= new node(input);
        tail= head;
//        append(input);
    }

    doubly_linked_list::doubly_linked_list(std::vector<int> vector_input)
    {
        head= nullptr;
        tail= nullptr;
        for(int i=0;i<size();i++)
            append(vector_input[i]);
    }

    doubly_linked_list::doubly_linked_list(const doubly_linked_list &original)
    {
        auto copy = original.head;

        if(original.size()!=0)
        {
            node* temp;
            head=new node(copy->get_data());
            tail=head;

            while (copy->next != nullptr)
            {
                copy = copy->next;//increment copy
                temp=new node(copy->get_data());

                tail->next=temp;
                temp->prev=tail;
                tail=tail->next;
            }
            while(tail->next!= nullptr)
                tail=tail->next;

        }
        else
        {
            head=nullptr;
            tail=nullptr;
        }
    }


    doubly_linked_list::~doubly_linked_list()
    {
        node *temp = head;

        if (head != NULL)
        {
            while (temp != NULL)
            {
                head = head->next;
                delete temp;
                temp = head;
            }
        }
    }

//    doubly_linked_list::~doubly_linked_list()
//    {
//        if(head)
//        {
//            node *del = head;
//            while (del != nullptr)
//            {
//                head = head->next;
//                delete del;
//                del = head;//null at the end
//            }
//        }
//        head= nullptr;
//        tail=nullptr;
//    }

    int doubly_linked_list::get_data(unsigned position)
    {
//        if(!head)
//            return -1;
        unsigned c = 0;
        auto tmp = head;
        while (tmp && (c < position)) {//when c=position, it reaches the node
            c++;tmp = tmp->next;

        }
        return tmp->get_data();
    }


    std::vector<int> doubly_linked_list::get_set(unsigned position_from, unsigned position_to)
    {
        std::vector<int> returner;
        for(unsigned i=position_from;i<=position_to;i++)
        {
            returner.push_back(get_data(i));
        }
        return returner;
    }

    unsigned doubly_linked_list::size() const
    {
        unsigned c = 0;
        if(head==nullptr)
            return c;
        node*tmp = head;
        while(tmp!=nullptr)
        {
            tmp = tmp->next;
            ++c;
        }
        return c;
    }

    bool doubly_linked_list::is_empty()
    {
        return !head;
    }

    void doubly_linked_list::append(int input)
    {
        node*nextnode=new node(input);

        if (!head) {//if head is nullptr
            head = nextnode;
            tail = nextnode;
        }
        else
        {
            tail->next=nextnode;
            nextnode->prev=tail;
            tail=tail->next;
        }
    }

    void doubly_linked_list::insert(int input, unsigned int location)
    {
        node *nNode = new node(input);
        int pos = 0;

        if (!head)
            append(input);
        else if (!location)
        {
            head->prev = nNode;
            nNode->next = head;
            head = nNode;
        } else if (location >= size())
        {
            tail->next = nNode;
            nNode->prev = tail;
            tail = tail->next;
        }
        else
        {
            node *pNode = head;
            node *temp = head;
            while (pos < location)
            {
                if(pos != 0)
                    pNode = pNode->next;
                temp = temp->next;
                pos++;
            }
            nNode->next = pNode->next;
            nNode->prev = pNode;
            pNode->next = nNode;
            temp->prev = nNode;
        }



//
//        if(!head)// if head is NULL
//        {head=new node(input);tail=head;}
//
//        else if(location==0)
//        {
//            auto newhead=new node(input);
//            head->prev=newhead;
//            newhead->prev=nullptr;
//            newhead->next=head;
//            head=newhead;
//        }
//        else if(location==size()-1)
//        {
//            node*newnode=new node(input);
//            tail->prev->next=newnode;
//            newnode->prev=tail->prev;
//            newnode->next=tail;
//            tail->prev=newnode;
//        }
//        else if(location >=size())
//        {
//            //   throw -1;
//        }
//        else
//        {
//            int counter=0;
//            node*current=head;
//            while(counter<location-1)//reaches the index to insert
//            {
//                current=current->next;
//                counter++;
//            }
//            node*nextn=new node(input);//node to be inserted
//            nextn->next=current->next;
//            current->next->prev=nextn;
//            nextn->prev=current;
//            current->next=nextn;
//        }
    }

    void doubly_linked_list::remove(unsigned location)
    {
        unsigned counter = 0;

        if(head)
        {
            if(!location && head->next)
            {
                node *temp = head;
                head = head->next;
                delete temp;
                head->prev = nullptr;
            }
            else if(!location && head->next== nullptr)
            {
                delete head;
                head = nullptr;
                tail = nullptr;
            }
            else if(location >= 0 && location <= size())
            {
                node *temp = head;
                node *prev = head;
                while(counter < location)
                {
                    temp = temp->next;
                    if (counter) {
                        prev = prev->next;
                    }
                    counter++;
                }
                prev->next = temp->next;

                if(temp->next)
                {
                    prev = temp->next;
                    prev->prev = temp->prev;
                    delete temp;
                }
                else
                {
                    delete temp;
                    tail = prev;
                    tail->next = nullptr;
                }
            }
        }
        if(!head)
        {
            head = nullptr;
            tail = nullptr;
        }
    }

//    void doubly_linked_list::remove(unsigned location) {
//        int counter =0;
//        if(head)
//        {
//            if (head->next && location == 0) {
//                node *del = head;//head should have nothing at prev
//                head = head->next;//new head
//                delete del;
//                head->prev = nullptr;
//            } else if (!location && !head->next) {
//                delete head;
//                head = nullptr;
//                tail = nullptr;
//            } else if (location && location <= size()) {
//                auto nNode = head;
//                auto pNode = head;
//                while (counter < location) {
//                    nNode = nNode->next;
//                    if (counter)
//                        pNode = pNode->next;
//                    counter++;
//                }
//                pNode->next = nNode->next;
//                if (!nNode->next) {
//                    pNode = nNode->next;
//                    pNode->prev = nNode->prev;
//                    delete nNode;
//                } else {
//                    delete nNode;
//                    tail = pNode;
//                    tail->next = nullptr;
//                }
//            }
//        }
//        else{
//            head= nullptr;
//            tail=nullptr;
//        }
//    }

    doubly_linked_list doubly_linked_list::split(unsigned position) //split has pos priority
    {

        doubly_linked_list splitoff;
        node*guide=head;
        node*temp=head;

//        if(!head)
//            return splitoff;
        if(position!=0)
        {
            int count=0;
            while(count<position-1)//&& guide->next)//go to location
            {
                guide=guide->next;
                count++;
            }//LL split
            temp=guide->next;//head of new LL
        }

        while(temp)//append to new LL
        {
            splitoff.append(temp->get_data());
            temp=temp->next;
        }
        if(position==0)
        {
            while(head!=nullptr)
                remove(0);
        }
        else
        {
            while (guide->next != nullptr)
                remove(position);
        }
        return splitoff;

        }

    doubly_linked_list doubly_linked_list::split_set(unsigned position_1, unsigned position_2)
    {
        doubly_linked_list newList;
        node *Node1 = head;
        node *Node2 = head;
        unsigned counter = 0, pos1 = 0, pos2 = 0;

        if (position_1 > position_2)
        {
            counter = position_1;
            position_1 = position_2;
            position_2 = counter;
        }

        while(pos2 < position_2)
        {
            Node1 = Node1->next;
            pos2++;
        }
        while(pos1 < position_1)
        {
            Node2 = Node2->next;
            pos1++;
        }

        while(Node2 != Node1)
        {
            newList.append(Node2->get_data());
            Node2 = Node2->next;
        }
        newList.append(Node2->get_data());

        for(int i = position_1; i < position_2+1; i++)
            remove(position_1);


        return newList;

////////////////////////////////
//        if (position_1 > position_2)
//        {
//            counter = position_1;
//            position_1 = position_2;
//            position_2 = counter;
//        }
//
//        auto splitlist1=*this;
//        auto splitlist2=*this;
//        unsigned s=size();//original LLsize
//        if(position_2>position_1 && head)
//        {
//            splitlist2=splitlist2.split(position_2);//holds stuff after pos2
//            splitlist1=split(position_1);//hold stuff from pos1, *this now only from 0 to pos1
//
//            *this=splitlist1+splitlist2;//middle section from pos1 to pos 2 cut out
//            splitlist1=splitlist1.split(splitlist1.size()-position_1);
//
//        }
//        return splitlist1;
    }


    void doubly_linked_list::swap(unsigned position_1, unsigned position_2)
    {
//just insert ahead the position and remove the one at it
    auto tnode=head;
    auto tnode2=head;
    unsigned counter=0;

    //verify pos1 is always lower than pos2
    if(position_2<position_1)
    {
        counter=position_1;
        position_1=position_2;
        position_2=counter;
    }
    //search for the node at each position
    counter=0;//reset
    while(counter<position_2)
    {
        if(counter<position_1)
            tnode=tnode->next;

        tnode2=tnode2->next;
        counter++;
    }//simultaneously tracks nodes at position1 and position2

    insert(tnode->get_data(),position_2+1);
    insert(tnode2->get_data(),position_1+1);
    remove(position_1);remove(position_2);






        //A - B - C - D - E
        //A - D - C - B - E
        //ptrB.prev = ptrD.prev
        //ptrB.next = ptrD.next
        //ptrD.prev.next=ptrB
        //ptrD.next.prev=ptrB

        //ptrD.prev=ptrA
        //ptrD.next=ptrC
        //ptrA.next=ptrD
        //ptrC.prev=ptrD
//
//        if(head==nullptr || position_1==position_2)
//        {
//
//        }
//        else
//        {
//            //search for em
//            auto pos1=head;
//            auto pos2=head;
//            unsigned count1=0;unsigned count2=0;
//            //searching
//            while(pos1->next && count1<position_1)//first search for pos1
//            {
//                pos1=pos1->next;
//                count1++;
//            }
//            while(pos2->next && count2<position_2)//then search for pos2
//            {
//                pos2=pos2->next;
//                count2++;
//            }
//            //IF HEAD AND TAIL
//            if(pos1==head && pos2==tail)
//            {
//                node*before2=pos2->prev;
//                node*after1=pos1->next;
//
//                pos2->prev=nullptr;//head has no prev
//                pos1->next=nullptr;//tail has no next
//                pos1->prev=before2;
//                pos1->next=after1;
//
//                before2->next=pos1;
//                after1->prev=pos2;
//            }
//            //IF TAIL AND HEAD
//            else if(pos1==tail && pos2==head)
//            {
//                node*before1=pos1->prev;
//                node*after2=pos2->next;
//
//                pos1->prev=nullptr;//head has no prev
//                pos2->next=nullptr;//tail has no next
//                pos2->prev=before1;
//                pos2->next=after2;
//
//                before1->next=pos2;
//                after2->prev=pos1;
//            }
//            //if TAIL or non tail
//            else if(pos1==tail && pos2) //[head]<->[head.next]<->[pos2.prev]<->[pos2]<->[pos1]
//            {
//                node*before1=pos1->prev;
//                //node*after1=pos1->next; //this is null bc tail
//
//                pos1->prev=pos2->prev;
//                pos1->next=pos2->next;
//                pos2->prev->next=pos1;
//                pos2->next->prev=pos1;
//
//                pos1->prev=before1;
//
//            }
//            else if(pos2==tail && pos1)
//            {
//                node*before2=pos2->prev;
//                //node*after2=pos1->next; //this is null bc tail
//
//                pos2->prev=pos1->prev;
//                pos1->next=pos1->next;
//                pos1->prev->next=pos2;
//                pos1->next->prev=pos2;
//
//                pos1->prev=before2;
//            }
//            //IF HEAD AND NOT HEAD
//            else if(pos1==head && pos2)//[pos1]<->[pos1.next]<->[pos2.prev]<->[pos2]<->[pos2.next]
//            {
//                node*after1=pos1->next;//preserve head's next
//
//                pos1->prev=pos2->prev;
//                pos1->next=pos2->next;
//                pos2->prev->next=pos1;
//                pos2->next->prev=pos1;
//
//                pos2->prev= nullptr;
//                pos2->next=after1;
//                after1->prev=pos2;
//            }
//            else if(pos2==head && pos1!=head)
//            {
//
//                node*after2=pos2->next;
//
//                pos2->next=pos1->next;
//                pos2->prev=pos1->prev;
//                pos1->prev->next=pos2;
//                pos1->next->prev=pos2;
//
//                pos1->prev= nullptr;
//                pos1->next=after2;
//                after2->prev=pos1;
//
//            }
//            else//if pos1 and pos2 are neither heads nor tails
//            {
//                node*after1=pos1->next;//keep track of pos1 next and prev
//                node*before1=pos1->prev;
//
//                pos1->next=pos2->next;
//                pos1->prev=pos2->prev;
//                after1->prev=pos2;
//                before1->next=pos2;
//                pos2->next=after1;
//                pos2->prev=before1;
//            }
//
//        }
    }
//bloated and inefficient, until swap is done
    void doubly_linked_list::swap_set(unsigned location_1_start, unsigned location_1_end, unsigned location_2_start,
                                      unsigned location_2_end)
    {
        node *Nodeh = head;
        node *Nodet = head;
        node *Node2h = head;
        node *Node2t = head;
        int counter = 0;

        if ((location_2_start + location_2_end) < (location_1_start + location_1_end))
        {
            unsigned temp1 = location_1_start;
            unsigned temp2 = location_1_end;
            location_1_start = location_2_start;
            location_1_end = location_2_end;
            location_2_start = temp1;
            location_2_end = temp2;
        }

        if ((location_2_start == location_2_end) && (location_1_start == location_1_end))
            swap(location_1_start, location_2_start);


        else
        {
            while (counter < location_2_end)
            {
                if (counter < location_1_start)
                    Nodeh = Nodeh->next;
                if (counter < location_1_end)
                    Nodet = Nodet->next;
                if (counter < location_2_start)
                    Node2h = Node2h->next;
                Node2t = Node2t->next;
                counter++;
            }

            counter=1;
            node *tNode = Nodeh;
            for (int i = location_1_start; i < location_1_end + 1; i++)
            {
                insert(tNode->get_data(),location_2_end + counter);
                counter++;
                tNode = tNode->next;
            }

            node *ttNode = Node2h;
            counter = 1;
            for (int i = location_2_start; i < location_2_end + 1; i++)
            {
                insert(ttNode->get_data(), location_1_end + counter);
                counter++;
                ttNode = ttNode->next;
            }

            unsigned math, math1, math2;


            for (int i = location_1_start; i < location_1_end + 1; i++)
                remove(location_1_start);

            math1 = location_1_end - location_1_start;
            math2 = location_2_end - location_2_start;

            if (math1 > math2)
            {
                math = math1 - math2;
                for (int i = location_2_start; i < location_2_end + 1; i++)
                    remove(location_2_start - math);

            }
            else if (math1 < math2)
            {
                math = math2 - math1;
                for (int i = location_2_start; i < location_2_end + 1; i++)
                    remove(location_2_start + math);

            }
            else
            {
                for (int i = location_2_start; i < location_2_end + 1; i++)
                    remove(location_2_start);
            }
        }


//        if(location_1_end<location_1_start || location_2_end<location_2_start ||!is_empty())
//        {
//            //throw
//        }
//        else if(location_1_end >size() || location_2_end >size() || location_1_start >size() || location_2_start >size())
//        {
//            //
//        }
//        else
//        {
//        doubly_linked_list this0=*this;
//        doubly_linked_list this01=*this;
//        doubly_linked_list this1=*this;
//        doubly_linked_list this2=*this;
//
////        unsigned j=size()-location_2_start;
////        unsigned i= size()-location_1_start;
//
//        auto s0= this0.split_set(location_1_end,location_2_start);//gets the in between nodes
//        auto s01= this01.split_set(location_2_end+1,size());//gets ending nodes
//        auto s2= this2.split_set(location_2_start,location_2_end);//truncates main dll at 2nd set
//        auto s1= this1.split_set(location_1_start,location_1_end);//truncates main dll at 1st set
//        //append them back in the starting positions
//
//        doubly_linked_list eqthis=this1;
//        eqthis+=s2;
//        eqthis+=s0;
//        this0+=s1;
//        eqthis+=s01;
//        this->operator=(eqthis);
//        }
    }
//incomplete
    void doubly_linked_list::sort()
    {
        auto minimum=head;
        int counter;
        int temp=minimum->get_data();

        for(int j=0;j<size()-1;j++)
        {
            if (j != 0)
            {
                minimum = head;
                counter=0;

            while(counter!=j)
            {
                minimum=minimum->next;
                counter++;
            }
            temp=minimum->get_data();//new min val
            }

            minimum=minimum->next;
            for(int k=j+1;k<size();k++)
            {
                if(minimum->get_data()<temp)
                {
                    temp=minimum->get_data();
                    swap(j,k);//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
                    minimum=head;
                    for(int c=0;c<k;c++)
                    {
                        minimum=minimum->next;
                    }
                }
                minimum=minimum->next;
            }

        }

//            node* sorted = NULL;
//
//
//            node* current = head;
//            int count=0;
//            while (current != NULL)
//            {
//                node* next = current->next;
//                current->prev = current->next = NULL;
//                insert(current->get_data(),count);
//                current = next;
//                count++;
//            }
//            head= sorted;

//        if(!head)
//        {}
//        else
//        {
//            auto min=head;
//            auto current=head->next;
//            int i,j,temp,temp2;
//            for(i=1;i<size();i++)
//            {
//                temp=current->get_data();
//                if(temp<min->get_data())
//                {
//                   swap(i,j);
//                }
//
//            }
//        }
    }

    doubly_linked_list doubly_linked_list::operator+(const doubly_linked_list &rhs) const
    {
        doubly_linked_list returner=*this;
        node*copy=rhs.head;
        while(copy)//copy another list
        {
            returner.append(copy->get_data());
            copy=copy->next;
        }
        return returner;
    }

    doubly_linked_list& doubly_linked_list::operator=(const doubly_linked_list &rhs)
    {
        if(!rhs.head)
        {
            head=nullptr;
            tail=nullptr;
        }
        else{
            auto anode=rhs.head;
            while(anode)
            {
                append(anode->get_data());
                anode=anode->next;
            }
        }
        return *this;
//        if (&rhs == this)
//            return *this;
//
//        else if(rhs.head==NULL)
//        {
//            head= nullptr;
//            tail= nullptr;
//            return *this;
//        }
//        else
//        {
//            node*copy=rhs.head;
//            while(copy)
//            //while(copy->next)
//            {
//                append(copy->get_data());
//                copy=copy->next;
//            }
////            append(copy->get_data());
////            tail->next=NULL;
//        }
//        return *this;
    }

    doubly_linked_list& doubly_linked_list::operator+=(const doubly_linked_list &rhs)
    {
//        if(rhs.head)
//        {
            node*adder=rhs.head;
            while(adder)
            {
            append(adder->get_data());
            adder=adder->next;
            }
//        }
            return *this;
    }

    bool doubly_linked_list::operator==(const doubly_linked_list &rhs)
    {
        node*temp0=this->head;
        node*temp1=rhs.head;
        if(rhs.size()!=size())
        {
        return false;
        }
        while(temp0)
        {
            if(temp0->get_data()!=temp1->get_data())
            {
                return false;
            }
            temp0=temp0->next;
            temp1=temp1->next;
        }
        return true;
    }

//        else if(!head && !rhs.head)
//            return false;

//        else if(head && rhs.head)
//        {


    std::ostream &operator<<(std::ostream &stream, doubly_linked_list &RHS)
    {
        node*out=RHS.head;
        if(!out)
        {
            stream<<"NULL";
        }
        else if(out)
        {
            stream<<"NULL"<<" <- "<<out->get_data()<<" <-> ";
            out=out->next;
            while(out->next)
            {
                stream<<out->get_data()<<" <-> ";
                out=out->next;
            }
            stream<<out->get_data()<<" -> "<<"NULL";
        }

    }

    std::istream &operator>>(std::istream &stream, doubly_linked_list &RHS)
    {

        int i;
        stream>>i;
        RHS.append(i);
    }
}

