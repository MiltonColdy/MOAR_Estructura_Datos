package T2_ABSTRACTOS;
// Se define la clase abstracta "Alumno".
class Alumno {
    //Estas son sus propiedades.
        String ap1; String ap2;
        String nom1; String nom2;
        Byte ed;
    //Aquí ordenamos sus propiedades
        public Alumno(String ap1, String ap2, String nom1, String nom2, Byte ed) 
        {
            //Definimos la variable que le corresponderá a cada propiedad
            this.ap1 = ap1;
            this.ap2 = ap2;
            this.nom1 = nom1;
            this.nom2 = nom2;
            this.ed = ed;
        }
    
        public void Datos2N() //Función para imprimir en caso de tener 2 nombres
    {
        {
        System.out.println("Nombre completo del alumno: " + ap1 + " " + ap2 + " " + nom1 + " " + nom2);
        System.out.println("Edad del alumno: " + ed);
        }
    }
  
      public void Datos1N() //Función para imprimir en caso de tener 1 solo nombre
    {
        {
        System.out.println("Nombre completo del alumno: " + ap1 + " " + ap2 + " " + nom1);
        System.out.println("Edad del alumno: " + ed);
        }
    }
}
/* Cabe aclarar que en este caso, no importa realmente si son 2 nombres o 1, pues no se notará la
   diferencia dentro de la terminal. Esto podría notarse en un programa más elaborado, así que
   prefiero dejar la validación.
*/ 


public class T2_ArrAbstracto_JAVA 
{
     public static void main(String[] args)
    {
       Alumno[] alumnos = 
       {
        new Alumno("Alcaraz","Pérez","Flérida","Romina",(byte)19),
        new Alumno("Apodaca","Romero","Milton","Omar",(byte)19),
        new Alumno("López","Medina","Ximena","",(byte)19),
        new Alumno("Rodríguez","Quiros","Jesús","Alfredo",(byte)19)
       };

       for (byte i = 0; i < alumnos.length; i++) {
        if (alumnos[i].nom2.equals(""))
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
