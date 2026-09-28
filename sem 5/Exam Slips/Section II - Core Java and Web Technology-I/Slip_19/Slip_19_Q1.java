import java.io.*;
import java.util.Scanner;

public class Slip_19_Q1 {
    public static void main(String[] args) {
        String filename = "sample.txt";
        // Create demo file
        try (FileWriter fw = new FileWriter(filename)) {
            fw.write("Java practical examination.\nSem V computer science.\nWeb technology practicals.");
        } catch (IOException e) {
            System.out.println("Error initializing file.");
        }

        int charCount = 0, wordCount = 0, lineCount = 0;

        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = br.readLine()) != null) {
                lineCount++;
                charCount += line.length();
                String[] words = line.trim().split("\\s+");
                if (words.length > 0 && !words[0].isEmpty()) {
                    wordCount += words.length;
                }
            }
            System.out.println("File: " + filename);
            System.out.println("Total Characters: " + charCount);
            System.out.println("Total Words:      " + wordCount);
            System.out.println("Total Lines:      " + lineCount);
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }
}
