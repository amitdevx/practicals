import java.io.*;
import java.util.Scanner;

public class Slip_05_Q1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter filename: ");
        String filename = sc.nextLine();
        
        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            StringBuilder content = new StringBuilder();
            String line;
            while ((line = br.readLine()) != null) {
                content.append(line).append("\n");
            }
            
            content.reverse();
            StringBuilder finalContent = new StringBuilder();
            for(int i = 0; i < content.length(); i++) {
                char c = content.charAt(i);
                if(Character.isUpperCase(c)) {
                    finalContent.append(Character.toLowerCase(c));
                } else if (Character.isLowerCase(c)) {
                    finalContent.append(Character.toUpperCase(c));
                } else {
                    finalContent.append(c);
                }
            }
            // Since we appended \n at the end of each line, reversing it puts \n at the beginning of the line.
            // A simple reverse string does this. The output may have a leading newline.
            System.out.println("Reversed and Case Changed Content:");
            System.out.println(finalContent.toString().trim());
        } catch (IOException e) {
            System.out.println("File error: " + e.getMessage());
        }
        sc.close();
    }
}
