import java.util.Random;
import java.util.Arrays;
import java.io.FileWriter;
import java.io.IOException;

public class Lab1 {
    private static class RandomMatrix {
        private final int size;
        private final int[][] matrix;

        public RandomMatrix(int size) {
            this.size = size;
            this.matrix = new int[size][size];
        }

        public void fillMatrix() {
            Random random = new Random();
            for (int i = 0; i < this.size; i++)
                for (int j = 0; j < this.size; j++)
                    this.matrix[i][j] = random.nextInt(1000);
        }
    }

    public static RandomMatrix horizontalMultiply(RandomMatrix A, RandomMatrix B) {
        int n = A.size;
        RandomMatrix C = new RandomMatrix(n);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    C.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
        return C;
    }

    public static RandomMatrix verticalMultiply(RandomMatrix A, RandomMatrix B) {
        int n = A.size;
        RandomMatrix C = new RandomMatrix(n);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    C.matrix[j][i] += A.matrix[j][k] * B.matrix[k][i];
        return C;
    }

    private static boolean areEqual(RandomMatrix A, RandomMatrix B) {
        if (A.size != B.size) return false;
        for (int i = 0; i < A.size; i++)
            if (!Arrays.equals(A.matrix[i], B.matrix[i]))
                return false;
        return true;
    }

    private static class MatrixMultiplierThread extends Thread {
        private final RandomMatrix A;
        private final RandomMatrix B;
        private final RandomMatrix C;
        private final int rowStart, rowEnd;
        private final int colStart, colEnd;

        public MatrixMultiplierThread(RandomMatrix A, RandomMatrix B, RandomMatrix C,
                                      int rowStart, int rowEnd, int colStart, int colEnd) {
            this.A = A;
            this.B = B;
            this.C = C;
            this.rowStart = rowStart;
            this.rowEnd = rowEnd;
            this.colStart = colStart;
            this.colEnd = colEnd;
        }

        public void run() {
            int n = A.size;
            for (int i = rowStart; i < rowEnd; i++)
                for (int j = colStart; j < colEnd; j++)
                    for (int k = 0; k < n; k++)
                        C.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
        }
    }

    public static RandomMatrix parallelMultiply(RandomMatrix A, RandomMatrix B, int numThreads) {
        int n = A.size;
        RandomMatrix C = new RandomMatrix(n);
        Thread[] threads = new Thread[numThreads];

        int rowsPerThread = n / numThreads;
        int extraRows = n % numThreads;

        int currentRow = 0;
        for (int t = 0; t < numThreads; t++) {
            int rowEnd = currentRow + rowsPerThread + (t < extraRows ? 1 : 0);
            threads[t] = new MatrixMultiplierThread(A, B, C, currentRow, rowEnd, 0, n);
            threads[t].start();
            currentRow = rowEnd;
        }

        try {
            for (Thread thread : threads) {
                thread.join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return C;
    }

    public static void main(String[] args) {
        RandomMatrix A = new RandomMatrix(2222);
        RandomMatrix B = new RandomMatrix(2222);
        A.fillMatrix();
        B.fillMatrix();

        try (FileWriter writer1 = new FileWriter("./lab1/answer1.txt");
             FileWriter writer2 = new FileWriter("./lab1/answer2.txt")) {

            long start = System.currentTimeMillis();
            RandomMatrix CVertical = verticalMultiply(A, B);
            long end = System.currentTimeMillis();
            String verticalTime = "Вертикальное умножение: " + (end - start) + " мс\n";
            writer1.write(verticalTime);

            start = System.currentTimeMillis();
            RandomMatrix CHorizontal = horizontalMultiply(A, B);
            end = System.currentTimeMillis();
            String horizontalTime = "Горизонтальное умножение: " + (end - start) + " мс\n";
            writer1.write(horizontalTime);

            String equalityCheck = "Равны ли матрицы: " + areEqual(CHorizontal, CVertical) + "\n";
            writer1.write(equalityCheck);

            for (int numThreads = 2; numThreads <= 100; numThreads += 2) {
                start = System.currentTimeMillis();
                RandomMatrix CParallel = parallelMultiply(A, B, numThreads);
                end = System.currentTimeMillis();
                long time = end - start;

                String result = numThreads + "-" + time + "\n";
                writer2.write(result);

                boolean isEqual = areEqual(CHorizontal, CParallel);
            }


        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}