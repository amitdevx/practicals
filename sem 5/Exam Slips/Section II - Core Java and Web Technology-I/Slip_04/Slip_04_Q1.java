import java.util.Scanner;

public class Slip_04_Q1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int rows = 2, cols = 2;
        int[][] a = {{1, 2}, {3, 4}};
        int[][] b = {{5, 6}, {7, 8}};
        int choice;

        System.out.println("Matrix A:");
        printMatrix(a);
        System.out.println("Matrix B:");
        printMatrix(b);

        do {
            System.out.println("\n1. Add Matrices\n2. Multiply Matrices\n3. Transpose of Matrix A\n4. Exit");
            System.out.print("Enter choice: ");
            choice = sc.hasNextInt() ? sc.nextInt() : 4;

            switch (choice) {
                case 1:
                    int[][] sum = new int[rows][cols];
                    for (int i = 0; i < rows; i++)
                        for (int j = 0; j < cols; j++)
                            sum[i][j] = a[i][j] + b[i][j];
                    System.out.println("Sum:");
                    printMatrix(sum);
                    break;
                case 2:
                    int[][] prod = new int[rows][cols];
                    for (int i = 0; i < rows; i++)
                        for (int j = 0; j < cols; j++)
                            for (int k = 0; k < cols; k++)
                                prod[i][j] += a[i][k] * b[k][j];
                    System.out.println("Product:");
                    printMatrix(prod);
                    break;
                case 3:
                    int[][] trans = new int[cols][rows];
                    for (int i = 0; i < rows; i++)
                        for (int j = 0; j < cols; j++)
                            trans[j][i] = a[i][j];
                    System.out.println("Transpose of A:");
                    printMatrix(trans);
                    break;
                case 4:
                    System.out.println("Exiting.");
                    break;
            }
        } while (choice != 4);
        sc.close();
    }

    static void printMatrix(int[][] m) {
        for (int[] row : m) {
            for (int val : row) System.out.print(val + " ");
            System.out.println();
        }
    }
}
