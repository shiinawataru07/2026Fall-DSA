# 第一章作业

## 1

填空题：

1. $\sum_{i=1}^{n} \frac{1}{i} = \Theta(\log n)$。
2. $\log(n!) = \Theta(n \log n)$。

解答：使用斯特林公式 $n! \approx \sqrt{2\pi n} \left(\frac{n}{e}\right)^n$，可以得到 $\log(n!) = \Theta(n \log n)$。

3. $f(n) = \Omega(g(n))$ 且 $f(n) = O(g(n))$ 等价于 $f(n) = \Theta(g(n))$。
4. $2026^n = \Omega(2025^n)$。（填写 $O$, $\Omega$ 或 $\Theta$）

## 2

```cpp
int cnt = 0;
int i = 1;
while (i <= n) {
    int j = i;
    while (j <= n) {
        cnt++;
        j *= 2;
    }
    i++;
}
```

分析程序，求出程序的时间复杂度（大 $O$ 表示，**给出推导过程**）。

可以看出外层固定有 $n$ 次循环，内层循环的次数忽略取整，约等于 $\log_2(n/i)$，因此总的时间复杂度为：
$$
\sum_{i=1}^{n} \log_2(n/i) = \sum_{i=1}^{n} \log_2(n) - \sum_{i=1}^{n} \log_2(i) = n \log_2(n) - \log_2(n!)
$$
然后应用斯特林公式 $n! \approx \sqrt{2\pi n} \left(\frac{n}{e}\right)^n$，可以得到：
$$
\log_2(n!) \approx \log_2(\sqrt{2\pi n}) + n \log_2(n) - n \log_2(e) = \frac{1}{2} \log_2(n) + \frac{1}{2} \log_2(2\pi) + n \log_2(n) - n \log_2(e)
$$
于是总的时间复杂度为：
$$
n \log_2(n) - \log_2(n!) \approx n \log_2(e) - \frac{1}{2} \log_2(n) - \frac{1}{2} \log_2(2\pi) = \Theta(n)
$$
答案为 $O(n)$。

## 3

求解下列递推式的 $\Theta$ 表示。

1. $T(n) = n^5 \times 3^n + 4^n$。

   观察每一项的增长率，$4^n$ 的增长速度比 $n^5 \times 3^n$ 快，因此总的时间复杂度为 $\Theta(4^n)$。

2. $T(n) = T(n - 1) + \Theta(n)$。

    进行累加，得到：
    $T(n) = \sum_{i=1}^{n} \Theta(i) = \Theta\left(\sum_{i=1}^{n} i\right) = \Theta(n^2)$

3. $T(n) = T(\lfloor n/2 \rfloor) + \Theta(1)$。

    使用主定理，$T(n) = \Theta(\log n)$。

4. $T(n) = T(n - 1) + \Theta(\log n)$。

    进行累加，得到：
    $T(n) = \sum_{i=1}^{n} \Theta(\log i) = \Theta\left(\sum_{i=1}^{n} \log i\right) = \Theta(\log(n!)) = \Theta(n \log n)$

## 4

1. 证明对任意正实数 $a$ 和 $b$，$a^n = O(b^n)$ 当且仅当 $a \le b$。

**充分性**：如果 $a \le b$，则存在常数 $c = 1$，使得对于所有足够大的 $n$，有 $a^n \le c \cdot b^n$，因此 $a^n = O(b^n)$。

**必要性**：如果 $a^n = O(b^n)$，则存在常数 $c > 0$ 和 $n_0$，使得对于所有 $n \ge n_0$，有 $a^n \le c \cdot b^n$。

也即是 $\frac{a^n}{b^n} \le c$，即 $\left(\frac{a}{b}\right)^n \le c$。

如果 $a > b$，则 $\frac{a}{b} > 1$，随着 $n$ 的增大，$\left(\frac{a}{b}\right)^n$ 会趋向于无穷大，这与 $\left(\frac{a}{b}\right)^n \le c$ 矛盾。因此必须有 $a \le b$。

2. 给定 $T(1) = 1$ 和 $T(n) = 2T(\lfloor n/2 \rfloor) + n$，证明 $T(n) = O(n \log n)$。（提示：考虑数学归纳法）

取 $c=2$，我们期望证明足够大的 $n$，有 $T(n) \le 2n \log n$。
$$T(2) = 2T(1) + 2 = 4 \le 2 \cdot 2 \log 2$$
$$T(3) = 2T(1) + 3 = 5 \le 2 \cdot 3 \log 3$$
假设对于所有 $k < n$，有 $T(k) \le 2k \log k$，则：
$$T(n) = 2T(\lfloor n/2 \rfloor) + n \le 2 \cdot 2 \cdot \frac{n}{2} \log \frac{n}{2} + n = 2n \log n - 2n + n = 2n \log n - n \le 2n \log n$$
因此 $T(n) = O(n \log n)$。