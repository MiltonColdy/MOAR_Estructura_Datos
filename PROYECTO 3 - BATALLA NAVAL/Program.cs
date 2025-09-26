class PROYECTO3_BatallaNaval
{
    // Revisión 26/09/2025 a las 2:44 p.m.
    static void Main(string[] args)
    {
        int c = 1, col = 0, fil = 0, b1 = 2, b2 = 2, ori = 0;
        string[,] arr1 = new string[10, 10];
        string[,] arr2 = new string[10, 10];
        bool ganar = false;

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                arr1[i, j] = " ";
                arr2[i, j] = " ";
            }
        }

        while (c < 11)
        {

            Console.Clear();
            if (c <= 5 && c >= 1) // Jugador 1
            {
                if (b1 == 4 && c == 3)
                {
                    b1 = 3;
                }
                Console.WriteLine("COLOCAR BARCO DE " + b1 + " DIMENSIONES | JUGADOR 1");
                for (int i = 0; i < 10; i++)
                {
                    if (i < 9)
                    {
                        Console.Write(" ");
                    }
                    Console.Write(i + 1 + " ");
                    for (int j = 0; j < 10; j++)
                    {
                        Console.Write("[" + arr1[i, j] + "]");
                    }
                    Console.WriteLine("");
                }

                ori = LeerEntero("¿Vertical(0) u horizontal(1)? ", 0, 1);
                col = LeerEntero("Ingrese la posición en X (1-10): ", 1, 10) - 1;
                fil = LeerEntero("Ingrese la posición en Y (1-10): ", 1, 10) - 1;

                bool colocado = false;
                while (!colocado)
                {
                    int len = b1;
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
                        if (ori == 0)
                        {
                            if (arr1[fil + i, col] == "*")
                            {
                                ocupado = true;
                                break;
                            }
                        }
                        else
                        {
                            if (arr1[fil, col + i] == "*")
                            {
                                ocupado = true;
                                break;
                            }
                        }
                    }

                    if (ocupado)
                    {
                        Console.WriteLine("La posición ya está ocupada por otro barco. Elija otra.");
                        ori = LeerEntero("¿Vertical(0) u horizontal(1)? ", 0, 1);
                        col = LeerEntero("Ingrese la posición en X (1-10): ", 1, 10) - 1;
                        fil = LeerEntero("Ingrese la posición en Y (1-10): ", 1, 10) - 1;
                        continue;
                    }

                    for (int i = 0; i < len; i++)
                    {
                        if (ori == 0)
                            arr1[fil + i, col] = "*";
                        else
                            arr1[fil, col + i] = "*";
                    }

                    colocado = true;
                }

                b1 += 1;
                
                    
            }
            else // Jugador 2
            {
                if (b2 == 4 && c == 8)
                {
                    b2 = 3;
                }
                Console.WriteLine("COLOCAR BARCO DE " + b2 + " DIMENSIONES | JUGADOR 2");
                for (int i = 0; i < 10; i++)
                {
                    if (i < 9)
                    {
                        Console.Write(" ");
                    }
                    Console.Write(i + 1 + " ");
                    for (int j = 0; j < 10; j++)
                    {
                        Console.Write("[" + arr2[i, j] + "]");
                    }
                    Console.WriteLine("");
                }

                ori = LeerEntero("¿Vertical(0) u horizontal(1)? ", 0, 1);
                col = LeerEntero("Ingrese la posición en X (1-10): ", 1, 10) - 1;
                fil = LeerEntero("Ingrese la posición en Y (1-10): ", 1, 10) - 1;

                bool colocado = false;
                while (!colocado)
                {
                    int len = b2;
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
                        if (ori == 0)
                        {
                            if (arr2[fil + i, col] == "*")
                            {
                                ocupado = true;
                                break;
                            }
                        }
                        else
                        {
                            if (arr2[fil, col + i] == "*")
                            {
                                ocupado = true;
                                break;
                            }
                        }
                    }

                    if (ocupado)
                    {
                        Console.WriteLine("La posición ya está ocupada por otro barco. Elija otra.");
                        ori = LeerEntero("¿Vertical(0) u horizontal(1)? ", 0, 1);
                        col = LeerEntero("Ingrese la posición en X (1-10): ", 1, 10) - 1;
                        fil = LeerEntero("Ingrese la posición en Y (1-10): ", 1, 10) - 1;
                        continue;
                    }

                    for (int i = 0; i < len; i++)
                    {
                        if (ori == 0)
                            arr2[fil + i, col] = "*";
                        else
                            arr2[fil, col + i] = "*";
                    }

                    colocado = true;
                }

                b2 += 1;
                
                    
            }

            c += 1;
        }

        while (ganar == false)
        {
            Console.WriteLine("TABLERO DEL JUGADOR 1: ");
            for (int i = 0; i < 10; i++)
            {
                if (i < 9)
                {
                    Console.Write(" ");
                }
                Console.Write(i + 1 + " ");
                for (int j = 0; j < 10; j++)
                {
                    Console.Write("[" + arr1[i, j] + "]");
                }
                Console.WriteLine("");
            }
            Console.WriteLine("TABLERO DEL JUGADOR 2: ");
            for (int i = 0; i < 10; i++)
            {
                if (i < 9)
                {
                    Console.Write(" ");
                }
                Console.Write(i + 1 + " ");
                for (int j = 0; j < 10; j++)
                {
                    Console.Write("[" + arr2[i, j] + "]");
                }
                Console.WriteLine("");
            }
            ganar = true;
        }
    }

    // Método auxiliar para validar entrada
    static int LeerEntero(string mensaje, int min, int max)
    {
        int valor;
        while (true)
        {
            Console.Write(mensaje);
            if (int.TryParse(Console.ReadLine(), out valor) && valor >= min && valor <= max)
            {
                return valor;
            }
            Console.WriteLine($"Entrada inválida. Ingresa un número entre {min} y {max}.");
        }
    }
}
