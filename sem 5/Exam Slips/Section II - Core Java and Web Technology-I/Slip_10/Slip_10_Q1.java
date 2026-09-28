import java.io.*;

public class Slip_10_Q1 {
    public static void main(String[] args) {
        String filename = "abc.txt";
        // Create demo file
        try (FileWriter fw = new FileWriter(filename)) {
            fw.write("Core Java and Web Technology practical examination 2026-2027.");
        } catch (IOException e) {
            System.out.println("File write error.");
        }

        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            System.out.println("Contents of 'abc.txt' in UPPERCASE:");
            while ((line = br.readLine()) != null) {
                System.out.println(line.toUpperCase());
            }
        } catch (IOException e) {
            System.out.println("File read error: " + e.getMessage());
        }
    }
}
