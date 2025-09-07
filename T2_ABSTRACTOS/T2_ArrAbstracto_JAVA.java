package T2_ABSTRACTOS;
class Alumno {
        String ap1; String ap2;
        String nom1; String nom2;
        Byte ed;

        public Alumno(String ap1, String ap2, String nom1, String nom2, Byte ed) 
        {
            this.ap1 = ap1;
            this.ap2 = ap2;
            this.nom1 = nom1;
            this.nom2 = nom2;
            this.ed = ed;
        }
    
        public void Datos2N() 
    {
        {
        System.out.println("Nombre completo del alumno: " + ap1 + " " + ap2 + " " + nom1 + " " + nom2);
        System.out.println("Edad del alumno: " + ed);
        }
    }
  
      public void Datos1N() 
    {
        {
        System.out.println("Nombre completo del alumno: " + ap1 + " " + ap2 + " " + nom1);
        System.out.println("Edad del alumno: " + ed);
        }
    }
}

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

       for (byte i = 0; i < 4; i++) {
        if (alumnos[i].nom2.equals(""))
        {
            alumnos[i].Datos1N();
        } else
        {
            alumnos[i].Datos2N();
        }
       }
    }
}
