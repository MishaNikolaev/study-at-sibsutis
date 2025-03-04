function QuickSortV2(array, L, R) {
    if (L < R) {
        let i = L, j = R;
        let pivot = array[Math.floor((L + R) / 2)];

        while (i <= j) {
            while (compare(array[i], pivot) < 0) {
                i++;
            }
            while (compare(array[j], pivot) > 0) {
                j--;
            }

            if (i <= j) {
                [array[i], array[j]] = [array[j], array[i]];
                i++;
                j--;
            }
        }

        if (L < j) {
            QuickSortV2(array, L, j);
        }
        if (i < R) {
            QuickSortV2(array, i, R);
        }
    }
}

function compare(a, b) {
    if (typeof a !== 'object' || typeof b !== 'object' || !a.name || !a.age || !b.name || !b.age) {
        throw new Error("Elements should be objects");
    }

    if (a.age < b.age) return -1;   
    if (a.age > b.age) return 1;
    if (a.name < b.name) return -1; 
    if (a.name > b.name) return 1;

    return 0;
}

function orderBy(array) {
    if (!array.every(item => typeof item === 'object' && item !== null)) {
        throw new Error('Element aint object');
    }

    if (!array.every(item => 'name' in item && 'age' in item)) {
        throw new Error('in object should be name and age');
    }

    const sortedArray = [...array];
    QuickSortV2(sortedArray, 0, sortedArray.length - 1);
    return sortedArray;
}


const data = [
     { name: 'Anton', age: 23 },
    { name: 'Misha', age: 19 },
    { name: 'Katya', age: 19 },
    { name: 'Kat', age: 100 },
    { name: 'Dima', age: 20 },
    { name: 'Dima', age: 19 }
];

console.log(orderBy(data)); 

module.exports = orderBy;
