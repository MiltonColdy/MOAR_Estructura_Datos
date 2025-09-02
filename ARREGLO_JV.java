public class ARREGLO_JV {

    public static void main(String[] args) 
    {
        byte[] arr = {6,7,8,9,10};
        System.out.println("El arreglo contiene los números: ");
        for(byte i = 0; i < 5; i++) 
        {
            if (i <= 3) 
            {
                System.out.print(arr[i]+" ");
            } else
            {
                System.out.println("y "+arr[i]);
            }
            
        }
        System.out.println("El tercer elemento del arreglo es: "+arr[2]);
    }
}
