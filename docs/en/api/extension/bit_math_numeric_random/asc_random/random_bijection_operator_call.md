# asc::random_bijection::operator_call (previous interface migration)

The current `<asc/random>` provides only the fixed [`asc::pcg64`](pcg64.md). The parameter template, equal_state and random_bijection interfaces are outside this design. Applications select their own index permutation algorithm.
