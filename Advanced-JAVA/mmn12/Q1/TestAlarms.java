package maman12;

import java.util.ArrayList;

public class TestAlarms {
    public static void process(ArrayList<Alarm> alarms) {
        int smokeCount = 0;
        for (Alarm alarm : alarms) {
            if (alarm instanceof Smoke) {
                smokeCount++;
            }

            if (alarm instanceof Elevator) {
                ((Elevator) alarm).reset();
            }

            alarm.action();
        }

        System.out.println("Number of smoke alarms: " + smokeCount);
    }

    public static void main(String[] args) throws BadAlarmException {
        ArrayList<Alarm> alarms = new ArrayList<Alarm>();
        alarms.add(new Smoke("12 Main Street", "John"));
        alarms.add(new Fire("24 Elm Street", "Jane"));
        alarms.add(new Elevator("8 Pine Street", 2));

        process(alarms);
    }
}