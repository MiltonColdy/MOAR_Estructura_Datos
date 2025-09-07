class Persona:
    def __init__(self,ap1,ap2,nom1,nom2,edad):
        self.nom1 = nom1
        self.nom2 = nom2
        self.ap1 = ap1
        self.ap2 = ap2
        self.edad = edad

Alumnos =[
        Persona("Apodaca","Romero","Milton","Omar",19),
        Persona("Alcaraz", "Pérez", "Flérida","Romina",19),
        Persona("López","Medina","Ximena","",19),
        Persona("Rodríguez", "Quiros", "Jesús","Alfredo",19)
    ]

for alumno in Alumnos:
    print("Nombre completo del alumno:",alumno.ap1,alumno.ap2,alumno.nom1,alumno.nom2)
    print("Edad del alumno:",alumno.edad)