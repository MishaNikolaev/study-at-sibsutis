#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdexcept>

using namespace std;

struct Node {
    Node* next;
    int data;
};

class List {
protected:
    Node* head;

public:
    List() : head(nullptr) {}

    List(const List& other) : head(nullptr) {
        Node* current = other.head;
        while (current) {
            add(current->data);
            current = current->next;
        }
    }
    virtual ~List() {
        clear();
    }

    virtual void add(int k) = 0;

    virtual bool remove(int k) = 0;

    virtual void print() = 0;

    virtual void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
    }

    Node* getHead() const {
        return head;
    }

    static int getSize(Node* head) {
        int size = 0;
        Node* p = head;
        while (p != nullptr) {
            size++;
            p = p->next;
        }
        return size;
    }
};

class Stack : public List {
public:
    Stack() : List() {}

    ~Stack() = default;

    void add(int k) override {
        Node* p = new Node;
        p->data = k;
        p->next = head;
        head = p;
    }

    bool remove(int k) override {
        if (head == nullptr) {
            throw runtime_error("Error: Stack is empty!");
        }

        if (head->data == k) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
            return true;
        }

        Node* p = head;
        while (p->next != nullptr) {
            if (p->next->data == k) {
                Node* tmp = p->next;
                p->next = p->next->next;
                delete tmp;
                return true;
            }
            p = p->next;
        }
        throw runtime_error("Error: Element not found in the stack!");
    }

    void print() override {
        if (head == nullptr) {
            cout << "Stack is empty!" << endl;
            return;
        }

        Node* p = head;
        while (p != nullptr) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
};

class Queue : public List {
protected:
    Node* tail;

public:
    Queue() : List(), tail(nullptr) {}

    ~Queue() = default;

    void add(int k) override {
        Node* p = new Node;
        p->data = k;
        p->next = nullptr;
        if (head == nullptr) {
            head = p;
            tail = p;
        } else {
            tail->next = p;
            tail = p;
        }
    }

    bool remove(int k) override {
        if (head == nullptr) {
            throw runtime_error("Error: Queue is empty!");
        }

        if (head->data == k) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
            if (head == nullptr) tail = nullptr;
            return true;
        }

        Node* p = head;
        while (p->next != nullptr) {
            if (p->next->data == k) {
                Node* tmp = p->next;
                p->next = p->next->next;
                if (tmp == tail) tail = p;
                delete tmp;
                return true;
            }
            p = p->next;
        }
        throw runtime_error("Error: Element not found in the queue!");
    }

    void print() override {
        if (head == nullptr) {
            cout << "Queue is empty!" << endl;
            return;
        }

        Node* p = head;
        while (p != nullptr) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

    void clear() override {
        List::clear();
        tail = nullptr;
    }
};

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Queue queue;
    Stack stack;
    int i = 0;
    char ch;

    do {
        system("cls");
        cout << "Stack: ";
        stack.print();
        cout << "Queue: ";
        queue.print();
        cout << "Enter command (+ to add, - to remove, s for size, c to clear, ESC to exit): ";
        ch = getch();

        try {
            if (ch == '+') {
                cout << "Element: ";
                cin >> i;
                queue.add(i);
                stack.add(i);
            } else if (ch == '-') {
                cout << "Element: ";
                cin >> i;
                int counter = 0;

                try {
                    stack.remove(i);
                    counter++;
                } catch (const runtime_error&) {
                    cout << "Error: Element not found in the stack!" << endl;
                }

                try {
                    queue.remove(i);
                    counter++;
                } catch (const runtime_error&) {
                    cout << "Error: Element not found in the queue!" << endl;
                }

                if (counter != 2) {
                    cout << "Press any key to continue!\n";
                    getch();
                }
            } else if (ch == 's') {
                cout << "\nStack size: " << List::getSize(stack.getHead()) << "\n";
                cout << "Queue size: " << List::getSize(queue.getHead()) << "\n";
                cout << "Press any key to continue!\n";
                getch();
            } else if (ch == 'c') {
                queue.clear();
                stack.clear();
                cout << "Both structures have been cleared!" << endl;
                getch();
            }
        } catch (const runtime_error&) {
            cout << "An error occurred!" << endl;
            getch();
        }
    } while (ch != 27);

    cout << "\nPress any key to finish!\n";
    getch();
    return 0;
}