## File概述       

* 用于将文件或者文件夹封装成对象，从而得到对文件的相关操作     

* 方便对文件或文件夹进行操作      

* File对象可以作为参数传递给流的构造函数      

我们先来看一下File类的构造方法     

```java
File(String pathname);
File(String parent, String child);
File(File parent, String child);
public File(URI uri);
```          

这里再介绍一个常量：   

```
File.separator;
```   

这个就是系统默认的文件名分隔符，在不同的系统中不一样的，在Windows下就是"\\"。      


写个例子：      

```java
public static void main(String[] args) {
       //创建文件对象，传入文件名
       File file = new File("test.txt");
       //传入文件目录和文件名
       File file1 = new File("D:\\", "test.txt");
       System.out.println(file);
       System.out.println(file1);
   }
```      

### 文件创建和删除     

* 创建      

```java
public boolean createNewFile() throws IOException
```

在指定的位置创建文件，如果文件已经存在就不创建，而且返回false。       

写个例子：      

```java
public static void main(String[] args) {
       File file = new File("D:\\test.txt");
       try {
           boolean flag = file.createNewFile();
           System.out.println(flag);
       } catch (IOException e) {
           e.printStackTrace();
       }
   }
```        

这样就能在D盘根目录下创建一个新的文件出来。       


* 删除     

其实就是一个函数：      

```java
file.delete();
```    

还有一个函数值得一提      

```java
file.deleteOnExit();
```     

这个函数就是在程序退出之后删除文件，应该会有情景会用到这个函数。       

### 判断文件是否存在           

```java
public static void main(String[] args) {
        File file = new File("test.txt");
        if (!file.exists()) {
            try {
                file.createNewFile();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
```   

这样就可以先判断文件是否存在，然后再去创建文件。      

### 创建文件夹     

```java
public static void main(String[] args) {
        //创建File对象
        File file = new File("barackbao");
        //创建文件夹，文件夹名为上面构造函数传入的名称
        file.mkdir();
    }
```     

可以看到在该项目根目录下又创建了一个名为barackbao的新文件夹。       

但是`mkdir()`只能创建一级目录，而`mkdirs()`可以创建多级文件夹目录。       

### 判断是否为文件/文件夹      

```java
public static void main(String[] args) {
       File file = new File("barackbao");
       System.out.println(file.isDirectory());
       System.out.println(file.isFile());
   }
```    

这里也是通过返回`boolean`值来确定结果，但是要注意一点，就是一定要确定这个文件或文件夹存在，所以我们可以将写法改进一下：     

```java
public static void main(String[] args) {
       File file = new File("barackbao");
       if (file.exists()) {
           if (file.isDirectory()) {
               System.out.println("文件夹");
           } else if (file.isFile()) {
               System.out.println("文件");
           }
       } else {
           try {
               file.createNewFile();
           } catch (IOException e) {
               e.printStackTrace();
           }
       }
   }
}
```      

### 获取文件和文件夹信息       

我们直接来一段代码介绍一下如果获取信息：      

```java
public static void main(String[] args) {
        File file = new File("test.txt");
        File file1 = new File("copy_test.txt");
        //列出文件相对路径，因为这个文件在项目中，所以这个函数只能列出该文件在该项目下的相对路径
        System.out.println("路径：" + file.getPath());
        //列出文件绝对路径
        System.out.println("绝对路径：" + file.getAbsolutePath());
        //最后一次修改时间
        System.out.println("时间：" + file.lastModified());
        //绝对路径中的文件父目录，如果是相对路径，返回为空
        System.out.println("父目录：" + file.getParent());
        //为文件重命名，其实相当于将原文件复制到一个文件中，然后将原文件删除
        System.out.println(file.renameTo(file1));
    }
```    

输出：    

```
路径：test.txt
绝对路径：D:\TestProjects\test.txt
时间：1509698932346
父目录：null
true
```  

而且文件名也已修改了。          

### 列出文件列表    

我们先输出一下系统目录     

```java
public static void main(String[] args) {
        File[] listRoots = File.listRoots();
        for (File file : listRoots) {
            System.out.println(file);
        }
    }
```      

输出：   

```
C:\
D:\
E:\
```   



输出一下选定盘下的文件列表     

```java
public static void main(String[] args) {
        File f = new File("D:\\");
        String[] fileList = f.list();
        for (String file : fileList) {
            System.out.println(file);
        }
    }
```      

输出：     

```
$RECYCLE.BIN
17-C-Train
360Zip
ACMCollections
AndroidProjects
AndroidStudio
BaiduNetdiskDownload
Cleaner
CloudMusic
Dev-Cpp
Download
GameDownload
Intellij IDEA
KotlinLoad
Oj C
SS
StudyNotes
Sublime Text 3
System Volume Information
test
test.txt
TestProjects
TIM
百度云盘
```     

### 文件过滤     

我们有的时候需要过滤一下文件,现在有这样一个需求，在D盘下过滤出后缀为`.txt`的文件，并把文件中的内容读取出来并打印            

```java
public static void main(String[] args) {
        File file = new File("D:\\");
        //使用过滤器
        String[] list = file.list(new FilenameFilter() {
            @Override
            public boolean accept(File dir, String name) {
                //以文件后缀来过滤
                return name.endsWith(".txt");
            }
        });
        for (String f : list) {
            System.out.println(f);
            //使用文件读取流将文件中的内容读取出来
            try {
                FileInputStream fis = new FileInputStream("D:" + File.separator + f);
                byte[] content = new byte[fis.available()];
                fis.read(content);
                System.out.println(new String(content));
                fis.close();
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }
```     

当然还有其他的过滤器，这里只介绍一种。       
