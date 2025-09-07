using System;
using System.ComponentModel.DataAnnotations;
using System.Net;

class T2_ArrAbstracto_CS
{
    static void Main(string[] args)
    {
        Alumno[] alumnos =
        {
        new Alumno("Alcaraz","Pérez","Flérida","Romina",(byte)19),
        new Alumno("Apodaca","Romero","Milton","Omar",(byte)19),
        new Alumno("López","Medina","Ximena",nom2:"",(byte)19),
        new Alumno("Rodríguez","Quiros","Jesús","Alfredo",(byte)19)
        };
    
        for (int i = 0; i < alumnos.Length; i++)
        {
            if (alumnos[i].Nom2.Equals("")) //Se hace uso del Nom2 (versión pública de solo lectura)
            {
                alumnos[i].Datos1N();
            }
            else
            {
                alumnos[i].Datos2N();
            }
        }
    }
}

class Alumno
{
    string ap1; string ap2;
    string nom1; string nom2;
    byte ed;

    public Alumno(string ap1, string ap2, string nom1, string nom2, byte ed)
    {
        this.ap1 = ap1;
        this.ap2 = ap2;
        this.nom1 = nom1;
        this.nom2 = nom2;
        this.ed = ed;
    }
    
    public void Datos2N()
    {
        Console.WriteLine("Nombre completo de alumn@: " + ap1 + " " + ap2 + " " + nom1 + " " + nom2);
        Console.WriteLine("Edad de alumn@: " + ed);
    }
    public string Nom2 => nom2; //Esto se encarga de convertir la propiedad privada nom2 a una pública de solo lectura.
    public void Datos1N()
    {
        Console.WriteLine("Nombre completo de alumn@: " + ap1 + " " + ap2 + " " + nom1);
        Console.WriteLine("Edad de alumn@: " + ed);
    }
}