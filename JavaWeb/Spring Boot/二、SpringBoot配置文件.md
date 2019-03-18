# 二、配置文件  

## application.yml   

项目配置文件`application.yml`中   

```yml
person:
  lastName: zhangsan
  age: 18
  boss: false
  birth: 2010/12/02
  maps: {k1: v1, k2: v2}
  lists:
    - lisi
    - zhaoliu
  dog:
    name: xiaoguo
    age: 2
```

javaBean为：  

```java
/**
 * 将配置文件中的每个值都注入到这个组件中
 *
 * @ConfigurationProperties告诉Springboot将本类中的所有属性和配置文件中相关的配置进行绑定 prefix代表配置文件中的前缀
 * <p>
 * 只有这个组件是容器中的组件，才能使用容器提供的@ConfigurationProperties功能
 */
@Component
@ConfigurationProperties(prefix = "person")
public class Person {

    private String lastName;
    private Integer age;
    private Boolean boss;
    private Date birth;
    private Map<String, Object> maps;
    private List<Object> lists;
    private Dog dog;
```

可以导入配置文件解析器，在pom.xml中添加依赖   

```xml
 <!--配置文件解析器-->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-configuration-processor</artifactId>
            <optional>true</optional>
        </dependency>
```

## 属性值的注入   

|                                | @ConfigurationProperties | @Value       |
| ------------------------------ | ------------------------ | ------------ |
| 功能                           | 批量注入配置文件中的属性 | 一个一个指定 |
| 松散绑定(模糊语法)             | 支持                     | 不支持       |
| SpEL（表达式求值）             | 不支持                   | 支持         |
| JSR303数据校验（数据格式校验） | 支持                     | 不支持       |
| 复杂类型封装                   | 支持                     | 不支持       |

配置文件yml和properties他们都可以获取到值。

如果只是需要在某个业务逻辑中获取一下配置文件中的某项值，使用@Value

如果专门编写了一个javaBean来和配置文件进行映射，就直接使用@ConfigurationProperties 





