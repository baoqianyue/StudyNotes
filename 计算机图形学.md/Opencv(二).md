* 尺寸调整: resize()函数          

函数原型    
```c++
void resize(InputArray src, OutputArray dst, Size dsize, double fx = 0, double fy = 0, int interpolation = INTER_LINEAR);
```     

第一个参数就是输入图像，Mat类的对象        

第二个参数为输出图像，其不为零时，其尺寸为第三个参数的值dsize,或者通过src.size()计算出来         

第三个参数为输出图像的大小，如果它为零，其值通过下式计算    

```
dsize=Size(round(fx∗src.cols),round(fy∗src.rows))      
这里，dsize,fx,fy都不能为零
```      

第四个参数为沿着水平轴的缩放系数，默认值为0，当期为0时，通过下式计算     

```
fx=(double)dsize.width/src.cols
```    

第五个参数为沿着垂直轴的缩放系数，默认值为0，当其为0时，通过下式计算       

```
fy=(double)dsize.height/src.rows
```     

第六个参数用来指定插值方式，默认为INTER_LINEAR(线性插值)             
其可选值为:         

INTER_NEAREST最近邻插值

目标如下的像素点为对应的最近的原图像的像素点。假设原图像大小为(s_height, s_width)，目标图像大小为(d_height, d_width)，那么高度和宽度的缩放比例为h_ratio = s_height/d_height，w_ratio=s_width/d_width。

对面目标图像像素:(x, y)其值等于原图像(x * w_ration, y * h_ration)处的值。

INTER_LINEAR 线性插值

默认使用。在使用最近邻插值时，得到的坐标未必是一个整数，例如
(xw_ration, yh_ration)=（10.5， 20.5），那么可能取得坐标点就有四种（10， 20）、（11， 20）、（10， 21）、（11， 21）。双线性插值，会把这四个坐标的像素值加权求和。
D(x, y) = S(j, k) * w1 + S(j+1, k) w2 + S(j+1,k+1) w3 + S(j, K+1) * w4，其中w为权值。权值大小和计算位置的小数部分有关。

CV_INTER_AREA：区域插值

区域插值分为3种情况。图像放大时类似于线性插值，图像缩小时可以避免波纹出现。

INTER_CUBIC 三次样条插值

使用4x4邻域内的像素双3次插值。

INTER_LANCZOS4 Lanczos插值

使用8×8像素邻域的Lanczos插值
