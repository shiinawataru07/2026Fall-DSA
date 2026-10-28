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
- [05-Binary Tree](#05-binary-tree)
    - [概念](#概念)
    - [遍历与线索二叉树](#遍历与线索二叉树)
    - [二叉搜索树](#二叉搜索树)
    - [堆](#堆)
    - [哈夫曼树](#哈夫曼树)
- [06-Tree](#06-tree)
    - [森林与二叉树的转换](#森林与二叉树的转换)
    - [链式存储](#链式存储)
    - [并查集](#并查集)
    - [顺序存储](#顺序存储)
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

## 05-Binary Tree
### 概念
二叉树是由节点构成的空集，或者一个根节点和其左右子树所构成的集合组成。

二叉树的唯一起始节点称之为根（root），非根节点的唯一前驱节点称为其的父节点（parent），而该节点的子节点称为其的子节点（child）。

一个节点的子树数目称为该节点的度（degree），叶子节点（leaf）是指没有子节点的节点。

父节点与子节点之间的连线称之为边，若二叉树中的节点序列两两成边，该路径所经过的边数称为该路径的长度。

若有一条从 $k$ 到 $k_s$ 的路径，则称 $k_s$ 是 $k$ 的子孙（descendant），而 $k$ 是 $k_s$ 的祖先（ancestor）。从根节点到某个节点的路径长度称为该节点的深度（depth），而从该节点到叶子节点的最长路径长度称为该节点的高度（height）。

任何节点是叶或者左右子树都非空的二叉树称为满二叉树（full binary tree），而除了最后一层外每一层都排满的二叉树称为完全二叉树（complete binary tree）。

把普通二叉树的每个空子树位置都用一个空节点代替，则称之为二叉树的扩展二叉树（extended binary tree）。  
值得注意的是，扩展二叉树的叶子节点数目总是比其非叶子节点数目多 1。  
证明：  
最初仅有根节点时，叶子节点数目为 1，非叶子节点数目为 0，满足条件。  
每次原树多一个节点时，替换掉了原先扩充的一个空节点，但又会新增两个空节点，因此扩展二叉树的叶子节点数目总是比其非叶子节点数目多 1。

- 性质1：第 $i$ 层最多有 $2^{i}$ 个节点。
- 性质2：深度为 $k$ 的二叉树最多有 $2^{k}-1$ 个节点。
- 性质3：非空二叉树有 $n_0$ 个叶子节点和 $n_2$ 个度为 2 的节点，则有 $n_0 = n_2 + 1$。
- 性质4：非空满二叉树有 $n_1$ 个度为 1 的节点，则有 $n_1 = 0$。
- 性质5：非空二叉树的空子树数目等于其结点数加 1。
- 性质6：有 $n$ 个节点的完全二叉树的深度为 $\lfloor \log_2 n \rfloor$。（也就是有几层）。高度为 $\lceil \log_2 (n+1) \rceil$。
- 性质7：完全二叉树节点编号为 $0...n-1$，$i$ 的父节点为 $\lfloor (i-1)/2 \rfloor$，左孩子为 $2i+1$，右孩子为 $2i+2$。且奇为左，偶为右。

### 遍历与线索二叉树
基于深度优先搜索（DFS）的遍历方式有三种：前序遍历（preorder）、中序遍历（inorder）和后序遍历（postorder）。  
前序遍历为根-左-右，中序遍历为左-根-右，后序遍历为左-右-根。从 $root$ 开始递归遍历。
```cpp
static void preorder(TreeNode* root) {
    if (root == nullptr) return;
    visit(root);
    preorder(root->left);
    preorder(root->right);
}
static void inorder(TreeNode* root) {
    if (root == nullptr) return;
    inorder(root->left);
    visit(root);
    inorder(root->right);
}
static void postorder(TreeNode* root) {
    if (root == nullptr) return;
    postorder(root->left);
    postorder(root->right);
    visit(root);
}
```
一个表达式树的前序、中序和后序遍历分别对应前缀表达式、中缀表达式和后缀表达式。

给定前序和中序，或者后序和中序，可以唯一确定一棵二叉树。但给定前序和后序，不能唯一确定一棵二叉树。

基于广度优先搜索的遍历是逐层遍历。  
伪代码如下：
```
root 入队
while 队列不为空 do
    出队一个节点
    访问节点
    若左子节点不为空，则左子节点入队
    若右子节点不为空，则右子节点入队
end while
```

接下来我们讨论线索二叉树，由先前的性质 5 可知，二叉树中空子树的数目总是比其结点数多 1。我们可以利用这些空子树来存储指向前驱和后继的指针，从而实现线索化。

一个节点的左指针空，就存放其中序前驱，一个节点的右指针空，就存放其中序后继。再额外使用一位 bool 来存放该指针是指向子节点还是前驱/后继的线索。
```cpp
struct Node {
    T value;
    Node* left = nullptr;
    Node* right = nullptr;
    bool left_thread = false;    // true：left 存的是中序前驱
    bool right_thread = false;   // true：right 存的是中序后继
};

// 线索化：按中序走一遍，pre 是上一个访问到的结点
static void thread_impl(Node* node, Node*& pre) {
    if (node == nullptr) return;
    thread_impl(node->left, pre);
    if (node->left == nullptr) {                   // 空左指针 → 存中序前驱
        node->left = pre;
        node->left_thread = true;
    }
    if (pre != nullptr && pre->right == nullptr) { // 上一个结点的空右指针 → 存后继
        pre->right = node;
        pre->right_thread = true;
    }
    pre = node;
    thread_impl(node->right, pre);
}

static void make_threaded(Node* root) {
    Node* pre = nullptr;
    thread_impl(root, pre);
    if (pre != nullptr) pre->right_thread = true;  // 最后一个结点：后继为空
}
```

Morris 遍历是一种不使用栈和递归的遍历方式。其核心思想是利用线索化的概念，在遍历过程中临时修改树的结构，从而实现 O(1) 的空间复杂度。

普通周游要用栈，是因为进左子树之前必须记住回来的路。Morris 注意到：cur 的左子树里最后被访问的结点（中序前驱，即左子树最右下的结点），它的 right 一定是空的——让它临时指回 cur，路就存在树里了。
```cpp
template <typename Visitor>
static void morris_inorder(Node* root, Visitor& visit) {
    Node* cur = root;
    while (cur != nullptr) {
        if (cur->left == nullptr) {            // 没有左子树：访问，往右走
            visit(cur->value);
            cur = cur->right;                  // 可能是真孩子，也可能是临时线索
            continue;
        }
        Node* pre = cur->left;                 // 找中序前驱：左子树最右下
        while (pre->right != nullptr && pre->right != cur) pre = pre->right;
        if (pre->right == nullptr) {           // 第一次到 cur：搭线索，进左子树
            pre->right = cur;
            cur = cur->left;
        } else {                               // 第二次到 cur：左子树已走完
            pre->right = nullptr;              // 拆线索，恢复原树
            visit(cur->value);
            cur = cur->right;
        }
    }
}
```
### 二叉搜索树
在应用中我们经常要维护一个需要查询、增删的集合类型数据结构，使用无序线性表实现的查询速度过慢，而使用有序线性表实现的增删速度过慢。

二叉搜索树（Binary Search Tree, BST）的每个节点代表一个数据，并且满足任何一个节点，其左子树上节点的数据都小于该节点，其右子树上节点的数据都大于该节点。

插入操作逐层检索即可，删除操作需要分情况讨论：在待删除的节点不存在左子树的情况下，只需要删除该节点并将右子树的根顶上即可；  
待删除的节点存在左子树时，朴素考虑我们可以用左子树的根节点顶上，并且将右子树的根节点置于左子树的中序遍历的最后一个节点的右子树下，但这样会让 BST 变得过于瘦长而不利于保持性质。  
改进方案也很简单，把左子树的中序遍历最后的一个节点顶替在待删除节点位置即可。
```cpp
bool BinarySearchTree::insert(const T& value) {
    Node** link = &root_; // 新结点该挂在哪个指针上，初始化为指向根指针的指针
    while(*link != nullptr){
        if(value < (*link)->value) {
            link = &(*link)->left;
        }else if(value > (*link)->value) {
            link = &(*link)->right;
        }else{
            return false; // 发现已经有重复值了
        }
    }
    *link = new Node{value, nullptr, nullptr};
    return true;
}

static bool BinarySearchTree::remove(Node*& link, const T& value) {
    if (link == nullptr) return false; // 没找到
    if (value < link->value) {
        return remove(link->left, value);
    } else if (value > link->value) {
        return remove(link->right, value);
    }
    Node* removed = link;
    if(removed->left == nullptr) {
        link = removed->right;
        delete removed;
        return true;
    }
    Node** pre = &removed->left;
    while((*pre)->right != nullptr) pre = &(*pre)->right;
    Node* replacement = *pre;
    *pre = replacement->left;
    replacement->left = removed->left;
    replacement->right = removed->right;
    link = replacement;
    delete removed;
    return true;
}
```
### 堆
最小堆是一种特殊的完全二叉树，满足每个节点的值都小于或等于其子节点的值。最大堆则是每个节点的值都大于或等于其子节点的值。写成序列有如下特性：
$$ K_i \leq K_{2i+1} \quad\text{and}\quad K_i \leq K_{2i+2} $$
插入新元素时，将其放在数组的末尾，然后通过上浮操作（swim）将其移动到正确的位置。删除某个给定元素时，先将其与数组末尾的元素交换，然后删除末尾元素，然后判断交换后的元素与父元素的大小关系，如果小于父元素则上浮，否则下沉（sink）到正确位置。
最小堆只适合于查找最小值，查找任意值的效率不高
```cpp
template <typename T>
class MinHeap {
public:
    using size_type = std::size_t;
    explicit MinHeap(size_type initial_capacity = 8)
        : data_(new T[initial_capacity]), capacity_(initial_capacity), size_(0) {}
    ~MinHeap() { delete[] data_; }
    MinHeap(const MinHeap& other)
        : data_(new T[other.capacity_]), capacity_(other.capacity_), size_(other.size_) {
        for(size_type i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    MinHeap& operator=(const MinHeap& other) {
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
    bool empty() const { return size_ == 0; }
    size_type size() const { return size_; }
    void insert(const T& value) {
        if(size_ == capacity_) grow();
        data_[size_] = value;
        sift_up(size_);
        ++size_;
    }
    std::optional<T> remove_min() {
        if(empty()) return std::nullopt;
        T min_value = data_[0];
        --size_;
        if(size_ > 0) {
            data_[0] = data_[size_];
            sift_down(0);
        }
        return min_value;
    }
private:
    void sift_up(size_type index) {
        while(index > 0) {
            size_type parent = (index - 1) / 2;
            if(!(data_[index] < data_[parent])) break;
            T tmp = data_[index];
            data_[index] = data_[parent];
            data_[parent] = tmp;
            index = parent;
        }
    }
    void sift_down(size_type index) {
        while(true) {
            size_type left = 2 * index + 1;
            size_type right = 2 * index + 2;
            size_type smallest = index;
            if(left < size_ && data_[left] < data_[smallest]) smallest = left;
            if(right < size_ && data_[right] < data_[smallest]) smallest = right;
            if(smallest == index) break;
            T tmp = data_[index];
            data_[index] = data_[smallest];
            data_[smallest] = tmp;
            index = smallest;
        }
    }
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
对一个无序序列建堆的方法朴素考虑可以做 $n$ 次 insert 操作，每次插入的时间复杂度为 $O(\log n)$，因此总的时间复杂度为 $O(n \log n)$。  
我们可以用下沉方法来优化这个过程，从最后一个非叶结点起，倒着对每个结点做一次下沉操作，直到根结点为止。  
满树的第 $i$ 层恰有 $2^i$ 个结点，其中的结点最多下沉 $h-i$ 层，因此总的时间复杂度为 $O(n)$：
$$ cost \leq \sum_{i=0}^{h}2^i(h-i)=\sum_{j=0}^h2^{h-j}j=2^h\sum_{j=0}^h\frac{j}{2^j}\leq 2^h\times 2 \leq 2n $$
优先队列（Priority Queue）是一种特殊的队列，其中每个元素都有一个优先级。与普通队列不同，优先队列中的元素是按照优先级顺序进行处理的，而不是按照插入顺序。最小堆和最大堆是实现优先队列的常用数据结构。
### 哈夫曼树
我们定义带权路径长度（Weighted Path Length, WPL）为每个叶子节点的权值与其到根节点的路径长度的乘积之和。

基于此，我们提出哈夫曼树，对于给定的权值集合，我们希望构建一棵二叉树，使得其 WPL 最小。哈夫曼树是一种带权路径长度最短的二叉树。  
构造方式就是每次从权值集合中选出两个最小的权值，构建一个新的节点，其权值为这两个最小权值的和，然后将这个新节点加入到权值集合中。重复这个过程，直到只剩下一个节点为止，这个节点就是哈夫曼树的根节点。

WPL 等于所有内部节点的权值之和。

Huffman 编码是一种经典的压缩算法，它通过构建哈夫曼树来实现。对于一串字符，我们可以根据其出现的频率来构建哈夫曼树，从而实现哈夫曼编码。哈夫曼编码是一种可变长度的编码方式，频率高的字符使用较短的编码，而频率低的字符使用较长的编码，从而达到压缩数据的目的。
## 06-Tree
### 森林与二叉树的转换
树形结构用分支关系定义层次：一个结点至多一个前驱，但可以有任意多个后继。定义和概念可以参考二叉树。
- 森林-二叉树：  
同一层的结点相连，只保留父结点到第一个孩子的连线，砍掉到其余孩子的连线。转换后，一个结点的左孩子是它在原树（或森林）里的第一个孩子，右孩子是原来的下一个兄弟。左枝上是父子关系，右枝上是兄弟关系。 
- 二叉树-森林：  
若 $x$ 是 $y$ 的左孩子，则将 x 右边整条右链都连到 y 下。
### 链式存储
1. 子结点表：使用一个结点数组来存所有结点，每个结点存储值、父节点索引、指向子节点链表的指针。
2. 静态左子右兄：使用一个节点数组存所有节点，每个节点存储值、父节点索引、指向左孩子的指针、指向右兄弟的指针。
3. 动态表示法：参考子结点表，只是采用动态数组来代替子节点链表。
4. 动态左子右兄：参考静态左子右兄，只是使用链表，具体实现给出代码如下：
```cpp
template<typename T>
class GeneralTree {
public:
    struct Node {
        T value;
        Node* child{nullptr};
        Node* sibling{nullptr};
        Node* parent{nullptr};
        explicit Node(const T& val) : value(val) {}
    };
    GeneralTree() = default;
    GeneralTree(const GeneralTree& other) noexcept : root_(clone(other.root_, nullptr)) {}
    GeneralTree& operator=(const GeneralTree& other) noexcept {
        if(this == &other) return *this;
        GeneralTree copy(other);
        std::swap(root_, copy.root_);
        return *this;
    }
    ~GeneralTree() { clear(); }
    [[nodiscard]] Node* root() noexcept { return root_; }
    [[nodiscard]] const Node* root() const noexcept { return root_; }
    void create_root(const T& value) {
        clear();
        root_ = new Node(value);
    }
    Node* insert_first(Node* parent, const T& value) {
        if(parent == nullptr) throw std::invalid_argument("Parent node is null");
        Node* new_node = new Node(value);
        new_node->parent = parent;
        new_node->sibling = parent->child;
        parent->child = new_node;
        return new_node;
    }
    Node* insert_next(Node* sibling, const T& value) {
        if(sibling == nullptr) throw std::invalid_argument("Sibling node is null");
        Node* new_node = new Node(value);
        new_node->parent = sibling->parent;
        new_node->sibling = sibling->sibling;
        sibling->sibling = new_node;
        return new_node;
    }
    [[nodiscard]] Node* parent_of(Node* node) const noexcept { return node ? node->parent : nullptr; }
    void delete_subtree(Node* node) {
        if(node == nullptr) return;
        Node** link = node->parent == nullptr ? &root_ : &node->parent->child;
        while(*link != nullptr && *link != node) link = &(*link)->sibling;
        if (*link != node) throw std::invalid_argument("Node is not a child of its parent");
        *link = node->sibling;
        node->sibling = nullptr;
        destroy(node);
    }
    void clear() {
        destroy(root_);
        root_ = nullptr;
    }
    void preorder(Visitor&& visitor) const{
        pre(root_, visitor);
    }
    void postorder(Visitor&& visitor) const{
        post(root_, visitor);
    }
    struct DualTagNode {
        T value;
        bool has_child;
        bool has_sibling;
    };
    [[nodiscard]] static GeneralTree from_dual_tag(const DualTagNode* nodes, std::size_t count) {
        GeneralTree tree;
        if(count == 0) return tree;
        std::vector<Node*> waiting; // stack
        Node* current = new Node(nodes[0].value);
        tree.root_ = current;
        for(std::size_t i = 0; i + 1 < count; ++i) {
            if (nodes[i].has_sibling) waiting.push_back(current);
            Node* fresh = new Node(nodes[i + 1].value);
            if (nodes[i].has_child) {
                current->child = fresh;
                fresh->parent = current;
            } else {
                if (waiting.empty()) {
                    delete fresh;
                    throw std::invalid_argument("Invalid dual tag sequence: no parent for sibling");
                }
                Node* owner = waiting.back();
                waiting.pop_back();
                owner->sibling = fresh;
                fresh->parent = owner->parent;
            }
            current = fresh;
        }
        return tree;
    }
private:
    static void destroy(Node* node) noexcept {
        if(node == nullptr) return;
        destroy(node->child);
        destroy(node->sibling);
        delete node;
    }
    static Node* clone(const Node* node, Node* parent) {
        if (node == nullptr) return nullptr;
        Node* copy = new Node(node->value);
        copy->parent = parent;
        try {
            copy->child = clone(node->child, copy);
            copy->sibling = clone(node->sibling, parent);
        } catch (...) {
            destroy(copy);
            throw;
        }
        return copy;
    }
    static void pre(Node* node, Visitor& visitor) {
        for (; node != nullptr; node = node->sibling) {
            visitor(node->value);
            pre(node->child, visitor);
        }
    }
    static void post(Node* node, Visitor& visitor) {
        for (; node != nullptr; node = node->sibling) {
            post(node->child, visitor);
            visitor(node->value);
        }
    }
    Node* release() noexcept {
        Node* old_root = root_;
        root_ = nullptr;
        return old_root;
    }
    Node* root_{nullptr};
};
```
### 并查集
并查集维护若干互不相干的子集，支持两种操作：
1. **Find**：判断两个元素是否属于同一个集合。
2. **Union**：将两个子集合并为一个子集。

用父指针表示时，把每个子集看成一棵树，森林中的每棵树代表一个子集，树根就是该集合的标识符。

改进一：重量权衡合并规则，把较小的树挂到较大的树上，避免树过高。能够保证树的高度限制到 $O(\log n)$。

改进二：路径压缩：find 在返回根之前，把沿途每个结点的父指针都直接改成根。

**todo**
### 顺序存储
**todo**