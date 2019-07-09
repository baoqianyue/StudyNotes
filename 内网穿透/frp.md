## ubuntu服务器配置      

可以访问校园网内的gpu服务器上的web服务   

## 有公网IP服务器做服务端   

frps.ini配置文件如下：    

```
[common]
bind_port = 7000 # 与客户端保持连接的端口
```   

## 内网服务器为客户端    

frpc.ini配置文件如下：    

```
[common]
server_addr = aaa.bbb.ccc.ddd
server_port = 7000 # 该端口要与服务器配置中端口一致    

[web]    
type = tcp
local_ip = 127.0.0.1
local_port = 6000  # 在内网服务器上部署好的web服务端口
remote_port = 6000
```

### frp后台开启和停止(有公网IP)   

后台开启服务：    
`nohup ./frps -c frps.ini &`    

查看服务端frp log：      
` tail -f nohup.out`   

后台服务停止：        
`ps -aux|grep frp| grep -v grep`   
输出：   
`root      3600  0.1  0.1 110188  9484 pts/0    Sl   15:04   0:00 ./frpc -c ./frpc.ini`    
得到进程号为3600    

关闭：   
`kill -9 3600`     

### 参考       
[在win10上将frp客户端服务注册为系统service](https://www.jianshu.com/p/a6e9627dbe29)    


 