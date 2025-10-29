package PROYECTO5_SUDOKUJAVA;

import java.util.*;

public class PROYECTO5_SUDOKU {

    static final int N = 9;
    static int[][] sudoku = new int[N][N];
    static Random rand = new Random();
    static Scanner sc = new Scanner(System.in);

    // Variables para el modo interactivo
    static int cursorFila = 0;
    static int cursorCol = 0;

    public static void main(String[] args) {
        // 1. Generar solución completa
        generarSudoku();
        System.out.println("Sudoku completo:");
        imprimirSudoku();

        // 2. Crear versión jugable
        int[][] puzzle = crearPuzzle(sudoku, 45);
        int[][] copiaPuzzle = copiarMatriz(puzzle); // Guardamos las pistas originales

        System.out.println("\nSudoku jugable:");
        imprimirSudoku(puzzle);

        // 3. Entrar al modo interactivo
        jugarSudoku(puzzle, copiaPuzzle);
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
                sudoku[fila][col] = num;
                if (llenarCelda(siguienteFila, siguienteCol)) return true;
                sudoku[fila][col] = 0;
            }
        }
        return false;
    }

    static boolean esValido(int fila, int col, int num) {
        for (int i = 0; i < N; i++) {
            if (sudoku[fila][i] == num || sudoku[i][col] == num)
                return false;
        }

        int startRow = fila - fila % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (sudoku[startRow + i][startCol + j] == num)
                    return false;

        return true;
    }

    // -------------------------------
    // Creación del puzzle jugable
    // -------------------------------
    static int[][] crearPuzzle(int[][] completo, int celdasAQuitar) {
        int[][] puzzle = copiarMatriz(completo);

        int eliminadas = 0;
        while (eliminadas < celdasAQuitar) {
            int fila = rand.nextInt(9);
            int col = rand.nextInt(9);

            if (puzzle[fila][col] != 0) {
                int backup = puzzle[fila][col];
                puzzle[fila][col] = 0;

                // Si tiene más de una solución, deshacer
                if (contarSoluciones(copiarMatriz(puzzle)) != 1) {
                    puzzle[fila][col] = backup;
                } else {
                    eliminadas++;
                }
            }
        }
        return puzzle;
    }

    // -------------------------------
    // Interacción en consola
    // -------------------------------
    static void jugarSudoku(int[][] puzzle, int[][] originales) {
        while (true) {
            imprimirSudokuInteractivo(puzzle, originales);

            System.out.println("\nUsa W/A/S/D para moverte, 1–9 para escribir, 0 para borrar.");
            System.out.println("Presiona C para comprobar, Q para salir.");
            System.out.print("→ ");
            String entrada = sc.nextLine().trim().toUpperCase();

            if (entrada.isEmpty()) continue;
            char tecla = entrada.charAt(0);

            if (tecla == 'Q') break;
            else if (tecla == 'C') {
                if (sudokuCompletoYCorrecto(puzzle))
                    System.out.println("\n🎉 ¡Sudoku resuelto correctamente!");
                else
                    System.out.println("\n❌ Aún hay errores o casillas vacías.");
           
            } else if (tecla == 'W' && cursorFila > 0) cursorFila--;
            else if (tecla == 'S' && cursorFila < N - 1) cursorFila++;
            else if (tecla == 'A' && cursorCol > 0) cursorCol--;
            else if (tecla == 'D' && cursorCol < N - 1) cursorCol++;
            else if (Character.isDigit(tecla)) {
                int num = tecla - '0';
                if (originales[cursorFila][cursorCol] == 0) {
                    puzzle[cursorFila][cursorCol] = num;
                } else {
                    System.out.println("⚠️ Esa celda es una pista y no se puede cambiar.");
                }
            }
        }
        System.out.println("\nJuego terminado.");
    }

    static boolean sudokuCompletoYCorrecto(int[][] grid) {
        for (int fila = 0; fila < N; fila++) {
            for (int col = 0; col < N; col++) {
                int num = grid[fila][col];
                if (num == 0) return false; // incompleto
                grid[fila][col] = 0;
                if (!esValidoEn(grid, fila, col, num)) {
                    grid[fila][col] = num;
                    return false; // hay error
                }
                grid[fila][col] = num;
            }
        }
        return true;
    }

    static void imprimirSudokuInteractivo(int[][] grid, int[][] originales) {
        System.out.println("\n=== Sudoku ===");
        for (int i = 0; i < N; i++) {
            if (i % 3 == 0 && i != 0)
                System.out.println("╠═══════════╬════════════╬═══════════╣");

            for (int j = 0; j < N; j++) {
                if (j % 3 == 0 && j != 0 || j == 0)
                    System.out.print("║");

                String valor = (grid[i][j] == 0 ? " " : Integer.toString(grid[i][j]));

                // Celda seleccionada
                if (i == cursorFila && j == cursorCol)
                    System.out.print("[" + valor + "] ");
                else if (originales[i][j] != 0)
                    System.out.print(" " + valor + "  "); // pista (fija)
                else
                    System.out.print(" " + valor + "  "); // editable
            }
            System.out.println();
        }
    }

    // -------------------------------
    // Validación y utilidades
    // -------------------------------
    static int contarSoluciones(int[][] grid) {
        return resolverYContar(grid, 0, 0, 0);
    }

    static int resolverYContar(int[][] grid, int fila, int col, int count) {
        if (fila == N) return count + 1;
        int siguienteFila = (col == N - 1) ? fila + 1 : fila;
        int siguienteCol = (col + 1) % N;

        if (grid[fila][col] != 0)
            return resolverYContar(grid, siguienteFila, siguienteCol, count);

        for (int num = 1; num <= 9; num++) {
            if (esValidoEn(grid, fila, col, num)) {
                grid[fila][col] = num;
                count = resolverYContar(grid, siguienteFila, siguienteCol, count);
                if (count > 1) return count;
                grid[fila][col] = 0;
            }
        }
        return count;
    }

    static boolean esValidoEn(int[][] grid, int fila, int col, int num) {
        for (int i = 0; i < N; i++)
            if (grid[fila][i] == num || grid[i][col] == num)
                return false;

        int startRow = fila - fila % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[startRow + i][startCol + j] == num)
                    return false;

        return true;
    }

    static int[][] copiarMatriz(int[][] original) {
        int[][] copia = new int[N][N];
        for (int i = 0; i < N; i++)
            copia[i] = Arrays.copyOf(original[i], N);
        return copia;
    }

    static void imprimirSudoku() {
        imprimirSudoku(sudoku);
    }

    static void imprimirSudoku(int[][] grid) {
        for (int i = 0; i < N; i++) {
            if (i % 3 == 0 && i != 0)
                System.out.println("------+-------+------");
            for (int j = 0; j < N; j++) {
                if (j % 3 == 0 && j != 0)
                    System.out.print("| ");
                System.out.print((grid[i][j] == 0 ? "." : grid[i][j]) + " ");
            }
            System.out.println();
        }
    }

}
