package maman12;

import java.io.Serializable;
import java.time.LocalDateTime;

public abstract class Alarm implements Serializable {
    private static final long serialVersionUID = 1L;

    private String address;
    private String operatorName;
    private LocalDateTime startTime;
    private boolean active;

    public Alarm(String address, String operatorName) throws BadAlarmException {
        if (address == null || address.isEmpty()) {
            throw new BadAlarmException("Address cannot be empty.");
        }
        this.address = address;
        this.operatorName = operatorName;
        this.startTime = LocalDateTime.now();
        this.active = true;
    }

    public String getAddress() {
        return this.address;
    }

    public String getOperatorName() {
        return this.operatorName;
    }

    public LocalDateTime getStartTime() {
        return this.startTime;
    }

    public boolean isActive() {
        return this.active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }

    public abstract void action();
}