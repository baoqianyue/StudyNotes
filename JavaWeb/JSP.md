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

* request作用域   

    request作用域在相邻两个web资源之间共享同一个request**请求对象**时使用   

#### response对象    

response对象代表来自服务端的响应，当服务端需要向客户端发送数据时，使用response对象承载    

response对象是`HttpSerlvetResponse`类的实例    

```java
//返回响应使用的字符编码集
String getCharacterEncoding();
```  

#### page对象   

代表正在运行的由JSP文件产生的类对象,指向当前JSP页面本身，类似于类中的this指针   

获取当前JSP页面对应的servlet实例的信息   

```java
page.getServletInfo();    
```

#### pageContext对象    

pageContext对象提供了获取其他内置对象的方法，还有转发请求到其他web资源的功能    

* 请求转发功能   

    ```java
    //将当前页面重导到其他页面
    pageContext.forward(String relativeUrlPath);   
    ```  

* 动态引入界面  

    ```java
    //在当前位置包含另一个文件
    pageContext.include(String relativeUrlPath);
    ```  

#### session对象    

session是指客户端与服务器的一次会话，此间所有的交互内容都会被记录在session对象中，是`HttpSession`类的实例   

* 相关信息的存取   

    ```java
    # 存数据 
    session.setAttribute(String s, Object o);
    # 取数据
    session.getAttribute(String s);
    ```  

* session有效时间   

    ```java
    session.setMaxInactiveInterval(int second); 
    ```    

#### exception对象   

当一个JSP页面在运行时出现了异常，这时就会产生一个exception对象    

如果希望在另一个页面中进行异常的处理，就在指定错误处理页面    

```java
<%@ page contentType="text/html;charset=UTF-8" errorPage="error.jsp" language="java" %>
```   
这样当当前界面发生异常时会自动跳转到`error.jsp`页面进行错误处理   

错误处理页面也需要进行设定    

```java
<%@ page contentType="text/html;charset=UTF-8" language="java" isErrorPage="true" %>
```

#### application对象   

application对象实现了不同用户之间的信息共享，存放全局变量，该对象的生命周期为从服务器启动到服务器关闭，在此期间，该对象一直存在，这样在用户的前后连接或者不同用户之间的连接中，都可以对该对象的同一属性进行操作和访问    

是`ServletContext`的实例   

属性值的存取   

```java
application.setAttribute(String name, Object o);
application.getAttribute(String name); 
```




