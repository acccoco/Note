### SFINAE
SFINAE：substitution failure is not an error.
利用这个机制来起到 concept 的作用。
例如：
```cpp
template<typename T>
class IsClassT {
  private:
    typedef char One;
    typedef struct { char a[2]; } Two;
    template<typename C> static One test(int C::*);
    // Will be chosen if T is anything except a class.
    template<typename C> static Two test(...);
  public:
    enum { Yes = sizeof(IsClassT<T>::test<T>(0)) == 1 };
    enum { No = !Yes };
};
```
对于 `int`来说，由于 `int`不是一个 `class`，`int::*`这种用法是错误的，因此 `One`匹配不成功，`Two`匹配成功。`IsClassT<int>::Yes`的值就是 `0`。

参考：
[C++ SFINAE examples?](https://stackoverflow.com/questions/982808/c-sfinae-examples)

