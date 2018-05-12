/**
 * 函数定义
 * 两种方式，一个函数也被视为一个对象
 */
// function abs(x) {
//     if (x > 0) {
//         return x;
//     } else {
//         return -x;
//     }
// }
// var abs = function (x) {
//     if (x > 0) {
//         return x;
//     } else {
//         return -x;
//     }
// };

/**
 * 调用函数
 * 传入参数时，可以传入的比定义多，也可以比定义少
 */

/**
 * arguments关键字，只在函数内部起作用，永远指向当前函数的调用者传入的所有参数
 * arguments类似于Array，但不是Array
 */
// function foo(x) {
//     console.log('x = ' + x);
//     for (var i = 0; i < arguments.length; i++) {
//         console.log('arg ' + i + '=' + arguments[i]);
//     }
// }

// foo(20, 12, 2);

/**
 * js的函数作用域
 * js的函数可以嵌套，此时，内部函数可以访问到外部函数的变量，反过来就不行
 */
// function foo() {
//     var x = 1;
//     function bar() {
//         var y = x + 1;
//     }
//     var z = x + y;//这里不能访问到内部函数的变量,会报异常
// }
// foo();

/**
 * 变量提升
 * js在扫描函数内部时，会将申明的变量先提升到顶部，但是不会提升赋值
 */
// function foo() {
//     var x = 'Hello' + y;
//     console.log(x); //y会打印出来undefined,表明不会提升赋值
//     var y = 'Bao';
// }
// foo();
// `
// 所以，在函数内部定义变量时，要严格遵守在函数内部首先申明所有变量这个原则
// `
// function fun() {
//     var
//         x = 1;
//     y = x + 1;
//     z, i;
//     //其他语句
//     // for
// }

/**
 * 全局作用域
 * 如果不在任何函数内部定义的变量就处于全局作用域中
 * 其实js默认有一个全局对象window，全局作用域中的变量都被绑定到这个window对象的一个属性中
 */
// var course = 'learn';
// alert.log(course);
// alert.log(window.course);//这两种方式相同

/**
 * 命名空间
 * 我们可以自定义一个全局空间，然后将自己的变量和函数都绑定到一个全局变量中
 */
// var myApp = {};
// myApp.name = 'myapp';
// myApp.version = 1.0;
// myApp.foo = function () {
//     return 'foo';
// };


/**
 * 局部作用域
 * 在js变量的作用域在函数内部，所以我们在for等语句块中无法定义具有局部作用域的变量
 * 就向下面这个例子一样
 */
// function foo() {
//     for (var i = 0; i < 100; i++) {
//         //
//     }
//     i += 100; //这里仍然可以使用到i
// }
// `
// 为了解决上面这个问题，引入了let关键字，可以代替var生命一个语句块级别的变量
// `
// function newfoo() {
//     for (let i = 0; i < 100; i++) {
//         //
//     }
//     i += 100;//error
// }
// newfoo();


/**
 * 常量
 * 由于var和let都是申明变量的，ES6引入了const关键字来定义常量
 * const和let一样都有块级作用域
 */
// const PI = 3.14;

/**
 * 解构赋值
 */
//同时对多个变量同时赋值
// var [x, y, z] = ['A', 'B', 'C'];
//对数组进行解构赋值时，要用[]抱起来
// let [x, [y, z]] = ['A', ['B', 'C']];
// `
// 解构赋值的使用场景
// `
// //交换两个变量的值
// var x = 1, y = 2;
// [x, y] = [y, x];
// console.log(x);
// console.log(y);
// //快速获取当前页面的域名和路径
// // var { hostname: domain, pathname: path } = location;
// //如果一个函数接受一个对象作为参数，可以使用解构直接将对象的属性绑定到变量中
// function buildDate({ year, month, day, hour = 0, minute = 0, second = 0 }) {
//     return new Date(year + '-' + month + '-' + day + ' ' + hour + ':' + minute + ':' + second);
// }
// console.log(buildDate({ year: 2018, month: 8, day: 15 }));


/**
 * 方法
 * 如果在定义一个对象中绑定了函数，这个函数就叫方法
 */
// var bao = {
//     name: 'baoqianyue',
//     height: 1.83,
//     birth: 1998,
//     getAge: function () {
//         var y = new Date().getFullYear();
//         return y - this.birth;
//     }
// };
// console.log(bao.getAge());
// console.log(bao.getAge);

// `方法中的this，当使用对像的方式调用方法时，方法中的this指向被调用的对象，
// 但是如果单独调用函数，方法中的this就指向了全局变量window`
// function getAge() {
//     var y = new Date().getFullYear();
//     return y - this.birth;
// }
// var bao = {
//     name: 'baoqianyue',
//     birth: 1998,
//     age: getAge
// };
// console.log(bao.age());//正常结果
// console.log(getAge());//返回NaN 

// `apply
// 我们可以通过使用apply方法指定函数中的this的指向
// apply方法是每一个函数自带的一个方法
// 它接受两个参数，第一个参数是要绑定的this变量，第二个参数是Array，表明函数本身的 参数
// `
// function getAge() {
//     var y = new Date().getFullYear();
//     return y - bao.birth;
// }
// var bao = {
//     name: 'baoqianyue',
//     birth: 1998,
//     age: getAge
// };
// console.log(bao.age());
// console.log(getAge.apply(bao, []));//第二个参数为空
// `与apply方法相似的还有一个call方法
// apply吧参数打包成Array再传入
// call吧参数按照顺序传入
//对于普通全局函数调用,通常把this参数传入null
// `


/**
 * 装饰器
 * 利用apply,可以动态的改变函数的行为
 * js中的所有对象都是动态的,即使是内置的函数,
 * 我们也可以使用apply和call将他们重新指向新的函数
 */

`现在有这样一个场景,我们想统计一个内置函数的调用次数`
var count = 0;
var oldParseInt = parseInt;//保存原内置函数

//改变内置函数指向
parseInt = function () {
    count += 1;
    return oldParseInt.apply(null, arguments); //调用原函数,这里的arguments是传入元函数中的
};
parseInt('10');
parseInt('23');
console.log('count = ' + count);