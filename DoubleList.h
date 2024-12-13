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
    // ����������� �� ���������
    MyList() : head(nullptr), tail(nullptr), size_(0) {}

    // ����������� �����������
    MyList(const MyList& other) : head(nullptr), tail(nullptr), size_(0) {
        Node<T>* current = other.head;
        while (current != nullptr) {
            push_tail(current->data);
            current = current->next;
        }
    }

    // �������� ������������
    MyList& operator=(const MyList& other) {
        if (this != &other) {
            Clear(); // ������� ������� ������
            Node<T>* current = other.head;
            while (current != nullptr) {
                push_tail(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // ����������
    ~MyList() {
        Clear();
    }

    // ���������� �������� � ������ ������
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
        if (other.head == nullptr) return; // ��������� ������� ������

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

    // ���������� �������� � ����� ������
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
        if (other.head == nullptr) return; // ��������� ������� ������

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

    // �������� �������� �� ������ ������
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

    // �������� �������� �� ����� ������
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

    // �������� ���� ��������� � ��������� ���������
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

    // ������ ������
    size_t size() const {
        return size_;
    }

    // �������� ������� �� ������� (������)
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

    // �������� ������� �� ������� (������)
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

    // ������� ������
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

    // ����������� � ���������� ��������� ��������
    MyList(size_t n, T minValue, T maxValue) : head(nullptr), tail(nullptr), size_(0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<T> dist(minValue, maxValue);

        for (size_t i = 0; i < n; ++i) {
            push_tail(dist(gen));
        }
    }
    ���

    // ������� ��� ������ ������� ����� � �������������� ������ ����������
    void FindPrimesInRange(int N) {
        std::vector<bool> sieve(N + 1, true);
        sieve[0] = sieve[1] = false; // 0 � 1 �� �������� �������� �������

        // ���������� ������ ����������
        for (int i = 2; i * i <= N; ++i) {
            if (sieve[i]) {
                for (int j = i * 2; j <= N; j += i) {
                    sieve[j] = false;
                }
            }
        }

        // ������� ������ ������� ����� �� ������
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


