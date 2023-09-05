import java.io.Serializable;
import java.util.Objects;

public class Date implements Serializable {
    private int day;
    private int month;
    private int year;

    
    public Date(int day, int month, int year) {
        this.day = day;
        this.month = month;
        this.year = year;
    }

    // Override equals
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Date date = (Date) o;
        return day == date.day && month == date.month && year == date.year;
    }

    // Override hashCode
    @Override
    public int hashCode() {
        return Objects.hash(day, month, year);
    }
}
