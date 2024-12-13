#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
class Node {
public:
    T data;
    Node* prev;
    Node* next;

    Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
};

template <typename T>
class MyList {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size_;

public:
    // Конструктор по умолчанию
    MyList() : head(nullptr), tail(nullptr), size_(0) {}

    // Конструктор копирования
    MyList(const MyList& other) : head(nullptr), tail(nullptr), size_(0) {
        Node<T>* current = other.head;
        while (current != nullptr) {
            push_tail(current->data);
            current = current->next;
        }
    }

    // Оператор присваивания
    MyList& operator=(const MyList& other) {
        if (this != &other) {
            Clear(); // Очищаем текущий список
            Node<T>* current = other.head;
            while (current != nullptr) {
                push_tail(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Деструктор
    ~MyList() {
        Clear();
    }

    // Добавление элемента в начало списка
    void push_head(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size_++;
    }

    void push_head(MyList<T>& other) { 
        if (other.head == nullptr) return; // Обработка пустого списка

        if (head == nullptr) {
            head = other.head;
            tail = other.tail;
            size_ = other.size_;
            other.head = other.tail = nullptr; 
            other.size_ = 0;

        }
        else {
            other.tail->next = head;
            head->prev = other.tail;
            head = other.head;
            size_ += other.size_;
            other.head = other.tail = nullptr; 
            other.size_ = 0;
        }
    }

    // Добавление элемента в конец списка
    void push_tail(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size_++;
    }

    void push_tail(MyList<T>& other) { 
        if (other.head == nullptr) return; // Обработка пустого списка

        if (tail == nullptr) {
            head = other.head;
            tail = other.tail;
            size_ = other.size_;
            other.head = other.tail = nullptr; 
            other.size_ = 0;
        }
        else {
            tail->next = other.head;
            other.head->prev = tail;
            tail = other.tail;
            size_ += other.size_;
            other.head = other.tail = nullptr; 
            other.size_ = 0;
        }
    }

    // Удаление элемента из начала списка
    void pop_head() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        Node<T>* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
        size_--;
    }

    // Удаление элемента из конца списка
    void pop_tail() {
        if (tail == nullptr) {
            throw std::out_of_range("List is empty");
        }
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete temp;
        size_--;
    }

    // Удаление всех элементов с указанным значением
    void delete_node(const T& value) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                Node<T>* toDelete = current;
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                }
                else {
                    tail = current->prev;
                }
                current = current->next;
                delete toDelete;
                size_--;
            }
            else {
                current = current->next;
            }
        }
    }

    // Размер списка
    size_t size() const {
        return size_;
    }

    // Операция доступа по индексу (чтение)
    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    // Операция доступа по индексу (запись)
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    // Очистка списка
    void Clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size_ = 0;
    }

    // Конструктор с генерацией случайных значений
    MyList(size_t n, T minValue, T maxValue) : head(nullptr), tail(nullptr), size_(0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<T> dist(minValue, maxValue);

        for (size_t i = 0; i < n; ++i) {
            push_tail(dist(gen));
        }
    }
    ‘’’

    // Функция для поиска простых чисел с использованием решета Эратосфена
    void FindPrimesInRange(int N) {
        std::vector<bool> sieve(N + 1, true);
        sieve[0] = sieve[1] = false; // 0 и 1 не являются простыми числами

        // Реализация решета Эратосфена
        for (int i = 2; i * i <= N; ++i) {
            if (sieve[i]) {
                for (int j = i * 2; j <= N; j += i) {
                    sieve[j] = false;
                }
            }
        }

        // Выводим только простые числа из списка
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data <= N && sieve[current->data]) {
                std::cout << current->data << " ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
};


