import { FormControl, ValidationErrors } from '@angular/forms';

/**
 * Custom form validators.
 */
export class ValidatorsForm {
  /**
   * Validates that the control's value is not only whitespace.
   * @param control - The form control to validate.
   * @returns A ValidationErrors object if the validation fails, or null if the validation passes.
   */
  static notOnlyWhitespace(control: FormControl): ValidationErrors {
    // Check if the control value is not null and only contains whitespace
    if (control.value != null && control.value.trim().length === 0) {
      // Invalid: return an error object indicating the validation failure
      return { notOnlyWhitespace: true };
    } else {
      // Valid: return null indicating the validation passed
      return null;
    }
  }
}
