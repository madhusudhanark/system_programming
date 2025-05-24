import ctypes
from ctypes import CDLL

def test_multiply():
    my_lib = CDLL('./My_header.so')
    # Define test cases as tuples: (input_a, input_b, expected_result)
    test_cases = [
        (3, 4, 12),           # Regular positive numbers
        (0, 5, 0),            # Zero multiplication
        (-3, 4, -12),         # One negative number
        (-3, -4, 12),         # Two negative numbers
        (2**30, 2, 2**31),    # Very large numbers
        (2**30, 0, 0),        # Zero multiplication with a large number
    ]

    # Loop through the test cases
    for a, b, expected in test_cases:
        result = my_lib.multiply(a, b)
        assert result == expected, f"Expected {expected} for multiply({a}, {b}), but got {result}"
        print(f"multiply({a}, {b}) passed: {result}")

# Run the test
if __name__ == "__main__":
    test_multiply()

