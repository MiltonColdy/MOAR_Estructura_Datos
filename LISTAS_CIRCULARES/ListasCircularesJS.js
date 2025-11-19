const readline = require("readline");

class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
    }
}

let head = null;

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function input(q) {
    return new Promise(res => rl.question(q, ans => res(ans)));
}

async function beginsert() {
    let item = parseInt(await input("Ingrese valor: "));
    let ptr = new Node(item);

    if (!head) {
        head = ptr;
        ptr.next = head;
    } else {
        let temp = head;
        while (temp.next !== head)
            temp = temp.next;

        ptr.next = head;
        head = ptr;
        temp.next = head;
    }
    console.log("Nodo insertado");
}

async function lastinsert() {
    let item = parseInt(await input("Ingrese valor: "));
    let ptr = new Node(item);

    if (!head) {
        head = ptr;
        ptr.next = head;
    } else {
        let temp = head;
        while (temp.next !== head)
            temp = temp.next;

        temp.next = ptr;
        ptr.next = head;
    }
    console.log("Nodo insertado");
}

async function randominsert() {
    let item = parseInt(await input("Valor: "));
    let loc = parseInt(await input("Ubicación: "));

    let ptr = new Node(item);
    let temp = head;

    for (let i = 0; i < loc; i++) {
        temp = temp.next;

        if (temp === head) {
            console.log("No se puede insertar");
            return;
        }
    }

    ptr.next = temp.next;
    temp.next = ptr;
    console.log("Nodo insertado");
}

async function begdelete() {
    if (!head) {
        console.log("Lista vacía");
        return;
    }

    if (head.next === head) {
        head = null;
        console.log("Nodo eliminado");
        return;
    }

    let last = head;
    while (last.next !== head)
        last = last.next;

    head = head.next;
    last.next = head;

    console.log("Nodo eliminado");
}

async function lastdelete() {
    if (!head) {
        console.log("Lista vacía");
        return;
    }

    if (head.next === head) {
        head = null;
        console.log("Nodo eliminado");
        return;
    }

    let ptr = head, prev = null;

    while (ptr.next !== head) {
        prev = ptr;
        ptr = ptr.next;
    }

    prev.next = head;
    console.log("Nodo eliminado");
}

async function randelete() {
    let loc = parseInt(await input("Ubicación: "));

    if (!head) {
        console.log("Lista vacía");
        return;
    }

    let ptr = head, prev = null;

    for (let i = 0; i < loc; i++) {
        prev = ptr;
        ptr = ptr.next;
        if (ptr === head) {
            console.log("No se puede eliminar");
            return;
        }
    }

    prev.next = ptr.next;
    console.log("Nodo eliminado");
}

async function search() {
    if (!head) {
        console.log("Lista vacía");
        return;
    }

    let item = parseInt(await input("Elemento a buscar: "));
    let ptr = head;
    let i = 0;
    let found = false;

    do {
        if (ptr.data === item) {
            console.log("Elemento encontrado en la ubicación", i + 1);
            found = true;
        }
        ptr = ptr.next;
        i++;
    } while (ptr !== head);

    if (!found)
        console.log("Elemento no encontrado");
}

async function display() {
    if (!head) {
        console.log("Nada que imprimir");
        return;
    }

    console.log("Imprimiendo valores...");
    let ptr = head;
    do {
        console.log(ptr.data);
        ptr = ptr.next;
    } while (ptr !== head);
}

async function menu() {
    while (true) {
        console.log("\n******MENÚ PRINCIPAL******");
        console.log("1. Insertar al principio\n2. Insertar al final\n3. Insertar");
        console.log("4. Eliminar del principio\n5. Eliminar del último\n6. Eliminar después de ubicación");
        console.log("7. Buscar\n8. Mostrar\n9. Salir");

        let choice = parseInt(await input("Ingrese opción: "));

        if (choice === 1) await beginsert();
        else if (choice === 2) await lastinsert();
        else if (choice === 3) await randominsert();
        else if (choice === 4) await begdelete();
        else if (choice === 5) await lastdelete();
        else if (choice === 6) await randelete();
        else if (choice === 7) await search();
        else if (choice === 8) await display();
        else if (choice === 9) { rl.close(); return; }
    }
}

menu();