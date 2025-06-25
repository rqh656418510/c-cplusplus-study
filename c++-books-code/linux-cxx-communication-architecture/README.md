# C++ 新经典 - Linux C++ 通信架构实战

## 常用命令

### 文件搜索

``` sh
# 在一批文件里搜索一个字符串（文件内容）
find / -iname "signal.h" | xargs grep -in "SIGHUP"
```

### 进程管理

``` sh
# 查看所有终端下的进程（不仅仅是当前用户）
ps la

# 查看某些进程的指定信息
ps -eo pid,ppid,sid,tty,pgrp,comm | grep -E 'bash|PID|linux'
```

### 进程信号

``` sh
# 监听某个进程接收到的信号
strace -e trace=signal -p <pid>

# 杀死指定的进程，进程会接收到 SIGTERM 信号（终止信号），kill 后面不带 "-数字" 时，那个数字默认是 "-15"
kill <pid>

# 杀死指定的进程，进程会接收到 SIGHUP 信号（挂断信号/终端断开信号）
kill -1 <pid>

# 杀死指定的进程，进程会接收到 SIGINT 信号（中断信号，比如用户在终端按下 Ctrl + C）
kill -2 <pid>
```
