const orderBy = require('../orderBy');

describe('orderBy function', () => {
    test('correct sort by name and age', () => {
        const data = [
            { name: 'Anton', age: 23 },
            { name: 'Misha', age: 19 },
            { name: 'Katya', age: 19 },
            { name: 'Kat', age: 100 },
            { name: 'Dima', age: 20 },
            { name: 'Dima', age: 19 }
        ];

        const sortedData = orderBy(data);

        expect(sortedData).toEqual([
            { name: 'Dima', age: 19 },
            { name: 'Katya', age: 19 },
            { name: 'Misha', age: 19 },
            { name: 'Dima', age: 20 },
            { name: 'Anton', age: 23 },
            { name: 'Kat', age: 100 }
        ]);
    });

    test('should throw error because array contains non object', () => {
        const data = [
            { name: 'Anton', age: 23 },
            'Misha', 
            { name: 'Katya', age: 19 }
        ];

        expect(() => orderBy(data)).toThrow('Element aint object');
    });

    test('should throw error cause field age is absent', () => {
        const data = [
            { name: 'Anton', age: 23 },
            { name: 'Misha' },
            { name: 'Katya', age: 19 }
        ];

        expect(() => orderBy(data)).toThrow('in object should be name and age');
    });
});
