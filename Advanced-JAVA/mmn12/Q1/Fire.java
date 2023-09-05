package maman12;

import java.io.Serializable;

public class Fire extends Smoke implements Serializable {
    private static final long serialVersionUID = 1L;

    public Fire(String address, String operatorName) throws BadAlarmException {
        super(address, operatorName);
    }

    @Override
    public void action() {
        setActive(false);
        System.out.println("Fire alarm at " + getAddress() + ", started at " + getAlertTime() + ", operator: " + getOperatorName());
    }
}