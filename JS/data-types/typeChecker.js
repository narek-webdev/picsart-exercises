//Write a function that returns true if a given value is falsy and false otherwise; 
// test it with 0, “”, null, undefined, NaN, and false.

function checkFalsy (n) {
    return !n;
}

console.log(checkFalsy(0));
console.log(checkFalsy(""));
console.log(checkFalsy(null));
console.log(checkFalsy(undefined));
console.log(checkFalsy(NaN));
console.log(checkFalsy(false));
