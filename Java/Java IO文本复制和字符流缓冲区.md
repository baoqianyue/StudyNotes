## 文件的复制     

上一篇note记录了文件使用字符流进行读取，下面来介绍一下文本的复制。     

复制其实很简单，就是读取和写入合成的一个过程，我们平时复制文件的时候就是从一个地方把文件复制到另一个地方，如果我们以JavaIO字符流的角度来看就是我们从一个文件中将内容读取出来，然后将读取到的内容再写入到一个新的文件中。      

+ 复制步骤：     

    - 在D盘根目录下创建一个新文件，并创建流与它关联。     

    - 找到要复制的文件路径，并创建流与它关联。     

    - 然后让字符流循环读取并写入到新文件中。     

    - 关闭流。         

* 读取一个字符存储一个字符      

```java
public static void main(String[] args) {
        try {
            FileReader fileReader = new FileReader("test.txt");
            FileWriter fileWriter = new FileWriter("D://test.txt");

            //用字符流读取一个存储一个
            int ch = 0;
            while ((ch = fileReader.read()) != -1) {
                fileWriter.write(ch);
            }

            fileReader.close();
            fileWriter.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
```   

* 先将原文件中的数据读取后存到数组里，再写入到新文件中。       

```java
public static void main(String[] args) {
    FileReader fileReader = null;
    FileWriter fileWriter = null;
    try {
        fileReader = new FileReader("test.txt");
        fileWriter = new FileWriter("D://test.txt");

        char[] result = new char[1024];
        int len = 0;
        while ((len = fileReader.read(result)) != -1) {
            fileWriter.write(result, 0, len);
        }
    } catch (FileNotFoundException e) {
        e.printStackTrace();
    } catch (IOException e) {
        e.printStackTrace();
    } finally {
        if (fileReader != null) {
            try {
                fileReader.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        if (fileWriter != null) {
            try {
                fileWriter.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
```        

可以看到可以正确的复制文件。        
