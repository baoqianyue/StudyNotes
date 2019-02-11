# JavaServer Page    

JSP部署在服务器上，用于响应客户端发送的请求，并根据请求内容动态的生成HTML，XML或其他格式的web网页，然后返回给请求者。

## JSP内Java相关语法块   

* jsp声明块    
    在声明块中只能进行变量和方法的声明和定义，且作用域为成员变量     
    标志`<%! %>`    

    ```java
    <%!
    //声明变量
    String str = "HelloWorld";

    //声明方法
    String getStr() {
        return "HelloWorld1";
    }
    %>
    ```      

* jsp脚本块    
    脚本块中可以放置java逻辑代码，在脚本块中声明的变量为局部变量   
    标志`<% %>`   
    
    ```java
    <% out.println(this.str);%>
    ```    

* jsp内容输出表达式   

    可以将java方法输出的内容或者java变量的值输出到web页面上，并且可以和html标签进行交叉编写   
    标志`<%= %>`
    ```java
    <%!
    public String getNow() {
        SimpleDateFormat formatter = new SimpleDateFormat("yyyy/MM/dd hh:mm:ss");
        Date currentTime = new Date();
        return formatter.format(currentTime);
    }
    %>

    <%= getNow()%>
    ```  

* jsp包引入语句块   

    将相关java类库引入到jsp文件中   
    标志`<%@ import="..." %>`   

    ```java
    <%--java包引入语句块--%>
    <%@ page import="java.util.*" %>
    <%@ page import="java.text.*" %>
    ```   

### JSP内置对象    

#### request对象   

request代表来自客户端的请求，例如在Form表单中填写的信息，客户端的请求信息被封装在request对象中，通过该对象，才能在服务端获得请求的信息，然后做出相应的响应   
request对象是`HttpServletRequest`类的实例    

```java
//通过一个元素的name属性获得该元素的value
request.getParameter(String name);
``` 

#### response对象    

response对象代表来自服务端的响应，当服务端需要向客户端发送数据时，使用response对象承载    

response对象是`HttpSerlvetResponse`类的实例    

```java
//返回响应使用的字符编码集
String getCharacterEncoding();
```





