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


## 字符流的缓冲区      

前面基本已经介绍完了字符流的基本内容，现在我们来看一下字符流的缓冲区。      

字符流缓冲区提高了字符读取和存储的效率，这个我们下面会写代码举例来验证。       

+ 字符流缓冲区的子类         

    - BufferedWriter         

    - BufferedReader        

缓冲区要结合具体存在的流才能使用。     


### BufferedWriter           

使用字符流缓冲区，既然要使用缓冲区，所以我们首先要有一个字符流，前面说过缓冲区的出现就是为了提高一般字符流的工作效率，所以我们把要提高效率的字符流作为参数传递给字符流缓冲区的构造函数。       

* 构造函数      

```java
BufferedWriter(Writer out);    
BufferedWriter(Writer out, int sz);
```          

构造函数很简单，就是传入一个具体的流，还可以直接指定缓冲区的大小。      

先看一个例子     

```java
public static void main(String[] args) {
        try {
            FileWriter fileWriter = new FileWriter("test.txt", true);
            BufferedWriter bufWriter = new BufferedWriter(fileWriter);
            //写入数据
            bufWriter.write("HelloWorld");
            //换行
            bufWriter.newLine();
            //刷新，用到了缓冲区就需要刷新才能将缓冲区内的内容写入到文件中
            bufWriter.flush();
            //这里关闭的
            bufWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
```     

可以看到文件续写成功。       

为了证明缓冲区进行了效率提高，我们来写一个程序来实际的确定一下。          

```java
public static void main(String[] args) {
       testFileWriter();
       testBufferedWriter();
   }

   //测试字符流
   private static void testFileWriter() {
       long begin = System.currentTimeMillis();
       long over;
       try {
           FileWriter fileWriter = new FileWriter("test.txt");
           fileWriter.write("ThePositiveThinkerSeesTheInvisibleFeelsTheIntangibleAndAchievesTheImpossible");
           fileWriter.close();
           over = System.currentTimeMillis();
           System.out.println("字符流写入操作用时：" + (over - begin) + "ms");
       } catch (IOException ex) {
           ex.printStackTrace();
       }
   }

   //测试字符流缓冲区
   private static void testBufferedWriter() {
       long begin = System.currentTimeMillis();
       long over;
       try {
           FileWriter fileWriter = new FileWriter("test.txt");
           BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
           bufferedWriter.write("ThePositiveThinkerSeesTheInvisibleFeelsTheIntangibleAndAchievesTheImpossible");
           bufferedWriter.flush();
           bufferedWriter.close();
           over = System.currentTimeMillis();
           System.out.println("字符流缓冲区写入操作用时：" + (over - begin) + "ms");
       } catch (IOException e) {
           e.printStackTrace();
       }

   }
```     

输出：    

```
字符流写入操作用时：11ms
字符流缓冲区写入操作用时：2ms
```      

为了使对比明显，我故意写了很长一段内容进去，可以看到缓冲区的完成速度要字符流快很多。        

在缓冲区中封装了一个数组，存入数据后一次取出。           

### BufferedReader     

* 构造函数    

```java
BufferedReader(Reader in);
BufferedReader(Reader in, int size);
```     

构造函数与BufferedWriter的很类似。      

我们来读取一个文件      

```java
public static void main(String[] args) {
       try {
           //先创建一个字符流对象与文件相关联
           FileReader fileReader = new FileReader("test.txt");
           //创建字符流缓冲区
           BufferedReader bufReader = new BufferedReader(fileReader);

           String line = null;
           while ((line = bufReader.readLine()) != null) {
               System.out.println(line);
           }
           bufReader.close();
       } catch (FileNotFoundException e) {
           e.printStackTrace();
       } catch (IOException e) {
           e.printStackTrace();
       }
   }
```     

可以输出文件中的内容，这段代码中出现了一个新的方法，`readLine()`。       

### readLine()函数的工作原理       


我们来看一下这个函数的源码和官方描述     

```java
/**
   * Reads a line of text.  A line is considered to be terminated by any one
   * of a line feed ('\n'), a carriage return ('\r'), or a carriage return
   * followed immediately by a linefeed.
   *
   * @return     A String containing the contents of the line, not including
   *             any line-termination characters, or null if the end of the
   *             stream has been reached
   *
   * @exception  IOException  If an I/O error occurs
   *
   * @see java.nio.file.Files#readAllLines
   */
  public String readLine() throws IOException {
      return readLine(false);
  }
```      

注释里面介绍的很清楚，这个函数就是来一行一行的读取文本，而且返回值就是这一行文本的内容，不包含结束符。           

其实这个方法在具体操作的时候还是一个字符一个字符的读取完成的，也就是最底层的实现是`read()`函数，只不过这个函数设置了一个数组，这个数组就是所谓的缓冲区，读取一个字符后先将字符存到这个数组里，当读到换行或者回车符等结束符时，才去把此时数组中的数据读取，这就是它的工作原理。     



### 使用缓冲区来复制文件        

我们直接上代码     

```java
public static void main(String[] args) {
       BufferedReader bufferedReader = null;
       BufferedWriter bufferedWriter = null;

       try {
           FileReader fileReader = new FileReader("test.txt");
           FileWriter fileWriter = new FileWriter("D://test.txt");

           bufferedReader = new BufferedReader(fileReader);
           bufferedWriter = new BufferedWriter(fileWriter);

           String line = null;
           while ((line = bufferedReader.readLine()) != null) {
               bufferedWriter.write(line);
           }

           bufferedWriter.flush();

           bufferedReader.close();
           bufferedWriter.close();
       } catch (FileNotFoundException e) {
           e.printStackTrace();
       } catch (IOException e) {
           e.printStackTrace();
       }
   }
```      

很简单。      



###  自定义readLine()      

```java
public static void main(String[] args) {
        /**
         * 使用自定义的readLine()函数
         */
        //先创建流与文件相关联
        try {
            FileReader fileReader = new FileReader("test.txt");
            CustomBufferedReader customBufferedReader = new CustomBufferedReader(fileReader);

            String content = null;
            while ((content = customBufferedReader.customReadLine()) != null) {
                System.out.println(content);
            }

            customBufferedReader.customClose();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public class CustomBufferedReader {
        private FileReader fileReader = null;

        public CustomBufferedReader(FileReader fileReader) {
            this.fileReader = fileReader;
        }

        public String customReadLine() throws IOException {
            //定义临时容器
            StringBuilder stringBuilder = new StringBuilder();
            int ch = 0;
            while ((ch = fileReader.read()) != -1) {
                if (ch == '\n') {
                    return stringBuilder.toString();
                } else if (ch == '\r') {
                    continue;
                } else {
                    stringBuilder.append((char) ch);
                }
            }

            if (stringBuilder.length() != 0) {
                return stringBuilder.toString();
            }

            return null;
        }

        public void customClose() throws IOException {
            fileReader.close();
        }
    }

```      

这就是简单的自定义`readLine()`。         


### LineNumberReader       

这个是BufferedReader的一个子类，我们来看一下这个类的官方描述：      

```
A buffered character-input stream that keeps track of line numbers.  This
 * class defines methods {@link #setLineNumber(int)} and {@link
 * #getLineNumber()} for setting and getting the current line number
 * respectively.
```        

这个类可以在读取的时候跟踪行号，也提供了修改行号的方法。       

我们来看个例子：    

```java
public static void main(String[] args) {
        try {
            FileReader fileReader = new FileReader("test.txt");
            LineNumberReader lineNumberReader = new LineNumberReader(fileReader);
            String content = null;

            while ((content = lineNumberReader.readLine()) != null){
                System.out.println(lineNumberReader.getLineNumber()+" " + content);
            }

            lineNumberReader.close();

        }catch (FileNotFoundException e){
            e.printStackTrace();
        }catch (IOException ex){
            ex.printStackTrace();
        }

    }
```      

输出：      

```
1 BarackBao
2 HelloWorld
3 AndroidLab
```      

我们还可以使用`setLineNumber(int)`来更改行号，但是需要注意的是这个方法并不会改变流中的当前位置，只更改`getLineNumber()`方法返回的值。      
