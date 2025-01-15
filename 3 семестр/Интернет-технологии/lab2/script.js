const number = 42;               
const str = "Hello, world!";  
const boolean = true;             
const null_const = null;                
let undefined_const;                    
const object_const = { key: "value" }; 

MainFunction = function() {
    let local = "local variable isn't available";
    const localConstant = "local const variable isn't available";
    OtherFunction();
}

function OtherFunction() {
        const output = document.getElementById("output");
        if (typeof number !== undefined)
            output.innerHTML += 'Переменная number, определенная в документе - Доступна<br>';
         if (typeof str !== undefined)
            output.innerHTML += 'Переменная str, определенная в документе - Доступна<br>';
         if (typeof boolean !== undefined)
            output.innerHTML += 'Переменная boolean, определенная в документе - Доступна<br>';
         if (typeof undefined_const !== undefined)
            output.innerHTML += 'Переменная undefined_const, определенная в документе - Доступна<br>';
          if (typeof object_const !== undefined)
            output.innerHTML += 'Переменная object_const, определенная в документе - Доступна<br>';
        if (typeof local !== undefined)
            output.innerHTML += `Переменная local is, ${typeof local}!<br>`;
        if (typeof localConstant !== undefined)
            output.innerHTML += `Переменная local is, ${typeof localConstant}!<br>`;
    }

MainFunction();
let a = 5;
let b = "10";

document.getElementById("output").innerHTML += `<p>5 (number) + "10" (string) = ${a + b}</p>`;  //510
document.getElementById("output").innerHTML += `<p>+"10" = ${+b}</p>`;  // 10 str to num
document.getElementById("output").innerHTML += `<p>++a = ${++a}, a = ${a}</p>`;  //увеличение на 1 = 6
document.getElementById("output").innerHTML += `<p>a++ = ${a++}, a = ${a}</p>`;  //7

alert("Hey man!");

if (confirm("Do you want to choice your name?")) {
    let newValue = prompt("Input your name:");
    if (newValue !== null) { 
        a = String(newValue); 
        document.getElementById("output").innerHTML += `<p>User name: ${a}</p>`;
    }
}


const langArray = ["Java", "Kotlin", "C++", "Scala", "Python"];
document.getElementById("output").innerHTML += `<p>Массив языков программирования:</p>`;

for (let i = 0; i < langArray.length; i++) {
    document.getElementById("output").innerHTML += `<p>${langArray[i]}</p>`;
}

let choice = 4; 
switch (choice) {
    case 1:
        document.getElementById("output").innerHTML += `<p>Your choice option 1 - Java</p>`;
        break;
    case 2:
        document.getElementById("output").innerHTML += `<p>Your choice option 2 - Kotlin</p>`;
        break;
    case 3:
        document.getElementById("output").innerHTML += `<p>Your choice option 3 - C++</p>`;
        break;
    case 4:
        document.getElementById("output").innerHTML += `<p>Your choice option 4 - Scala</p>`;
        break;
    case 5:
        document.getElementById("output").innerHTML += `<p>Your choice option 5 - Python</p>`;
        break;
    default:
        document.getElementById("output").innerHTML += `<p>Invalid choice</p>`;
        break;
}

const greetUser = function (name) {
    return `Привет, ${name}!`;
};
console.log(greetUser("Алексей"));
