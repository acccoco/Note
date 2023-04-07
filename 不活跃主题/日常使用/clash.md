使用需要记住：

- 开启系统代理
- 设置环境变量
- ping 由于走的是 ICMP 协议，不会被 clash 代理，因此 ping 总是不通的。使用 curl -v 替代