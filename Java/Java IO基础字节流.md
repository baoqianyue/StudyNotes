## 字节流的读写操作         

+ 字节流的抽象基类     

   - InputStream     

   - OutputStream  

前几篇note主要介绍了字符流的见简单使用和方法，现在开始介绍字节流的一些操作和使用。           

### 字符流写文件      

其实和字符流的方式是一样的，只是换成操作字节了。    

我们直接来写一个例子：    

```java
public static void main(String[] args) {
        try {
            FileOutputStream fos = new FileOutputStream("test.txt");
            fos.write("Barack".getBytes());
            fos.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
```    

因为是操作字节，我们要将要写入的数据转换成字节在进行操作，而且这里写入后不需要刷新操作，这是和字符流写入不同的一点。      

### 字符流读取文件      

同样我们先用之前的步骤来读取文件，只是将字符流换成字节流。      

* 第一种方式


```java
public static void main(String[] args) {
        try {
            FileInputStream fis = new FileInputStream("test.txt");
            int ch = 0;
            while ((ch = fis.read()) != -1) {
                System.out.println((char) ch);
            }
            fis.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
```   

* 第二种方式     

```java
public static void main(String[] args) {
        try {
            FileInputStream fis = new FileInputStream("test.txt");
            byte[] buf = new byte[1024];
            int len = 0;
            while ((len = fis.read(buf)) != -1) {
                System.out.println(new String(buf, 0, len));
            }
            fis.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
```    
