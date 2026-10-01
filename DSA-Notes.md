# DSA 速记
## 目录
- [01-Complexity](#01-complexity)
    - [大 O、Ω、Θ 表示法](#大-oωθ-表示法)
    - [主定理](#主定理)
- [02-Linear List](#02-linear-list)
    - [顺序表](#顺序表)
    - [链表](#链表)
    - [技巧（链表的相交、反转、合并、回文判断、环的检测）](#技巧)
- [03-Stack and Queue](#03-stack-and-queue)
    - [顺序栈](#顺序栈)
    - [链式栈](#链式栈)
    - [表达式](#表达式)
    - [Shunting yard algorightm（调度场算法）](#shunting-yard-algorightm调度场算法)
    - [队列](#队列)
    - [技巧（循环队列，单调队列）](#技巧-1)
## 01-Complexity
### 大 O、Ω、Θ 表示法
若 $f(x) \leq c \cdot g(x)$，则 $f(x) = O(g(x))$，$g(x) = \Omega(f(x))$。

若 $f(x) = O(g(x))$ 且 $g(x) = O(f(x))$，则 $f(x) = \Theta(g(x))$。
### 主定理
如若：
$$ T(n) = aT\left(\frac{n}{b}\right) + f(n) $$
分为三种情况：
1. 若 $f(n) = O(n^{\log_b a - \epsilon})$，则 $T(n) = \Theta(n^{\log_b a})$。
2. 若 $f(n) = \Theta(n^{\log_b a} \cdot \log^k n)$，则 $T(n) = \Theta(n^{\log_b a} \log^{k+1} n)$。
3. 若 $f(n) = \Omega(n^{\log_b a + \epsilon})$ 且 $af(n/b) \leq cf(n)$，则 $T(n) = \Theta(f(n))$。
## 02-Linear List
### 顺序表
```cpp
template <typename T>
class ArrayList {
public:
    explicit ArrayList(size_type initial_capacity = 8)
        : data_(new T[initial_capacity]), capacity_(initial_capacity), size_(0) {}
    ~ArrayList() { delete[] data_; }
private:
    T* data_;
    size_type capacity_;
    size_type size_;
};
```
### 链表
```cpp
template <typename T>
class LinkedList {
private:
    struct Node {
        T value;
        Node* next;
    };
    Node* head_;
    Node* tail_;
    size_type size_;
public:
    LinkedList() : head_(new Node), tail_(head_), size_(0) {
        head_->next = nullptr;
    }
    ~LinkedList() {
        Node* current = head_;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};
```
可以为 Node 添加一个 prev 指针来实现双向链表。

优点在于，删除已知节点的时间复杂度变为 O(1)，而不需要 O(n) 的时间来查找前驱节点。
### 技巧
- 判断两链表相交：双指针换头
- 反转链表：三指针迭代
- 合并有序列表：使用虚拟头节点 dummy
- 判断链表是否回文：快慢指针找到中点，反转后半链表
- 判断链表是否有环：快慢指针
## 03-Stack and Queue
### 顺序栈
```cpp
template <typename T>
class ArrayStack {
public:
    using value_type = T;
    using size_type = std::size_t;
    explicit ArrayStack(size_type initial_capacity = 8)
        : data_(new T[initial_capacity]), capacity_(initial_capacity), size_(0) {}
    ~ArrayStack() { delete[] data_; }
    ArrayStack(const ArrayStack& other)
        : data_(new T[other.capacity_]), capacity_(other.capacity_), size_(other.size_) {
        for(size_type i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    ArrayStack& operator=(const ArrayStack& other) {
        if(this == &other) return *this;
        T* fresh = new T[other.capacity_];
        for(size_type i = 0; i < other.size_; ++i) {
            fresh[i] = other.data_[i];
        }
        delete[] data_;
        data_ = fresh;
        capacity_ = other.capacity_;
        size_ = other.size_;
        return *this;
    }
    void push(const T& value) {
        if(size_ == capacity_) grow();
        data_[size_++] = value;
    }
    std::optional<T> pop() {
        if(empty()) return std::nullopt;
        return data_[--size_];
    }
    std::optional<T> top() const {
        if(empty()) return std::nullopt;
        return data_[size_ - 1];
    }
    bool empty() const { return size_ == 0; }
    size_type size() const { return size_; }
    void clear() { size_ = 0; }
private:
    void grow() {
        size_type next = (capacity_ == 0) ? 1 : capacity_ * 2;
        T* fresh = new T[next];
        for(size_type i = 0; i < size_; ++i) {
            fresh[i] = data_[i];
        }
        delete[] data_;
        data_ = fresh;
        capacity_ = next;
    }
    T* data_;
    size_type capacity_;
    size_type size_;
};
```
### 链式栈
```cpp
template <typename T>
class LinkedStack {
public:
    using value_type = T;
    using size_type = std::size_t;
    LinkedStack() : top_(nullptr), size_(0) {}
    ~LinkedStack() { clear(); }
    LinkedStack(const LinkedStack& other) : top_(nullptr), size_(0) {
        copy_from(other);
    }
    LinkedStack& operator=(const LinkedStack& other) {
        if(this == &other) return *this;
        clear();
        copy_from(other);
        return *this;
    }
    void push(const T& value) {
        Node fresh = new Node;
        fresh->value = value;
        fresh->next = top_;
        top_ = fresh;
        ++size_;
    }
    std::optional<T> pop() {
        if(empty()) return std::nullopt;
        Node old_top = top_;
        T value = old_top->value;
        top_ = old_top->next;
        delete old_top;
        --size_;
        return value;
    }
    std::optional<T> top() const {
        if(empty()) return std::nullopt;
        return top_->value;
    }
    bool empty() const { return size_ == 0; }
    size_type size() const { return size_; }
    void clear() {
        while(top_ != nullptr) {
            Node old_top = top_;
            top_ = old_top->next;
            delete old_top;
        }
        size_ = 0;
    }
private:
    struct Node {
        T value;
        Node* next;
    };
    Node* top_;
    size_type size_;
    void copy_from(const LinkedStack& other) {
        Node** tail = &top_;
        for(Node* source = other.top_; source != nullptr; source = source->next) {
            Node* fresh = new Node;
            fresh->value = source->value;
            fresh->next = nullptr;
            *tail = fresh;
            tail = &fresh->next;
            ++size_;
        }
    }
};
```
### 表达式
巴科斯范式（BNF）是一种用于表示上下文无关文法的形式化方法。
- <数字> 最底层的砖块
- <常数> 拼成一个多位数
- <因子> 可以是一个数字、一个常数，或者一个括号内的表达式
- <项> 可以是一个因子，或者是一个项与一个因子相乘
- <表达式> 可以是一个项，或者是一个表达式与一个项相加

中缀表达式是我们日常使用的表达式形式，例如 `3 + 4 * 2 / (1 - 5) ^ 2 ^ 3`。

后缀表达式（逆波兰表示法）是将运算符放在操作数之后的表达式形式，例如 `3 4 2 * 1 5 - 2 3 ^ ^ / +`。

后缀表达式的求值可以通过两个栈来实现：一个栈用于存储操作数，另一个栈用于存储运算符。遍历后缀表达式，当遇到操作数时，将其压入操作数栈；当遇到运算符时，从操作数栈中弹出相应数量的操作数，进行运算，并将结果压入操作数栈。最终，操作数栈中剩下的唯一元素就是表达式的值。

### Shunting yard algorightm（调度场算法）
从左到右扫描中缀表达式：
- 操作数：压入后缀表达式
- 左括号：压入运算符栈
- 右括号：弹出运算符栈中的运算符，直到遇到左括号为止，将这些运算符压入后缀表达式
- 运算符：弹出运算符栈中优先级大于或等于当前运算符的运算符，直到遇到左括号或栈底为止，将这些运算符压入后缀表达式，然后将当前运算符压入运算符栈

最终，将运算符栈中剩余的运算符依次弹出，压入后缀表达式。
### 队列
队列是一种先进先出（FIFO）的数据结构。基本操作包括：
- 入队（enqueue）：将元素添加到队列的末尾。
- 出队（dequeue）：移除并返回队列的第一个元素。
### 技巧
- 循环队列：使用数组实现队列时，可以通过取模运算来实现循环队列，从而有效利用数组空间。
- 单调队列：每次入队时，保持队列中的元素单调递增或单调递减，这样就能维护滑动窗口的最大值或最小值。