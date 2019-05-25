简介
---
基于resst_rpc在Linux(Centos 7)平台开发的网络对战的五子棋，项目代码不到1000行，难度不大，比较适合作为C++的新手入门项目。

特性
---
只支持Linux
目前只有五子棋和猜数字两款游戏

用法
---
依赖软件
---
要编译运行当前程序需要先检查或者升级一下自己的Linux的环境。
1、需要使用cmake 3.7以上的版本进行mkaefile的生成。
2、需要安装boost库，具体编译的时候，错误信息会提示
3、gcc7.0版本以上
cmake安装或升级链接：https://blog.csdn.net/fancyler/article/details/78009812
安装高版本gcc链接:https://www.jianshu.com/p/76fb9b6a781b

下载和编译
---
git clone https://github.com/heartangle/Gobang.git

客户端
-cd Gobang/game/client
mkdir build
cmake ..
make //生成可执行程序game_client

服务器端
cd Gobang/game/server
mkdir build
cmake //
make //生成可执行成程序game_server

运行客户端和服务器
---
1、先进到服务器目录下启动服务器。
./game_server

2、在进到客户端目录下，启动客户端
./game_client ip + port   //在server/main.cpp中默认端口号是9001，这是可以修改的，注意不要和知名端口号重复就好了。

3、接下里在客户端界面就可以玩游戏了。

4、注意因为五子棋最少需要两个人才能玩，所以需要你启动两个客户端才能玩游戏，一个人完会匹配失败。

扩展和改进
---
1、目前采用的匹配机制，对与匹配池中的落单的那个人会直接匹配失败，后期会进行改进，添加机器人。

2、欢迎各位大佬提出意见，或者一起合作开发该项目。

作者
---
heart_angle
