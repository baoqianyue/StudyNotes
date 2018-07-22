# Spring Boot   

## 属性注入注解    

* @Value("${属性名}")
* @Component   
* @ConfigurationProperties(prefix = "前缀")     


## Controller的使用    

* 相关注解    

    * @Controller 处理Http请求    
    * @RestController  
        Spring4之后新加的注解，原来返回json需要@ResponseBody配合@Controller     

    * @RequestMapping 
        配置url映射     

    * @PathVariable   

        使用这种注解的url形式为：  
        `127.0.0.1:8080/hello/say/xxx`
        获取url中的id的数据,通过在注解中指定变量名来获取      
        ```java
        @RequestMapping(value = {"/hello/say/{id}"}, method = RequestMethod.GET)
        public String say(@PathVariable("id") Integer id) {
            return "id: " + id;
        }
        ```

    * @RequestParam     
        
        使用这种注解的url形式为：   
        `127.0.0.1:8080/hello/say?id=xxx`
        获取请求url中id的值     
        ```java
        @RequestMapping(value = {"/hello/say"}, method = RequestMethod.GET)
        public String say(@RequestParam("id") Integer mId) {
            return "id: " + mId;
        }
        ```      

        还可以给url中的参数设置其他属性，比如说是否必填和默认值   
        ```java
        @RequestMapping(value = {"/hello/say"}, method = Request.GET)
        public String say(@RequestParam())
        ```

    * @GetMapping 
        将@RequestMapping简化    
        ```java
        @RequestMapping(value = "/hello/say",method = Request.GET)
        @GetMapping(value = "/hello/say")
        ```          


## 数据库操作      

### RESTful API设计     

|  请求类型  |  请求路径     |  功能     | 
|-----|------|-------|   
| GET   |   /girls     |     请求girl列表       |
| POST   | /girls     |   创建一个girl  |   
| GET    |  /girls/id  |  通过id查询一个girl  |   
| PUT    |  /girls/id  |  通过id更新一个girl |    
| DELETE | /girls/id   |  通过id删除一个girl |   




    