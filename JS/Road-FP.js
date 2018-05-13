/**
 * 函数式编程
 * 高阶函数
 * 函数的参数能够接受另一个函数作为参数
 * 这种函数就是高阶函数
 */
// 一个最简单的高阶函数
function add(x, y, f) {
    return f(x) + f(y);
}
var x = add(-5, 6, Math.abs);
console.log(x);

`map函数
内置在Array内部
现在有这样一个场景,将一个元素都为Number的array每个元素都乘方
`
//首先使用传统方式
var arr = [1, 3, 43, 32, 2, 0];
var resArr = [];
arr.forEach(function (element, index, array) {
    resArr.push(element * element);
});
resArr.forEach(function (value, index, array) {
    console.log(value);
})
//使用map高阶函数
function pow(x) {
    return x * x;
}
resArr.map(pow);
console.log(resArr);
//使用map高阶函数只需要一行就可以完成操作,核心是我们吧函数作为参数传入到了map中


`reduce函数
Array的reduce吧一个函数作用在这个Array的[x1,x2,x3...]上
这个函数必须接受两个参数,reduce吧结果继续和序列的下一个元素做累计运算
[x1,x2,x3,x4].reduce(f) = f(f(f(x1,x2),x3),x4);
`
//使用reduce对arr求和
var arr = [1, 3, 5, 7, 9];
var x = arr.reduce(function (x, y) {
    return x + y;
});
console.log(x);

//使用reduce对arr求积
function product(array) {
    return array.reduce(function (x, y) {
        return x * y;
    });
}
var y = product(arr);
console.log(y);

//将字符数组变成一个整数,例如[1,3,5,7,9]变成13579
var z = arr.reduce(function (x, y) {
    return 10 * x + y;
});
console.log(z);

//将一个字符串'13579'先变成一个Array[1,3,5,7,9],在使用reduce就可以实现一个字符串转Number的函数
var str = '13579';
function string2int(str) {
    var temp = [];
    //先将'13579'转换为['1','3','5','7','9']
    for (let i = 0; i < str.length; i++) {
        temp.push(str[i]);
    }
    //将['1','3','5','7','9']变成[1,3,5,7,9]
    temp = temp.map(function (x) {
        return x - '0';
    });
    //将[1,3,5,7,9]变成13679
    return temp.reduce(function (x, y) {
        return x * 10 + y;
    });
}
console.log(string2int(str));

// 将['adam','LISA','barT'],首字母大写,其他小写
var arr = ['adam', 'LISA', 'barT'];
function normalize(arr) {
    return arr.map(function (name) {
        return name.charAt(0).toUpperCase() + name.slice(1).toLowerCase();
    });
}
console.log(normalize(arr));



/**
 * filter
 * 将Array的某些元素过滤掉,然后返回剩下的元素
 * 和map类似,他也接受一个函数,但是不同的是,filter吧传入的函数作用于array的每一个元素
 * 然后根据函数返回的true和false值决定保留还是去除该元素
 */
//在一个Array中,删掉偶数,只保留奇数
var arr = [3, 32, 3, 234, 1, 0];
var res = arr.filter(function (element) {
    if (element % 2 === 0) {
        return false
    } else {
        return true;
    }
});
console.log(res);

`回掉函数
filter接受的回掉函数其实可以有多个参数,通常我们只使用第一个参数,
表示array的某个元素,其实他还可以接受两个另外的参数
`
var arr = ['A', 'B', 'C'];
var r = arr.filter(function (element, index, self) {
    console.log(element);
    console.log(index);
    console.log(self);
});


/**
 * 闭包
 * 将函数作为函数的返回值返回
 */
//闭包通常可以看成是一个可以延时调用的函数
function lazy_sum(arr) {
    var sum = function () {
        return arr.reduce(function (x, y) {
            return x + y;
        });
    }
    //将内部定义的sum函数返回
    return sum;
}
//当我们调用lazy_sum()时,返回的并不是求和的结果,而是求和函数
var f = lazy_sum([1, 2, 3, 4, 5]);

//调用函数f时,才是真正的计算求和结果
console.log(f());
`
这个例子中,当lazy_sum返会函数sum时,相关参数和变量都保存在了返回的函数中,这就是闭包
`



/**
 * 箭头函数
 * 相当于lambda表达式
 * () => something
 */

y => y * y;
//相当于
var z = function (x) {
    return x * x;
}
    `箭头函数就相当于是一个更加简洁的匿名函数,他有两种格式,
一种就是向上面的那样直接指向一个表达式
另一种是内部语句较为复杂,可以使用{}和return语句
`

x => {
    if (x > 0) {
        return x * x;
    } else {
        return - x * x;
    }
}

//如果参数不是一个,就需要用()将参数抱起来
(x, y) => x * x + y * y;
() => 1;

//如果要返回一个对象,如果是单表达式,就需要用()将对象{}抱起来
x => ({ foo: x });








