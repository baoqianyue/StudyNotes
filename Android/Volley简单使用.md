# Volley简介    
Android网络技术有很多框架，之前只会用Http协议来进行通信，使用HttpURLConnection和HttpClient，但是由于HttpClient存在API数量过多，扩展困难等缺点，Android官方在Android 6.0系统中就将HttpClient的功能完全移除了。
2003年GoogleI/O大会上推出了新的网络通信框架————Volley  
除了简单易用之外，Volley在性能方面也进行了大幅度的调整，它的设计目标就是非常适合去进行数据量不大，但通信频繁的网络操作，而对于大数据量的网络操作，比如说下载文件等，Volley的表现就会非常糟糕。    
## StringRequest        
* 1 在项目build.gradle的dependencies闭包中将Volley的依赖添加进来     
```
compile 'com.android.volley:volley:1.0.0'    
```
* 2 StringRequest的用法    
 * 先创建一个RequestQueue对象，其实就是创建一个请求队列，它可以缓存所有的HTTP请求，然后按照一定的算法并发地发出这些请求。RequestQueue内部的设计就是非常合适高并发的，因此我们不必为每一次HTTP请求都创建一个RequestQueue对象，这是非常浪费资源的，基本上在每一个需要和网络交互的Activity中创建一个RequestQueue对象就足够了。  
 ```java
 RequestQueue mQueue = new RequestQueue(context);
 ```     

 * 创建一个StringRequest对象来发送Http请求    
 ```java
 StringRequest stringRequest = new StringRequest("http://www.baidu.com",
                 new Response.Listener<String>() {
                     @Override
                     public void onResponse(String response) {
                         Log.d(TAG, "onResponse:");
                     }
                 }, new Response.ErrorListener() {
             @Override
             public void onErrorResponse(VolleyError error) {
                 Log.d(TAG, "onErrorResponse");
             }
         });
 ```
 这里StringRequest的构造函数需要传入三个参数，第一个参数是目标服务器的URL地址，第二个参数服务器响应成功的回调，第三个参数是服务器响应失败的回调。其中，目标服务器地址我们填写的是百度的首页，然后在响应成功的回调里打印出服务器返回的内容，在响应失败的回调里打印出失败的详细信息。    

  * 将StringRequest对象添加到RequestQueue队列中去     
 ```java
 mQueue.add(stringRequest);
 ```
 * 在Manifest.xml注册文件中申请一下网络权限就可以了    

## JsonRequest      
* 1 简单介绍    
类似于StringRequest的用法，JsonRequest也是继承自Request类的，不过因为JsonRequest是个抽象类，所以不能直接创建它的实例，只能从它的子类入手，JsonRequest有两个直接子类，JsonObjectRequest和JsonArrayRequest,前者用来请求一段JSON数据，后者用来请求一段JSON数组       
