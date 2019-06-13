
文档地址：https://blog.csdn.net/COCO56/article/details/91038011
开源仓库：https://github.com/COCO5666/MahatmaComeBack
## 作品介绍
* 大圣归来（MahatmaComeBack）
* 简介：一款基于Cocos2dx的联网游戏，含服务端与客户端源码及打包后的可执行或安装包文件。
* 支持注册、登陆、选择角色、自动寻路、聊天、发送公告等。
## 数据库设计
![在这里插入图片描述](https://img-blog.csdnimg.cn/2019060607340573.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0NPQ081Ng==,size_16,color_FFFFFF,t_70)
不想自己设计也可以直接导入我导出的sql文件，可以全自动创建（注意应该使用和我的MySQL相同的或更高的版本，实测在老版本的MySQL没法正常导入，那样的话参照我设计的表的截图，自己慢慢设计吧）
sql指令文件地址：https://github.com/COCO5666/MahatmaComeBack/tree/master/Server
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190614011245419.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0NPQ081Ng==,size_16,color_FFFFFF,t_70)
先建个数据库，名字为gametable，然后右键点击，运行我发的SQL指令文件
意应该使用和我的MySQL相同的或更高的版本，实测在老版本的MySQL没法正常导入，那样的话参照我设计的表的截图，自己慢慢设计吧。
我用的：
* 数据库为关系型数据库
* 数据库管理系统：MySQL Community Server version: 8.0.16
* 数据库管理和设计工具：Navicat 12.0.18（64-bit）-Premium
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190614011124973.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0NPQ081Ng==,size_16,color_FFFFFF,t_70)
## 服务器端开发
用的C#
* Microsoft Visual Studio Enterprise 2019 版本 16.1.1
VisualStudio.16.Release/16.1.1+28922.388
## 客户端开发
* Cocos2d-x 3.17.2
## 压缩包
下载地址：
http://coco5666.github.io/blog/articles/20190406-03/
在**开发相关/我开发的**
![在这里插入图片描述](https://img-blog.csdnimg.cn/2019060620350279.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0NPQ081Ng==,size_16,color_FFFFFF,t_70)
## 说明
### 为什么选择WebSocket
Cocos 封装的Socket.IO 与 HTTP在电脑上可以正常连接服务器，但是打包到Android上总是无法正常连接服务器，因此采用WebSocket，客户端的话使用Cocos封装好的WebSocket就可以了，开发起来难度也不大。服务器端我用的Node.js开发的（我开发的不是这个项目），这个项目是我们张红银学长做的，我后期又优化了一下，他服务器端用的C#开发的。

服务器端因为用到了数据库，所以还要先配好数据库。
数据库我自己安装的最新版的MySQL，然后用navicat连接MySQL配的。
Cocos 封装的Socket.IO 与 HTTP在电脑上可以正常连接服务器，但是打包到Android上总是无法正常连接服务器，因此采用WebSocket，客户端的话使用Cocos封装好的WebSocket就可以了，开发起来难度也不大。服务器端我用的Node.js开发的（我开发的不是这个项目），这个项目是我们张红银学长做的，我后期又优化了一下，他服务器端用的C#开发的。
### 配置说明
服务器端因为用到了数据库，所以还要先配好数据库。
数据库我自己安装的最新版的MySQL，然后用navicat连接MySQL配的。
VS2019+VS2017（Cocos工程Debug用的VS2019，Release用的VS2017；C#工程Debug与Release用的都是VS2019）
VS2019以Release模式编译时会卡在CCTweenFunction.cpp这个文件上很久，应该是不兼容。
VS2019与2017都装好后，用VS2019打开工程，然后右键点击项目，再点击属性，即可进行切换平台工具集（即切换成用VS2017打包）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190606204133325.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0NPQ081Ng==,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190606204035394.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0NPQ081Ng==,size_16,color_FFFFFF,t_70)
Cocos2dx3.17.2
MySQL 8.0.16
Android打包教程：https://blog.csdn.net/COCO56/article/details/89392349
#### 流程概要
1、配置并启动MySQL
2、打开服务器端软件，输入ip地址和端口号，开启即可。
先链接数据库，然后开始监听服务
3、打开客户端先注册账号，然后登录，这个就不多说了。
