---
tags:
    - vulkan
---

## command 的执行顺序

同一个 queue 之内的，根据 submit 的时间来 start，结束时间无法预测

不同的 queue，就完全没有限制了

同一个 queue 中的 command 开始顺序是 in order 的，结束顺序无法保证。

一个example：draw 命令如果放到bind 之前，会报错


## command 的提交顺序

提交顺序并不能保证执行顺序和内存访问顺序

但是提交顺序是 memory barrier 的基础。