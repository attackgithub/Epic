# Epic
一个简单的socket程序<br>

## Description
客户端给服务端发送数据后，服务端接受数据并与服务端已有数据进行验证，发送验证结果给客户端<br>
如果验证无误，进行信息修改等操作

## Setup
首先把项目`clone`到本地
```
$ git clone https://github.com/m4XEp1/Epic.git
```
`cd`到源代码目录
```
$ cd Epic\src
```
使用`make`命令进行编译生成
```
$ make -j2
```
当然你也可以单独的生成server或者client
```
$ make server
```
```
$ make client
```

## Usage

服务端的部署很简单，参数只需要带上端口号就可以了
```
$ ./Epic-server 233
# 意思是运行服务端并监听到233端口
```

客户端有几个参数，`-l`代表学号，`-p`代表着服务器端口，`-n`代表姓名，`-a`代表服务器地址
```
$ ./Epic-client -l 666666666 -p 233 -n Epi -a 127.0.0.1
# 意思是运行程序，学号为666666666，服务端端口号为233，姓名是Epi，服务器地址是127.0.0.1
```

## TODO
现在还有很多事情去做……

* [ ] 账号的验证
* [ ] 读取excel
* [ ] 写入excel

## License

MIT