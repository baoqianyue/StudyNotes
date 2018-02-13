# 画布操作       

## 1.位移(translate)    
```java
/**
     * Preconcat the current matrix with the specified translation
     *
     * @param dx The distance to translate in X
     * @param dy The distance to translate in Y
    */
    public void translate(float dx, float dy) {
        native_translate(mNativeCanvasWrapper, dx, dy);
    }
```    
这个位移指的是坐标系的移动，也可以看作是坐标原点的移动，屏幕默认坐标原点在左上角，但是我想在稍微靠近屏幕中间的位置画图      

```java
@Override
   protected void onDraw(Canvas canvas) {
       super.onDraw(canvas);
       mPaint.setColor(Color.BLACK);
       mPaint.setAntiAlias(true);
       mPaint.setStyle(Paint.Style.FILL);
       //第一个圆
       //translate移动画布中心，每次移动相对于当前位置，而不是相对与左上角坐标原点
       canvas.translate(200, 200);
       canvas.drawCircle(0, 0, 100, mPaint);

       //第二个圆
       mPaint.setColor(Color.BLUE);
       canvas.translate(200, 200);
       canvas.drawCircle(0, 0, 100, mPaint);
   }
```     
效果如图    
<div align="center">       
<img src="http://i2.muimg.com/588926/6413f9e051e3b51d.png"
width="300" height="600" align=center/>      
</div>    


可以看到translate移动画布中心，每次移动相对于当前位置，而不是相对与左上角坐标原点，而且位移是可叠加的        

## 2.缩放(scale)     
有两个的方法       
```java
/**
    * Preconcat the current matrix with the specified scale.
    *
    * @param sx The amount to scale in X
    * @param sy The amount to scale in Y
    */
   public void scale(float sx, float sy) {
       native_scale(mNativeCanvasWrapper, sx, sy);
   }

   /**
    * Preconcat the current matrix with the specified scale.
    *
    * @param sx The amount to scale in X
    * @param sy The amount to scale in Y
    * @param px The x-coord for the pivot point (unchanged by the scale)
    * @param py The y-coord for the pivot point (unchanged by the scale)
    */
   public final void scale(float sx, float sy, float px, float py) {
       translate(px, py);
       scale(sx, sy);
       translate(-px, -py);
   }
```      
第一个方法有两个参数，分别代表在x，y坐标上缩放的程度，如果参数大于0，小于1，就会将画布按参数缩小，如果参数小于0，且大于-1，同样会将画布缩小，但是根据缩放中心进行反转(默认缩放中心为坐标原点)       
第二个方法相比前一个多了两个参数，这两个参数用来确定缩放中心       

```java
       int mWidth = canvas.getWidth();
       int mHeight = canvas.getHeight();
       canvas.translate(mWidth / 2, mHeight / 2);

       RectF rect = new RectF(0, -400, 400, 0);
       mPaint.setColor(Color.BLACK);
       canvas.drawRect(rect, mPaint);

       //缩放时根据缩放中心轴进行翻转（参数都小于1）
       canvas.scale(-0.5f, -0.5f);

       mPaint.setColor(Color.BLUE);
       canvas.drawRect(rect, mPaint);
```       

效果如图：  

<div align="center">       
<img src="http://i4.buimg.com/588926/4b52337503b91017.png"
width="300" height="600" align=center/>      
</div>    


此外，缩放也可以叠加，叠加效果就是多次缩放的参数之积       

最后还有一个功能，可以强行改变坐标轴的方向        

**canvas.scale(1,-1)**         

这样就直接把y坐标轴方向改变，与传统坐标轴符合             

## 3.旋转(rotate)    

```java
/**
     * Preconcat the current matrix with the specified rotation.
     *
     * @param degrees The amount to rotate, in degrees
     */
    public void rotate(float degrees) {
        native_rotate(mNativeCanvasWrapper, degrees);
    }

    /**
     * Preconcat the current matrix with the specified rotation.
     *
     * @param degrees The amount to rotate, in degrees
     * @param px The x-coord for the pivot point (unchanged by the rotation)
     * @param py The y-coord for the pivot point (unchanged by the rotation)
     */
    public final void rotate(float degrees, float px, float py) {
        translate(px, py);
        rotate(degrees);
        translate(-px, -py);
    }
```     

同样两个方法，同样第二个方法多了两个参数，同样这两个参数控制操作中心，这里用来控制旋转中心      

同样旋转也是可叠加的，叠加效果就是多次旋转参数之和      


来个例子，相信以后一看到它就能想起来这个函数       

```java
int mWidth = canvas.getWidth();
       int mHeight = canvas.getHeight();

       canvas.translate(mWidth / 2, mHeight / 2);

       mPaint.setColor(Color.BLACK);
       mPaint.setStyle(Paint.Style.STROKE);

       canvas.drawCircle(0, 0, 400, mPaint);
       canvas.drawCircle(0, 0, 360, mPaint);

       for (int i = 0; i < 360; i++) {
           canvas.drawLine(0, 360, 0, 400, mPaint);
           canvas.rotate(10);
       }
```      

效果如图：  
<div align="center">       
<img src="http://i2.muimg.com/588926/8d8dfe1508a9a7b3.png"
width="300" height="600" align=center/>      
</div>       

## 4.错切(skew)      

```java
/**
     * Preconcat the current matrix with the specified skew.
     *
     * @param sx The amount to skew in X
     * @param sy The amount to skew in Y
     */
    public void skew(float sx, float sy) {
        native_skew(mNativeCanvasWrapper, sx, sy);
    }
```      

有两个参数：
**float sx** : 将画布在x方向上倾斜相应的角度，sx为角度的tan值        
**float sy** : 将画布在y方向上倾斜相应的角度，sy为角度的tan值          

变化后view的坐标为：        
X = x + sx x y         
Y = y + sy x x            

同样效果可以叠加         
