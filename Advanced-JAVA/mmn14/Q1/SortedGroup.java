/**
 * A generic class for an ordered collection of Comparable elements.
 */

import java.util.ArrayList;
import java.util.Iterator;

public class SortedGroup<T extends Comparable<T>> {
	
    private ArrayList<T> list;

    public SortedGroup() {
        this.list = new ArrayList<T>();
    }

    /**
     * Adds the specified item in its correct position in the sorted group. 
     */
    public void add(T item) {
        if (this.list.isEmpty()) {
            this.list.add(item);
        } else {
            int i = 0;
            while (i < this.list.size() && item.compareTo(this.list.get(i)) > 0) {
                i++;
            }
            this.list.add(i, item);
        }
    }

    /**
     * Removes all instances of the specified item from the group.
     * Returns the count of items removed.
     */
    public int remove(T item) {
        int count = 0;
        while (this.list.remove(item)) {
            count++;
        }
        return count;
    }

    /**
     * Returns an Iterator over the elements in this group in proper sequence.
     */
    public Iterator<T> iterator() {
        return this.list.iterator();
    }
}
