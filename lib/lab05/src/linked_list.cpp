#include <linked_list.h>
namespace lab5 {
    linked_list::linked_list() {
        head=NULL;
        tail=NULL;
    }
        linked_list::linked_list(std::string &data){
        head=new node(data);
        tail=head;
    }

    linked_list::linked_list(const linked_list &original)//copy constructor
    {
        if(original.listSize()!=0)
        {
            node *copy = original.head;
            while (copy->next != NULL)
            {
                append(copy->data);//append the head
                copy = copy->next;//increment copy
            }
            append(copy->data);
            tail->next=NULL;//inc tail and loop
        }
        else{
            head=NULL;
            tail=NULL;
        }
    }



    linked_list::~linked_list()
        {
        node*del=head;
        while (del!= nullptr)
        {
            head=head->next;
            delete del;
            del=head;
        }

    }

    linked_list &lab5::linked_list::operator=(const linked_list &RHS) {//delete every node first then assign

        if (&RHS == this)
            return *this;
        else if(RHS.head==NULL)
        {
            head= nullptr;
            tail= nullptr;
            return *this;
        }
        else{
            node*copy=RHS.head;
            while(copy->next!=nullptr)
            {
                append(copy->data);
                copy=copy->next;
            }
            append(copy->data);
            tail->next=NULL;
        }
        return *this;
    }
        bool linked_list::isEmpty() const {
            return !head;
        }

    unsigned linked_list::listSize() const {
        if(head==NULL)
            return 0;
        unsigned c = 0;
        node*tmp = head;
        while(tmp!=nullptr) {
            tmp = tmp->next;
            c++;
        }
        return c;
    }
/*Runner algorithm

        node*tmp=n1;
        while(tmp!=null)
        {
            cout<<tmp->data<<endl;
            tmp=tmp->next;
        }
 */
    void linked_list::insert(const std::string input, unsigned int location) {
        if(location >listSize())
        {
            //   throw -1;
        }
        else if(!head)//head is NULL
            append(input);
        else if(location==0)
        {
            auto newhead=new node(input);
            newhead->next=head;
            head=newhead;
        }
        else
        {
            int counter=0;
            node*prev;
            prev=head;
            while(counter<location-1)
            {
                prev=prev->next;
                counter++;
            }//reaches the index to insert
            node*nextn=new node(input);
            nextn->next=prev->next;
            prev->next=nextn;
        }
    }
    void linked_list::append(const std::string input) {
        if (!head) {
            head = new node(input);
            tail = head;
        } else {
            tail->next = new node(input);
            tail = tail->next;
        }
    }
    void linked_list::remove(unsigned location)
    {
        int counter =0;
        if(head!=nullptr && location<=listSize() && location==0)
        {
            node*del=head;
            node*newh=head;
            newh=newh->next;
            delete del;
            head=newh;
        }
        else
        {

            auto tmp = head;
            unsigned c = 0;
            while(tmp && c < location - 1) {
                tmp = tmp->next;
                c++;
            }
            if (!tmp || !tmp->next){}// throw std::exception();
            auto toDelete = tmp->next;
            tmp->next = tmp->next->next;
            delete toDelete;
        }
    }

    std::ostream& operator<<(std::ostream &stream, linked_list &RHS) {
        node*out=RHS.head;
        for(int i=0;i<RHS.listSize();i++) {
            stream << out->data <<" -> ";
            out=out->next;
        }
        stream<<"NULL";

    }

    std::istream& operator>>(std::istream &stream, linked_list &RHS) {
        std::string val;
        stream>>val;
        RHS.append(val);
        return stream;
    }

    void linked_list::sort() {
        node*temp=head;
        node*min;
        while(temp!= nullptr)
        {
            min=temp;
            node*swap=temp->next;
            while(swap!= nullptr)
            {
                if(min->data > swap->data)
                    min=swap;
                swap=swap->next;
            }

            std::string s=temp->data;
            temp->data=min->data;
            min->data=s;
            temp=temp->next;

        }
    }


    std::string linked_list::get_value_at(unsigned location) const {
        unsigned c = 0;
        auto tmp = head;
        while (tmp && c < location) {
            tmp = tmp->next;
            c++;
        }
        if (tmp) return tmp->data;
        else throw std::exception();
    }

}

//Look on my works, ye mighty, and despair:


/*
//       if(original.head==NULL)
//            head=NULL;
//        else{
//        node *temp = nullptr;
//        this->head=original.head;
//        while(original.head->next!=nullptr)
//            temp=this->head->next=original.head;
//        this->tail=temp;
//        delete temp;}

//        node *nextL= nullptr;
//        node *current= nullptr;
//        current=head;
//        while(current!=nullptr)
//        {
//            nextL=current;
//            current=current->next;
//            delete nextL;
//        }

//
//            int count = 0;
//            //deletion, basically copied the destructor code
//            if(head!=NULL)
//            {
//            node *nextL= nullptr;
//            node *current= nullptr;
//            current=head;
//            while(current->next!=nullptr)
//            {
//                nextL=current;
//                current=current->next;
//                delete nextL;
//            }
//            head= nullptr;
//            tail=nullptr;
//            }
//            //copy assignment
////            if (RHS.head == NULL)//if empty linked list
////                head = NULL;
//            node *copy = RHS.head;
//            head=new node(copy->data);
//            node*tmp=NULL;
//            while (copy!=nullptr)
//            {
//                if(head==NULL)
//                    head=tmp=new node(RHS.head->data);
//                else{
//                    tmp->next=new node(copy->data);
//                    tmp=tmp->next;
//                }
//                copy=copy->next;
//            }
//            return *this;
//            }

    //            if (RHS.head == NULL)
//            {
//                head = NULL;
//                tail = NULL;
//            }
//
//            node *prev = nullptr;
//            node *current = RHS.head;
//            head = current;//right side's head copied to head
//
//            while (current->next != nullptr)//if rhs next is not null, make head.next... into prev
//            {
//                prev = current;//the head set to rhs head
//                current = current->next;//head.next of RHS iterated
//                head->next = prev;
//            }
//            if (current->next == nullptr)//next was null, so we are at the end
//                tail = current;
//
//            delete prev;
//            delete current;


//dequeue in queue
//node*temp= head;
//    head->head.next;

//stack
//node*prev=null;
//node*tmp=head;
//while tmp.next!=null;
//  prev=tmp;
//  tmp=tmp.next;

    void linked_list::insert(const std::string input, unsigned int location)
    {

        if(location >listSize())
        {
         //   throw -1;
        }
        else if(!head)//head is NULL
            append(input);
        else if(location==0)
        {
            auto newhead=new node(input);
            newhead->next=head;
            head=newhead;
        }
        else
        {
            int counter=0;
            node*prev;

            prev=head;
            while(counter<location-1)
            {
                prev=prev->next;
                counter++;
            }//reaches the index to insert
            node*nextn=new node(input);
            nextn->next=prev->next;
            prev->next=nextn;

        }
    }
*/

//        int counter=0;
//        if(location>0 && location<listSize())
//        {
//            node*prev=head;
//
//            while(prev->next!=NULL && counter<location-1)
//            {
//                prev=prev->next;
//                counter++;
//            }//reaches the index to insert
//            node*nextn=new node(input);
//
//            nextn->next=prev->next;
//            prev->next=nextn;
//        }
//        if(location==0)//add to head
//        {
//            if(head==NULL)
//            {
//                node*tmp=new node(input);
//                head=tmp;
//                tail=tmp;
//            }
//            else
//            {
//                node *tmp = new node(input);
//                tmp->next = head;
//                head = tmp;
//            }
//        }
//        else if(location==listSize() && location!=0)
//        {
//            node* nTail=new node(input);
//            tail->next=nTail;
//            tail=nTail;
//            tail->next=nullptr;
//        }

//
//        current=head;
//        if(head!=NULL)
//        {
//            while(current->next!=NULL && counter!=location)
//            {
//                prev=current;
//                current=current->next;
//                ++counter;
//            }
//
//            if(location==0)//addtohead
//            {
//                nNode->next=head;//new node points to head
//                head=nNode;//head is now newnode
//            }
//            else if(current->next==NULL & location==counter+1)//add to tail
//            {
//                tail->next=nNode;//.next automatically points to null
//                nNode=tail;//becomes new tail
//            }
//        }
//        else if(head==NULL)
//        {
//            append(input);
//        }

/*
    void linked_list::append(const std::string input)
    {
        node*current=new node(input);

        if(!head)//addtohead
        {//new node points to head
            head=current;
            tail=head;
        }
        else{
            tail->next=current;
            tail=tail->next;
        }

    }

    //        int counter =0;
//        if(head!=nullptr && location<=listSize() && location==0)
//        {
//            node*del=head;
//            node*newh=head;
//            newh=newh->next;
//            delete del;
//            head=newh;
//        }
//
//        if(head!=nullptr && location<=listSize() &&location>0) {
//            node *del=head;
//
//            if (del != nullptr) {
//                while (counter < location-1) {
//                    del = del->next;
//                    counter++;
//                }
//                node *temp = del;
//                temp->next = del->next;
//                delete del;
//            }
//        }

 //        node*sortthis=head;
//        auto sortedlist=new linked_list();
//        for(int i=0;i<listSize();i++)
//        {
//            for(int j=i;j<listSize();j++)
//            {
//                if(get_value_at(j)>get_value_at(i))
//                {
//
//                }
//            }
//        }

//        int c=0;
//        node*tmp;
//        if(head!=NULL)
//        {
//            tmp=head;
//            if(location>=0 && location<=listSize())
//            {
//                else if(location>listSize())
//                {//get last element instead if out of bounds
//                    while (c < location)
//                    {
//                        tmp = tmp->next;
//                        c++;
//                    }
//                    return tmp->data;
//                }
//                return "NULL";
//            }
//
//            else if(head==NULL){
//                //
//            }         while (c < location)
//                {
//                    tmp = tmp->next;
//                    c++;
//                }
//                return tmp->data;
//            }
//

*/
