# opencv基本函数，数据结构            

* Mat类

Mat类就是保存图像以及其他矩阵数据的数据结构，主要是用来存放图像的数据结构。默认情况下其尺寸为0，不过我们也可以指定它的尺寸       


```c++
cv::Mat img(320,640,cv::Scalar(100));
```     

这里Scalar()函数是设置图像的颜色的函数          


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


* 图像显示：imshow()函数        

函数原型       

```c++
void imshow(const string& winname, InputArray mat);
```    

第一个参数就是显示的窗口名称       
第二个参数就是要显示的图像        

此函数的显示窗口大小和图像的深度有关：       



* InputArray类型        

大多数情况下，就当它是Mat就行了           


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
