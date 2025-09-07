package T2_ABSTRACTOS;
abstract class Alumno {
        private final String nom1; private final String nom2;
        private final String ap1; private final String ap2;
        private final Byte ed;

        public Alumno(String nom1, String nom2, String ap1, String ap2, Byte ed) 
        {
            this.nom1 = nom1;
            this.nom2 = nom2;
            this.ap1 = ap1;
            this.ap2 = ap2;
            this.ed = ed;
        }
        public abstract void Datos2N();
        public abstract void Datos1N();
        public String obtNom1() {return nom1;}
        public String obtNom2() {return nom2;}
        public String obtAp1() {return ap1;}
        public String obtAp2() {return ap2;}
        public Byte obtEd() {return ed;}
    
    }

class Estudiante extends Alumno 
{
    public Estudiante(String nom1, String nom2, String ap1, String ap2, Byte ed) 
    {
        super(nom1,nom2,ap1,ap2,ed);
    }

    @Override
     public void Datos2N() 
    {
        {
        System.out.println("Nombre completo del alumno: " + obtNom1() + " " + obtNom2() + " " + obtAp1() + " " + obtAp2());
        System.out.println("Edad del alumno: " + obtEd());
        }
    }
    @Override
      public void Datos1N() 
    {
        {
        System.out.println("Nombre completo del alumno: " + obtNom1() + " " + obtAp1() + " " + obtAp2());
        System.out.println("Edad del alumno: " + obtEd());
        }
    }
}

public class T2_ArrAbstracto_JAVA 
{
     public static void main(String[] args)
    {
       Alumno[] alumnos = 
       {
        new Estudiante("Milton","Omar","Apodaca","Romero",(byte)19),
        new Estudiante("Flérida","Romina","Alcaraz","Pérez",(byte)19),
        new Estudiante("Ximena","","López","Medina",(byte)19),
        new Estudiante("Jesús","Alfredo","Rodríguez","Quiros",(byte)19),
       };

       for (byte i = 0; i < 4; i++) {
        if (alumnos[i].obtNom2().equals(""))
        {
            alumnos[i].Datos1N();
        } else
        {
            alumnos[i].Datos2N();
        }
           
       }
    }
}
