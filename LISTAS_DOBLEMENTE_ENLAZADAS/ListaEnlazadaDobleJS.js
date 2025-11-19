class Node {
    constructor() {
        this.data = 0;
        this.next = null;
        this.prev = null;
    }
}

let head = null;

function beginsert() {
    let ptr = new Node();
    let item = parseInt(prompt("Ingrese valor: "));
    ptr.data = item;

    ptr.next = head;
    ptr.prev = null;

    if (head !== null) {
        head.prev = ptr;
    }
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
    while (temp.next !== null) temp = temp.next;

    temp.next = ptr;
    ptr.prev = temp;
}

function randominsert() {
    let item = parseInt(prompt("Valor: "));
    let loc = parseInt(prompt("Ubicación: "));

    let ptr = new Node();
    ptr.data = item;

    let temp = head;
    for (let i = 0; i < loc; i++) {
        temp = temp.next;
        if (temp === null) {
            console.log("No se puede insertar");
            return;
        }
    }

    ptr.next = temp.next;
    ptr.prev = temp;

    if (temp.next !== null) temp.next.prev = ptr;

    temp.next = ptr;
}

function begdelete() {
    if (!head) {
        console.log("Lista vacía");
        return;
    }

    let ptr = head;
    head = head.next;

    if (head) head.prev = null;

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
    while (temp.next !== null) temp = temp.next;

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

    if (ptr.prev) ptr.prev.next = ptr.next;
    if (ptr.next) ptr.next.prev = ptr.prev;

    console.log("Nodo eliminado");
}

function search() {
    let item = parseInt(prompt("Elemento a buscar: "));
    let ptr = head;
    let i = 0;
    let flag = 1;

    while (ptr !== null) {
        if (ptr.data === item) {
            console.log("Elemento encontrado en la ubicación " + (i + 1));
            flag = 0;
        }
        i++;
        ptr = ptr.next;
    }

    if (flag === 1) console.log("Elemento no encontrado");
}

function display() {
    let ptr = head;
    if (ptr === null) {
        console.log("Nada que imprimir");
        return;
    }

    console.log("Imprimiendo valores...");
    while (ptr !== null) {
        console.log(ptr.data);
        ptr = ptr.next;
    }
}