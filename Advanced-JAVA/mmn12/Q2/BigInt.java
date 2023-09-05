import java.util.ArrayList;
import java.util.Collections;

/**
 * BigInt class to handle unlimited integer arithmetic operations.
 */
public class BigInt implements Comparable<BigInt> {
    private ArrayList<Integer> digits;
    private boolean isNegative;

    /**
     * Constructs a BigInt object from a string representation of an integer.
     *
     * @param number The string representation of the integer.
     * @throws IllegalArgumentException if the input string is not a valid integer.
     */
    public BigInt(String number) {
        if (number.isEmpty()) {
            throw new IllegalArgumentException("Input string can`t be empty");
        }

        digits = new ArrayList<>();
        isNegative = (number.charAt(0) == '-');
        for (int i = isNegative ? 1 : 0; i < number.length(); i++) {
            char c = number.charAt(i);
            if (!Character.isDigit(c)) {
                throw new IllegalArgumentException("Input string must represent a valid integer");
            }
            digits.add(Character.getNumericValue(c));
        }
    }

    /*
     * Adds two BigInt numbers and returns the result.
     */
    public BigInt plus(BigInt other) {
        if (isNegative != other.isNegative) {
            BigInt positive = isNegative ? other : this;
            BigInt negative = isNegative ? this : other;
            negative.isNegative = false;
            BigInt result = positive.minus(negative);
            negative.isNegative = true;
            return result;
        }
        return sumWithSameSign(other);
    }

    /*
     * Subtracts two BigInt numbers and returns the result.
     */
    public BigInt minus(BigInt other) {
        if (isNegative != other.isNegative) {
            other.isNegative = !other.isNegative;
            BigInt result = plus(other);
            other.isNegative = !other.isNegative;
            return result;
        }
        return differenceWithSameSign(other);
    }

    /*
     * Multiplies two BigInt numbers and returns the result.
     */
    public BigInt multiply(BigInt other) {
        BigInt result = new BigInt("0");
        for (int i = 0; i < digits.size(); i++) {
            BigInt product = multiplyByDigit(digits.get(digits.size() - 1 - i), other);
            for (int j = 0; j < i; j++) {
                product.digits.add(0);
            }
            result = result.plus(product);
        }
        result.isNegative = isNegative != other.isNegative;
        return result;
    }

    /*
     * Divides two BigInt numbers and returns the quotient.
     * @throws ArithmeticException if division by zero is attempted.
     */
    public BigInt divide(BigInt other) {
        if (other.isZero()) {
            throw new ArithmeticException("Division by zero");
        }

        BigInt result = new BigInt("0");
        BigInt dividend = new BigInt("0");
        dividend.digits = new ArrayList<>(digits);
        dividend.isNegative = false;
        other.isNegative = false;

        while (compareAbs(dividend, other) >= 0) {
            dividend = dividend.minus(other);
            result = result.plus(new BigInt("1"));
        }
        result.isNegative = isNegative != other.isNegative;
        return result;
    }
    /*
     * Calculates the sum of two BigInt objects with the same sign.
     */
    private BigInt sumWithSameSign(BigInt other) {
        ArrayList<Integer> resultDigits = new ArrayList<>();
        int carry = 0;
        for (int i = 0; i < Math.max(digits.size(), other.digits.size()); i++) {
            int thisDigit = i < digits.size() ? digits.get(digits.size() - 1 - i) : 0;
            int otherDigit = i < other.digits.size() ? other.digits.get(other.digits.size() - 1 - i) : 0;
            int sum = thisDigit + otherDigit + carry;
            carry = sum / 10;
            resultDigits.add(sum % 10);
        }
        if (carry > 0) {
            resultDigits.add(carry);
        }
        Collections.reverse(resultDigits);
        BigInt result = new BigInt("0");
        result.digits = resultDigits;
        result.isNegative = isNegative;
        return result;
    }

    /*
     * Computes the difference between two BigInt objects with the same sign.
     */
    private BigInt differenceWithSameSign(BigInt other) {
        int cmp = compareAbs(this, other);
        if (cmp == 0) {
            return new BigInt("0");
        }

        BigInt greater = cmp > 0 ? this : other;
        BigInt smaller = cmp > 0 ? other : this;
        ArrayList<Integer> resultDigits = new ArrayList<>();
        int borrow = 0;
        for (int i = 0; i < greater.digits.size(); i++) {
            int greaterDigit = greater.digits.get(greater.digits.size() - 1 - i);
            int smallerDigit = i < smaller.digits.size() ? smaller.digits.get(smaller.digits.size() - 1 - i) : 0;
            int diff = greaterDigit - smallerDigit - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            resultDigits.add(diff);
        }
        Collections.reverse(resultDigits);
        while (resultDigits.get(0) == 0) {
            resultDigits.remove(0);
        }
        BigInt result = new BigInt("0");
        result.digits = resultDigits;
        result.isNegative = (cmp < 0) == isNegative;
        return result;
    }

    /*
     * Multiplies a BigInt object by a single digit.
     */
    private BigInt multiplyByDigit(int digit, BigInt other) {
        ArrayList<Integer> resultDigits = new ArrayList<>();
        int carry = 0;
        for (int i = 0; i < other.digits.size(); i++) {
            int product = digit * other.digits.get(other.digits.size() - 1 - i) + carry;
            carry = product / 10;
            resultDigits.add(product % 10);
        }
        if (carry > 0) {
            resultDigits.add(carry);
        }
        Collections.reverse(resultDigits);
        BigInt result = new BigInt("0");
        result.digits = resultDigits;
        return result;
    }

    /*
     * Checks if the BigInt object represents zero.
     */
    private boolean isZero() {
        return digits.size() == 1 && digits.get(0) == 0;
    }

    /*
     * Returns a string representation of the BigInt object.
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        if (isNegative) {
            sb.append('-');
        }
        for (int digit : digits) {
            sb.append(digit);
        }
        return sb.toString();
    }

    /*
     * Compares two BigInt objects for equality.
     */
    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }  if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        BigInt other = (BigInt) obj;
        return isNegative == other.isNegative && digits.equals(other.digits);
    }

    /*
     * Compares two BigInt objects to determine their order.
     */
    @Override
    public int compareTo(BigInt other) {
        if (isNegative != other.isNegative) {
            return isNegative ? -1 : 1;
        }
        return isNegative ? -compareAbs(this, other) : compareAbs(this, other);
    }

    /*
     * Compares the absolute values of two BigInt objects.
     */
    private static int compareAbs(BigInt a, BigInt b) {
        if (a.digits.size() != b.digits.size()) {
            return a.digits.size() - b.digits.size();
        }
        for (int i = 0; i < a.digits.size(); i++) {
            if (a.digits.get(i) != b.digits.get(i)) {
                return a.digits.get(i) - b.digits.get(i);
            }
        }
        return 0;
    }
}