
## Functor

### 定义
定义如下：
```c
class Functor f where
  fmap :: (a ->b) -> f a -> f b
```

其中，`fmap` 需要遵守以下两个约束：
```c
-- Identity
fmap id == id

-- Composition
fmap (f . g) == fmap f . fmap g
```

注：`<$>` 就是 `fmap` 


### 相关的例子
Maybe 是如何实现 Functor 的：
```c
instance Functor Maybe where
  fmap f fa = case fa of 
    Nothing -> Nothing
    Just a -> Just (f a)
```

列表是如何实现 Functor 的：
```c
instance Functor [] where
  fmap _ [] = []
  fmap f x:xs = (f x): (fmap f xs)
```


### 范畴论相关
![[不活跃主题/Haskell/_attachments/1635921209619-a5a60667-eedc-465a-9710-c9bfc67acdcd.png | 525]]


## Applicative 

### 定义
定义如下：首先需要是 `Functor` 的实例，然后才能是 `Applicative` 的实例
```c
class Functor f => Applicative f where
  pure   :: a -> f a
  (<*>)  :: f (a -> b) -> f a -> f b
  liftA2 :: (a -> b -> c) -> f a -> f b -> f c
```
其中，`<*>` 和 `liftA2` 只需要满足一个即可，两者之间存在如下关系：
```c
(<*>) = liftA2 id
liftA2 f x y = f <$> x <*> y
```
需要满足以下的约束条件：
```c
-- Identity
pure id <*> v = v

-- Composition
pure (.) <*> u <*> v <*> w = u <*> (v <*> w)
    
-- Homomorphism
pure f <*> pure x = pure (f x)

-- Interchange
u <*> pure y = pure ($ y) <*> u
```
Functor 和 Applicative 的关系：
```c
fmap f x = pure f <*> x
```


### 例子
Maybe 如何实现：
```c
instance Applicative Maybe where
  pure = Just
  (<*>) Nothing = id
  (<*>) (Just f) = fmap f
```


### Monad
monad 是范畴论里面的一个概念；在 Haskell 中，应该将其理解为「an abstract datatype of actions」
定义：首先要是 `Applicative` 的实例，然后才能是 `Monad` 的实例：
```c
class Applicative m => Monad m where
  return :: a -> m a
  (>>=)  :: m a -> (a -> m b) -> m b
```
其中：

- `return` 和 `pure` 是等价的，历史原因
- `>>=` 表示绑定。其第一个参数 `m a` 被叫做「mobit」，它表示一个计算过程，这种计算产生类型 `a` 的结果，这种计算会有一些「副作用」。第二个参数 `a -> m b` 可以理解为：基于第一次计算的结果，选择如何进行第二次计算。

`>>` 运算符的实现：先进行一次计算，然后忽略计算结果，紧接着进行第二次计算，保留第二次计算的结果
```c
(>>) :: m a -> m b -> m b
m1 >> m2 = m1 >>= \_ -> m2
```

满足以下的**约束**：
```c
-- Left Identity
return a >>= k = k a

-- Right Identity
m >>= return = m

Associativity
m >>= (\x -> k x >>= h) = (m >>= k) >>= h
```


### 例子
Maybe 实现 Monad 的例子：
```c
instance Monad Maybe where
  return = Just
  Nothing >>= _ = Nothing
  Just x >>= k = k x
```


### 作业中的想法：

- Applicative 的意义：是不是就是为了 a <$> b <*> c 这个运算而存在的？
- 我想 Functor 和 Applicative 的最大意义在于使用，而不是抽象理解
- 范畴论并不是目的，而是帮助理解的。重点还是 Haskell 中 `Functor` 和 `Applicative` 层级的使用。

**直观的理解 **`**liftA2**`** 这个函数**：
关于 `liftA2` 这个函数，要站在 `Functor` 和 `Applicative` 的角度思考，不要关心实现细节。
```c
liftA2 :: Applicative f => (a -> b -> c) -> f a -> f b -> f c
```
把 `f a` 中的 `a` 提取出来，并应用在 `(a -> b -> c)` 这种函数中，最后再放入 `f` 中得到 `f c`
这就是「提取 lift」的含义。 



#### 这种用法的魅力
对于这样一个新类型：
```c
data Foo = Bar Int Int Char
```
如果要从 `String` 中解析出它，只需要：
```c
parseFoo :: Parser Foo
parseFoo = Bar <$> ParseInt <*> ParseInt <*> ParseChar
```

