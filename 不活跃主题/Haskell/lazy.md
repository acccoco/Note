
## Lazy
**什么是「strict 求值」的**：意味着表达式的求值顺序是可以预测的，比如：
```
f (do_A(), do_B())
```
可以知道会先执行 `do_A()` ，然后执行 `do_B()`，最后执行 `f()` 

**「strict 求值」有什么弊端**：
对于一下的表达式，「不 Lazy」 的策略是：
```
f (x, y) = x + 2
f (5, (29 * 32))
```
先计算子表达式 `5` 的值，再计算表达式 `29 * 32` 的值，最后计算 `f` 函数。这这个例子中，`29 * 32` 的计算是没有必要的

**「strict 求值」有什么好处**：
UI操作，文件的读写操作，网络相关的操作，都依赖于可以预知的求值时刻。
如果一个语言是完全「lazy 求值」的，那么上述操作是无法实现的。


**什么是「lazy 求值」**：
函数的参数表达式并不会马上求值，而是作为一个 `thunk` 被包装起来，直到必须求值的时候，才计算其值。

**「lazy 求值」的弊端**：
可能导致栈溢出。
例如，`foldl (+) 0 [1,2,3]` 的求值过程中，会存在这样一个表达式：`foldl (+) (((0+1)+2)+3) []`，在计算 `(0+1)` 时，`2, 3` 都在栈里面。如果列表很长，这可能导致栈溢出。

**什么时候才进行求值**：
Haskell 的一个策略是：**模式匹配驱动的求值**，最小限度的求值，只需要满足模式匹配即可。
例如有以下两个函数定义：
```
-- 生成无限的列表
repeat :: a -> [a]
repeat x = x : repeat x

-- 取出列表中的前 n 个元素，组成一个新的列表
take :: Int -> [a] -> [a]
take n _     | n <= 0 = []
take _ []         = []
take n (x:xs)     = x : take (n-1) xs
```

对于如下的表达式：`take 3 (repeat 7)` 
其求值步骤为：
```
  take 3 (repeat 7)
= take 3 (7 : repeat 7)
= 7 : take (3-1) (repeat 7)
= 7 : take 2 (repeat 7)
= 7 : take 2 (7 : repeat 7)
= 7 : 7 : take(2-1) (repeat 7)
= ...
= 7 : 7 : 7 : take 0 (repeat 7)
= 7 : 7 : 7 : []
```

**短路运算**：
比如 `&&` 运算，如果第一个操作数是 `False`，那么不需要关心第二个操作数，直接就能够得到结果。
这个特性是「lazy」的。这个特性在一些「strict 求值」的语言里面也有，算是比较奇怪了。

**无限的数据结构**：
「Lazy」的特性让 Haskell 能够定义无限的数据结构，例如：`repeat 7` 和 `[1..]` 

**用于动态规划**：
对于动态规划的问题，求解的结果通常是一张表格，后面的项通常一样与前面的项。
如果使用 Haskell 解决这种问题，只需要直接定义表格的每一项应该长什么样子即可。如果一些值依赖于另一些值，由于「Lazy」的特性，会在需要的时候再计算哪些值。所以**不需要关心表格中值的计算顺序，只需要定义表达式即可**。

以「0-1 背包问题」为例：
```haskell
import Data.Array

knapsack01 :: [Double]   -- values 
           -> [Integer]  -- nonnegative weights
           -> Integer    -- knapsack size
           -> Double     -- max possible value
knapsack01 vs ws maxW = m!(numItems-1, maxW)
  where numItems = length vs
        m = array ((-1,0), (numItems-1, maxW)) $
              [((-1,w), 0) | w <- [0 .. maxW]] ++
              [((i,0), 0) | i <- [0 .. numItems-1]] ++
              [((i,w), best) 
                  | i <- [0 .. numItems-1]
                  , w <- [1 .. maxW]
                  , let best
                          | ws!!i > w  = m!(i-1, w)
                          | otherwise = max (m!(i-1, w)) 
                                            (m!(i-1, w - ws!!i) + vs!!i)
              ]

example = knapsack01 [3,4,5,8,10] [2,3,4,5,9] 20
-- 26.0
```

