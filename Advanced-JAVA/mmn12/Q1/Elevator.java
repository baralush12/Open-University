package maman12;

public class Elevator extends Alarm {
    private static final long serialVersionUID = 1L;
    
    private int floor;

    public Elevator(String address, int floor) throws BadAlarmException {
        super(address, null);
        this.floor = floor;
    }

    public void action() {
        System.out.printf("Elevator alarm at %s started at %s on floor %d\n",
            this.getAddress(), this.getStartTime().toString(), this.floor);
    }

    public void reset() {
        this.floor = 0;
    }
}