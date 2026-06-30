/*
 Տրված է զանգված՝ const items = [100, 200, 300];։ 
 Վերագրեք առաջին տարրը first փոփոխականին, իսկ երկրորդը՝ second փոփոխականին։
*/

const items = [100, 200, 300];
const [first, second] = items;

// console.log(first);
// console.log(second);

/*
 Տրված է զանգված՝ const data = ['apple', 'banana', 'orange', 'pear'];։ 
 Օգտագործելով քայքայում (destructuring)՝ ստեղծեք fruit1 և fruit3 փոփոխականները՝ 
 բաց թողնելով երկրորդ տարրը (banana)։
*/
const data = ['apple', 'banana', 'orange', 'pear'];
const [fruit1, , fruit3] = data;

//console.log(fruit1)
//console.log(fruit3)


/*
 Տրված է զանգված՝ const numbers = [1, 2, 3, 4, 5];։ 
 Օգտագործելով քայքայում՝ վերագրեք առաջին տարրը a փոփոխականին, երկրորդը՝ 
 b փոփոխականին, իսկ մնացած բոլոր տարրերը (3, 4, 5)՝ rest զանգվածին։
*/

const numbers = [1, 2, 3, 4, 5];
const [a, b, ...rest] = numbers;

// console.log(a);
// console.log(b);
// console.log(rest);

/*
 Տրված են երկու փոփոխականներ՝ let x = 10; և let y = 20;։ 
 Փոխեք դրանց արժեքները տեղերով՝ օգտագործելով զանգվածի քայքայման [x, y] = ... շարահյուսությունը։
*/

let x = 10;
let y = 20;
[y, x] = [x, y];

// console.log(x);
// console.log(y);

/*
 Տրված է զանգված՝ let arr = [10, 20, 30, 40];։ 
 Օգտագործելով քայքայում՝ փոխեք արժեքները այնպես, որ զանգվածը դառնա [20, 10, 40, 30]։
*/
let arr = [10, 20, 30, 40];
let [k, m, ...rest2] = arr;
arr = [m, k, ...rest2.reverse()];

//console.log(arr);