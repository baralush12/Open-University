/**
 * The Student class represents a student with a name, identification document, and score.
 *	The Student class implements Comparable,allowing for comparison between students based on their score.
  **/

public class Student implements Comparable<Student> {
	private String name;
    private String id;
    private int score;

    public Student(String name, String id, int score) {
        this.name = name;
        this.id = id;
        this.score = score;
    }

    public int getScore() {
        return score;
    }
    
    public String getName() {
		return name;
	}

    @Override
    public int compareTo(Student other) {
        return Integer.compare(this.score, other.getScore());
    }
    
    @Override
    public String toString() {
        return "Student{name='" + name + '\'' +
                ", I.D='" + id + '\'' +
                ", score=" + score +
                '}';
    }
}
