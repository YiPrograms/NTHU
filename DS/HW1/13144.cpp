#include "function.h"
using namespace std;

#include <algorithm>
#include <iostream>

#define START_CAPACITY 2

template <class T>
BaseStack<T>::BaseStack() : _top(0), capacity(START_CAPACITY) {
    _stack = new T[START_CAPACITY];
}

template <class T>
BaseStack<T>::~BaseStack() {
    delete[] _stack;
}

template <class T>
bool BaseStack<T>::empty() {
    return _top == 0;
}

template <class T>
int BaseStack<T>::size() {
    return _top;
}

template <class T>
T& BaseStack<T>::top() {
    return _stack[_top - 1];
}

template <class T>
void BaseStack<T>::push(const T& item) {
    if (_top == capacity) {
        T* _new = new T[capacity * 2];
        copy(_stack, _stack + capacity, _new);
        capacity *= 2;
        delete[] _stack;
        _stack = _new;
    }
    _stack[_top++] = item;
}

template <class T>
void BaseStack<T>::pop() {
    _top--;
}

template <class T>
BaseQueue<T>::BaseQueue(): _front(0), _rear(0), capacity(START_CAPACITY) {
    _queue = new T[START_CAPACITY];
}

template <class T>
BaseQueue<T>::~BaseQueue() {
    delete[] _queue;
}

template <class T>
bool BaseQueue<T>::empty() {
    return _front == _rear;
}

template <class T>
int BaseQueue<T>::size() {
    return _rear - _front;
}

template <class T>
T& BaseQueue<T>::front() {
    return _queue[_front % capacity];
}

template <class T>
void BaseQueue<T>::push(const T& item) {
    if (_rear - _front == capacity) {
        T* _new = new T[capacity * 2];
        for (int i = _front, j = 0; i < _rear; i++, j++)
            _new[j] = _queue[i % capacity];
        _rear = capacity;
        _front = 0;

        capacity *= 2;
        delete[] _queue;
        _queue = _new;
    }
    _queue[(_rear++) % capacity] = item;
}

template <class T>
void BaseQueue<T>::pop() {
    _front++;
}



BaseQueue<char> *slots;
BaseStack<string> *stk;

void insert(int L) {
    if (slots == NULL)
        slots = new BaseQueue<char>[L];
    
    int pos;
    string s;
    cin >> pos >> s;

    int mx = -1;
    for (int i = pos; i < pos + s.length(); i++)
        mx = max(mx, slots[i].size());

    for (int i = pos; i < pos + s.length(); i++) {
        int obs = mx - slots[i].size();
        while (obs--)
            slots[i].push('@');
        slots[i].push(s[i - pos]);
    }
}

string first_row(int L, bool print) {
    if (slots == NULL)
        slots = new BaseQueue<char>[L];
    string res;
    for (int i = 0; i < L; i++) {
        if (slots[i].empty())
            res += '~';
        else
            res += slots[i].front();
    }

    if (print)
        cout << "BOTTOM_ROW\n" << res << "\n";

    return res;
}

void query(int L) {
    string s;
    cin >> s;

    string btm = first_row(L, false);
    for (int i = 0; i < L - s.length() + 1; i++) {
        if (s.compare(0, s.length(), btm, i, s.length()) == 0) {
            for (int k = i; k < i + s.length(); k++)
                slots[k].pop();

            if (stk == NULL)
                stk = new BaseStack<string>;
            stk->push(s);
            break;
        }
    }
}

void flush() {
    cout << "FLUSH\n";
    if (stk == NULL)
        return;

    while (!stk->empty()) {
        cout << stk->top() << "\n";
        stk->pop();
    }
}

void reset(int L) {
    delete[] slots;
    slots = NULL;
    delete stk;
    stk = NULL;
}

