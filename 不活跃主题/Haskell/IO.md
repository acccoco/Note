为了和外界交互，需要一种新的类型 `IO a` 
这种类型表示用于产生某种事物的「**配方**」，可以将其看作是「**回调**」函数

例如：
以下是 `putStrLn` 这个函数的类型，它可以将字符串输出到命令行
```python
putStrLn :: String -> IO ()
```

所有的 `IO` 都只是配方，配方的执行者只有唯一一个，就是 runtime ，执行配方，需要这样做：
```python
-- main 是总配方
main :: IO ()
main = putStrLn "hello world!"

-- 执行命令为：runhaskell <filename>
```

**执行多次 IO 操作**：
进行多次有副作用的操作，可以用 `>>` 运算符，它表示「先做什么，再做什么」
IO 操作的结果都会被**丢弃**
```python
(>>) :: IO a -> IO b -> b
```

例如：
```python
main = putStr "hello " >> putStrLn "world!"
```

取得上次 IO 操作的值：
使用 `>>=` 运算符：
```python
(>>=) :: IO a -> (a -> IO b) -> IO b
```

例如：
```python
main :: IO ()
main =
  putStrLn "please write something."
    >> readLn
    >>= (\ln -> putStrLn $ "your input is: " ++ show (ln + 1))
```
