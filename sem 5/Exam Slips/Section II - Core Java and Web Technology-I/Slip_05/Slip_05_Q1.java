import java.io.*;
import java.util.Scanner;

public class Slip_05_Q1 {
    public static void main(String[] args) {
        String filename = "sample.txt";
        // Create demo file if not exists
        try (FileWriter fw = new FileWriter(filename)) {
            fw.write("Hello World from Java File Handling");
        } catch (IOException e) {
            System.out.println("Error writing sample file.");
        }

        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            StringBuilder content = new StringBuilder();
            String line;
            while ((line = br.readLine()) != null) {
                content.append(line).append("\n");
            }
            System.out.println("Original File Content:\n" + content);
            System.out.println("Reversed Content:\n" + content.reverse());
        } catch (IOException e) {
            System.out.println("File error: " + e.getMessage());
        }
    }
}
