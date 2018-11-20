## 一、ping   

主要是测试本机TCP/IP协议配置正确性与当前网络现状.  

ping命令的基本使用格式是：  

`ping  IP地址/主机名/域名 [-t] [-a] [-n count] [-l size]`   

-t：连续对IP地址/主机名/域名执行Ping命令，直到被用户以Ctrl+C中断.   

-a：以IP地址格式显示目标主机网络地址，默认选项.   
 
-n count：指定要Ping多少次，具体次数由count来指定，默认值为4.  

-l size：指定Ping命令中发送的数据长度，默认值是32字节.  


## 二、netstat   

主要是帮助了解整体网络情况以及当前连接情况.

基本使用命令格式：  
`netstat [-n] [-a] [-e] [-r][-s]`    

-n：显示所有已建立的有效连接.    

-s：本选项能够按照各个协议分别显示其统计数据。如果应用程序（如Web浏览器）运行速度比较慢，或者不能显示Web页之类的数据，那么我们就可以用本选项来查看一下所显示的信息.我们需要仔细查看统计数据的各行，找到出错的关键字，进而确定问题所在.    


-e：本选项用于显示关于以太网的统计数据。它列出的项目包括传送的数据报的总字节数、错误数、删除数、数据报的数量和广播的数量。这些统计数据既有发送的数据报数量，也有接收的数据报数量.（这个选项可以用来统计一些基本的网络流量）          


-r：本选项可以显示关于路由表的信息，除了显示有效路由外，还显示当前有效的连接.      


-a：本选项显示一个所有的有效连接信息列表，包括已建立的连接（ESTABLISHED），也包括监听连接请求（LISTENING）的那些连接.     


 

## 三、ipconfig

主要是了解当前TCP/IP协议所设置的值，如IP地址、子网掩码、缺省网关、Mac地址等.   

基本使用方法：ipconfig [/all/release/renew]   

ipconfig：当不带任何参数选项，那么它为每个已经配置了的接口显示IP地址、子网掩码和缺省网关值.     

/all：当使用all选项时，能为DNS和WINS服务器显示它已配置且所要使用的附加信息（如IP地址等），并且显示内置于本地网卡中的物理地址（MAC）.如果IP地址是从DHCP服务器租用的，它会显示DHCP服务器的IP地址和租用地址预计失效的日期.      

/release & /renew ：这是两个附加选项，只能在向DHCP服务器租用其IP地址的计算机上起作用.如果我输入ipconfig/release，那么所有接口的租用IP地址便重新交付给DHCP服务器（归还IP地址）.如果输入ipconfig /renew，那么本地计算机便设法与DHCP服务器取得联系，并租用一个IP地址.请注意，大多数情况下网卡将被重新赋予和以前所赋予的相同的IP地址.    


 

## 四、route   

主要用于配置路由与查看当前路由情况.    

基本使用方法：route [print] [add] [change] [delete]    

print：主要是打印当前路由情况.    

add：手动添加路由或配路由，例子如下：     

```
route ADD 157.0.0.0 MASK 255.0.0.0  157.55.80.1 METRIC 3 IF 2
 
  destination^ （目标地址）  ^mask      ^gateway   metric^    ^
 
                                                   Interface^ (接口)  

```  

change：只用于修改网关和/或跃点数.例子如下：

`route CHANGE 157.0.0.0 MASK 255.0.0.0 157.55.80.5 METRIC 2 IF 2`    

delete：删除路由.例子如下：

`route DELETE 157.0.0.0`    
 

## 五、tracert(trace router的缩写，为路由跟踪命令)

主要用于显示将数据包从计算机传递到目标位置的一组IP路由器，以及每个跃点所需的时间(即跟踪数据报传送路径),测试网络连通性问题.    


基本用法:    
 ```tracert [-d] [-h maximum_hops] [-j host-list] [-w timeout]    
　[-R] [-S srcaddr] [-4] [-6] target_name(目标IP、URL或域名)
 
选项:
 
    -d                 不将地址解析成主机名.
 
    -h maximum_hops    搜索目标的最大跃点数.
 
    -j host-list       与主机列表一起的松散源路由(仅适用于 IPv4).
 
    -w timeout         等待每个回复的超时时间(以毫秒为单位).
 
    -R                 跟踪往返行程路径(仅适用于 IPv6).
 
    -S srcaddr         要使用的源地址(仅适用于 IPv6).
 
    -4                 强制使用 IPv4.
 
    -6                 强制使用 IPv6.   
```    

 

## 六、ARP(Address Resolution Protocol，地址解析协议，是获取物理地址的一个TCP/IP协议.)

主要用来查看本地计算机或另一台计算机的ARP高速缓存中的当前内容.

基本使用方法：  

`arp [-a/g] [-s] [-d]`     

-a：用于查看高速缓存中的所有项目,-a和-g参数的结果是一样的.

-s：向ARP高速缓存中人工输入一个静态ARP项目.

-d：删除ARP高速缓存中的内容.



附CMD比较常用命令集：
```
winver---------检查Windows版本    
wmimgmt.msc----打开windows管理体系结构(WMI)
wupdmgr--------windows更新程序
wscript--------windows脚本宿主设置
write----------写字板
winmsd---------系统信息
wiaacmgr-------扫描仪和照相机向导
winchat--------XP自带局域网聊天
mem.exe--------显示内存使用情况
Msconfig.exe---系统配置实用程序
mplayer2-------简易widnows media player
mspaint--------画图板
mstsc----------远程桌面连接
mplayer2-------媒体播放机
magnify--------放大镜实用程序
mmc------------打开控制台
mobsync--------同步命令
dxdiag---------检查DirectX信息
drwtsn32------ 系统医生
devmgmt.msc--- 设备管理器
dfrg.msc-------磁盘碎片整理程序
diskmgmt.msc---磁盘管理实用程序
dcomcnfg-------打开系统组件服务
ddeshare-------打开DDE共享设置
dvdplay--------DVD播放器
net stop messenger-----停止信使服务
net start messenger----开始信使服务
notepad--------打开记事本
nslookup-------网络管理的工具向导
ntbackup-------系统备份和还原
narrator-------屏幕“讲述人”
ntmsmgr.msc----移动存储管理器
ntmsoprq.msc---移动存储管理员操作请求
netstat -an----(TC)命令检查接口
syncapp--------创建一个公文包
sysedit--------系统配置编辑器
sigverif-------文件签名验证程序
sndrec32-------录音机
shrpubw--------创建共享文件夹
secpol.msc-----本地安全策略
syskey---------系统加密，一旦加密就不能解开，保护windows xp系统的双重密码
services.msc---本地服务设置
Sndvol32-------音量控制程序
sfc.exe--------系统文件检查器
sfc /scannow---windows文件保护
tsshutdn-------60秒倒计时关机命令
tourstart------xp简介（安装完成后出现的漫游xp程序）
taskmgr--------任务管理器
eventvwr-------事件查看器
eudcedit-------造字程序
explorer-------打开资源管理器
packager-------对象包装程序
perfmon.msc----计算机性能监测程序
progman--------程序管理器
regedit.exe----注册表
rsop.msc-------组策略结果集
regedt32-------注册表编辑器
rononce -p ----15秒关机
regsvr32 /u *.dll----停止dll文件运行
regsvr32 /u zipfldr.dll------取消ZIP支持
cmd.exe--------CMD命令提示符
chkdsk.exe-----Chkdsk磁盘检查
certmgr.msc----证书管理实用程序
calc-----------启动计算器
charmap--------启动字符映射表
cliconfg-------SQL SERVER 客户端网络实用程序
Clipbrd--------剪贴板查看器
conf-----------启动netmeeting
compmgmt.msc---计算机管理
cleanmgr-------垃圾整理
ciadv.msc------索引服务程序
osk------------打开屏幕键盘
odbcad32-------ODBC数据源管理器
oobe/msoobe /a----检查XP是否激活
lusrmgr.msc----本机用户和组
logoff---------注销命令
iexpress-------木马捆绑工具，系统自带
Nslookup-------IP地址侦测器
fsmgmt.msc-----共享文件夹管理器
utilman--------辅助工具管理器
```



