class Fraction:
    def __init__(self, a, b):
        self.a = a
        self.b = b
    def __add__(self, other):
        return Fraction.reduce(Fraction(self.a * other.b + self.b * other.a, self.b * other.b))
    def __str__(self):
        return f"{self.a}/{self.b}"
    def reduce(self):
        def gcd(x, y):
            while y:
                x, y = y, x % y
            return x
        g = gcd(self.a, self.b)
        return Fraction(self.a // g, self.b // g)

a, b, c, d = map(int, input().split())
print(Fraction(a, b) + Fraction(c, d))