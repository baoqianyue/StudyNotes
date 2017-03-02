# 简单的使用github  

github是目前世界上热门的项目托管网站，有很多知名的项目都通过github来完成，将全世界的开发者联系起来，下面我来解释一下如何简单的使用github，和如何利用它合作完成项目。    
## Repositories

首先你要注册一个github账号，因为这个网站也相当于一个社交网站，登陆后，最常用到的就是Repositories了，这个就是代码仓库，如果你要在github上托管项目，你需要先创建一个仓库。
![](http://p1.bpimg.com/567571/dcd1e9809270ce07.png)
* Repositories name - 为你的仓库设置一个名字
* Description - 对你的项目进行简单描述   
* Public/Private - 为你的仓库设置访问权限  
* Initialize a README -  是否添加说明文档  
* Add.gitignore - 设置忽略文件类型，就是告诉Git哪些文件不需要添加到版本控制中去  
* Add a license - 设置证书   
创建成功后就可以通过Git将代码上传到仓库   


## Fork和branch  
如果有两个哥们要和合作完成一个项目，就要用到Fork了，如果老哥A负责主要工作，那么就是他先创建仓库，成为master主分支线，老哥A写完代码上传了以后就轮到老哥B工作了，如果让A把已经写好的代码发给他的话，就有点太麻烦了，老哥B只需要在A的仓库下Fork一下，这样就会在B这里创建一个同样的仓库，B就成为这个项目的一个branch了，就是成为了一个分支，B就可以在自己的github上clone项目到本地，这样就可以在A的代码基础上继续开发了。


## git fetch  
如果在Bfork仓库的过程中，老哥A又写了好多代码，这个时候就要用到fetch了，fetch就是从远程仓库中抽取本地没有的代码。


## git merge 和 pull request   
当B使用git fetch在远程仓库抽取了本地没有的代码后，就使用git merge合并一下分支，如果没有发生合并冲突，那老哥B就能在github上向A发送pull request申请项目合并，老哥A可以看到B修改的具体内容，然后同意项目合并，这样老哥B就正式成为项目的contributer了。  
