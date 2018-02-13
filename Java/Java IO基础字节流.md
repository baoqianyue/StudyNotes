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

可以看到这里的读取操作基本与之前使用字符流进行读取操作很类似，只是把字符流换成了相应的字节流而已。      

下面我们来介绍一个新的方法`available()`       

```java
public static void main(String[] args) {
        try {
            FileInputStream fis = new FileInputStream("test.txt");
            int num = fis.available();
            System.out.println(num);
            byte[] buf = new byte[num];
            fis.read(buf);
            System.out.println(new String(buf));
            fis.close();
        } catch (FileNotFoundException f) {
            f.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
```      

输出：    

```
6
Barack
```     

我们看一下`available`的官方解释：      

```java
/**
     * Returns an estimate of the number of remaining bytes that can be read (or
     * skipped over) from this input stream without blocking by the next
     * invocation of a method for this input stream. Returns 0 when the file
     * position is beyond EOF. The next invocation might be the same thread
     * or another thread. A single read or skip of this many bytes will not
     * block, but may read or skip fewer bytes.
     *
     * <p> In some cases, a non-blocking read (or skip) may appear to be
     * blocked when it is merely slow, for example when reading large
     * files over slow networks.
```    

就是说该方法可以返回当前文件剩余的字节数，可以提前设置数组的长度，该方法在后面的网络编程中还有其他的作用，未完待续...           


## 字节流复制图片       

我们先理一下思路：      

* 创建字节读取流与原图片相关联     

* 创建字节写入流创建新图片文件       

* 循环读写，存储图片    

* 关闭流      

直接上代码，必须很熟练的写出来：      

```java
public static void main(String[] args) {
       try {
           //读取原图片
           FileInputStream fis = new FileInputStream("testimg.jpg");
           //写入新文件
           FileOutputStream fos = new FileOutputStream("copy_img.png");
           int length = fis.available();
           byte[] buf = new byte[length];
           int ch = 0;
           while ((ch = fis.read(buf)) != -1) {
               fos.write(buf, 0, ch);
           }
           fis.close();
           fos.close();
       } catch (FileNotFoundException e) {
           e.printStackTrace();
       } catch (IOException e) {
           e.printStackTrace();
       }
   }
```    


这样图片就复制好了。       
