# View的Layout过程      

Layout的作用是ViewGroup用来确定子元素的位置，当ViewGroup的位置被确定了后，它在onLayout中会遍历所有的子元素并调用其layout方法，在layout方法中onLayout方法又会被调用。     
layout方法确定View本身的位置，而onLayout方法则会确定所有子元素的位置.    

