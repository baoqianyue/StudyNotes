## 字节流的缓冲区     

前面的note中已经有过字符流的缓冲区，字节流的缓冲区也类似，这里我们直接用一段代码来介绍字节流缓冲区的使用方法。     

* 使用字节流缓冲区复制图片     

```java
public static void main(String[] args) {
        try {
            FileInputStream fis = new FileInputStream("testimg.jpg");
            FileOutputStream fos = new FileOutputStream("copy_img.png");
            BufferedInputStream buf = new BufferedInputStream(fis);
            BufferedOutputStream bos = new BufferedOutputStream(fos);

            int ch = 0;
            while ((ch = buf.read()) != -1) {
                bos.write(ch);
            }
            buf.close();
            bos.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
```    

这样就复制好了。      
