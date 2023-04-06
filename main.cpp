#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

class Stack {
public:
    virtual void push(int data) = 0;
    virtual int pop() = 0;
    virtual int stackTop() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
    virtual void display() = 0;
};

class ArrStack : public Stack{

private:
    int* stackArr;
    int size;
    int top =-1;
public:
    explicit ArrStack(int size=10){
        this->size=size;
        stackArr = new int[size];
    }

    void push(int data){
        if(isFull()){
            cout<<"Stack Overflow"<<endl;
        }
        else{
            stackArr[++top] = data;
        }
    }

    int pop(){
        if(isEmpty())
            cout<<"Stack Underflow"<<endl;
        else
            return stackArr[top--];
    }

    bool isEmpty(){
        return top==-1;
    }

    bool isFull(){
        return top==(size-1);
    }

    int stackTop(){
        if(isEmpty()){
            cout<<"Stack is empty"<<endl;
            return -1;
        }

        else
            return stackArr[top];
    }

    void display(){
        cout<<endl;
        for(int i=top;i>=0;i--)
            cout<<stackArr[i]<<endl;
        cout<<endl;
    }

};

class LinkListStack : public Stack{
    class Node{
    public:
        int data;
        Node* next = nullptr;

        explicit Node(int data) : data(data) {}
    };

private:
    Node* head;
public:
    explicit LinkListStack(){
        head = nullptr;
    }

    void push(int data){
        Node* node = new Node(data);
        if(isEmpty())
            head = node;
        else{
            node->next = head;
            head=node;
        }
    }

    int pop(){
        if(isEmpty()) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        else{
            int data = head->data;
            head=head->next;
            return data;
        }
    }

    int stackTop(){
        if(isEmpty()){
            cout<<"Stack is Empty"<<endl;
            return -1;
        }
        else return head->data;
    }

    bool isFull(){
        return false;
    }

    bool isEmpty(){
        return head== nullptr;
    }

    void display(){
        cout<<endl;
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << endl;
            current = current->next;
        }
        cout<<endl;
    }

};

int timeTakenForPush(Stack& stack, vector<int>& pushInputs){
    int time=0;
    for(auto data:pushInputs){

        // time start
        auto start_time = std::chrono::high_resolution_clock::now();

        stack.push(data);

        // time end
        auto end_time = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        time+=duration.count();
    }
    return time;
}

int timeTakenForPop(Stack& stack,int numOFPops){
    int time =0;

    for(int i=0;i<numOFPops;i++) {

        // time start
        auto start_time = std::chrono::high_resolution_clock::now();

        stack.pop();

        // time end
        auto end_time = std::chrono::high_resolution_clock::now();

        // calculate time
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        time+=duration.count();
    }
    return time;
}

int timeTakenForDisplay(Stack& stack){
    int time =0;
    // time start
    auto start_time = std::chrono::high_resolution_clock::now();
    stack.display();

    // time end
    auto end_time = std::chrono::high_resolution_clock::now();

    // calculate time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    time+=duration.count();

    return time;
}

vector<int> createRandomArray(int size) {
    vector<int> randArray(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 99);
    for (int i = 0; i < size; i++)
        randArray[i] = dis(gen);
    return randArray;
}

int timeTaken(Stack& stack,vector<int>& pushInputs,int numOfPops){

    int timeForPush =timeTakenForPush(stack,pushInputs);
    cout<<typeid(stack).name()<<" is displaying after pushing"<<endl;
    int timeForDisplay01 = timeTakenForDisplay(stack);
    int timeForPop = timeTakenForPop(stack,numOfPops);
    cout<<typeid(stack).name()<<" is displaying after popping"<<endl;
    int timeForDisplay02 = timeTakenForDisplay(stack);

    return (timeForPush+timeForDisplay01+timeForPop+timeForDisplay02);

}

void testStack(int numOFPushes, int numOfPops){

    int totalTimeForArrStack=0;
    int totalTimeForLinklistStack =0;

    for(int i=0;i<10;i++) {

        ArrStack arrStack;
        LinkListStack linkListStack;

        auto pushInputs = createRandomArray(numOFPushes);

        auto timeTakenForArrStack = timeTaken(arrStack, pushInputs, numOfPops);
        auto timeTakenForLinkListStack = timeTaken(linkListStack, pushInputs, numOfPops);

        totalTimeForArrStack+=timeTakenForArrStack;
        totalTimeForLinklistStack+=timeTakenForLinkListStack;
    }

    cout<<"Time taken for Array implementation of Stack : "<< totalTimeForArrStack/10<<endl;
    cout<<"Time taken for Linklist implementation of Stack : "<<totalTimeForLinklistStack/10<<endl;

}

int main() {

    testStack(10,5);
    return 0;
}
