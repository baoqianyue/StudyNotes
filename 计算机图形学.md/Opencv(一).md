# opencv基本函数，数据结构            

* Mat类

Mat类就是保存图像以及其他矩阵数据的数据结构，主要是用来存放图像的数据结构。默认情况下其尺寸为0，不过我们也可以指定它的尺寸       


```c++
cv::Mat img(320,640,cv::Scalar(100));
```     

这里Scalar()函数是设置图像的颜色的函数          


***       


* 图像的载入：imread()函数       

函数原型    

```c++
Mat imread(const string& filename, int flag = 1);
```    

第一个参数就是我们要传入的图片路径，此函数支持大多数图片格式       

第二个参数为载入标识，指定一个加载图像的颜色类型，默认值为1，其实在源码中这个参数是枚举定义的，这里只要知道以下几点即可：     

  1. flag > 0 返回一个3通道的彩色图像(如果已彩色类型载入图像，解码后的图像会以BGR的通道顺序存储，不是通常的RGB顺序)     

  2. flag = 0 返回灰度图像      

  3. flag < 0 返回包含Alpha通道的加载图像          

***        




* 图像显示：imshow()函数        

函数原型       

```c++
void imshow(const string& winname, InputArray mat);
```    

第一个参数就是显示的窗口名称       
第二个参数就是要显示的图像        

此函数的显示窗口大小和图像的深度有关：       

***    


* InputArray(OutputArray)类型        

大多数情况下，就当它是Mat就行了           


***


* 创建窗口:namedWindow()函数      

函数原型       

```c++
namedWindow(const string& winname, int flags=WINDOW_AUTOSIZE);
```       


前面说的imshow()也可以设置图像的显示窗口,并且第一个参数也是显示窗口的名称，但是如果我们要在显示窗口之前就需要窗口名称时，就需要用到这个函数，比如我们有的时候需要将滑动条设置到某个窗口上，就要先通过这个函数设置出窗口名称。          

第二个参数用来指定窗口大小和调节类型：

1. WINDOW_NORMAL 用户可以自行调节窗口大小      

2. WINDOW_AUTOSIZE 窗口自适应调节，而且用户不能进行调节(默认参数)       

3. WINDOW_OPENGL 窗口创建时支持OpenGL              


***


* 图像叠加函数:addweighted()    

函数原型       

```c++
AddWeighted( const CvArr* src1, double alpha,  const CvArr* src2, double beta,  double gamma, CvArr* dst );
```     
1. src1，第一个图像，可以是Mat        

2. alpha，第一个图像占的权值        

3. src2，第二个图像        

4. beta，第二个图像占的权值           

5. gamma，添加的常数项，用来进行微调         

6. dst，输出图像                  


***


* 点的表示: Point类          

```c++
Point point;
point.x = 10;
point.y = 10;
//或者
Point point = Point(10,10);
```     

Point和Point_<int>,Point2i等价，Point_<float>和Point2f等价        

***


* 颜色的表示: Scalar类          

```c++
Scalar(x,y,z);
```      

Scalar()表示拥有4个元素的数组，主要用来传递像素值，如果一个像素值只有RGB三通道，我们只写三个参数即可     

***



* 尺寸的表示: Size类            

```c++
Size(2,2);
```         

Size和Size_<int>,Size2i等价               


***


* 图像存储类型标识符        


对于二维多通道图像，在定义和存储的时候需要指定存储元素的数据类型以及每个矩阵点的通道数        
```
CV_[位数][带符号与否][类型前缀]C[通道数]     
```

CV_8UC3 表示使用8位的unsigned char型，每个像素由3个元素组成三通道           
CV_64FC1 常用来图像计算处理              
CV_8UC1 常用来显示图像          

***



* 矩形的表示: Rect类            

这个构造函数和Android自定义View的很相似       


***



* 颜色空间转化: cvtColor()函数          

函数原型          

```c++
void cvtColor(InputArray arc, OutputArray dst, int code, int dstCn = 0)
```     

第一个参数是输入图像，第二个是输出图像，第三个整形量为颜色空间转换的标识，第四个参数是转换后的通道数，如果该参数为0，就取源图像的通道数。            

常用标识符：      
```
RGB <--> BGR
CV_BGR2BGRA,CV_RGB2BGRA,CV_BGRA2RGBA...      

RGB <--> Gray  
CV_RGB2GRAY,CV_RGBA2GRAY,CV_GRAY2RGB,CV_GRAY2RGBA                

```

***



* 图像划分: Range()函数          

```c++
Mat A = Mat::eye(10,10,CV_32S);
//提取A的1到3列(不包含)   
Mat B = A(Range::All(),Range(1,3));
//提取B的5到9行(不包含)
Mat C = B(Range(5,9),Range::All());         
```      

***      

* 绘制圆: circle()函数           

```c++
circle(img,
      center,
      banjin,
      Scalar(0,255,255),
      thickness,
      lineType);
```   

第一个参数就是画圈区域，第二个参数就是圆心位置，第三个参数就是半径，第四个参数就是颜色，第五个参数就是线粗，第六个参数就是绘图模式    



***



* 产生随机数: RNG()           


***







***
***
***
***
***
***
