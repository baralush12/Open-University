package maman12;

public class BadAlarmException extends Exception {
    private static final long serialVersionUID = 1L;

    public BadAlarmException(String message) {
        super(message);
    }
}
