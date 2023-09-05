package maman12;

import java.io.Serializable;
import java.time.LocalDateTime;

public class Smoke extends Alarm implements Serializable {
    private static final long serialVersionUID = 1L;

    private LocalDateTime alertTime;

    public Smoke(String address, String operatorName) throws BadAlarmException {
        super(address, operatorName);
        this.alertTime = LocalDateTime.now();
    }

    public LocalDateTime getAlertTime() {
        return this.alertTime;
    }

    public void action() {
        setActive(false);
        System.out.println("Smoke alarm at " + getAddress() + ", started at " + getAlertTime() + ", operator: " + getOperatorName());
    }
}