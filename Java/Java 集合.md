## Java集合     


### Map的Entry接口      

Map是一个接口，Map.Entry是Map的一个内部接口           

Map提供了一系列方便访问内部数据的方法，其中常见的有两个`keySet()`,`entrySet()`        

* Entry接口    

    A map entry(key-value pair)      
    该接口表示Map中的一个实体       

* keySet()     

    keySet()方法返回Map中key的集合         

* entrySet()      

    entrySet()方法返回一个Map.Entry集合          

* 几种遍历Map的方式      

    * 使用keySet()方法    

        ```java
        Map map = new HashMap();
        Set keySet = map.keySet();
        
        ```

