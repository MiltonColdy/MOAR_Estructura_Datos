class Alumno {
    constructor(ap1, ap2, nom1, nom2, ed) 
    {
        this.ap1 = ap1;
        this.ap2 = ap2;
        this.nom1 = nom1;
        this.nom2 = nom2;
        this.ed = ed;
    }
}

const alumnos = [
        new Alumno("Alcaraz","Pérez","Flérida","Romina",19),
        new Alumno("Apodaca","Romero","Milton","Omar",19),
        new Alumno("López","Medina","Ximena","",19),
        new Alumno("Rodríguez","Quiros","Jesús","Alfredo",19)];

        for(i = 0; i < alumnos.length; i++) 
        {
            console.log("Nombre completo de alumn@: " + alumnos[i].ap1 + " " + alumnos[i].ap2 + " " + alumnos[i].nom1 + " " + alumnos[i].nom2);
            console.log("Edad de alumn@: " + alumnos[i].ed);
        }
        
