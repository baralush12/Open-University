/**
 * Provides a static method to produce a reduced SortedGroup.
 */

import java.util.Iterator;

public class SortedGroupRed {
    public static <T extends Comparable<T>> SortedGroup<T> reduce(SortedGroup<T> sGroup, T x) {
        SortedGroup<T> newGroup = new SortedGroup<>();
        Iterator<T> iterator = sGroup.iterator();
        while (iterator.hasNext()) {
            T item = iterator.next();
            if (item.compareTo(x) > 0) {
                newGroup.add(item);
            }
        }
        return newGroup;
    }
}
