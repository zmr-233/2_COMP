Alright, let's tackle this problem step by step to understand why the smallest positive integer that has exactly 4 divisors is 6.

First, let's talk about the basics of finding the number of divisors of a given number. The number of divisors of a number can be determined from its prime factorization. If the prime factorization of a number $N$ is $p_1^{e_1} \cdot p_2^{e_2} \cdot ... \cdot p_k^{e_k}$, where $p_1, p_2, ..., p_k$ are distinct prime numbers and $e_1, e_2, ..., e_k$ are their respective exponents, then the total number of divisors of $N$ is given by $(e_1 + 1) \cdot (e_2 + 1) \cdot ... \cdot (e_k + 1)$.

For a number to have exactly 4 divisors, there are two main scenarios:

1. The number is the cube of a prime number, i.e., its form is $p^3$. This gives us $4$ divisors: $1, p, p^2$, and $p^3$.
2. The number is a product of two distinct primes, i.e., its form is $p \cdot q$. This also gives us $4$ divisors: $1, p, q$, and $pq$.

Given these scenarios, we need to find the smallest positive integer that fits one of these criteria and has exactly $4$ divisors. Comparing the two scenarios:

1. The smallest prime number is $2$, so the smallest number in the first scenario is $2^3 = 8$.
2. The smallest prime numbers are $2$ and $3$, so the smallest number in the second scenario is $2 \cdot 3 = 6$.

Therefore, the smallest positive integer that has exactly $4$ divisors, considering these criteria, is $6$. This is why when the input is $4$, the output is $6$.