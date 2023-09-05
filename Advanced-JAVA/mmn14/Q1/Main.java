/**
 * Demonstrates the use of SortedGroup and Student classes with add, remove, and reduce operations.
 */

import java.util.Iterator;

public class Main {
    public static void main(String[] args) {
    	
        // Create a SortedGroup of Student objects
        SortedGroup<Student> studentGroup = new SortedGroup<>();

        // Create Student objects
        Student student1 = new Student("Bar", "1232323245", 95);
        Student student2 = new Student("Arik", "67843242390", 75);
        Student student3 = new Student("Amit", "54232321", 65);
        Student student4 = new Student("Eli", "098423476", 85);
        Student student5 = new Student("Or", "123230293", 90);
        Student student6 = new Student("Mor", "123230293", 50);

        // Add the students to the group and print the details
        System.out.println("Adding Students:");
        studentGroup.add(student1);
        System.out.println(student1 + " has been added.");
        studentGroup.add(student2);
        System.out.println(student2 + " has been added.");
        studentGroup.add(student3);
        System.out.println(student3 + " has been added.");
        studentGroup.add(student4);
        System.out.println(student4 + " has been added.");
        studentGroup.add(student5);
        System.out.println(student5 + " has been added.");
        studentGroup.add(student6);
        System.out.println(student6 + " has been added.");
       

        // Print the initial group
        printGroup("Initial group", studentGroup);

        // Remove a student from the group and print the details
        studentGroup.remove(student2);
        System.out.println("\n" + student2.getName() + " has been removed.");
        printGroup("After removal", studentGroup);

        // Use the reduce method to create a new group with students having score > 60
        Student minScore = new Student("", "", 60);
        SortedGroup<Student> reducedGroup = SortedGroupRed.reduce(studentGroup, minScore);
        printGroup("Group with students having score > 60", reducedGroup);
    }

    private static void printGroup(String text, SortedGroup<Student> group) {
        System.out.println("\n" + text + ":");
        Iterator<Student> iterator = group.iterator();
        while (iterator.hasNext()) {
            System.out.println(iterator.next().toString());
        }
    }
}
