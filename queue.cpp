#include <iostream>
using namespace std;

template <typename T>
struct Node{
    T data;
    Node<T> *next;

    Node(T data = T(), Node<T> *next = nullptr): data(data), next(next){};
};

template <typename T>
class Queue{
private:
    int ssize;
    Node<T> *head;
public:
    friend ostream& operator<<(ostream& os, const Queue<T>& queue){
        Node<T>* curr = queue.head;
        while(curr != nullptr){
            os<< curr->data;
            if(curr->next != nullptr){
                os << "->";
            }
            curr = curr->next;
        }
        os << "->" << endl;
        return os;
    }

    Queue();
    ~Queue();

    void enqueue(T data);
    T dequeue();
    T front();
    bool isEmpty();
    int size(){return ssize;};
    void pop();
    void clear();
};

template <typename T>
Queue<T>::Queue(){
    ssize = 0;
    head = nullptr;
}

template <typename T>
Queue<T>::~Queue(){
    clear();
}

template <typename T>
void Queue<T>::enqueue(T data) {
    Node<T> *nNode = new Node<T>(data); 
    if(head == nullptr){
        head = nNode;
    }else{
        nNode->next = head;
        head = nNode;
    }
    ssize++;
}

template <typename T>
T Queue<T>::dequeue(){
    Node<T> *toDelete = new Node<T>;
    if(isEmpty()){
        cout << "queue is empty" << endl;
        return T();
    }else{
        T val{};
        Node<T> *prev = head;
        for(int i{}; i < ssize-2; i++){
            prev = prev->next;
        }
        toDelete = prev->next;
        val = toDelete->data;
        delete toDelete;
        ssize--;
        prev->next = nullptr;
        return val;
    }
}

template <typename T>
T Queue<T>::front(){
    if(isEmpty()){
        cout << "queue is empty" << endl;
        return T();
    }
    return head->data;
}

template <typename T>
bool Queue<T>::isEmpty(){
    return (ssize == 0) ? true : false;
}

template <typename T>
void Queue<T>::pop(){
    Node<T> *toDelete = new Node<T>;
    if(isEmpty()){
        cout << "queue is empty" << endl;
        return;
    }else{
       toDelete = head;
       head = toDelete->next;
       delete toDelete;
       ssize--;
       return;       
    }
}
template <typename T>
void Queue<T>::clear() {
    while(head != nullptr){
        pop();
    }
};


#include <iostream>
using namespace std;

int main() {
    // Создание очереди
    Queue<int> q;

    // Тест 1: Проверка пустоты очереди
    cout << "Is queue empty? " << (q.isEmpty() ? "Yes" : "No") << endl;  // Ожидаемый вывод: Yes

    // Тест 2: Добавление элементов в очередь
    cout << "Enqueuing 10, 20, 30 to the queue." << endl;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Queue after enqueueing 10, 20, 30: ";
    cout << q;  // Ожидаемый вывод: 10->20->30->

    // Тест 3: Проверка первого элемента очереди
    cout << "Front element: " << q.front() << endl;  // Ожидаемый вывод: 10

    // Тест 4: Извлечение элемента
    int val = q.dequeue();
    cout << "Dequeued element: " << val << endl;  // Ожидаемый вывод: 10
    cout << "Queue after dequeue: ";
    cout << q;  // Ожидаемый вывод: 20->30->

    // Тест 5: Проверка первого элемента после извлечения
    cout << "Front element after dequeue: " << q.front() << endl;  // Ожидаемый вывод: 20

    // Тест 6: Удаление элемента с начала очереди (pop)
    q.pop();
    cout << "Queue after pop: ";
    cout << q;  // Ожидаемый вывод: 30->

    // Тест 7: Удаление последнего элемента с помощью pop
    q.pop();
    cout << "Queue after pop (empty): ";
    cout << q;  // Ожидаемый вывод: (пустая очередь)

    // Тест 8: Попытка извлечь элемент из пустой очереди
    cout << "Attempting to dequeue from empty queue:" << endl;
    q.dequeue();  // Ожидаемый вывод: queue is empty

    // Тест 9: Добавление элементов снова
    q.enqueue(40);
    q.enqueue(50);
    cout << "Queue after enqueueing 40 and 50: ";
    cout << q;  // Ожидаемый вывод: 40->50->

    // Тест 10: Очистка очереди
    q.clear();
    cout << "Queue after clear: ";
    cout << q;  // Ожидаемый вывод: (пустая очередь)

    return 0;
}
