#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
#include <queue>


using namespace std; 


template <typename T>
class Stack
{
private:
    class Node {
    public:
        T data;
        Node* prev;
        Node* next;

        Node(int value) : data(value), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    int count;

public:
    Stack() : head(nullptr), count(0) {}

    void Push(T value)
    {
        Node* newNode = new Node(value);

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            newNode->next = head;
            head->previous = newNode;
            head = newNode;
        }

        count++;
    }

    T Pop()
    {
        if (IsEmpty())
        {
            throw std::runtime_error("Stack is empty");
        }

        T data = head->data;
        Node* temp = head;

        head = head->next;

        if (head != nullptr)
        {
            head->previous = nullptr;
        }

        delete temp;
        count--;

        return data;
    }

    T Top()
    {
        if (IsEmpty())
        {
            throw std::runtime_error("Stack is empty");
        }

        return head->data;
    }

    bool IsEmpty()
    {
        return count == 0;
    }

    int Size()
    {
        return count;
    }
};



template <typename T>
class DoublyLinkedList {
private:
    class Node {
    public:
        T data;
        Node* prev;
        Node* next;

        Node(int value) : data(value), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int length;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), length(0) {}

    void insertAt(int index, int value) {
        if (index < 0 || index > length) {
            throw std::out_of_range("Index out of range");
        }

        Node* newNode = new Node(value);

        if (index == 0) {
            prepend(value);
        }
        else if (index == length) {
            append(value);
        }
        else {
            Node* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }

            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;

            length++;
        }
    }

    void removeAt(int index) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }

        if (index == 0) {
            Node* temp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            delete temp;
        }
        else if (index == length - 1) {
            Node* temp = tail;
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
            delete temp;
        }
        else {
            Node* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }

            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }

        length--;
    }

    void append(T value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }

        length++;
    }

    void prepend(T value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        length++;
    }

    int get(int index) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }

    int getLength() {
        return length;
    }
};

template <typename T>
class DynamicArray {
private:
    T* arr;
    int size;
    int capacity;

    bool AllowedIndex(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Index is not available!" << std::endl;
            return false;
        }

        return true;
    }


public:
    DynamicArray() {
        capacity = 10;
        size = 0;
        arr = new T[capacity];
    }

    ~DynamicArray() {
        delete[] arr;
    }


    int getSize() {
        return size;
    }

    void insertAt(int index, T value) {
        if (AllowedIndex(index)) return;

        if (size == capacity) {
            resize();
        }

        for (int i = size; i > index; i--) {
            arr[i] = arr[i - 1];
        }

        arr[index] = value;
        size++;
    }

    void remove(T value) {
        int index = -1;

        for (int i = 0; i < size; i++) {
            if (arr[i] == value) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            removeAt(index);
        }
        else {
            std::cout << "Element is not found!" << std::endl;
        }
    }

    void removeAt(int index) {
        if (AllowedIndex(index)) return;

        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }

        size--;
    }

    void append(T value) {
        if (size == capacity) {
            resize();
        }

        arr[size] = value;
        size++;
    }

    T get(int index) {

        if (AllowedIndex(index)) return;
        return arr[index];
    }

    int getCapacity() {
        return capacity;
    }

private:
    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];

        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
    }
};


int getPrecedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '^')
        return 3;
    else if (op == 's' || op == 'c' || op == 't')
        return 4;
    else
        return 0;
}

double applyOperator(double a, double b, char op) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a, b);
    case 's':
        return sin(b);
    case 'c':
        return cos(b);
    case 't':
        return tan(b);
    }
    return 0;
}

double evaluateExpression(string expression) {
    stack<char> operators;
    queue<double> operands;

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ')
            continue;

        if (isdigit(expression[i])) {
            double operand = 0;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                operand = operand * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            operands.push(operand);
        }
        else if (expression[i] == '(') {
            operators.push('(');
        }
        else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                double b = operands.front();
                operands.pop();

                double a = operands.front();
                operands.pop();

                char op = operators.top();
                operators.pop();

                double result = applyOperator(a, b, op);
                operands.push(result);
            }
            operators.pop(); // Remove '('
        }
        else {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(expression[i])) {
                double b = operands.front();
                operands.pop();

                double a = operands.front();
                operands.pop();

                char op = operators.top();
                operators.pop();

                double result = applyOperator(a, b, op);
                operands.push(result);
            }
            operators.push(expression[i]);
        }
    }

    while (!operators.empty()) {
        double b = operands.front();
        operands.pop();

        double a = operands.front();
        operands.pop();

        char op = operators.top();
        operators.pop();

        double result = applyOperator(a, b, op);
        operands.push(result);
    }

    return operands.front();
}


int main() {
    string expression;
    cout << "Enter an expression: ";
    getline(cin, expression);

    double result = evaluateExpression(expression);
    cout << "Result: " << result << endl;

    return 0;
}