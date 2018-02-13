## StringBuffer概述      

* StringBuffer是一个容器     

* StringBuffer是线程安全的      

* 可以操作多个数据类型    

* 最后通过`toString()`方法转换为字符串。          

## StringBuffer各项操作     

* 存储      


`StringBuffer append();`    

将指定的数据拼接到缓存区内已有数据的后面。      

该方法连接字符串比String更加节省内容，经常用于数据库SQL语句的连接。        


* 删除   

`StringBuffer delete(start, end);`       

删除缓存区内的数据，含头不含尾。        

`StringBuffer deleteCharAt(index);`    

删除指定位置的字符。       

```java
StringBuffer stringBuffer = new StringBuffer("Barack");
stringBuffer.append("Bao");
System.out.println(stringBuffer.toString());
stringBuffer.delete(0, 6);
System.out.println(stringBuffer.toString());
}
```   

输出：    

```
BarackBao
Bao
```     

* 获取    

```
char charAt(int index);
int indexOf(String str;
String subString(int start, int end);
```    


* 修改    

```
StringBuffer replace(start, end, string);
void setCharAt(int dex, char ch);  
```         

介绍就这么多。            


## StringBuilder概述及其与StringBuffer的区别        

StringBuffer、StringBuilder和String都是代表字符串，前面说过String是不可变类，任何对String的改变都会引发新的String对象生成，StringBuffer则是可变类，任何对它所指代的字符串的改变都不会产生新的对象，但是为什么还要有StringBuilder。        

对集合来说，HashTable是线程安全的，很多方法都是synchronized方法，而HashMap则线程不安全，但是其在单线程程序中的性能比HashTable要高很多，StringBuffer和StringBuilder的区别也是如此，StringBuffer支持并发操作，适合用于多线程程序中，而StringBuilder线程不安全，不支持并发操作，但其在单线程中的性能要高。    


* 操作    

基本与StringBuffer一样。      
