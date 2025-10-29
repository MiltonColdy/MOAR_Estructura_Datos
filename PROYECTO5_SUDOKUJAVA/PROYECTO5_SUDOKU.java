package PROYECTO5_SUDOKUJAVA;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;
public class PROYECTO5_SUDOKU {
    static int nivel = 0;
    static int diff = 0;
    static int vaciar = 0;
    static int vidas = 3;
    static boolean salir = false;
    static String usuario;
    static boolean ganar = false;
    static final int N = 9;
    static int[][][] sudoku = new int[25][N][N];
    static Random rand = new Random();
    static Scanner sc = new Scanner(System.in);
    static int tiempo = 0; // ahora solo un int simple
    static int cursorFila = 0;
    static int cursorCol = 0;
    static long inicioGeneral = System.currentTimeMillis();

    public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.println("Ingrese su usuario: ");
    usuario = scanner.nextLine();
    inicioGeneral = System.currentTimeMillis();
    while (vidas > 0 && !ganar && !salir) {
        // Determinar dificultad y celdas a vaciar
        if (nivel >= 0 && nivel <= 4) {
            vaciar = 81 - 36;
            diff = 0;
        } else if (nivel >= 5 && nivel <= 9) {
            vaciar = 81 - 32;
            diff = 1;
        } else if (nivel >= 10 && nivel <= 14) {
            vaciar = 81 - 28;
            diff = 2;
        } else if (nivel >= 15 && nivel <= 19) {
            vaciar = 81 - 24;
            diff = 3;
        } else if (nivel >= 20 && nivel <= 24) {
            vaciar = 81 - 17;
            diff = 4;
        }
        
        // Genera sudoku completo para este nivel
        for (int i = 0; i < N; i++)
            Arrays.fill(sudoku[nivel][i], 0);
        generarSudoku();

        // Crear puzzle y copia
        int[][][] puzzle = crearPuzzle(sudoku, vaciar);
        int[][][] copiaPuzzle = copiarMatriz(puzzle);

        // Jugar
        jugarSudoku(puzzle, copiaPuzzle);

        // Si lo ganó, pasamos al siguiente nivel
        if (ganar) {
            nivel++;
            if (nivel >= 25) {
                System.out.println("¡Felicidades, completaste todos los niveles!");
                guardarRecord(usuario, nivel, tiempo);
                mostrarRecords();
                break;
            }
            ganar = false; // reseteamos bandera
        }
    }
}

    // -------------------------------
    // Generación del sudoku completo
    // -------------------------------
    static boolean generarSudoku() {
        return llenarCelda(0, 0);
    }

    static boolean llenarCelda(int fila, int col) {
        if (fila == N) return true;

        int siguienteFila = (col == N - 1) ? fila + 1 : fila;
        int siguienteCol = (col + 1) % N;

        List<Integer> numeros = new ArrayList<>();
        for (int i = 1; i <= 9; i++) numeros.add(i);
        Collections.shuffle(numeros);

        for (int num : numeros) {
            if (esValido(fila, col, num)) {
                sudoku[nivel][fila][col] = num;
                if (llenarCelda(siguienteFila, siguienteCol)) return true;
                sudoku[nivel][fila][col] = 0;
            }
        }
        return false;
    }

    static boolean esValido(int fila, int col, int num) {
        for (int i = 0; i < N; i++)
            if (sudoku[nivel][fila][i] == num || sudoku[nivel][i][col] == num)
                return false;

        int startRow = fila - fila % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (sudoku[nivel][startRow + i][startCol + j] == num)
                    return false;

        return true;
    }

    // -------------------------------
    // Creación del puzzle jugable
    // -------------------------------
    static int[][][] crearPuzzle(int[][][] completo, int celdasAQuitar) {
        
        int[][][] puzzle = copiarMatriz(completo);

        int eliminadas = 0;
        int intentos = 0; // evita bucles infinitos
        while (eliminadas < celdasAQuitar && intentos < 500) {
            int fila = rand.nextInt(N);
            int col = rand.nextInt(N);
            intentos++;

            if (puzzle[nivel][fila][col] != 0) {
                int backup = puzzle[nivel][fila][col];
                puzzle[nivel][fila][col] = 0;

                if (contarSoluciones(copiarMatriz(puzzle)) == 1) {
                    eliminadas++;
                } else {
                    puzzle[nivel][fila][col] = backup;
                }
            }
        }
        System.out.println("Celdas eliminadas: " + eliminadas);
        return puzzle;
    }

    // -------------------------------
    // Interacción en consola
    // -------------------------------
    static void jugarSudoku(int[][][] puzzle, int[][][] originales) {
        
        while (true) {
            // Calculamos tiempo transcurrido en segundos
            tiempo = (int) ((System.currentTimeMillis() - inicioGeneral) / 1000);

            // Mostrar sudoku
            imprimirSudokuInteractivo(puzzle, originales);
            System.out.println("Tiempo: " + tiempo + "s");

            System.out.println("\nUsa W/A/S/D para moverte, 1-9 para escribir, 0 para borrar.");
            System.out.println("Presiona C para comprobar, Q para salir.");
            System.out.print("→ ");
            String entrada = sc.nextLine().trim().toUpperCase();

            if (entrada.isEmpty()) continue;
            char tecla = entrada.charAt(0);
            
            //SALIR
            if (tecla == 'Q') {
                salir = true;
                break;
            }
            //VALIDAR
            if (tecla == 'C') {
                if (sudokuCompletoYCorrecto(puzzle)) {
                System.out.println("\n¡Sudoku resuelto correctamente!");
                ganar = true;
                if (vidas < 3) {
                    vidas = 3;
                } else {
                    vidas += 1;
                }
                return; // <-- salimos para que main() cree el siguiente sudoku
            } else {
                vidas -= 1;
                System.out.println("\nAún hay errores o casillas vacías.");
            }
            }   else if (tecla == 'W' && cursorFila > 0) cursorFila--;
                else if (tecla == 'S' && cursorFila < N - 1) cursorFila++;
                else if (tecla == 'A' && cursorCol > 0) cursorCol--;
                else if (tecla == 'D' && cursorCol < N - 1) cursorCol++;
                else if (Character.isDigit(tecla)) {
                int num = tecla - '0';
            if (originales[nivel][cursorFila][cursorCol] == 0) {
                puzzle[nivel][cursorFila][cursorCol] = num;
            } else {
                System.out.println("Esa celda es una pista y no se puede cambiar.");
            }
}   
            }
            
        }
        
    

    // -------------------------------
    // Validación y utilidades
    // -------------------------------
    static boolean sudokuCompletoYCorrecto(int[][][] grid) {
        for (int fila = 0; fila < N; fila++) {
            for (int col = 0; col < N; col++) {
                int num = grid[nivel][fila][col];
                if (num == 0) return false;
                grid[nivel][fila][col] = 0;
                if (!esValidoEn(grid, fila, col, num)) {
                    grid[nivel][fila][col] = num;
                    return false;
                }
                grid[nivel][fila][col] = num;
            }
        }
        return true;
    }

    static int contarSoluciones(int[][][] grid) {
        return resolverYContar(grid, 0, 0, 0);
    }

    static int resolverYContar(int[][][] grid, int fila, int col, int count) {
        if (fila == N) return count + 1;
        int siguienteFila = (col == N - 1) ? fila + 1 : fila;
        int siguienteCol = (col + 1) % N;

        if (grid[nivel][fila][col] != 0)
            return resolverYContar(grid, siguienteFila, siguienteCol, count);

        for (int num = 1; num <= 9; num++) {
            if (esValidoEn(grid, fila, col, num)) {
                grid[nivel][fila][col] = num;
                count = resolverYContar(grid, siguienteFila, siguienteCol, count);
                if (count > 1) return count;
                grid[nivel][fila][col] = 0;
            }
        }
        return count;
    }

    static boolean esValidoEn(int[][][] grid, int fila, int col, int num) {
        for (int i = 0; i < N; i++)
            if (grid[nivel][fila][i] == num || grid[nivel][i][col] == num)
                return false;

        int startRow = fila - fila % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[nivel][startRow + i][startCol + j] == num)
                    return false;

        return true;
    }

    static void imprimirSudokuInteractivo(int[][][] grid, int[][][] originales) {
        System.out.println("\n         === Sudoku ===");
        switch (diff) {
            case 0:
            System.out.println("\nDificultad: MUY FÁCIL");
            break;
            case 1:
            System.out.println("\nDificultad: FÁCIL");
            break;
            case 2:
            System.out.println("\nDificultad: MEDIO");
            break;
            case 3:
            System.out.println("\nDificultad: DIFÍCIL");
            break;
            case 4:
            System.out.println("\nDificultad: MUY DIFÍCIL");
            break;
        }
        System.out.println("\nNivel: " + (nivel+1));
        System.out.println("\nVidas: " + (vidas));
        System.out.println("╔═════════╦═════════╦═════════╗");
        for (int i = 0; i < N; i++) {
            if (i % 3 == 0 && i != 0)
                System.out.println("╠═════════╬═════════╬═════════╣");

            for (int j = 0; j < N; j++) {
                if (j % 3 == 0 || j == 0)
                    System.out.print("║");

                String valor = (grid[nivel][i][j] == 0 ? " " : Integer.toString(grid[nivel][i][j]));

                if (i == cursorFila && j == cursorCol)
                    System.out.print("[" + valor + "]");
                else
                    System.out.print(" " + valor + " ");
            }
            System.out.print("║\n");
        }
        System.out.println("╚═════════╩═════════╩═════════╝");
    }

    static int[][][] copiarMatriz(int[][][] original) {
        int[][][] copia = new int[25][N][N];
        for (int i = 0; i < 25; i++)
            for (int j = 0; j < N; j++)
                copia[i][j] = Arrays.copyOf(original[i][j], N);
        return copia;
    }
    static void guardarRecord(String usuario, int nivel, int tiempo) {
        try (FileWriter fw = new FileWriter("records_sudoku.txt", true)) {
            fw.write(usuario + "," + (nivel + 1) + "," + tiempo + "s\n");
        } catch (IOException e) {
            System.out.println("Error al guardar el récord: " + e.getMessage());
        }
    }

    static void mostrarRecords() {
        System.out.println("\n=== RÉCORDS ===");
        try (BufferedReader br = new BufferedReader(new FileReader("records_sudoku.txt"))) {
            String linea;
            while ((linea = br.readLine()) != null) {
                String[] datos = linea.split(",");
                if (datos.length == 3) {
                    System.out.printf("Usuario: %-10s | Nivel: %-2s | Tiempo: %s\n",
                    datos[0], datos[1], datos[2]);
                }
            }
        }   catch (IOException e) {
                System.out.println("No hay récords guardados aún.");
            }
    }
}