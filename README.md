Any AS  任意字符串

git config --global user.name [Any]
git config --global user.email [Any]
cat ~/.gitconfig

创建仓库

git init
git add . // “.”的意思是把当前目录下的所有文件加入缓冲区
git commit -m "[Any]" //Any中代表的是本次更新的注册信息
git remote add origin [Any] //Any代表要提交仓库的https地址
git push -u origin master


[
    弹出的窗口输入你GitHub上的账号和密码，不是刚刚写入的user的信息
]




git pull //把远程仓库的代码拉过来覆盖本地的代码

git clone [Any] //想要克隆的仓库https地址
