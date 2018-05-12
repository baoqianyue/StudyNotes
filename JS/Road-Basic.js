//console.log('helloworld');

//创建对象，是有一组键值对组成的无序集合
// var person = {
//     name: "baoqianyue",
//     age: 20,
//     tags: ['js', 'web', 'moblie'],
//     city: "taiyuan",
//     hasCar: false,
//     zipcode: null
// }

/*
    字符串模板
*/

// var name = '小明';
// var age = 20;
// var message = '你好，${name},今年${age}岁了';
// alert(message);



/*
    字符串函数
*/
// var s = "Hello,world";
// s[0]; //使用索引获取字符，如果索引越界不会报错，但是会返回undefined
// s.toUpperCase(); //将字符串大写，但是不会更改原来的字符串，而是返回一个新的字符串
// s.indexOf('world');//返回字符串出现的位置,没有找到返回-1
// s.substring(0,5);//截取字符串，含头不含尾


/*
    Array数组
*/

// 获取Array的长度，直接访问属性
// 如果给Array的length赋值会修改Array的长度
// var arr = [1,3,2,'Hello',null,true];
// console.log(arr.length);
// arr.length = 10;//长度发生改变
// console.log(arr.length); 
//也可以通过对索引赋值来将对应的元素修改，而且如果对索引赋值的时候超过了范围，也会变长array的长度
// arr[10] = 0;//Array长度发生变换
// console.log(arr.length);
//js中如果数组访问越界不会有任何报错，所以不建议直接修改Array的大小，以索引访问时要保证不越界

//indexOf,与String类似，Array也可以通过indexOf来获取一个元素的位置
// var arr = [20,32,'bao',1,true];
// console.log(arr.indexOf(32));


//slice，对应String的subString,截取Array的部分元素，然后返回一个新的Array
// var arr = ['a', 'b', 'c', 'd', 'e', 'f', 'g'];
// var arr1 = arr.slice(0, 3);//含头不含尾
// for (var x of arr1) {
//     console.log(x);
// }
// var arr2 = arr.slice(3);//从索引3开始到结束
// for (var x of arr2) {
//     console.log(x);
// }
// //如果不给slice传任何参数，它就会从头到尾截取所有元素，所以可以使用这种方式来复制一个Array
// var arr3 = arr.slice();
// for (var x of arr3) {
//     console.log(x);
// }


//push和pop，push()向Array的尾部添加元素，pop()吧Array的最后一个元素删除掉
//unshift和shift，unshift()向Array的头部添加元素，shift()函数将第一个元素删掉
// var arr = [1, 23];
// arr.push(30);
// arr.push(2, 100);
// arr.pop();
// arr.unshift(233, 0);
// arr.shift();
// for (var x of arr) {
//     console.log(x);
// }


//sort排序，直接使用array调用，它会直接修改当前Array的元素位置，直接调用时，按照默认顺序排序
//可以通过函数的方式自定义排序规则
// var arr = ['A','c','B'];
// arr.sort();
// for (var x of arr) {
//     console.log(x);
// }


//Array的万能方法splice，可以从指定的索引开始删除若干元素，然后再从该位置添加若干元素
// var arr = ['Microsoft', 'Apple', 'Yahoo', 'AOL', 'Excite', 'Oracle'];
// //从索引2开始删除3个元素，然后再添加2个元素
// //返回被删除的元素构成的Array
// var deleteArr = arr.splice(2, 3, 'Google', 'Facebook');
// for (var x of arr) {
//     console.log(x);
// }
// for (var x of deleteArr) {
//     console.log('deleted atom: ' + x);
// }
// //只删除，不添加，就只写前两个参数即可
// arr.splice(1, 2);
// for (var x of arr) {
//     console.log(x);
// }


//concat()将两个Array连接起来并返回一个新的Array
// var arr = ['A', 'B', 'C'];
// var arrAdd = arr.concat([1, 2, 3]);
// arrAdd.forEach(function (element, index, array) {
//     console.log(element);
// });
// //其实concat方法并没有直接修改Array，而是返回了一个新的Array
// //concat方法可以接受任意个元素和array，并且自动把array拆开，然后全部添加到新的array中
// var newArrAdd = arrAdd.concat(100);
// newArrAdd.forEach(function (element, index, array) {
//     console.log("the element is: " + element);
//     console.log('the index is: ' + index);
// });


//join方法，他可以将当前Array的每个元素都用指定的字符串连接起来，然后返回连接后的字符串
//如果Array的元素不全是字符串，将自动转换为字符串后链接
// var arr = ['A', 'B', 1, 2, 34, 0];
// var x = arr.join("-");
// console.log(x);

// var arr = ['小红','小明','大军','阿黄'];
// arr.sort();
// var end = arr[3];
// var newArr = arr.slice(0,3);
// var str = newArr.join(',');
// console.log("欢迎"+str+"和"+end+"同学!");


/**
 * 对象，是一种无序的集合数据类型，由若干key-value组成
 * 在对象定义内部，键值对用逗号隔开
 */
// var baoqianyue = {
//     name: 'baoqianyue',
//     sex: true,
//     birth: 1998,
//     height: 1.80,
//     score: null
// }
//将对象赋值给变量后，就可以通过变量名来访问到其中的属性了
// console.log('姓名为:' + baoqianyue.name);
//访问对象中的属性是通过.来访问的，这就需要我们保证对象定义中需要有有效的变量名
//如果属性名中含有特殊字符，就必须用''抱起来
var baoqianyue = {
    name: 'baoqianyue',
    'middle-school': 'No.1 Middle School'
};
//而且这个含有特殊字符的属性在被访问时，也不能用.来访问了，需要使用[]
// console.log(baoqianyue.name);
// console.log(baoqianyue['middle-school']);
// console.log(baoqianyue['name']);
//因为js中对象是动态类型，所以可以自由的给一个对象添加或者删除属性
// baoqianyue.age = 20;//添加一个属性
// console.log(baoqianyue.age);
// delete baoqianyue.age;//删除一个属性
// console.log(baoqianyue.age);
// delete baoqianyue['name'];
// console.log(baoqianyue.name);
// delete baoqianyue.sex;//删除一个不存在的属性也不会报错

//如果我们要检测一个对象中是否含有一个属性，使用in操作符
// console.log('name' in baoqianyue);
// console.log('age' in baoqianyue);
// //不过需要注意的是，使用in来判断一个对象的属性是否存在，这个属性有可能不是当前对象的
// //有肯能是从父类那里继承过来的
// //比如'toString'
// console.log('toString' in baoqianyue);//toString定义在Object对象中
// //要判断一个属性是否是当前类对象自身所带有的，而不是继承到的可以使用hasOwnProperty方法
// console.log(baoqianyue.hasOwnProperty('age'))
// console.log(baoqianyue.hasOwnProperty('toString'));

/**
 * Map，键值对数据结构，和对象不同的是key可以是任意类型
 * 初始化时需要一个二维数组，或者直接初始化一个空Map，然后使用自带的一些函数进行数据的增删
 */
// var m = new Map([['baoqianyue', 100], ['barack', 100], ['bao', 80]]);
// // console.log(m.get('baoqianyue'));

// var map = new Map();
// map.set('bao', 100); //添加新的key-value
// map.set('barack', 100);
// console.log("是否存在bao:" + map.has('bao'));//判断是否存在key 
// console.log('barack: ' + map.get('barack'));
// map.delete('bao'); //删除key
// console.log('bao: ' + map.get('bao'));

// //一个key只能对应一个value，所以，多次对一个key放入value，会将前面的值给覆盖掉
// var m1 = new Map();
// m1.set('bao',100);
// m1.set('bao',80);
// console.log('bao is ' + m1.get('bao'));


/**
 * Iterator
 * 遍历Array可以使用索引，但是Map和Set没有索引，为了统一
 * ES6引入了新的iterator类型，Array、Map、Set都属于iterator类型
 * 具有iterator类型的集合都可以使用for..of来遍历
 */
var map = new Map([['name', 'baoqianyue'], ['age', 20], ['height', 1.83]]);
for (var x of map) {
    console.log(x[0] + ':' + x[1]);
}

//for..in 和 for..of的区别
// `
// for..in遍历的实际上是对象的属性，其实前面接触的Array也是一个对象，它的每一个元素的索引都被是为一个属性
// 当我们给手动给一个array对象赋予了新的属性后，再使用for..in遍历一下
// `
// var arr = [2, 3, 2];
// arr.name = 'arr'
// for (var x in arr) {
//     console.log(x)
// }
// `
// for..of循环则只循环集合本身的元素
// `
// for (const x of arr) {
//     console.log(x);
// }

`
然而还有更好的方法，就是使用iterator内置的forEach方法
它接收一个函数，每次迭代就自动回调该函数
function(element,index,array)
element:指向当前元素的值
index：指向当前索引
array: 指向Array对象本身
`
var a = ["a", 'A', 'B', 'D'];
a.forEach(function (element, index, array) {
    console.log('元素为:' + element);
    console.log('索引为: ' + index);
});
//对于Set，没有索引，所以回掉函数的前两个参数都是元素本身
var s = new Set(['A', "b", 'C']);
s.forEach(function (element, sameElement, array) {
    console.log(element);
});
//Map回掉函数参数依次为:value,key,map本身
var m = new Map([[1, 'x'], [2, 'y'], [3, 'z']]);
m.forEach(function (value, key, map) {
    console.log(value);
});
//如果对某些参数不感兴趣，可以忽略掉