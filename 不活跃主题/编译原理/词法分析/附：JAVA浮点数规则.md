浮点数规则：

```java
// 单个数字，或者中间有下划线的数字串
// 如：12__23__45
Digits = [0-9]
		|[0-9][0-9_]+[0-9]
// 浮点后缀
FloatTypeSuffix = (f|F|d|D)
// 指数部分
// 如：e+23_3,E23_4
ExponentPart = (e|E)(+|-)?Digits
// float的定义：
DecimalFloatingPointLiteral =
	// 有小数部分的浮点数 
	Digits.[Digits]?[ExponentPart]?[FloatTypeSuffix]?
	|.Digits[ExponentPart]?[FloatTypeSuffix]?
	// 只有整数部分的浮点数
	|Digits ExponentPart [FloatTypeSuffix]?
	|Digits[ExponentPart]?FloatTypeSuffix
```



参考文献：[The Java® Language Specification Java SE 13 Edition](https://docs.oracle.com/javase/specs/jls/se13/html/index.html)

