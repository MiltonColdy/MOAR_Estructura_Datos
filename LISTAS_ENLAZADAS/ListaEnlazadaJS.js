class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
    }
}

let head = null;
const prompt = require("prompt-sync")();

function beginsert() {
    let item = parseInt(prompt("Ingrese valor: "));
    let ptr = new Node(item);
    ptr.next = head;
    head = ptr;
    console.log("Nodo insertado");
}

function lastinsert() {
    let item = parseInt(prompt("Ingrese valor: "));
    let ptr = new Node(item);

    if (head === null) {
        head = ptr;
        return;
    }
    let temp = head;
    while (temp.next !== null) temp = temp.next;
    temp.next = ptr;
}

function randominsert() {
    let item = parseInt(prompt("Ingrese valor: "));
    let loc = parseInt(prompt("Ubicación: "));

    let ptr = new Node(item);
    let temp = head;

    for (let i = 0; i < loc; i++) {
        temp = temp.next;
        if (temp === null) {
            console.log("No se puede insertar");
            return;
        }
    }
    ptr.next = temp.next;
    temp.next = ptr;
}

function begdelete() {
    if (!head) {
        console.log("Lista vacía");
        return;
    }
    head = head.next;
}

function lastdelete() {
    if (!head) {
        console.log("Lista vacía");
        return;
    } else if (!head.next) {
        head = null;
        return;
    }
    let ptr = head, ptr1 = null;
    while (ptr.next) {
        ptr1 = ptr;
        ptr = ptr.next;
    }
    ptr1.next = null;
}

function randelete() {
    let loc = parseInt(prompt("Ubicación: "));
    let ptr = head, ptr1 = null;

    for (let i = 0; i < loc; i++) {
        ptr1 = ptr;
        ptr = ptr.next;
        if (!ptr) {
            console.log("No se puede eliminar");
            return;
        }
    }
    ptr1.next = ptr.next;
}

function search() {
    let item = parseInt(prompt("Buscar: "));
    let ptr = head;
    let pos = 1;
    let found = false;

    while (ptr) {
        if (ptr.data === item) {
            console.log("Encontrado en " + pos);
            found = true;
        }
        ptr = ptr.next;
        pos++;
    }
    if (!found) console.log("No encontrado");
}

function display() {
    let ptr = head;
    if (!ptr) {
        console.log("Nada que imprimir");
        return;
    }
    while (ptr) {
        console.log(ptr.data);
        ptr = ptr.next;
    }
}