# 一、Spring Boot入门  

## 1. Spring Boot简介  

> 简化Spring应用开发的一个框架     
> 整合Spring技术栈的一个整合框架   
> J2EE开发的一站式解决方案   

## 2. 微服务   

2014年，martin fowler   

微服务是一种架构风格(将各种服务微化)   
一个应用应该是由一组小型服务构成，每个小服务都运行在独立的进程中，可以通过Http的方式进行互通   

每一个功能元素最终都是一个可以独立替换和独立升级的软件单元   

## 3. 环境准备  

* maven配置   

    在maven本地配置文件settings.xml中添加如下配置代码：   
    ```xml
    <profile>
      <id>jdk-1.8</id>

      <activation>
        <jdk>1.8</jdk>
      </activation>

      <repositories>
        <repository>
          <id>jdk18</id>
          <name>Repository for JDK 1.8 builds</name>
          <url>http://www.myhost.com/maven/jdk18</url>
          <layout>default</layout>
          <snapshotPolicy>always</snapshotPolicy>
        </repository>
      </repositories>
    </profile>
    ```  

* 然后将IDEA中的默认maven(Build -> Build Tools)替换成本地maven，并将设置文件也替换掉     

## 4. Spring Boot Hello World   

实现一个功能   
浏览器发送Hello请求，服务器接受请求并处理，相应Hello World字符串   

### 1.创建一个maven工程(jar)   
### 2.导入Springboot相关依赖    
在项目根目录下的pom.xml中加入下列配置代码  

```xml
    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>1.5.9.RELEASE</version>
    </parent>
    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
    </dependencies>
```  

* 父项目   
    ```xml
     <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>1.5.9.RELEASE</version>
    </parent> 

    它的父项目为  
    <parent>
		<groupId>org.springframework.boot</groupId>
		<artifactId>spring-boot-dependencies</artifactId>
		<version>1.5.9.RELEASE</version>
		<relativePath>../../spring-boot-dependencies</relativePath>
	</parent>
    ``` 
    这个父项目的父项目是Spring Boot的版本仲裁中心，负责管理项目里面用到的各种组建的版本   
    所以以后在项目中导入相关依赖是不需要写版本号的    

* 启动器   

    ```xml
    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
    </dependencies>
    ```  
    spring-boot-starter-web是Springboot的场景启动器，web启动器帮我们导入了web模块正常运行所依赖的组件  

    Spring Boot将所有的功能场景都抽取出来，做成一个一个的starters，只需在项目里面引入这些相关场景的启动器就可以导入所需要的依赖。   

### 3.编写一个主程序，来启动Springboot应用  

```java
@SpringBootApplication
public class HelloWorldMainApplication {
    public static void main(String[] args) {

        //传入当前类
        SpringApplication.run(HelloWorldMainApplication.class, args);
    }
}
```  

### 4.编写相应的Controller或者Service   

```java
@Controller
public class HelloController {
    
    @ResponseBody
    @RequestMapping("/hello")
    public String hello() {
        return "Hello World!";
    }
}
``` 

### 5.运行测试程序   

### 6.简化部署   

在项目配置文件pom.xml中添加maven插件，该插件可以将springboot应用打包成jar     

```xml
<build>
        <plugins>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
            </plugin>
        </plugins>
</build>
```
然后可以直接使用java -jar的命令执行这个应用，并且无需配置tomcat，因为这个jar包中已经包含了嵌入式的tomcat环境   




