#!/bin/bash

declare depends   # declare: 是bash中的内置命令，用于声明变量

get_depends() {
    # ldd $1: 打印$1可执行程序依赖的共享库
    # awk '{if(match($3, "/")){print $3}}'：从ldd的输出结构中过滤出所有共享库的路径
    # 共享库的路径让depends保存
    # cp $depends $2: 将depends保存的共享库路径拷贝到$2目录下
    depends=$(ldd $1 | awk '{if(match($3, "/")){print $3}}')
    cp $depends $2
}

mkdir -p $2

# S1: 是启动脚本时的第一个参数，为可执行文件的路径
# S2: 是启动脚本时的第二个参数，将共享库拷贝到的目录
# 例如：./depend.sh ./bin/UserService ./bin/dependLib
get_depends $1 $2
