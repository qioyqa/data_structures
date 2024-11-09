#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T data = T(), Node<T>* next = nullptr) : data(data), next(next) {}
};

template <typename T>
class LinkedList {
public:
    friend ostream& operator<<(ostream& os, const LinkedList<T>& list) {
        typename Node<T>::Node<T>* curr = list.head;
        while (curr != nullptr) {
            os << "[" << curr->data << "]";
            if (curr->next != nullptr) {
                os << "->";
            }
            curr = curr->next;
        }
        os << "->nullptr" << endl;
        return os;
    }

    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList<T>& other); 
    LinkedList<T>& operator=(const LinkedList<T>& other);

    void push_back(T data);
    void push_front(T data);
    void pop_back();
    void pop_front();
    void clear();
    void insert(T data, int index);
    void remove(int index);
    T& operator[](const int index);
    T get(int index) const;
    void set(T data, int index);

    bool operator==(const LinkedList<T>& other) const;
    bool operator!=(const LinkedList<T>& other) const;

private:
    Node<T>* head;
    Node<T>* tail;
    int size;
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), size(0) {
    Node<T>* curr = other.head;
    while (curr != nullptr) {
        push_back(curr->data);
        curr = curr->next;
    }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != &other) {
        clear();
        Node<T>* curr = other.head;
        while (curr != nullptr) {
            push_back(curr->data);
            curr = curr->next;
        }
    }
    return *this;
}

template <typename T>
void LinkedList<T>::push_back(T data) {
    Node<T>* newNode = new Node<T>(data);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    ++size;
}

template <typename T>
void LinkedList<T>::push_front(T data) {
    Node<T>* newNode = new Node<T>(data, head);
    head = newNode;
    if (!tail) {
        tail = newNode;
    }
    ++size;
}

template <typename T>
void LinkedList<T>::pop_back() {
    if (!head) return;

    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node<T>* curr = head;
        while (curr->next != tail) {
            curr = curr->next;
        }
        delete tail;
        tail = curr;
        tail->next = nullptr;
    }
    --size;
}

template <typename T>
void LinkedList<T>::pop_front() {
    if (!head) return;

    Node<T>* temp = head;
    head = head->next;
    if (!head) {
        tail = nullptr;
    }
    delete temp;
    --size;
}

template <typename T>
void LinkedList<T>::clear() {
    while (head) {
        pop_front();
    }
}

template <typename T>
void LinkedList<T>::insert(T data, int index) {
    if (index < 0 || index > size) return;

    if (index == 0) {
        push_front(data);
    } else if (index == size) {
        push_back(data);
    } else {
        Node<T>* newNode = new Node<T>(data);
        Node<T>* curr = head;
        for (int i = 0; i < index - 1; ++i) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
        ++size;
    }
}

template <typename T>
void LinkedList<T>::remove(int index) {
    if (index < 0 || index >= size) return;

    if (index == 0) {
        pop_front();
    } else {
        Node<T>* curr = head;
        for (int i = 0; i < index - 1; ++i) {
            curr = curr->next;
        }
        Node<T>* toDelete = curr->next;
        curr->next = toDelete->next;
        if (toDelete == tail) {
            tail = curr; 
        }
        delete toDelete;
        --size;
    }
}

template <typename T>
T &LinkedList<T>::operator[](const int index){
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }

    Node<T>* curr = head;
    for (int i = 0; i < index; ++i) {
        curr = curr->next;
    }
    return curr->data;
}

template <typename T>
T LinkedList<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }

    Node<T>* curr = head;
    for (int i = 0; i < index; ++i) {
        curr = curr->next;
    }
    return curr->data;
}

template <typename T>
void LinkedList<T>::set(T data, int index) {
    if (head == nullptr) {
        return;
    } else {
        Node<T>* curr = head;
        for (int i = 0; i < index; ++i) {
            curr = curr->next;
        }
        curr->data = data;
    }
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& other) const {
    if (size != other.size) return false;

    Node<T>* curr1 = head;
    Node<T>* curr2 = other.head;
    while (curr1 != nullptr && curr2 != nullptr) {
        if (curr1->data != curr2->data) return false;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    return true;
}

template <typename T>
bool LinkedList<T>::operator!=(const LinkedList<T>& other) const {
    return !(*this == other);
}

int main() {
    LinkedList<int> lst;
    lst.push_front(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);

    lst.insert(5, 2);
    lst.set(4, 2);

    cout << "List: " << lst;

    LinkedList<int> lst2 = lst;
    lst2.push_front(1);
    cout << "List2 (copy of List): " << lst2;

    cout << "Are the no lists equal? " << (lst != lst2 ? "Yes" : "No") << endl;

    lst.clear();

    return 0;
}
