//Write a function that returns the sum of two values only if both are numbers; o
// otherwise return the string “Invalid input”.

function sum (a, b) {
    if (typeof a !== "number" || typeof b !== "number" || isNaN(a) || isNaN(b)) {
        return "Invalid input";
    }

    return a + b;
}

console.log(sum(9, 4));
console.log(sum(9, NaN));
console.log(sum(9, 'text'));
