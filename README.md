# Интерпретируемый язык программирования Scripty


# Особенности и возможности
- Язык имеет динамическую типизацию
- TODO: придумать что нибудь еще :)

# Сборка и использование
Для выполнения скрипта необходимо передать путь к файлу в параметрах интерпретатора:
```bash
Scripty.exe -f /path/to/your/script.vsc
```
# Синтаксис

__for__ ( `<initialization>`; `<condition>`; `<increment>`) `<block>`

__while__ `<condition>` `<block>`

__do__ (`<block>`) __while__ `<condition>`

__if__ (`<condition>`) `<block>`

__if__ (`<condition>`) `<block>` __else__ `<block>`

__return__ [`<expression>`]

__break__

__continue__

__var__ `<name>` [= `<expression>`]{, `<name>` [= `<expression>`]}

__function__ `<name>` (`<parameters>`) `<block>`
# Типы данных
`Array`
```js
var array = [1, 2.5, "hello", {a: 3, b: 42}];
```
`Object`
```js
var object = {
    str: "string",
    number: 42,
    bool: true
};
```
`String`
```js
var string1 = "Hello, World";
var string2 = 'Hello, World';
```
`Number`
```js
var number = 3.1415;
```
`Boolean`
```js
var bool = true;
```
`Functions`
```js
function isOdd(number) {
    return number % 2;
}
```
# Комментарии
```python
# Однострочный комментарий
```
```cpp
/*
Многострочный
комментарий
*/
```

# Операторы
```python
+, -, *, /, %, //, +=, -=, *=, /=, %=, //=, ==, >=, <=, <, >, &&, ||, !
```

