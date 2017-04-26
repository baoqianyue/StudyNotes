# Bitmap简单介绍    
今天写《Android权威编程指南》的时候遇到了```BitmapFactory.Options()```,然后我又详细了解了Bitmap,
* Bitmap是Android开发中经常用到的，开发中，如果图片占用内存太大，就很容易造成OOM(Out Of Memory),因此了解Bitmap相关知识，在一定条件下对图片进行裁剪等操作就很有必要   
...

## 使用BitmapFactory.Options()     
首先放一段代码       
```java
public class PictureUtils {

  public static Bitmap getScaleBitmap(String path,int destWidth,int destHeight){
    BitmapFactory.Options options = new BitmapFactory.Options();
    options.inJustDecodeBounds = true;

  }

  BitmapFactory.decodeFile(path,options);
  float srcWidth = options.outWidth;
  float srcHeight = options.outHeight;
  int inSampleSize = 1;
  if (srcHeight > destHeight || srcWidth > destWidth) {
    if (srcWidth > srcHeight) {
      inSampleSize = Math.round(srcHeight / destHeight);
    } else {
      inSampleSize = Math.round(srcWidth / destWidth);
    }
  }

  options = new BitmapFactory.Options();
  options.inSampleSize = inSampleSize;
  return BitmapFactory.decodeFile(path,options);
}
```   

第一次看到这段代码真是一脸懵逼，真的不知道它干了什么，经过多方查询，终于有所了解   

* inJustDecodeBounds     
sdk是这样描述它的     
```If set to true,the decoder will return null(no bitmap),but the out...```                         
如果我们把它设为true,那```BitmapFactory.decodeFile(String path,Options options)```就不会像正常那样返回一个Bitmap，仅仅返回这个Bitmap的高和宽，这样就不会占用过多的内存，反而得到有用的信息，方便完成下面的操作         



* options.outWidth()和options.outHeight()       
在上一步设置为true之后，调用这两个方法就能得到我们期望的高和宽了       

* inSampleSize    
