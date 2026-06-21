// Write a function that takes a string as an argument and returns the number of characters in the string.
function returnLength (str) {
	if (typeof str != "string") return "Error";
	return str.length;
}
/////////////////////////////////////////////////

// Create a function that converts a given string to uppercase.
function makeUppercase (str) {
	if (typeof str != "string") return "Error";

	var new_str = "";

	for (var i = 0; i < str.length; ++i) {
		new_str += String.fromCharCode(str[i].charCodeAt(0) ^ 32);
	}

	return new_str;
}
/////////////////////////////////////////////////

// Write a function that accepts two numbers and returns their sum.
function sum (a, b) {
	if (typeof a != "number" || typeof b != "number" || isNaN(a) || isNaN(b)) return "Error";
	return a + b;
}
/////////////////////////////////////////////////


// Reverse the string "hello" without using a built-in function.
function customReverse (str) {
	if (typeof str != "string") return "Error";

	var reversed = "";

	for (var i = str.length - 1; i >= 0; --i) {
		reversed += str[i];
	}

	return reversed;
}
/////////////////////////////////////////////////

// Check if the string "Learning JavaScript" contains the substring "Java".
function isContain (str, substr) {
	if (typeof str != "string" || typeof substr != "string") return "Error";
	return str.includes(substr);
}
/////////////////////////////////////////////////

// Find the index of the value 9 in the array let numList = [3, 6, 9, 12];
function findIndex (val, array) {
	if (!Array.isArray(array) || typeof val != "number") return "Error";

	for (var i = 0; i < array.length; ++i) {
		if (array[i] == val) return i;
	}

	return "Not found";
}
/////////////////////////////////////////////////

// Compute the sum of all elements in the array let expenses = [50, 75, 100];.
function compute (expenses) {
	if (!Array.isArray(expenses)) return "Error";

	var sum = 0;

	for (var i = 0; i < expenses.length; ++i) {
		sum += expenses[i];
	}

	return sum;
}
/////////////////////////////////////////////////

// Create a function that accepts a number and returns whether it is even or odd.
function is_odd (n) {
	if (typeof n != "number") return "Error";
	return !!(n % 2);
}
/////////////////////////////////////////////////

// Write a function that returns the exact type of a given value and correctly handles null, arrays, objects, and functions (typeof alone is not sufficient).
function exactType (param) {
	if (param == null) return "null";
	if (Array.isArray(param)) return "array";
	return typeof param;
}
/////////////////////////////////////////////////

// Write a function that returns true if a given value is falsy and false otherwise; test it with 0, "", null, undefined, NaN, and false.
function is_falsy (param) {
	return !param;
}
/////////////////////////////////////////////////

// Write a function that returns true only if a value is a number, not NaN, finite, and a safe integer.
function is_num (param) {
	return typeof param == "number" && !isNaN(param) && param != Infinity && param != -Infinity && param <= Number.MAX_SAFE_INTEGER;
}
/////////////////////////////////////////////////

//Write a function that attempts to convert a value to a number and returns null if the result is NaN.
function convert_to_number (param) {
	return isNaN(+param) ? null : +param;
}
/////////////////////////////////////////////////

// Write a function that explicitly converts any value to a boolean without using if statements.
function to_bool (param) {
	return Boolean(param);
}
/////////////////////////////////////////////////

// Write a function that returns true only for plain objects and false for arrays, null, and functions.
function is_plain_object (param) {
	if (param == null || param instanceof Array || param instanceof Function) return false;
	return (param instanceof Object);
}
/////////////////////////////////////////////////

// Write a function that returns true if a value is a primitive type and false otherwise.
function is_primitive (param) {
	return !(param instanceof Object) && param != null;
}
/////////////////////////////////////////////////


// Task: Write a function that returns true if a number is prime, otherwise false.
function isPrime (n) {
	if (typeof n != "number") return "Invalid input";
	if (n <= 1) return false;
	if (n == 2) return true;

	for (var i = n - 1; i > 1; --i) {
		if (!(n % i)) return false;
	}

	return true;
}
/////////////////////////////////////////////////

// Task: Return true if a string reads the same forward and backward.
function isPalindrome (str) {
	if (typeof str != "string") return "Invalid input";
	
	var start = 0;

	for (var i = str.length - 1; i >= 0; --i) {
		if (str[i] != str[start]) return false;
		++start;
	}

	return true;
}
/////////////////////////////////////////////////


// Task: Return the factorial of a non-negative integer n.
function factorial (n) {
	if (typeof n != "number" || isNaN(n) || n == Infinity || n == -Infinity || n < 0) return "Error";
	
	if (n == 1 || n == 2 || !n) return n;

	return n * factorial(n - 1);
}
/////////////////////////////////////////////////

// Task: Return the maximum number in a non-empty array.
function maxInArray(arr) {
	if (!Array.isArray(arr)) return "Invalid value";
	if (!arr.length) return "empty array";

	var max = arr[0];
	
	for (var i = 0; i < arr.length; ++i) {
		if (typeof arr[i] != "number") return "invalid array";

		if (arr[i] > max) {
			max = arr[i];
		}
	}

	return max;
}
/////////////////////////////////////////////////

// Task: Return the sum of all digits of a number (negative numbers included).
function sumDigits (n) {
	if (typeof n != "number" || isNaN(n) || n == Infinity || n == -Infinity) return "error";

	if (n == 0) return n;

	if (n < 0) {
		n = n - n - n;
	}

	return (n % 10) + sumDigits(parseInt(n / 10));
}
/////////////////////////////////////////////////

// Task: Reverse the digits of a number while preserving the sign.
function reverseNumber (n) {
	if (typeof n != "number" || isNaN(n) || n == Infinity || n == -Infinity) return "error";

	var numToStr = n + "";

	var result = "";

	for (var i = numToStr.length - 1; i >= 0; --i) {
		if (numToStr[i] == '0' || numToStr[i] == '-') continue;
		result += numToStr[i];
	}

	if (n < 0) {
		result = +result;
		result = result - result - result;
	}

	return +result;
}
/////////////////////////////////////////////////

// Task: Count the vowels (a, e, i, o, u) in a string. Case-insensitive.
function countVowels(str) {
	if (typeof str != "string") return "error";

	var count = 0;

	for (var i = 0; i < str.length; ++i) {
		var char = str[i].toLowerCase();

		if (char == "a" || char == "e" || char == "i" || char == "o" || char == "u") {
			++count;
		}
	}

	return count;
}
/////////////////////////////////////////////////


// Return the n-th Fibonacci number using an iterative approach.
// in my case index starts from 1
function fib (n) {
	if (typeof n != "number" || n <= 0) return "invalid input";
	if (n == 1) return 0;

	var prev = 0;
	var next = 1;

	for (var i = 1; i < n; ++i) {
		var tmp = next;
		next = prev + next;
		prev = tmp;
	}

	return next;
}
/////////////////////////////////////////////////

// Task: Compare two numbers using a tolerance (epsilon).
function almostEqual (a, b) {
	if (typeof a != "number" || typeof b != "number") return "invalid input";
	return (a - b) < Number.EPSILON;
}
/////////////////////////////////////////////////

// Task: Convert a value to a number. Return null if the result is NaN.
function toNumberOrNull (value) {
	value = +value;
	return isNaN(value) ? null : value;
}
/////////////////////////////////////////////////

// Task: Return the exact type of a value
function exactType (value) {
	if (value == null) return "null";
	if (value == undefined) return "undefined";
	if (value instanceof Array) return "array";

	return typeof value;
}
/////////////////////////////////////////////////

// Task: Explicitly convert a value to a boolean without using if statements.

function toBoolean (value) {
	return Boolean(value);
}
/////////////////////////////////////////////////

// Task: Return true if a value is a primitive type (including null).
function isPrimitive (value) {
	if ((typeof value == "object" && value != null) || typeof value === "function") return false;
	return true;
}
/////////////////////////////////////////////////

// Task: Return true only if the value is an array.
function isArray (value) {
	return value instanceof Array;
}
/////////////////////////////////////////////////