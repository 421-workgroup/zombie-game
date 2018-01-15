# 开发指南

## 开发平台

- Windows(推荐)
- Linux

## 开发依赖

这是指你在写代码前要装的东西。当然你不装这些也可以**写**代码，但你就不能很方便地把你的贡献上传到网上我们合作的仓库里，也无法用这些工具来编译这些代码来保证你写的正确性。

### git的安装

从群文件下载，安装。一路默认就好。

### python2的安装和配置

到https://www.python.org/downloads/下载右边的Python 2.7.14(可能版本号略有变化)，然后安装。

如果你已经安装了python3。请让新安装的python安装目录下的主程序和以前安装的python安装目录下的主程序(他们默认都叫python.exe)的名字不一样，如可以把新的主程序改成python2.exe。

比较方便的调用python2的方式是将python主程序的路径加到环境变量Path里面，不会的话参考这里：https://jingyan.baidu.com/article/48206aeafdcf2a216ad6b316.html。

### cocos2d-x的安装和配置

1. 先从这里下载：http://www.cocos2d-x.org/download
2. 解压到**不包含中文路径**的目录！
3. 在解压后的目录下有个`setup.py`。用python2执行它。也就是在该目录打开命令提示符或PowerShell，输入python或python2 setup.py。(你可能需要用管理员权限运行命令提示符或PowerShell)
4. 请确认cocos2d-x-3.16\tools\cocos2d-console\bin下cocos.bat的文件内容，确保它里面出现的python能够调用到python2，而不是python3。

## 源代码的获取

完成了上述依赖的安装。你就可以把[zombie-game](https://github.com/421-workgroup/zombie-game)仓库的内容克隆到本地了。

找到一个**不包含中文路径**的目录，在命令行下执行：

```bat
git clone https://github.com/421-workgroup/zombie-game
```

克隆完后在命令行进入该仓库：

```bat
cd zombie-game
```

你会发现，这个仓库所包含的文件只会包含该cocos项目中我们创建的类，也就是Classes文件夹下的内容。而每个cocos项目除了Classes文件夹还包含许多别的库文件，这些文件需要你执行generate.bat脚本来生成：

```bat
.\generate.bat
```

至此你的本地仓库就是一个完整的cocos2d-x项目了。