import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        BigInt number1 = null, number2 = null;

        System.out.println("Enter the first unlimited number:");
        while (number1 == null) {
            try {
                number1 = new BigInt(scanner.nextLine());
            } catch (IllegalArgumentException e) {
                System.out.println("Invalid input. Please enter a valid number:");
            }
        }

        System.out.println("Enter the second unlimited number:");
        while (number2 == null) {
            try {
                number2 = new BigInt(scanner.nextLine());
            } catch (IllegalArgumentException e) {
                System.out.println("Invalid input. Please enter a valid number:");
            }
        }

        System.out.println("Results:");
        System.out.println("Number 1: " + number1);
        System.out.println("Number 2: " + number2);

        BigInt sum = number1.plus(number2);
        System.out.println("Sum: " + sum);

        BigInt difference = number1.minus(number2);
        System.out.println("Difference: " + difference);

        BigInt product = number1.multiply(number2);
        System.out.println("Product: " + product);

        try {
            BigInt quotient = number1.divide(number2);
            System.out.println("Quotient: " + quotient);
        } catch (ArithmeticException e) {
            System.out.println("Division by zero is not allowed");
        }

        scanner.close();
    }
}