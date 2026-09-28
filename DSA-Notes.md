# DSA 速记
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