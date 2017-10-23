## String类概述         

先来一个经典的例子：    

```java
public class Main {

    public static void main(String[] args) {
        String str = "barack";
        str = "bao";
        System.out.println("str is: " + str);
    }
}
```    

输出为：     
```
str is: barack
str is: bao
```

我们说字符串对象最大的特点是一旦被创建就不会被改变，但这里这个字符串明显发生了改变，其实str只是一个对象的一个引用，就像指针一样，这里它只是指向字符串对象而已，本质上并不是一个对象，所以第二次对它赋值的时候，相当于又创建了一个字符串对象，然后让该引用指向了一个新的对象，而原来的对象"barack"并没有改变，仍然存在于内存中。       

在看一个例子：     

```java
public static void main(String[] args) {
    String str = "barack";
    String str1 = new String("barack");
    String str2 = "barack";
    System.out.println(str == str1);
    System.out.println(str.equals(str1));
    System.out.println(str == str2);
}
```           

输出：   

```
false
true
```      

这里第一个比较==是比较地址的，这里比较了两个引用，当然不相等，最后一个因为str,str2指向了同一个对象，所以比较地址的时候自然一样。而`equals()`方法是String类重写过的可以用来比较两个字符串的值是否相等。   

我们可以看一下`equals()`的源码：      

```java
public boolean equals(Object anObject) {
       if (this == anObject) {
           return true;
       }
       if (anObject instanceof String) {
           String anotherString = (String)anObject;
           int n = value.length;
           if (n == anotherString.value.length) {
               char v1[] = value;
               char v2[] = anotherString.value;
               int i = 0;
               while (n-- != 0) {
                   if (v1[i] != v2[i])
                       return false;
                   i++;
               }
               return true;
           }
       }
       return false;
   }

```      

是通过逐个比较字符来确定的。       

## 字符串常见操作       

* 字符串切割函数      

`String [] split(regex);`           

```java
public static void main(String[] args) {
    String str = "barackANDROIDisANDROIDaANDROIDboy";
    String[] result = str.split("ANDROID");
    for (int i = 0; i < result.length; i++) {
        System.out.println(result[i]);
    }
}
```

输出：    
```
 barack is a boy
```     

后面来补充源码及对源码的理解。     

* 获取字串函数    

`String subString(begin);`
`String subString(begin,end);`     

```java
public static void main(String[] args) {
    String str = "barackANDROIDisANDROIDaANDROIDboy";
    System.out.println(str.substring(1));
    System.out.println(str.substring(0, 6));
}
```    

输出：    

```
arackANDROIDisANDROIDaANDROIDboy
barack
```     

可以看到这个函数在截取的时候会根据参数啦截取，而且是含头不含尾。      


* 转换字符串大小写    

`String toUpperCase();`
`String toLowerCase();`



+ String类缓冲池介绍       

先来看一段代码：     

```java
public static void main(String[] args) {
            String s0 = "Android";
            String s1 = "Android";
            String s2 = "实验室";
            String s3 = s1 + s2;
            String s4 = "Android" + "实验室";
            String s5 = "Android实验室";
            String s6 = new String("Android");
            String s7 = new String("Android实验室");

            System.out.println(s0 == s1);
            System.out.println(s0 == s6);
            System.out.println(s3 == s4);
            System.out.println(s3 == s5);
            System.out.println(s4 == s5);
            System.out.println(s3 == s7);
            System.out.println(s4 == s7);

    }
```      

输出：       

```
true
false
false
false
true
false
false
```    

下面一行一行的解释原因：        

1). Java的字符串类是不可变类，所以任何对其对象的改变都会导致新建一个新的字符串对象出来，而且对其引用做的操作，对引用原来指向的字符串对象没有任何影响。    

这里s0指向的字符串已经存在于缓冲区中，所以s0，s1都指向了缓冲区中的同一个对象，所以地址相同。      

2). 当我们又使用new时，首先会新建一个对象，而且会重新分配空间，所以这里两个引用指向的位置不同。      

3). s3是对两个变量的操作，等同于`new StringBuilder(String.valueOf(s1)).append(s2).toString();`,因为新建了对象，所以内存经过了重新分配，而`s4 = "Android" + "实验室";`编译器会在编译的时候自动优化为`s4 = "Android实验室";`,所以两个地址不同。         

4). 原因同上。      

5). 原因同上。      

6). 原因同2.     

7). 原因同2.
