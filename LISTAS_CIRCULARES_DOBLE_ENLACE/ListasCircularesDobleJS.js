const prompt = require("prompt-sync")();

class Node {
    constructor() {
        this.data = 0;
        this.next = null;
        this.prev = null;
    }
}

let head = null;

function beginsert() {
    let item = parseInt(prompt("Ingrese valor: "));
    let ptr = new Node();
    ptr.data = item;
    ptr.next = head;
    ptr.prev = null;

    if (head !== null)
        head.prev = ptr;

    head = ptr;
    console.log("Nodo insertado");
}

function lastinsert() {
    let ptr = new Node();
    ptr.data = parseInt(prompt("Ingrese valor: "));
    ptr.next = null;

    if (head === null) {
        ptr.prev = null;
        head = ptr;
        return;
    }

    let temp = head;
    while (temp.next !== null)
        temp = temp.next;

    temp.next = ptr;
    ptr.prev = temp;
}

function randominsert() {
    let item = parseInt(prompt("Valor: "));
    let ptr = new Node();
    ptr.data = item;

    let loc = parseInt(prompt("Ubicación: "));
    let temp = head;

    for (let i = 0; i < loc; i++) {
        temp = temp.next;
        if (!temp) {
            console.log("No se puede insertar");
            return;
        }
    }

    ptr.next = temp.next;
    ptr.prev = temp;

    if (temp.next !== null)
        temp.next.prev = ptr;

    temp.next = ptr;
}

function begdelete() {
    if (!head) {
        console.log("Lista vacía");
        return;
    }

    let ptr = head;
    head = head.next;

    if (head)
        head.prev = null;

    console.log("Nodo eliminado desde el principio");
}

function lastdelete() {
    if (!head) {
        console.log("Lista vacía");
        return;
    }
    if (!head.next) {
        head = null;
        return;
    }

    let temp = head;
    while (temp.next)
        temp = temp.next;

    temp.prev.next = null;
}

function randelete() {
    let loc = parseInt(prompt("Ubicación: "));
    let ptr = head;

    for (let i = 0; i < loc; i++) {
        ptr = ptr.next;
        if (!ptr) {
            console.log("No se puede eliminar");
            return;
        }
    }

    if (ptr.prev)
        ptr.prev.next = ptr.next;

    if (ptr.next)
        ptr.next.prev = ptr.prev;
}

function display() {
    let ptr = head;

    if (!ptr) {
        console.log("Nada que imprimir");
    } else {
        console.log("\nImprimiendo valores...");
        while (ptr) {
            console.log(ptr.data);
            ptr = ptr.next;
        }
    }
}

while (true) {
    console.log("\n1.Insertar principio\n2.Insertar final\n3.Insertar\n4.Eliminar principio\n5.Eliminar final\n6.Insertar loc\n7.Eliminar loc\n8.Mostrar\n9.Salir");
    let c = parseInt(prompt("Opción: "));

    if (c === 9) break;

    switch (c) {
        case 1: beginsert(); break;
        case 2: lastinsert(); break;
        case 3: randominsert(); break;
        case 4: begdelete(); break;
        case 5: lastdelete(); break;
        case 6: randominsert(); break;
        case 7: randelete(); break;
        case 8: display(); break;
    }
}