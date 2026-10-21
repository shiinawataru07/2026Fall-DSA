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
    - [卡特兰数](#卡特兰数)
    - [表达式](#表达式)
    - [Shunting yard algorightm（调度场算法）](#shunting-yard-algorightm调度场算法)
    - [队列](#队列)
    - [技巧（循环队列，单调队列）](#技巧-1)
- [04-String](#04-string)
    - [字符串类](#字符串类)
    - [LPS 与 KMP 模式匹配算法](#lps-与-kmp-模式匹配算法)
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
### 卡特兰数
对于一个给定的序列，我们将其压入栈并推出栈，最终得到一个合法出栈序列。对于长度为 n 的序列，合法出栈序列的数量为第 n 个卡特兰数 $C_n$，其计算公式为：
$$ C_n = \frac{1}{n+1} \binom{2n}{n} = \frac{(2n)!}{(n+1)!n!} $$
证明方式如下：  
我们假定元素 $1$ 是第 $k+1$ 个出栈的元素，那么先于 $1$ 出栈的元素有 $k$ 个，它们的出栈顺序是一个长度为 $k$ 的合法出栈序列；而后于 $1$ 出栈的元素有 $n-k-1$ 个，它们的出栈顺序是一个长度为 $n-k-1$ 的合法出栈序列。因此我们可以得到递推公式：
$$ C_n = \sum_{k=0}^{n-1} C_k C_{n-k-1} $$
然后生成函数：
$$ C(x) = \sum_{n=0}^{\infty} C_n x^n $$
根据递推公式，我们可以得到：
$$ C(x) = 1 + xC(x)^2 $$
再加上我们需要满足 $C(0) = 1$，我们可以解出：
$$ C(x) = \frac{1 - \sqrt{1-4x}}{2x} $$
我们再使用广义二项式定理展开：
$$ (1-4x)^{\frac{1}{2}} = \sum_{n=0}^{\infty} \binom{\frac{1}{2}}{n}(-4x)^n $$
最终再进行若干化简，我们可以得到：
$$ C_n = \frac{1}{n+1} \binom{2n}{n} $$
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


## 04-String
### 字符串类
```cpp
class String {
public:
    using size_type = std::size_t;
    String() : data_(new char[1]), size_(0) {
        data_[0] = '\0';
    }
    String(const char* str) {
        if (s == nullptr) throw std::invalid_argument("Null pointer");
        size_ = std::strlen(str);
        data_ = new char[size_ + 1];
        std::memcpy(data_, str, size_ + 1);
    }
    ~String() { delete[] data_; }

    String(const String& other) : data_(new char[other.size_ + 1]), size_(other.size_) {
        std::memcpy(data_, other.data_, size_ + 1);
    }
    String& operator=(const String& other) {
        if (this == &other) return *this;
        char* fresh = new char[other.size_ + 1];
        std::memcpy(fresh, other.data_, other.size_ + 1);
        delete[] data_;
        data_ = fresh;
        size_ = other.size_;
        return *this;
    }

    size_type size() const { return size_; }
    size_type length() const { return size_; }
    bool empty() const { return size_ == 0; }
    const char* c_str() const { return data_; }

    void clear() {
        char* fresh = new char[1];
        fresh[0] = '\0';
        delete[] data_;
        data_ = fresh;
        size_ = 0;
    }

    char at(size_type index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    String& append(char c) {
        char* fresh = new char[size_ + 2];
        std::memcpy(fresh, data_, size_);
        fresh[size_] = c;
        fresh[size_ + 1] = '\0';
        delete[] data_;
        data_ = fresh;
        ++size_;
        return *this;
    }

    String& concatenate(const char* s) {
        if (s == nullptr) throw std::invalid_argument("Null pointer");
        size_type len = std::strlen(s);
        char* fresh = new char[size_ + len + 1];
        std::memcpy(fresh, data_, size_);
        std::memcpy(fresh + size_, s, len + 1);
        delete[] data_;
        data_ = fresh;
        size_ += len;
        return *this;
    }

    String substr(size_type pos, size_type len) const {
        if (pos > size_) throw std::out_of_range("Position out of range");
        size_type available = size_ - pos;
        size_type take = (len < available) ? len : available;
        String result;
        char* fresh = new char[take + 1];
        std::memcpy(fresh, data_ + pos, take);
        fresh[take] = '\0';
        delete[] result.data_;
        result.data_ = fresh;
        result.size_ = take;
        return result;
    }

    std::optional<size_type> find(char c, size_type start = 0) const {
        for (size_type i = start; i < size_; ++i) {
            if (data_[i] == c) return i;
        }
        return std::nullopt;
    }

    int compare(const String& other) const {
        return std::strcmp(data_, other.data_);
    }

private:
    char* data_;
    size_type size_;
};

inline bool operator==(const String& lhs, const String& rhs) {
    return lhs.compare(rhs) == 0;
}
inline bool operator!=(const String& lhs, const String& rhs) {
    return !(lhs == rhs);
}
inline bool operator<(const String& lhs, const String& rhs) {
    return lhs.compare(rhs) < 0;
}
```

### LPS 与 KMP 模式匹配算法
模式匹配是指我们有一个长字符串 $s$ 和一个模式字符串 $p$，我们希望在 $s$ 中找到与 $p$ 匹配的子串的位置。

朴素算法就是从 $s$ 的每一个位置开始，尝试匹配 $p$，如果匹配失败，就移动到下一个位置继续尝试。这种方法的时间复杂度是 $O(nm)$，其中 $n$ 是字符串 $s$ 的长度，$m$ 是模式字符串 $p$ 的长度。

我们可以通过 KMP 算法来优化这个过程。KMP 算法的核心思想是利用已经匹配的信息，避免重复比较。我们对模式串进行预处理，得到其 $next$ 数组（也称为失配函数），这个数组告诉我们当匹配失败时，模式串应该移动到哪个位置继续匹配。

可以看出 $next$ 数组的第 $i$ 位就是 str[0: i] 的最长相等真前后缀长度（longest proper prefix which is also suffix）。例如，字符串 "ABCDABD" 的 $next$ 数组为 [-1, 0, 0, 0, 1, 2, 0]。

$next$ 数组也可以经过优化，来处理那些在匹配失败时，模式串中有重复字符的情况。优化后的 $next$ 数组可以减少不必要的比较，从而提高匹配效率。

```python
def build_next(pattern: str) -> list[int]:
    if not pattern:
        return []
    next_values = [-1] * len(pattern)
    i = 0
    k = -1
    while i < len(pattern):
        while k >= 0 and pattern[i] != pattern[k]:
            k = next_values[k]
        i += 1
        k += 1
        if i == len(pattern):
            break
        next_values[i] = next_values[k] if pattern[i] == pattern[k] else k
    return next_values
```

KMP 的匹配过程如下，相当于朴素的配对算法，但是失配时，模式串不需要回溯，而是根据 $next$ 数组直接跳到下一个可能匹配的位置。

```python
def kmp_search(text: str, pattern: str, next_values: list[int] | None = None) -> int | None:
    if not pattern:
        return 0
    if next_values is None:
        next_values = build_next(pattern)
    if len(next_values) != len(pattern):
        raise ValueError("kmp_search: next 数组长度与模式不符")
    i = 0
    j = 0
    while i < len(pattern) and j < len(text):
        if i == -1 or text[j] == pattern[i]:
            i += 1
            j += 1
        else:
            i = next_values[i]
    return j - len(pattern) if i == len(pattern) else None
```

注意到目标串的下标只增不减，故而时间复杂度为 $O(|P|+|T|)$，其中 $|P|$ 是模式串的长度，$|T|$ 是目标串的长度。

我们还可以利用前缀函数求得字符串的周期：

对于字符串 $s$ 和 $0\leq k < |s|$，如果 $s[i] = s[i+k]$ 对于所有 $0 \leq i < |s|-k$ 都成立，则称 $s$ 有周期 $k$。

对于 $0\leq r < |s|$，如果 $s$ 长度为 $r$ 的前缀和后缀相等，则称这个前缀为原字符串的边界。

注意到 $|s| - r$ 就是字符串的周期。

于是我们求出最长相等真前后缀数组 $\pi$ 后，就可以得到字符串的最小周期为 $|s| - \pi[|s|-1]$。