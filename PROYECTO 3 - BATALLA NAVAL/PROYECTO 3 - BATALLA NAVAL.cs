using System;
using System.ComponentModel.Design;
using System.Runtime.CompilerServices;
using System.Threading;

class PROYECTO3_BatallaNaval
{
    public static void ConsoleClear()
    {
        Console.Write("\u001b[2J\u001b[H"); // Esto me permite limpiar la terminal de Visual Studio Code.
    }
    // Método auxiliar para leer enteros válidos
    static int LeerEntero(string mensaje, int min, int max)
    {
        while (true) //Es un while infinito hasta que se cumpla lo del return valor, que lo interrumpe y regresa un valor.
        {
            Console.Write(mensaje);
            if (int.TryParse(Console.ReadLine(), out int valor) && valor >= min && valor <= max)
            /* En este caso, el TryParse es un método que intenta convertir un string a un int,
               si llega a haber un error en el proceso, devuelve un true o un false.*/
            {
                return valor;
            }
            else
            {
                Console.WriteLine($"Entrada inválida. Ingresa un número entre {min} y {max}.");
            /* El símbolo $ permite interpolar las variables sin necesidad de concatenar diréctamente
               las llaves vendrían siendo como la concatenación dentro de esta línea.*/
            }
        }
    }
    static void MostrarTablero(string[,] tablero)
    {
        for (int i = 0; i < 10; i++)
        {
            if (i < 9) Console.Write(" ");
            Console.Write(i + 1 + " ");
            for (int j = 0; j < 10; j++)
                Console.Write("[" + tablero[i, j] + "]");
            Console.WriteLine();
        }
    }
    static void ColocarBarco(string[,] tablero, int barcoNumero, int len)
    {
        int ori = LeerEntero("¿Vertical(0) u horizontal(1)? ", 0, 1);
        int col = LeerEntero("Ingrese la posición en X (1-10): ", 1, 10) - 1;
        int fil = LeerEntero("Ingrese la posición en Y (1-10): ", 1, 10) - 1;

        bool colocado = false;
        while (!colocado)
        {
            bool fits = (ori == 0) ? (fil <= 10 - len) : (col <= 10 - len);
            if (!fits)
            {
                Console.WriteLine("El barco no cabe en esa posición/orientación. Intente otra.");
                ori = LeerEntero("¿Vertical(0) u horizontal(1)? ", 0, 1);
                col = LeerEntero("Ingrese la posición en X (1-10): ", 1, 10) - 1;
                fil = LeerEntero("Ingrese la posición en Y (1-10): ", 1, 10) - 1;
                continue;
            }
            bool ocupado = false;
            for (int i = 0; i < len; i++)
            {
                if ((ori == 0 && tablero[fil + i, col] != " ") ||
                    (ori == 1 && tablero[fil, col + i] != " "))
                {
                    ocupado = true;
                    break;
                }
            }
            if (ocupado)
            {
                Console.WriteLine("La posición ya está ocupada por otro barco. Intente otra.");
                ori = LeerEntero("¿Vertical(0) u horizontal(1)? ", 0, 1);
                col = LeerEntero("Ingrese la posición en X (1-10): ", 1, 10) - 1;
                fil = LeerEntero("Ingrese la posición en Y (1-10): ", 1, 10) - 1;
                continue;
            }
            // Identificador del barco ("A", "B", ...)
            string barcoID = ((char)('A' + barcoNumero - 1)).ToString();
            /* Esta línea de código parece rara en un principio. pero no es nada más que representar A como un carácter
            dentro del código ASCII, esto me permite avanzar a los carácteres dentro del abecedario sin necesidad
            de hacer una cadena de comparaciones como un case o muchos ifs, al menos en este caso*/
            for (int i = 0; i < len; i++)
            {
                if (ori == 0)
                    tablero[fil + i, col] = barcoID;
                else
                    tablero[fil, col + i] = barcoID;
            }
            colocado = true;
        }
    }
    static bool Bombardear(string[,] tableroB, string[,] tablero)
    {
        int col = LeerEntero("Ingrese la posición a bombardear en X (1-10): ", 1, 10) - 1;
        int fil = LeerEntero("Ingrese la posición a bombardear en Y (1-10): ", 1, 10) - 1;
        while (tableroB[fil, col] != " ")
        {
            Console.WriteLine("La posición ya fue bombardeada con anterioridad. Intente otra.");
            col = LeerEntero("Ingrese la posición en X (1-10): ", 1, 10) - 1;
            fil = LeerEntero("Ingrese la posición en Y (1-10): ", 1, 10) - 1;
        }

        if (tablero[fil, col] != " ")
        {
            
        }
        if (tablero[fil, col] != " ")
        {
            tableroB[fil, col] = "X";
            tablero[fil, col] = " ";
            return true;
        }
        else
        {
            tableroB[fil, col] = "O";
            return false;
        }
    }
    static bool ConfirmarElim(string[,] tablero)
    {
        int cont = 0;
        int[] Cant = new int[5];
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                switch (tablero[i, j])
                {
                    case "A":
                        Cant[0] += 1;
                        break;
                    case "B":
                        Cant[1] += 1;
                        break;
                    case "C":
                        Cant[2] += 1;
                        break;
                    case "D":
                        Cant[3] += 1;
                        break;
                    case "E":
                        Cant[4] += 1;
                        break;
                }
            }
        }
        if (Cant[0] == 0)
        {
            Console.WriteLine("El barco destructor ha caído D:");
        }
        if (Cant[1] == 0)
        {
            Console.WriteLine("El submarino ha caído D:");
        }
        if (Cant[2] == 0)
        {
            Console.WriteLine("El crucero ha caído D:");
        }
        if (Cant[3] == 0)
        {
            Console.WriteLine("El barco acorazado ha caído D:");
        }
        if (Cant[4] == 0)
        {
            Console.WriteLine("El barco portaaviones ha caído D:");
        }
        for (int i = 0; i < 5; i++)
        {
            if (Cant[i] != 0)
            {
                cont += 1;
            }
        }
        if (cont == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    static void Main(string[] args)
    {
        int c = 1, b1 = 2, b2 = 2;
        string[,] arr1 = new string[10, 10];
        string[,] arr2 = new string[10, 10];
        string[,] arrJ1 = new string[10, 10];
        string[,] arrJ2 = new string[10, 10];
        // En C#, es así como se declaran los arreglos con todo y dimensión.

        // Inicializar tableros
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
            {
                arr1[i, j] = " ";
                arr2[i, j] = " ";
                arrJ1[i, j] = " ";
                arrJ2[i, j] = " ";
            }
        while (c <= 10)
        {
            ConsoleClear();
            if (c <= 5) // Jugador 1
            {
                if (b1 == 4 && c == 3) b1 = 3;
                Console.WriteLine("COLOCAR BARCO DE " + b1 + " DIMENSIONES | JUGADOR 1");
                MostrarTablero(arr1);
                ColocarBarco(arr1, c, b1);
                b1++;
            }
            else // Jugador 2
            {
                if (b2 == 4 && c == 8) b2 = 3;
                Console.WriteLine("COLOCAR BARCO DE " + b2 + " DIMENSIONES | JUGADOR 2");
                MostrarTablero(arr2);
                ColocarBarco(arr2, c - 5, b2); // Ajustar número de barco para el jugador 2.
                b2++;
            }
            c++;
        }
        Console.WriteLine("COMIENZA EL JUEGO!");
        Thread.Sleep(3000); // Pausa de 3000ms (3 segundos)
        ConsoleClear();
        c = 1;
        bool ganar = false;
        while (!ganar)
        {
            ConsoleClear();
            if (c % 2 != 0)
            {
                Console.WriteLine("TURNO DEL JUGADOR 1");
                Console.WriteLine("¡Ingrese una casilla a la cual BOMBARDEAR! :D");
                MostrarTablero(arrJ1);
                bool gol = Bombardear(arrJ1, arr2);
                ConsoleClear();
                if (gol)
                {
                    Console.WriteLine("¡Golpeaste un barco!");
                    c = 1;
                }
                else
                {
                    Console.WriteLine("Agua...");
                    c = 2;
                }
                MostrarTablero(arrJ1);
                ganar = ConfirmarElim(arr2);
                Thread.Sleep(2000);
            }
            else
            {
                Console.WriteLine("TURNO DEL JUGADOR 2");
                Console.WriteLine("¡Ingrese una casilla a la cual BOMBARDEAR! :D");
                MostrarTablero(arrJ2);
                bool gol = Bombardear(arrJ2, arr1);
                ConsoleClear();
                if (gol)
                {
                    Console.WriteLine("¡Golpeaste un barco!");
                    c = 2;
                }
                else
                {
                    Console.WriteLine("Agua...");
                    c = 1;
                }
                MostrarTablero(arrJ2);
                ganar = ConfirmarElim(arr1);
                Thread.Sleep(2000);
            }

        }

        Console.WriteLine("¡El jugador " + c + " ha ganado!");
    }
}
